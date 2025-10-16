#include <Arduino.h>

// declarations here:
int num = 0;

void setup() { // this will run once
  Serial.begin(9600); // this is optimal baud-rate - I TESTED IT MYSELF
  // for some reason it wont print anything here, even after some pause
  // it goes straight to loop()
}

void loop() {
  if(Serial.available() > 0){
    num = Serial.parseInt();
    Serial.println("twice your number: ");
    Serial.println(num*2);
  }
}

// function definitions here: