#include <Arduino.h>

// declarations here:
#define LED1 23
#define LED2 19
#define LED3 22
#define LED4 18
#define LED5 21
#define LED6 17

void setup() { // this will run once
  // Serial.begin(9600); // this is optimal baud-rate - I TESTED IT MYSELF
  // for some reason it wont print anything here, even after some pause
  // it goes straight to loop()
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);

}

void loop() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED5, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED6, LOW);
  delay(1000);
}

// function definitions here: