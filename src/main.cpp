#include <Arduino.h>
#include <map>
#include <vector>
#include "BluetoothSerial.h"
using namespace std;

// wires are connected like this:
//    D23 (1)   D19 (4)
//    D22 (2)   D18 (5)
//    D21 (3)   D17 (6)

// declarations here: 
int8_t pin[7] = {0, 23, 22, 21, 19, 18, 17};
uint32_t mask = 0;
int8_t size = 0;
int8_t pin_number = 0;
char num = 0;
char prev_char = 0;

BluetoothSerial SerialBT;

std::map<char, vector<int8_t> > mapping = {
	// latin alphabet letters
    {'a', {1}},        // ⠁
    {'b', {1,2}},      // ⠃
    {'c', {1,4}},      // ⠉
    {'d', {1,4,5}},    // ⠙
    {'e', {1,5}},      // ⠑
    {'f', {1,2,4}},    // ⠋
    {'g', {1,2,4,5}},  // ⠛
    {'h', {1,2,5}},    // ⠓
    {'i', {2,4}},      // ⠊
    {'j', {2,4,5}},    // ⠚
    {'k', {1,3}},      // ⠅
    {'l', {1,2,3}},    // ⠇
    {'m', {1,3,4}},    // ⠍
    {'n', {1,3,4,5}},  // ⠝
    {'o', {1,3,5}},    // ⠕
    {'p', {1,2,3,4}},  // ⠏
    {'q', {1,2,3,4,5}},// ⠟
    {'r', {1,2,3,5}},  // ⠗
    {'s', {2,3,4}},    // ⠎
    {'t', {2,3,4,5}},  // ⠞
    {'u', {1,3,6}},    // ⠥
    {'v', {1,2,3,6}},  // ⠧
    {'w', {2,4,5,6}},  // ⠺
    {'x', {1,3,4,6}},  // ⠭
    {'y', {1,3,4,5,6}},// ⠽
    {'z', {1,3,5,6}},   // ⠵

	// special signs
	{'~', {3,4,5,6}}, // before every continuos number sequence
	{'#', {4,6}}, // before every capital letter
	{' ', {}}, // for space

	// interpuction symbols
	{'"', {3,5,6}},
	{'.', {2,5,6}},
	{',', {2}},
	{';', {2,3}},
	{'-', {3, 4}},
	{'(', {2,3,5,6}},
	{')', {2,3,5,6}},
	{'!', {2,3,5}},
	{'?', {2,6}},
};

// function declarations:
void charToBraille(char l);

// here is another function for applying charToBraille() for
// all letters from some long text
// void textToBraille(String &t);


// this will run only once:
void setup() {
	// here I activate my LED pins for output to give voltage to leds
	gpio_set_direction(GPIO_NUM_23, GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_NUM_22, GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_NUM_21, GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_NUM_19, GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_NUM_18, GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_NUM_17, GPIO_MODE_OUTPUT);

	// Serial.begin(9600); // this is optimal baud-rate - I TESTED IT MYSELF
	// for some reason it wont print anything here, even after some pause
	// it goes straight to loop()
	Serial.begin(9600);
	SerialBT.begin("TextToBraille");
}


// this code will be looped:
void loop() {
	if (SerialBT.available()){
		char letter = SerialBT.read();
		Serial.println(letter);
		charToBraille(letter);
		prev_char = letter;
	}
}


// function definitions:
bool is_capital(char c){
	return c >= 'A' && c <= 'Z';
}

bool is_number(char c){
	return c >= '0' && c <= '9';
}

uint32_t gen_char_mask(char l){
	mask = 0;
	size = mapping[l].size();
	for(int j = 0; j < size; j++){
		pin_number = mapping[l][j];
		mask |= (1UL << pin[pin_number]);
	}
	return mask;
}

void display_letter_by_mask(uint32_t m){
	GPIO.out_w1ts = m;
	delay(500);
	GPIO.out_w1tc = m;
	delay(200);
}

void charToBraille(char l){
	if(is_capital(l)){
		display_letter_by_mask(gen_char_mask('#'));
		display_letter_by_mask(gen_char_mask(tolower(l)));
	}
	else if(is_number(l)){
		if(!is_number(prev_char))
			display_letter_by_mask(gen_char_mask('~'));
		num = 'j'; // j = 0
		if(l > '0') // 1 = a, 2 = b ... 9 = k
			num = l+48; 
		display_letter_by_mask(gen_char_mask(num));
	}
	else
		display_letter_by_mask(gen_char_mask(l));
}

// void textToBraille(string &t){
// 	for(int i = 0; i < t.size(); i++){
// 		charToBraille(t[i]);
// 	}
// }