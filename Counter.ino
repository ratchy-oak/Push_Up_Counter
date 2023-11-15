// Ultrasonic
#include <SoftwareSerial.h>

// Audio
#include <Arduino.h>
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2SNoDAC.h"
#include "whistle.h"
#include "one.h"
#include "two.h"
#include "three.h"
#include "four.h"
#include "five.h"
#include "six.h"
#include "seven.h"
#include "eight.h"
#include "nine.h"
#include "ten.h"
#include "eleven.h"
#include "twelve.h"
#include "thirteen.h"
#include "fourteen.h"
#include "fifteen.h"
#include "sixteen.h"
#include "seventeen.h"
#include "eighteen.h"
#include "nineteen.h"
#include "twenty.h"
#include "end.h"

// LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define time 20000

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
    delay(50);
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

  if (Count == 1) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( one, sizeof(one) );
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
  } else if (Count == 2) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( two, sizeof(two) );
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
  } else if (Count == 3) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( three, sizeof(three) );
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
  } else if (Count == 4) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( four, sizeof(four) );
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
  } else if (Count == 5) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( five, sizeof(five) );
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
  } else if (Count == 6) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( six, sizeof(six) );
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
  } else if (Count == 7) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( seven, sizeof(seven) );
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
  } else if (Count == 8) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( eight, sizeof(eight) );
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
  } else if (Count == 9) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( nine, sizeof(nine) );
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
  } else if (Count == 10) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( ten, sizeof(ten) );
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
  } else if (Count == 11) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( eleven, sizeof(eleven) );
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
  } else if (Count == 12) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( twelve, sizeof(twelve) );
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
  } else if (Count == 13) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( thirteen, sizeof(thirteen) );
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
  } else if (Count == 14) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( fourteen, sizeof(fourteen) );
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
  } else if (Count == 15) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( fifteen, sizeof(fifteen) );
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
  } else if (Count == 16) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( sixteen, sizeof(sixteen) );
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
  } else if (Count == 17) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( seventeen, sizeof(seventeen) );
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
  } else if (Count == 18) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( eighteen, sizeof(eighteen) );
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
  } else if (Count == 19) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( nineteen, sizeof(nineteen) );
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
  } else if (Count == 20) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( twenty, sizeof(twenty) );
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
  }

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( end, sizeof(end) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);
}

void loop() {
  if (wav->isRunning()) {
    if (!wav->loop()) wav->stop();
  }
}