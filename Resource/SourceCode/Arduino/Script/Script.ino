// For I2C
#include <Wire.h>
#include <Servo.h>
// Libraries for Matrix
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_GFX.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <SPI.h>

#include <ArduinoJson.h>
// Wifi and MQTT
#include "arduino_secrets.h"

//LED Strip
#include "FastLED.h"
#define NUM_LEDS 36
#define DATA_PIN 5
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
uint8_t max_bright = 1;
CRGB leds[NUM_LEDS];

#include "ServoEasing.hpp"
/*
**** please enter your sensitive data in the Secret tab/arduino_secrets.h
**** using format below

#define SECRET_SSID "ssid name"
#define SECRET_PASS "ssid password"
#define SECRET_MQTTUSER "user name - eg student"
#define SECRET_MQTTPASS "password";
 */

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;
const char mqtt_server[] = "mqtt.cetools.org";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

#define btnPin 1
#define servoPin 13

ServoEasing myservo;  // create an instance of the servo class

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();  // create an instance of the LED class

// Variables not changing

const int ledInterval = 27;  // number of millisecs between refreshing
const int iniInterval = 90;  // number of millisecs between refreshing
const int btnInterval = 300;
const int numberOfData = 4;
const String dataArray[numberOfData] = {  "Temperature","Noise", "pm1","RoomCapacity" };
const int maxArray[numberOfData] = {  35,140, 250, 30 };
const int minArray[numberOfData] = {  15, 30,0, 0 };
const int ledArray[numberOfData] = {  -80, -60, -28, -100 };
const int initServoLocation = 0;


// Variables will be changed
int stateIndexInterval = 1;
int nextRotateDegree = 0;
// int lastButtonState = 1;
// int buttonState;
int letRotate = 1;
int rotateDegree = 0;
int unitRotation = 0;
int stateIndex = 0;
//mqtt data
int Temperature = 25;
int RoomCapacity=15;
int pm1 = 1;
int Noise = 10;
int mapped = 1;
unsigned long previousLed_Interval = 0;
unsigned long previousiniLed_Interval = 0;
unsigned long previousBtnDebounceTime = 0;

bool ledReady = false;
bool stripReady = false;
bool mqttdisconnected = false;
int x = 7;



void setup() {
  startWifi();
  //LED Display
  matrix.begin(0x70);         // set the address
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextSize(1);
  matrix.setTextColor(LED_GREEN);

  //LED strip
  LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(max_bright);



  // start MQTT server
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);

  Serial.begin(115200);  // open serial connection for debug info
  Serial.println("Power Connected.");

  // run initialisation functions
  //Servo
  myservo.attach(servoPin);
  myservo.write(initServoLocation);
  // myservo.setEasingType(EASE_SINE_IN_OUT);
    // myservo.startEaseTo(initServoLocation,20);
  unitRotation = 180 / numberOfData;
  //Button
  pinMode(btnPin, INPUT);
  // pinMode(btnPin, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(btnPin), readRotateBtnState, RISING);
}

void loop() {

  if (btnPin == HIGH){
    readRotateBtnState();
  }

  if (mqttdisconnected) {
    displayLEDINI();
    Serial.print("Connectionledini");
  }

  if (ledReady) {
    displayLED();
  } else {
    displayLEDPB();
  }

  if (stripReady) {
    LEDstrip();
  }

  // Connect MQTT
  if (!mqttClient.connected()) {
    Serial.print("Connection Failed.");
    reconnect();
  }

  mqttClient.loop();
}


void readRotateBtnState() {
  if ((millis() - previousBtnDebounceTime) > btnInterval) {
    ledReady = false;
    stripReady = false;
    x = 7;
    rotateServo();

    stateIndex = stateIndex + stateIndexInterval;
    if (stateIndex == numberOfData - 1 || stateIndex == 0) {
      stateIndexInterval = -stateIndexInterval;
    }
    Serial.println(stateIndex);
    ledReady = true;
    stripReady = true;
  }
  previousBtnDebounceTime = previousBtnDebounceTime + btnInterval;
}


void displayLED() {
  if (previousLed_Interval == ledInterval) {

    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print(dataArray[stateIndex]);

    if (strcmp(dataArray[stateIndex].c_str(), "Noise") == 0) {
      matrix.setCursor(x + 33, 0);
      matrix.print(Noise);
    } else if (strcmp(dataArray[stateIndex].c_str(), "Temperature") == 0) {
      matrix.setCursor(x + 70, 0);
      matrix.print(Temperature);
    } else if (strcmp(dataArray[stateIndex].c_str(), "pm1") == 0) {
      matrix.setCursor(x + 22, 0);
      matrix.print(pm1);
    
    } else if (strcmp(dataArray[stateIndex].c_str(), "RoomCapacity") == 0) {
      matrix.setCursor(x + 78, 0);
      matrix.print(RoomCapacity);
    }
    x--;
    if (x < ledArray[stateIndex]) {
      x = 7;
    };
    matrix.writeDisplay();
    previousLed_Interval = 0;
  }

  previousLed_Interval = previousLed_Interval + 1;
}

void displayLEDPB() {
  if (previousiniLed_Interval == iniInterval) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Press Button");
    x--;
    if (x < -80) {
      x = 7;
    }
    matrix.writeDisplay();
    previousiniLed_Interval = 0;
  }
  previousiniLed_Interval = previousiniLed_Interval + 1;
}

void displayLEDINI() {
  if (previousiniLed_Interval == iniInterval) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Connecting to WIFI and MQTT");
    x--;
    if (x < -170) {
      x = 7;
    }
    matrix.writeDisplay();
    previousiniLed_Interval = 0;
  }
  previousiniLed_Interval = previousiniLed_Interval + 1;
}

void rotateServo() {
  nextRotateDegree = (unitRotation * stateIndex) + initServoLocation;
  // myservo.startEaseTo(nextRotateDegree,20);
  myservo.write(nextRotateDegree);
}

void startWifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // check to see if connected and wait until you are
  while (WiFi.status() != WL_CONNECTED) {
    // delay(500);
    // Serial.print(".");
    displayLEDINI();
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, "UCL/OPS/107/SLS/WS1361_01/dB") == 0) {
    Serial.print("noise:");
    char str[length + 1];
    for (int i = 0; i < length; i++) {
      // Serial.print((char)payload[i]);
      str[i] = (char)payload[i];
    }
    str[length] = '\0';
    Noise = atoi(str);
    Serial.println(Noise);
    Serial.println("-----------------------");
  }
  if (strcmp(topic, "student/CASA0019/TwinLab/RoomCapacity") == 0) {
    Serial.print("RoomCapacity:");
    char str[length + 1];
    for (int i = 0; i < length; i++) {
      // Serial.print((char)payload[i]);
      str[i] = (char)payload[i];
    }
    str[length] = '\0';
    RoomCapacity = atoi(str);
    Serial.println(RoomCapacity);
    Serial.println("-----------------------");
  }
  if (strcmp(topic, "UCL/OPS/107/MTS/enviro") == 0) {
    Serial.print("environmental :");
    char str[length + 1];
    int i = 0;
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      str[i] = (char)payload[i];
    }
    str[i] = 0;  // Null termination
    Serial.println();
    //practise string
    //char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

    StaticJsonDocument<256> doc;
    deserializeJson(doc, payload);

    // deserializeJson(doc,str); can use string instead of payload
    Temperature = int(doc["temperature"]);

    pm1 = int(doc["pm1"]);

    Serial.println("temperature  =");
    Serial.println(Temperature);

    Serial.println("pm1  =");
    Serial.println(pm1);
    Serial.println();

    Serial.println("-----------------------");
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    displayLEDINI();
    mqttdisconnected = true;
    Serial.print("Attempting MQTT connection...");

    // Create a random client ID
    String clientId = "mlClient";
    clientId += String(random(0xffff), HEX);
    // mqttClient.connect(clientId.c_str(), mqttuser, mqttpass);
    mqttClient.connect(clientId.c_str());
    mqttClient.subscribe("UCL/OPS/107/SLS/WS1361_01/dB");
    mqttClient.subscribe("UCL/OPS/107/MTS/enviro");
    mqttClient.subscribe("student/CASA0019/TwinLab/RoomCapacity");
    mqttdisconnected = false;
  }
}

void LEDstrip() {
  FastLED.clearData();
  // Serial.print("Status in LEDstrip is :");
  // Serial.println(dataArray[stateIndex].c_str());
  if (strcmp(dataArray[stateIndex].c_str(), "Noise") == 0) {
    mapped = map(Noise, minArray[stateIndex], maxArray[stateIndex], 1, NUM_LEDS);
    // if (mapped > 85){
    // fill_solid(leds, 85, CRGB::Green);
    // fill_solid(leds+85, mapped-85, CRGB::OrangeRed);} else{
      fill_solid(leds, mapped, CRGB::Green);
    // }
    FastLED.show();
  }

  else if (strcmp(dataArray[stateIndex].c_str(), "Temperature") == 0) {
    if (Temperature < minArray[stateIndex] || Temperature > maxArray[stateIndex]) {
      mapped = NUM_LEDS;
    } else {
      mapped = map(Temperature, minArray[stateIndex], maxArray[stateIndex], 1, NUM_LEDS);
    }
    // if (mapped > 25){
    // fill_solid(leds, 25, CRGB::Blue);
    // fill_solid(leds+25, mapped-25, CRGB::OrangeRed);} else{
      fill_solid(leds, mapped, CRGB::Blue);
    // }
    FastLED.show();
  }

  else if (strcmp(dataArray[stateIndex].c_str(), "pm1") == 0) {
    mapped = map(pm1, minArray[stateIndex], maxArray[stateIndex], 1, NUM_LEDS);
    // if (mapped > 125){
    // fill_solid(leds, 125, CRGB::Green);
    // fill_solid(leds+125, mapped-125, CRGB::OrangeRed);} else{
      fill_solid(leds, mapped, CRGB::Green);
    // }
    FastLED.show();
  }
  else if (strcmp(dataArray[stateIndex].c_str(), "RoomCapacity") == 0) {
    mapped = map(RoomCapacity, minArray[stateIndex], maxArray[stateIndex], 1, NUM_LEDS);
    // if (mapped > 15){
    // fill_solid(leds, 15, CRGB::Green);
    // fill_solid(leds+15, mapped-15, CRGB::OrangeRed);} else{
      fill_solid(leds, mapped, CRGB::Green);
    // }
    FastLED.show();
  }
}