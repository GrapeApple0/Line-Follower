//MIT License

//Copyright 2022 04san (Leguino)
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
//to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,

//and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PRO VIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//Website https://04.si
//E-Mail mail@04.si

// --Motor Connection--
//    motorL is Left
// 　 motorR is Right

//history
//ver 1.3 18/1/2022 => bug fix,add slope detect
//ver 1.2 17/1/2022 => bug fix,add line follow program
//ver 1.1 14/1/2022 => add sensor_gui
//ver 1.0 7/1/2022 => first version
#include <Arduino.h>
#include <Wire.h>

const int no_define1 = 0;//RX
const int no_define2 = 1;//TX
const int touch = 2;
const int sensor1 = 3;
const int sensor2 = 4;
const int sensor3 = 5;
const int sensor4 = 6;
const int sensor5 = 7;
const int motorR1 = 8;
const int motorR2 = 9;
const int motorRPWM = 10;
const int motorLPWM = 11;
const int motorL2 = 12;
const int motorL1 = 13;
const int bump = 14;
const int encoder_L1 = 15;
const int encoder_L2 = 16;
const int encoder_R1 = 17;
const int encoder_R2 = 18;
const int no_define3 = 19;//Reserved with green sensor

const double left_speed_conf = 1.2;//1.2
const double right_speed_conf = 0.9;//0.9

void linetrace();
void back(int);
void forward(int);
void right(int);
void left(int);
void t_right(int);
void t_left(int);
void m_stop();
int true_sensor();

void setup() {
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);
  pinMode(motorLPWM, OUTPUT);
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);
  pinMode(motorRPWM, OUTPUT);
  pinMode(touch, INPUT);
  pinMode(bump, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(encoder_L1, INPUT);
  pinMode(encoder_L2, INPUT);
  pinMode(encoder_R1, INPUT);
  pinMode(encoder_R2, INPUT);
}

void loop() {
  linetrace();
}

void linetrace() {
  if (digitalRead(touch) == 1)
  {
    back(140);
    delay(700);
    left(150);
    delay(800);
    while (digitalRead(sensor3) != 1)
    {
      left(140);
      delay(300);
    }
  }
  else if (digitalRead(bump) == 1)
  {
    forward(200);
    delay(1300);
    back(100);
    delay(500);
  }
  else if (true_sensor() == 5)//交差点・T字路・バンプ
  {
    back(140);
    delay(50);
    left(100);
  }
  else if (true_sensor() == 4 || true_sensor() == 3)//直角
  {
    int l_sensor_cnt = 0;
    int r_sensor_cnt = 0;
    if (digitalRead(sensor1) == 1)
    {
      l_sensor_cnt++;
    }
    if (digitalRead(sensor2) == 1)
    {
      l_sensor_cnt++;
    }
    if (digitalRead(sensor4) == 1)
    {
      r_sensor_cnt++;
    }
    if (digitalRead(sensor5) == 1)
    {
      r_sensor_cnt++;
    }    
    if (l_sensor_cnt < r_sensor_cnt)
    {
      back(120); 
      while (digitalRead(sensor3) != 1)
      {
        t_right(150);
      }
    }
    else if (l_sensor_cnt > r_sensor_cnt)
    {
      back(120);
      while (digitalRead(sensor3) != 1)
      {
        t_left(150);
      }
    }
    else
    {
      forward(130);
    }
  }
  else if (true_sensor() == 1 || true_sensor() == 2)//直線・カーブ
  {
    if (digitalRead(sensor1) == 1)
    {
      back(120);
      left(140);
    }    
    else if (digitalRead(sensor5) == 1)
    {
      back(120);       
      right(140);
    }
    else if (digitalRead(sensor2) == 1)
    {
      right(120);
      forward(130);
    } 
    else if (digitalRead(sensor4) == 1)
    {
      left(120);
      forward(130);
    }
    else if (digitalRead(sensor3) == 1)
    {
      forward(130);
    }     
  }
  else{//白
    forward(130);
  }
}

void back(int mspeed) {
  m_stop();
  digitalWrite(motorL1, HIGH);
  analogWrite(motorLPWM, mspeed);
  digitalWrite(motorR1, HIGH);
  analogWrite(motorRPWM, mspeed);
}

void forward(int mspeed) {
  m_stop();
  digitalWrite(motorL2, HIGH);
  analogWrite(motorLPWM,constrain(mspeed * right_speed_conf,0,254));
  digitalWrite(motorR2, HIGH);
  analogWrite(motorRPWM, mspeed * left_speed_conf);
}

void left(int mspeed) {
  m_stop();
  digitalWrite(motorL2, HIGH);
  analogWrite(motorLPWM, mspeed * left_speed_conf);
}

void right(int mspeed) {
  m_stop();
  digitalWrite(motorR2, HIGH);
  analogWrite(motorRPWM, mspeed);
}

void t_left(int mspeed) {
  m_stop();
  digitalWrite(motorL2, HIGH);
  analogWrite(motorLPWM, mspeed * left_speed_conf);
  digitalWrite(motorR1, HIGH);
  analogWrite(motorRPWM, mspeed);
}

void t_right(int mspeed) {
  m_stop();
  digitalWrite(motorR2, HIGH);
  analogWrite(motorRPWM, mspeed);
  digitalWrite(motorL1, HIGH);
  analogWrite(motorLPWM, mspeed);
}

void m_stop() {
  digitalWrite(motorL1, LOW);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR2, LOW);
}

int true_sensor() {
  int sensor_cnt = 0;
  if (digitalRead(sensor1) == 1)
  {
    sensor_cnt++;
  }
  if (digitalRead(sensor2) == 1)
  {
    sensor_cnt++;
  }
  if (digitalRead(sensor3) == 1)
  {
    sensor_cnt++;
  }
  if (digitalRead(sensor4) == 1)
  {
    sensor_cnt++;
  }
  if (digitalRead(sensor5) == 1)
  {
    sensor_cnt++;
  }
  return sensor_cnt;
}