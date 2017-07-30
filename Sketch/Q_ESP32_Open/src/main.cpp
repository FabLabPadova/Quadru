#include <Arduino.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#define N_LEG 4
#define N_PART 3
#define CLIENT_TIMEOUT 5000

IPAddress ip(192, 168, 1, 247);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
const char* ssid     = "MonkeyPlanet";
const char* password = "paperagiallachenuota1999";

WiFiServer server(80, 1);
WiFiClient client;

unsigned long timerExecution;

void convertAndSend(String &jsonReq);

void connectClient(){
    WiFi.config(ip, gateway, subnet);
    WiFi.setAutoConnect(true);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {

        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

}

void setup(){
  Serial.begin(115200);
  connectClient();
  //Set slave number
  server.begin();
  Serial.println("Partito...!");
  Wire.begin();
}//setup

void loop() {
  if (client = server.available()) {

      Serial.println("_CONN");
      String currentLine = "";
      int timeout = millis();
      bool toKill = false;
      while (client.connected()) {
        if (toKill = (millis() - timeout > CLIENT_TIMEOUT)){
          client.stop();
          Serial.println("_DISCONN");
          break;
        }
        if (client.available()) {
          char c = client.read();
          if (c == '$') {
            currentLine.trim();
            if (currentLine != ""){
              convertAndSend(currentLine);
              currentLine = "";
              timeout = millis();
            }
          } else {
            currentLine += c;
          }

        }//while
      }
    }
}//loop

void convertAndSend(String& jsonReq){
  char json[jsonReq.length()+1];
  jsonReq.toCharArray(json, jsonReq.length()+1);
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  if (!root.success()){
    Serial.println("Json non valido.");
  } else {
    for(int i=0; i<root["nl"]; i++){
      Wire.beginTransmission((int)root["legs"][i]["index"]);
      for (int j=0; j<root["legs"][i]["np"]; j++){
        int value = (int)(root["legs"][i]["parts"][j]["value"]);
        Wire.write(value >> 8);
        Wire.write(value & 255);
      }
      Wire.endTransmission();
    }
  }
}
