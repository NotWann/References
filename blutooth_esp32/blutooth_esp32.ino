#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

String message = "";
char incomingChar;

int buzzer = 2;
int speeds = 200;

const int IN1 = 5; 
const int IN2 = 4; 
const int ENA = 13; 

const int IN3 = 23; 
const int IN4 = 25; 
const int ENB = 26; 

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32 armot"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(IN1,OUTPUT); 
  pinMode(IN2,OUTPUT); 
  pinMode(IN3,OUTPUT); 
  pinMode(IN4,OUTPUT); 
  pinMode(ENA,OUTPUT); 
  pinMode(ENB,OUTPUT); 

  pinMode(buzzer, OUTPUT);
}

void loop() {
 if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n')
    {
      message += String(incomingChar);
     analogWrite(ENA,speeds); 
     analogWrite(ENB,speeds); 
     digitalWrite(buzzer,HIGH);
     delay(50);
     digitalWrite(buzzer,LOW);
    }
    else
    {
      message = "";
    }
    Serial.write(incomingChar);  
  }
  // Check received message and control output accordingly
  if (message =="w")
  {
   digitalWrite(IN1,LOW); 
   digitalWrite(IN2,HIGH);   
   digitalWrite(IN3,LOW); 
   digitalWrite(IN4,HIGH); 
  }
  else if(message == "d")
  {     
   digitalWrite(IN1,HIGH); 
   digitalWrite(IN2,LOW);   
   digitalWrite(IN3,LOW); 
   digitalWrite(IN4,HIGH);  
  }
   
  else if(message == "a")
  {     

   digitalWrite(IN1,LOW); 
   digitalWrite(IN2,HIGH);   
   digitalWrite(IN3,HIGH); 
   digitalWrite(IN4,LOW);  
  }
 
  else if(message == "s")
  {   
   digitalWrite(IN1,HIGH); 
   digitalWrite(IN2,LOW);   
   digitalWrite(IN3,HIGH); 
   digitalWrite(IN4,LOW);  
  }

  else if(message == "o")
  {  
   digitalWrite(IN1,LOW); 
   digitalWrite(IN2,LOW);   
   digitalWrite(IN3,LOW); 
   digitalWrite(IN4,LOW);  
  }
}
