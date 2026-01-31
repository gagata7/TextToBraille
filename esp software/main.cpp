#include <Arduino.h>
#include <map>
#include <vector>
#include "BluetoothSerial.h"
#include <ESP32Servo.h>
using namespace std;

#define UP_POSITION 170
#define DOWN_POSITION 150
#define SLOW_DOWN 10


// declarations here: 
uint32_t mask = 0;
int8_t size = 0;
int8_t pin_number = 0;
char num = 0;
char prev_char = 0;

BluetoothSerial SerialBT;

Servo a,b,c,d,e,f;

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
	{'~', {3,4,5,6}}, // before every continuos number sequence ~a = 1, ~b = 2 ...
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
void pin_up(int id);
void pin_down(int id);
void display_reset();


// this will run only once:
void setup() {
	Serial.begin(9600);
	SerialBT.begin("TextToBraille"); // so ESP will be seen as "TextToBraille" device

	// this is exactly how my servos are connected to GPIO pins
	// numbers refer to servos just like in photos/servos_mechanism.jpg
	a.attach(25); // 1
	delay(SLOW_DOWN);
	b.attach(33); // 2
	delay(SLOW_DOWN);
	c.attach(32); // 3
	delay(SLOW_DOWN);
	d.attach(14); // 4
	delay(SLOW_DOWN);
	e.attach(13); // 5
	delay(SLOW_DOWN);
	f.attach(27); // 6
	delay(SLOW_DOWN);

	// reset all pins before displaying
	display_reset();
}


int i = 0;
void loop() {
	if (!SerialBT.hasClient())
		display_reset();

	if (SerialBT.hasClient() and SerialBT.available()){
		char letter = SerialBT.read();
		Serial.println(letter);
		charToBraille(tolower(letter));
		prev_char = letter;
		delay(300);
	}
}


// function definitions:
bool is_capital(char c){
	return c >= 'A' && c <= 'Z';
}

bool is_number(char c){
	return c >= '0' && c <= '9';
}

void pin_up(int id){
	switch(id){
		case 1:
			a.write(UP_POSITION);
			break;
		case 2:
			b.write(UP_POSITION);
			break;
		case 3:
			c.write(UP_POSITION);
			break;
		case 4:
			d.write(UP_POSITION);
			break;
		case 5:
			e.write(UP_POSITION);
			break;
		case 6:
			f.write(UP_POSITION);
			break;
	}
	delay(SLOW_DOWN);
}

void pin_down(int id){
	switch(id){
		case 1:
			a.write(DOWN_POSITION);
			break;
		case 2:
			b.write(DOWN_POSITION);
			break;
		case 3:
			c.write(DOWN_POSITION);
			break;
		case 4:
			d.write(DOWN_POSITION);
			break;
		case 5:
			e.write(DOWN_POSITION);
			break;
		case 6:
			f.write(DOWN_POSITION);
			break;
	}
	delay(SLOW_DOWN);
}


void display_letter(char l){
	for(auto pin : mapping[l]){
		pin_up(pin);
	}
	delay(1000);
	for(auto pin : mapping[l]){
		pin_down(pin);
	}
	delay(1000);
}

void charToBraille(char l){
	if(is_capital(l)){
		display_letter('#');
		display_letter(tolower(l));
	}
	else if(is_number(l)){
		if(!is_number(prev_char))
			display_letter('~');
		num = 'j'; // j = 0
		if(l > '0') // 1 = a, 2 = b ... 9 = k
			num = l+48; 
		display_letter(num);
	}
	else
		display_letter(l);
}

void display_reset(){
	for(int i = 1; i <= 6; i++)
		pin_down(i);
	while(SerialBT.available())
		SerialBT.read();
}
