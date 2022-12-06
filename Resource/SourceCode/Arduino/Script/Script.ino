// For I2C
#include <Wire.h>
#include <Servo.h>
// Libraries for Matrix
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_GFX.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <SPI.h>

// Wifi and MQTT
#include "arduino_secrets.h"
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

#define SERVO_PIN 2  // pin used to control the servo
Servo myservo;       // create an instance of the servo class

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();  // create an instance of the LED class

// Variables not changing
const int servoInterval = 500;
const int ledInterval = 50000;  // number of millisecs between refreshing
const int btnInterval = 100;
const int numberOfData = 3;
const String dataArray[numberOfData] = {"RoomCapacity", "Temperature", "Humidity"}; 
const int initServoLocation = 0;

// Variables will be changed
int stateIndexInterval = 1;
int nextRotateDegree = 0;
int lastButtonState = 1;
int buttonState;
int letRotate = 1;
int rotateDegree = 0;
int unitRotation = 0;
int stateIndex = 0;
unsigned long previousservoInterval = 0;  // will store last time the LED was updated
unsigned long previousLed_Interval = 0;
unsigned long previousBtnDebounceTime = 0;
bool ledReady = false;

int x = 7;

void setup() {

  Serial.begin(115200);  // open serial connection for debug info
  Serial.println("Power Connected.");

  // startWifi();

  // start MQTT server
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);

  // run initialisation functions
    //Servo
  myservo.attach(servoPin);
  myservo.write(initServoLocation);
  unitRotation = 180 / numberOfData;
    //Button
  pinMode(btnPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(btnPin), readRotateBtnState, RISING);
    //LED Display
  matrix.begin(0x70);         // set the address
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextSize(1);
  matrix.setTextColor(LED_GREEN);
}

void loop() {
  // Connect MQTT
  // if (!mqttClient.connected()) {
  //   Serial.print("Connection Failed.");
  //   reconnect();
  // }
  // mqttClient.loop();

  // LED Display
  if (ledReady){
    displayLED();
  }
}

void readRotateBtnState() {
  if ((millis() - previousBtnDebounceTime) > btnInterval) {
  ledReady = false;
  x = 7;
  rotateServo();
  // displayLED();
  stateIndex = stateIndex + stateIndexInterval;
  if (stateIndex == numberOfData - 1 || stateIndex == 0){
    stateIndexInterval = -stateIndexInterval;
  }
  Serial.println(stateIndex);
  ledReady = true;
  }
  previousBtnDebounceTime = previousBtnDebounceTime + btnInterval;
}

void displayLED(){
  if(previousLed_Interval == ledInterval){
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print(dataArray[stateIndex]);
    Serial.print("LED Info");
    // Serial.print(matrix.displaybuffer[8].size());
    // Serial.println(matrix.width());
    x--;
    if (x < -100){
      x = 7;
    }
    matrix.writeDisplay();
    previousLed_Interval = 0;
  }
  previousLed_Interval = previousLed_Interval + 1;
}

void rotateServo() {
  nextRotateDegree = (unitRotation * stateIndex) + initServoLocation;
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
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, "UCL/OPS/107/SLS/WS1361_01/dB") == 0) {
    Serial.print("noise:");
    char noise[length + 1];
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      noise[i] = (char)payload[i];
    }
    noise[length] = '\0';
    Serial.println();
    Serial.println("-----------------------");
  }
  if (strcmp(topic, "UCL/OPS/107/SLS/WS1361_01/speed") == 0) {
    Serial.print("PM 2.5:");
    char PM25[length + 1];
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      PM25[i] = (char)payload[i];
    }
    PM25[length] = '\0';
    Serial.println();
    Serial.println("-----------------------");
  }
}

void reconnect() {
  // Loop until we're reconnected
  if (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "mlClient";
    clientId += String(random(0xffff), HEX);
    // mqttClient.connect(clientId.c_str(), mqttuser, mqttpass);
    mqttClient.connect(clientId.c_str());
    // Temp
    // mqttClient.subscribe("UCL/OPS/107/SLS/WS1361_01/dB");
    // mqttClient.subscribe("UCL/OPS/107/SLS/WS1361_01/speed");
    // Temp
    // mqttClient.subscribe("UCL/OPS/107/SLS/WS1361_01/dB");
    // mqttClient.subscribe("UCL/OPS/107/SLS/WS1361_01/dB");
    // mqttClient.subscribe("UCL/OPS/107/SLS/WS1361_01/dB");
  }
}