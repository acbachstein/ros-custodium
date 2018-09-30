#include <dummy.h>
#include <ESP8266WiFi.h>
int reading;
char buf;
const char* host="192.168.1.100";
WiFiServer wifiserver(8080);
 WiFiClient cli;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(50);
  pinMode(D2, OUTPUT);
  Serial.println("Started");
  digitalWrite(D2, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.begin("linksys", "mysecretkey");
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("");
  Serial.print("Connected: IP ");
  Serial.println(WiFi.localIP());
  wifiserver.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
     cli = wifiserver.available();
      if(cli && cli.connected()){
        Serial.println("Powering sensor");
        digitalWrite(D2, HIGH);
        delay(500);
        Serial.println("reading");
        reading = analogRead(A0);
        Serial.println(analogRead(A0));
        delay(3);
        Serial.println("De-powering sensor");
        digitalWrite(D2, LOW);
        Serial.print("Reading: ");
        Serial.println(reading);
        Serial.println(WiFi.localIP());
        cli.write(reading);
        delay(30);
        cli.stop();
      
    }
}
 
