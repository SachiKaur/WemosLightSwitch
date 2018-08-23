#include <Servo.h>
#include "ESP8266WiFi.h"
#include <aREST.h>

const char* ssid = WIFI_NAME;
const char* password = WIFI_PASSWORD;

aREST rest = aREST();

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

  rest.function("light", turn_light);
  rest.set_id("1");
  rest.set_name("MiniWemosLights");
  
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");


  server.begin();
  Serial.println("Server started");

  Serial.println(WiFi.localIP());
}

void loop() {
  /*light_on();
  delay(5000);
  light_off();
  delay(5000);*/

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}

