#include <Arduino.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#define N_LEG 4
#define N_PART 3
#define CLIENT_TIMEOUT 5000

IPAddress ip(192, 168, 1, 233);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
const char* ssid     = "MonkeyPlanet";
const char* password = "paperagiallachenuota1999";
unsigned long timer = 0;

WiFiServer server(80, 1);
WiFiClient client;

void convertAndSend(String &jsonReq);

void setup(){
  Serial.begin(115200);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  Wire.begin();
  //Set slave number
  server.begin();
  Serial.println("Partito...!");
}//setup

void loop() {
  if (client = server.available()) {
      Serial.println("_CONN");
      String currentLine = "";
      int timeout = millis();
      bool toKill = false;
      while (client.connected()) {
        if (toKill = (millis() - timeout > CLIENT_TIMEOUT && currentLine == "")){
          break;
        }
        if (client.available()) {
        timer = millis();
          char c = client.read();
          if (c == '$') {
            currentLine.trim();
            if (currentLine != ""){
              convertAndSend(currentLine);
            }
            currentLine = "";
            timeout = millis();

          } else if (c != '\r') {
            currentLine += c;
          }
        }//while
      }
      if (toKill){
        client.stop();
      }
    }
}//loop

void convertAndSend(String& jsonReq){
  char json[jsonReq.length()+1];
  jsonReq.toCharArray(json, jsonReq.length()+1);
  StaticJsonBuffer<2048> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  if (!root.success()){
    Serial.println("Json non valido.");
  } else {
    for (int i=0; i<N_LEG; i++){
      Wire.beginTransmission(i);

      for (int j=0; j<N_PART; j++){
        int motor_send = root["GhostSingleLeg"][i]["GhostSinglePart"][j]["Value"];
        Wire.write(motor_send >> 8);
        Wire.write(motor_send & 255);
      }
    }
  }

}
