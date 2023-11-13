#define BLYNK_TEMPLATE_ID "TMPL3lwQEwl-u"
#define BLYNK_TEMPLATE_NAME "ins"

#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


const int led1=D1;
const int led2=D5;
const int triggerPin=D4;
const int echoPin=D3;
const int buzzerPin=D2;

long duration;
int distance;


char auth[] = "ibLlDbb0al-x_3UO594VYjzVn3Y_Y9QG";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "iQOO Neo7";
char pass[] = "your_wifi_password";

void setup(){
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(buzzerPin,OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  delay(2000); 
}

void loop(){
   digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);

  duration=pulseIn(echoPin,HIGH);

  distance =duration * 0.034/2;
  Blynk.virtualWrite(V0, distance);
  if(distance<20){
    digitalWrite(led1,HIGH);
    tone(buzzerPin, 100); 
    delay(100); 
    noTone(buzzerPin); 
    delay(100);
  }
  if(distance<10){
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    tone(buzzerPin,1000);
    delay(100);
    noTone(buzzerPin);
    delay(100);
  }
  else{
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    delay(100); 
    noTone(buzzerPin); 
    delay(100);
  }
  Blynk.run();
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(2000);
}
