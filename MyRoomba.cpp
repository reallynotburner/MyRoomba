/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "MyRoomba.h"

MyRoomba::MyRoomba(HardwareSerial* serialArg, long int baud = 115200)
{
  _serial = serialArg;
  _serial->begin(baud);
  bumpers = 0;
  bumperRight = false;
  bumperLeft = false;
  wheelDropRight = false;
  wheelDropLeft = false;
  cliffLeft = false;
  cliffFrontLeft = false;
  cliffFrontRight = false;
  cliffRight = false;
  cleanButton = false;
  spotButton = false;
  dockButton = false;
  dayButton = false;
  hourButton = false;
  minuteButton = false;
  scheduleButton = false;
  clockButton = false;
  distance = 0;
  angle = 0;
  batteryVoltage = 0;
  cliffAnalogLeft = 0;
  cliffAnalogFrontLeft = 0;
  cliffAnalogFrontRight = 0;
  cliffAnalogRight = 0;
  lightBumpers = 0;
  lightBumperLeft = false;
  lightBumperFrontLeft = false;
  lightBumperCenterLeft = false;
  lightBumperCenterRight = false;
  lightBumperFrontRight = false;
  lightBumperRight = false;
  delay(1000);
}

void MyRoomba::dot()
{
  _serial->println("ABC");
}

void MyRoomba::dash()
{
  _serial->println("DEF");
}

void MyRoomba::startSafe()
{
  byte buf[] = {128, 131};
  _serial->write(buf, 2);  //Start
  delay(1000);
}

void MyRoomba::startFull()
{
  _serial->println("DEF");
}

void MyRoomba::stop()
{
  _serial->println("DEF");
}

void MyRoomba::readAllData()
{
  byte buf[] = {143, 100};
  byte inByte = 0;
  byte counter = 0;
  _serial->write(buf, 2); // request a group of packets, ALL OF THEM

  while (_serial->available() <= 0) {} // wait for response
  while (counter < 80) {
    while (_serial->available() <= 0) {} // wait for response
    _inputBuffer[counter] = _serial->read();
      Serial.println(_inputBuffer[counter]);
    counter++;
  }
  delay(40);
}

void MyRoomba::updateState()
{
  readAllData();
  bumpers = _inputBuffer[0];
}




