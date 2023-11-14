// Ultrasonic
#include <SoftwareSerial.h>

// Audio
#include <Arduino.h>
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2SNoDAC.h"
#include "whistle.h"

// LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define time 120000

// Ultrasonic
SoftwareSerial mySerial(12, 14);
unsigned int HighByte = 0;
unsigned int LowByte  = 0;
unsigned int Len  = 0;
unsigned int Dis = 0;
unsigned int Count = 0;
bool checkstart = false;
bool check10 = false;
bool check25 = false;

// Audio
AudioGeneratorWAV *wav;
AudioFileSourcePROGMEM *file;
AudioOutputI2SNoDAC *out;

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
unsigned long prMillis = millis();

void setup() {
  Serial.begin(9600);

  // Ultrasonic
  mySerial.begin(9600);

  // LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Count: ");
  lcd.setCursor(3, 1);
  lcd.print("Time: ");

  // Audio
  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( whistle, sizeof(whistle) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);
  do {
    if (wav->isRunning()) {
      if (!wav->loop()) {
        wav->stop();
        break;
      } 
    } 
  }   
  while (1);

  do {
    // LCD
    lcd.setCursor(10, 0);
    lcd.print(Count);
    lcd.setCursor(9, 1);
    lcd.print((millis() - 1000) / 1000);

    // Ultrasonic
    mySerial.flush();
    mySerial.write(0X55);          
    if (mySerial.available() >= 2) {
      HighByte = mySerial.read();
      LowByte  = mySerial.read();
      Len  = HighByte * 256 + LowByte;
      Dis = Len / 10;
      Serial.print("Distance: ");
      Serial.print(Dis, DEC);          
      Serial.println(" cm"); 
      if (Dis >= 1000) {
        Dis = 0;
      }

      if (check25 == false) {
        //check start
        if (Dis >= 20 && Dis <= 45) {
          checkstart = true;
        }

        if (checkstart == true) {
          //check10
          if (Dis <= 5) {
            check10 = true;
          }
          //notcount
          else if (Dis > 45) {
            checkstart = false;
          }
        }

        if (check10 == true) {
          //check25
          if (Dis >= 20 && Dis <= 45) {
            check25 = true;
          }
          //notcount
          else if (Dis > 45) {
            checkstart = false;
            check10 = false;
          }
        }
      }
      else {
        Count += 1;
        checkstart = false;
        check10 = false;
        check25 = false;
      }  
    }
  }
  while ((millis() - 1000) - prMillis < time);

  // Audio
  file = new AudioFileSourcePROGMEM(whistle, sizeof(whistle) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);
}

void loop() {
  // Audio
  if (wav->isRunning()) {
    if (!wav->loop()) wav->stop();
  }
}