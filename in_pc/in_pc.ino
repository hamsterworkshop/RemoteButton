#include <ESP8266WiFi.h>
WiFiServer server(80);
IPAddress IP(192,168,10,1);
IPAddress mask = (255, 255, 255, 0);
byte ledPin = 2;
char comm_name[] = "IN_PC";
char password[] = "pa55w0rd";
void setup() {
 Serial.begin(9600);
 WiFi.mode(WIFI_AP);
 WiFi.softAP(comm_name, password);
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();
 pinMode(ledPin, OUTPUT);
 Serial.println();
 Serial.println("Server started.");
 Serial.print("IP: "); Serial.println(WiFi.softAPIP());
 Serial.print("MAC:"); Serial.println(WiFi.softAPmacAddress());
}
void loop() {
 Serial.println("start...");
 WiFiClient client = server.available();
 Serial.println("end...");
 if (!client) {
  digitalWrite(ledPin, HIGH);
  return;
 }else{
  digitalWrite(ledPin, LOW);
  String request = client.readStringUntil('\r');
  client.flush();  
 }
}
