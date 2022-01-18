//MIT License

//Copyright 2022 04san (Leguino)
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
//to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,

//and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//Website https://04.si
//E-Mail mail@04.si

// --Motor Connection--
//    MotorA is Left
// 　 MotorB is Right

//Mechanism pictures
//Coming soon

//history
//ver 1.3 18/1/2022 => bug fix,add slope detect
//ver 1.2 17/1/2022 => bug fix,add line follow program
//ver 1.1 14/1/2022 => add sensor_gui
//ver 1.0 7/1/2022 => first version
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int touch = 2;
const int sensor1 = 3;
const int sensor2 = 4;
const int sensor3 = 5;
const int sensor4 = 6;
const int sensor5 = 7;
const int motorB1 = 8;
const int motorB2 = 9;
const int motorBPWM = 10;
const int motorAPWM = 11;
const int motorA2 = 12;
const int motorA1 = 13;
const int green1 = 14;//Analog 0 Left
const int runSwitch = 15;
const int green2 = 16;//Analog 1 Right
const int slopeSensor = 3;//Analog 3
const byte lcd_id = 0x27;
bool isRun = true;
bool slope = false;
int val = 0;
int get_slope();
void linetrace();
void sensor_gui();
void back(int, int);
void forward(int, int);
void right(int, int);
void left(int, int);
void m_stop();

LiquidCrystal_I2C lcd(lcd_id, 16, 2);

void setup() {
  // put your setup code here, to run once:
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorAPWM, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(motorBPWM, OUTPUT);
  pinMode(touch, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(green1, INPUT);
  pinMode(green2, INPUT);
  pinMode(runSwitch, INPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  sensor_gui();
}

void loop() {
  if (digitalRead(runSwitch) == 1) {
    linetrace();
    isRun = true;
  } else {
    isRun = false;
  }
  sensor_gui();
}

float readAnalog(int pin) {
  int i = analogRead(pin);
  float f = i * 5.0 / 1023.0;
  return f;
}

void linetrace() {
  //B => Black
  //W => White
  //G => Green
  //? => null
  //to hard...
  if (1 < get_slope()) {
      forward(200, 300);
  }
  if (digitalRead(sensor1) == 1) { //          farest left sensor B????
    if (digitalRead(sensor2) == 1) { //               left sensor BB???
      if (digitalRead(sensor3) == 1) { //           center sensor BBB??
        if (digitalRead(sensor4) == 1) { //          right sensor BBBB?
          if (digitalRead(sensor5) == 1) { // farest right sensor BBBBB
            int turn_cnt = 0;
            if (digitalRead(green1) == 1) { // green sensor left   GB?

            }
            if (digitalRead(green2) == 1) { // green sensor right  GBG

            }
            for (int i = 0; i <= turn_cnt; i++) {

            }
          }
          else { //                                               BBBBW sensor 5

          }
        }
        else { //                                                 BBBW? sensor 4
          if (digitalRead(sensor5) == 1) { // farest right sensor BBBWB

          }
          else { //                                               BBBWW sensor 5

          }
        }
      }
      else { //                                                   BBW?? sensor 3
        if (digitalRead(sensor4) == 1) { //          right sensor BBWB?
          if (digitalRead(sensor5) == 1) { // farest right sensor BBWBB

          }
          else { //                                               BBWBW sensor 5

          }
        }
        else { //                                                 BWBW? sensor 4
          if (digitalRead(sensor5) == 1) { //                   BWBWB

          }
          else { //                                             BBBWW sensor 5

          }
        }
      }
    }
    else { //                                                     BW??? sensor 2
      if (digitalRead(sensor3) == 1) { //           center sensor BWB??
        if (digitalRead(sensor4) == 1) { //          right sensor BWBB?
          if (digitalRead(sensor5) == 1) { // farest right sensor BBBWB

          }
          else { //                                               BBBWW sensor 5

          }
        }
        else {
          if (digitalRead(sensor5) == 1) { // farest right sensor BWBWB

          }
          else { //                                               BWBWW sensor 5

          }
        }
      }
      else {
        if (digitalRead(sensor4) == 1) { //          right sensor BWBB?
          if (digitalRead(sensor5) == 1) { //        right sensor BWBBB

          }
          else { //                                               BWBBW sensor 5

          }
        }
        else {
          if (digitalRead(sensor5) == 1) { //       right sensor BWWWB

          }
          else { //                                              BWWWW sensor 5

          }
        }
      }
    }
  }
  else { //                                                     W???? sensor 1
    if (digitalRead(sensor2) == 1) { //             left sensor WB???
      if (digitalRead(sensor3) == 1) { //         center sensor WBB??
        if (digitalRead(sensor4) == 1) { //        right sensor WBBB?
          if (digitalRead(sensor5) == 1) {//farest right sensor WBBBB

          }
          else { //                                             WBBBW sensor 5
            forward(180, 300);
          }
        }
        else { //                                               WBBW? sensor 4
          if (digitalRead(sensor5) == 1) {//farest right sensor WBBWB

          }
          else { //                                             WBBWW sensor 5

          }
        }
      }
      else { //                                                 WBW?? sensor 3
        if (digitalRead(sensor4) == 1) { //        right sensor WBWB?
          if (digitalRead(sensor5) == 1) {//farest right sensor WBWWB

          }
          else { //                                             WBWWW sensor 5

          }
        }
        else { //                                               WBWW? sensor 4
          if (digitalRead(sensor5) == 1) {//farest right sensor WBWWB

          }
          else { //                                             WBWWW sensor 5

          }
        }
      }
    }
    else {//                                                    WW??? sensor 2
      if (digitalRead(sensor3) == 1) { //         center sensor WWB??
        if (digitalRead(sensor4) == 1) { //        right sensor WWBB?
          if (digitalRead(sensor5) == 1) {//farest right sensor WWBBB

          }
          else { //                                             WWBBW sensor 5

          }
        }
        else { //                                               WWBW? sensor 4
          if (digitalRead(sensor5) == 1) {//farest right sensor WWBWB

          }
          else { //                                             WWBWW sensor 5

          }
        }
      }
      else { //                                   center sensor WWW?? sensor 3
        if (digitalRead(sensor4) == 1) { //        right sensor WWWB?
          if (digitalRead(sensor5) == 1) {//farest right sensor WWWBB

          }
          else { //                                             WWWBW sensor 5

          }
        }
        else { //                                               WWWW? sensor 4
          if (digitalRead(sensor5) == 1) {//farest right sensor WWWWB

          }
          else { //                                             WWWWW sensor 5

          }
        }
      }
    }
  }
}

int get_slope() {
  float ms2 = 9.8;
  float offset_voltage = 2500.0;
  float y =  (analogRead(slopeSensor) / 1024.0) * 5.0 * 1000;
  y = y - offset_voltage;
  float yg = y / 1000.0;
  int rtn = yg * ms2;
  return rtn;
}

//0 = stop,1 = forward,2 = back,3 = left,4 = right
void back(int mspeed, int movetime) {
  digitalWrite(motorA1, HIGH);
  analogWrite(motorAPWM, mspeed);
  digitalWrite(motorB1, HIGH);
  analogWrite(motorBPWM, mspeed);
  delay(movetime);
  m_stop();
}

void forward(int mspeed, int movetime) {
  digitalWrite(motorA2, HIGH);
  analogWrite(motorAPWM, mspeed);
  digitalWrite(motorB2, HIGH);
  analogWrite(motorBPWM, mspeed);
  delay(movetime);
  m_stop();
}

void right(int mspeed, int movetime) {
  digitalWrite(motorA2, HIGH);
  analogWrite(motorAPWM, mspeed);
  delay(movetime);
  m_stop();
}

void left(int mspeed, int movetime) {
  digitalWrite(motorB2, HIGH);
  analogWrite(motorBPWM, mspeed);
  delay(movetime);
  m_stop();
}

void m_stop() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB2, LOW);
  digitalWrite(motorAPWM, LOW);
  digitalWrite(motorBPWM, LOW);
}

void sensor_gui() {
  if (digitalRead(runSwitch) == 1) {
    isRun = true;
  } else {
    isRun = false;
  }
  lcd.clear();
  lcd.setCursor(1, 0);
  if (digitalRead(sensor1) == 1) {
    lcd.print("B");
  } else {
    lcd.print("W");
  }
  if (digitalRead(sensor2) == 1) {
    lcd.print("B");
  } else {
    lcd.print("W");
  }
  if (digitalRead(sensor3) == 1) {
    lcd.print("B");
  } else {
    lcd.print("W");
  }
  if (digitalRead(sensor4) == 1) {
    lcd.print("B");
  } else {
    lcd.print("W");
  }
  if (digitalRead(sensor5) == 1) {
    lcd.print("B");
  } else {
    lcd.print("W");
  }
  lcd.setCursor(7, 0);
  if (isRun == true) {
    lcd.print("RUN");
  }
  else {
    lcd.print("STOP");
  }
  lcd.setCursor(2, 1);
  if (digitalRead(green1) == 1) {
    lcd.print("W");
  } else {
    lcd.print("G");
  }
  lcd.setCursor(4, 1);
  //White 4v
  //Green and Black 0v
  if (digitalRead(green2) == 1) {
    lcd.print("W");
  } else {
    lcd.print("G");
  }
  lcd.setCursor(6, 1);
  lcd.print(get_slope());
  delay(500);
}