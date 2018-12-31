#include <Arduino.h>
#include <TimerOne.h>
#include <TM1637Display.h>
#include <OneButton.h>
#include "Tachometer.h"

#define HALL_EFFECT 2
#define DISPLAY_CLK 3
#define DISPLAY_DAT 4
#define CALIBRATE_BTN 13


volatile unsigned int counter = 0;
volatile unsigned int average = 0;
unsigned long duration;
unsigned long rpm;
TM1637Display display(DISPLAY_CLK, DISPLAY_DAT);
Tachometer tach(HALL_EFFECT);
//OneButton calibrateBtn(CALIBRATE_BTN, true);


void calibratePressed() {
  Serial.print("Calibrating...");
  display.clear();
  bool result = tach.calibrate();
  if(result) {
    display.showNumberDec(8008);
    Serial.println("OK!");
    delay(3000);
  } else {
    display.showNumberDec(12345);
    Serial.println(":( failed!");
    delay(3000);
  }
}

void setup() {
  display.setBrightness(7);
  display.showNumberDec(counter, false); 


  Serial.begin(9600);

  pinMode(HALL_EFFECT, INPUT);
  pinMode(CALIBRATE_BTN, INPUT);
} 
bool busy = false;
void loop() {
  if(digitalRead(CALIBRATE_BTN) && !busy) {
    busy = true;
    calibratePressed();
    busy = false;
  }
  display.showNumberDec(tach.measure(1000000));
}