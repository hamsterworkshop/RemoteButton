#include <ESP8266WiFi.h>
byte input_pin = 2;
char comm_name[] = "IN_PC";
char password[] = "pa55w0rd";
IPAddress server(192,168,10,1);         
WiFiClient client;
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(comm_name, password);      
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  pinMode(input_pin, INPUT_PULLUP);
}
void loop() {
  int input_val = digitalRead(input_pin);
  if (input_val == LOW){
    client.connect(server, 80);
    while (input_val == LOW){
      input_val = digitalRead(input_pin);
      client.print(' ');
    }
    client.print('\r');
    client.flush();
    client.stop();
  }
}
