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
//    MotorA is Left
// 　 MotorB is Right

//history
//ver 1.3 18/1/2022 => bug fix,add slope detect
//ver 1.2 17/1/2022 => bug fix,add line follow program
//ver 1.1 14/1/2022 => add sensor_gui
//ver 1.0 7/1/2022 => first version
#include <Arduino.h>
#include <Wire.h>

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
const int bump = 14;
void linetrace();
void sensor_gui();
void back(int);
void forward(int);
void right(int);
void left(int);
void t_right(int);
void t_left(int);
void m_stop();
int true_sensor();

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
}

void loop() {
  linetrace();
}

void linetrace() {
  if (digitalRead(touch) == 1)
  {
    
  }
  else if (digitalRead(bump) == 1)
  {
    /* code */
  } 
  else if (true_sensor() == 5)//交差点・T字路・バンプ
  {
    back(80);
    delay(50);
    if (digitalRead(sensor3) == 1)
    {
      forward(100);
      delay(300);
    }
    else
    {
      while (digitalRead(sensor3) != 1)
      {
        if (digitalRead(sensor2) == 1)
        {
          right(70);
        }
        else{
          left(70);
        }
      }
      
    }
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
      back(80); 
      right(150);
      delay(100);
    }
    else if (l_sensor_cnt > r_sensor_cnt)
    {
      back(80);   
      left(150);
      delay(100);
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
      back(80); 
      left(150);
    }    
    else if (digitalRead(sensor5) == 1)
    {
      back(80);       
      right(150);
    }
    else if (digitalRead(sensor2) == 1)
    {
      forward(110);
    } 
    else if (digitalRead(sensor4) == 1)
    {
      forward(110);
    }
    else if (digitalRead(sensor3) == 1)
    {
      forward(100);
    }     
  }
  else{//白
    forward(130);
  }
}

void back(int mspeed) {
  m_stop();
  digitalWrite(motorA1, HIGH);
  analogWrite(motorAPWM, mspeed);
  digitalWrite(motorB1, HIGH);
  analogWrite(motorBPWM, mspeed);
}

void forward(int mspeed) {
  m_stop();
  digitalWrite(motorA2, HIGH);
  analogWrite(motorAPWM, mspeed * 1.5);
  digitalWrite(motorB2, HIGH);
  analogWrite(motorBPWM, mspeed * 1.5);
}

void left(int mspeed) {
  m_stop();
  digitalWrite(motorA2, HIGH);
  analogWrite(motorAPWM, mspeed * 1.2);
}

void right(int mspeed) {
  m_stop();
  digitalWrite(motorB2, HIGH);
  analogWrite(motorBPWM, mspeed * 1.2);
}

void t_right(int mspeed) {
  m_stop();
  digitalWrite(motorA2, HIGH);
  analogWrite(motorAPWM, mspeed);
  digitalWrite(motorB1, HIGH);
  analogWrite(motorBPWM, mspeed);
}

void t_left(int mspeed) {
  m_stop();
  digitalWrite(motorB2, HIGH);
  analogWrite(motorBPWM, mspeed);
  digitalWrite(motorA1, HIGH);
  analogWrite(motorAPWM, mspeed);  
}

void m_stop() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB2, LOW);
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