// For I2C
#include <Wire.h>
#include <Servo.h>
// Libraries for Matrix
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_GFX.h>

#define btnPin 1

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
Servo myservo;

// Variables not changing
const int servoInterval = 500;
const int led_A_Interval = 500;  // number of millisecs between refreshing
const int btnInterval = 100;
const int numberOfData = 3;

// Variables will be changed
int lastButtonState = 1;
int buttonState;
int letRotate = 1;
int rotateDegree = 0;
int unitRotation = 0;
unsigned long previousservoInterval = 0;  // will store last time the LED was updated
unsigned long previousLed_A_Millis = 0;

unsigned long previousBtnDebounceTime = 0;

int x = 7;

void setup() {
  myservo.attach(13);
  // pinMode(btnPin, INPUT);
  pinMode(btnPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(btnPin), readRotateBtnState, RISING);
  myservo.write(0);
  Serial.begin(9600);
  // Good idea to send data to both
  // device and serial as it helps with
  // troubleshooting.
  Serial.println("8x8 LED Matrix Test");
  // set the address
  matrix.begin(0x70);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextSize(1);
  matrix.setTextColor(LED_GREEN);
  unitRotation = 180/numberOfData;
}

void loop() {
  // currentMillis = millis();   // capture the latest value of millis()
  //   this is equivalent to noting the time from a clock
  if (x >= -37) {
    //ledboard();
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Hello");
    matrix.writeDisplay();
    x--;
  } else {
    x = 7;
  }


  // bool buttonState = digitalRead(btnPin);
  // readRotateBtnState();
  // Serial.println(buttonState);

  // if (buttonState == 0) {
  //   myservo.write(180);
  // } else {
  //   myservo.write(0);
  // }
  delay(150);
}

void readRotateBtnState() {
  if (millis() - previousBtnDebounceTime >= btnInterval) {
    if (digitalRead(btnPin) == HIGH) {
      Serial.println("I am working!");
      rotateServo();
      previousBtnDebounceTime += btnInterval;
    }
  }
}

void rotateServo(){
  int nextRotateDegree = unitRotation + rotateDegree;
  Serial.println("unit:" + String(unitRotation) + "rotate:" + String(rotateDegree));
  if(nextRotateDegree > 180 || nextRotateDegree < 0){
    Serial.println("I am adding!");
    unitRotation = -unitRotation;
    nextRotateDegree = unitRotation + rotateDegree;
  }
  myservo.write(nextRotateDegree);
  
  ledboard();
  rotateDegree = nextRotateDegree;

}

void ledboard() {
  if (nextRotateDegree = 60){
    if (x >= -37) {
    //ledboard();
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Temperature");
    matrix.writeDisplay();
    x--;
  } else {
    x = 7;
  };};
    if (nextRotateDegree = 120){
    if (x >= -37) {
    //ledboard();
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Humidity");
    matrix.writeDisplay();
    x--;
  } else {
    x = 7;
  };};
  // matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  // matrix.setTextSize(1);
  // matrix.setTextColor(LED_GREEN);


  // for (int8_t x = 7; x >= -36; x--) {

  //   // if (millis() - previousLed_A_Millis > led_A_Interval) {
  //   matrix.clear();
  //   matrix.setCursor(x, 0);
  //   matrix.print("Hello");
  //   matrix.writeDisplay();
  //   delay(150);

  //   // NOTE: The previous line could alternatively be
  //   //              previousOnBoardLedMillis = currentMillis
  //   //        which is the style used in the BlinkWithoutDelay example sketch
  //   //        Adding on the interval is a better way to ensure that succesive periods are identical
  //   //           previousLed_A_Millis = (millis());
  //   //  }
  // }

  // matrix.setRotation(3);
  // matrix.setTextColor(LED_RED);
}