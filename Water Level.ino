#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL36bdL6p0S"
#define BLYNK_TEMPLATE_NAME "Water Level Monitoring System"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "dXbOlE1dkX0ayPTCNnI4KsKeMsP5n3gc";
char ssid[] = "Redmi 9";
char pass[] = "ZuveRiya";

BlynkTimer timer;
bool pinValue = 0;

#define trig D3
#define echo D4
#define relay D8

void setup() {
  Serial.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(relay, OUTPUT);
  WiFi.begin(ssid, pass);
  Blynk.config(auth);
  timer.setInterval(10L, Wlevel);
  digitalWrite(relay, HIGH);
}

BLYNK_WRITE(V0) {
  pinValue = param.asInt();
}

void loop() {
  Blynk.run();
  timer.run();
  // ESP.reset();
}

void Wlevel() {
  if (pinValue == 1) {
    digitalWrite(relay, LOW);
  } else if (pinValue == 0) {
    digitalWrite(relay, HIGH);
  }

  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;

  Blynk.virtualWrite(V1, cm);
  Serial.println(cm);
}
