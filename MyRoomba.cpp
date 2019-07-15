/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "MyRoomba.h"

MyRoomba::MyRoomba(HardwareSerial* serialArg)
{
  _serial = serialArg;
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
  _serial->write(start);  //Start
  _serial->write(safe);  //Safe mode
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
  byte inByte = 0;
  byte counter = 0;
  _serial->write(143); // request a group of packets
  _serial->write(100); // specifically, ALL OF THEM

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
  bumpers = _inputBuffer[0];
}




