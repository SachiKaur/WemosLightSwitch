#include <Servo.h>
#include <ArduinoJson.h>
#include <FirebaseArduino.h>
#include "ESP8266WiFi.h"

#define durationSleep  600
#define NB_TRYWIFI     3
#define url ""
#define database ""
#define secret ""

const char* ssid = "";
const char* password = "";

WiFiServer server(80);

Servo myservo;  // create servo object to control a servo

int turn_light(String state){ // 30 0 16 Works
  if (state == "on"){
    Serial.println("---------------");
    Serial.println("LIGHT ON");
    Serial.println("Angle: 60");
    myservo.write(60);
    delay(250); //110
    Serial.println("Angle: 15");
    myservo.write(15);
    delay(250);
    Serial.println("Rest State: 45");
    myservo.write(45);
    delay(20);
  }
  else if (state == "off") {
    Serial.println("---------------");
    Serial.println("LIGHT OFF");
    Serial.println("Angle: 26");
    myservo.write(26);
    delay(125);
    Serial.println("Angle: 60");
    myservo.write(70);
    delay(125);
    Serial.println("Rest State: 45");
    myservo.write(45);
    delay(125); 
  }
}

void setup() {
  Serial.begin(115200);
  myservo.attach(2);
  myservo.write(45);
  delay(20); 
  
  WiFi.begin(ssid, password);
  
  int _try = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("..");
    delay(500);
    _try++;
    if ( _try >= NB_TRYWIFI ) {
        Serial.println("Impossible to connect WiFi network, go to deep sleep");
        ESP.deepSleep(durationSleep * 1000000);
    }
  }
  
  Serial.println("Connected to the WiFi network");
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  Firebase.begin(database, secret);
  FirebaseObject object = Firebase.get(url);
  JsonObject& obj = object.getJsonVariant();

  for (JsonObject::iterator it=obj.begin(); it!=obj.end(); ++it)
  { 
    turn_light(Firebase.getString(url + String(it->key) + "/state"));
  }

  Firebase.remove(url);
  
  ESP.deepSleep(durationSleep * 1000000);
}

void loop() {
}
