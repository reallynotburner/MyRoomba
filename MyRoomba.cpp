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
  _serial->write("ABC");
}

void MyRoomba::dash()
{
  _serial->write("DEF");
}

void MyRoomba::driveStandard(int velocity, int radius)
{
  byte buf[] = { 137, 255, 56, 1, 244 }; // TODO make this actually use the arguments
  _serial->write(buf, 5);
}

void MyRoomba::startSafe()
{
  _serial->write(128);  //Start
  delay(1000);          // IDK if this is a necessary pause
  _serial->write(131);  //Safe mode
  delay(1000);          // IDK if this is a necessary pause
}

void MyRoomba::startFull()
{
  _serial->write(128);  //Start
  delay(1000);          // IDK if this is a necessary pause
  _serial->write(132);  //Full mode
  delay(1000);          // IDK if this is a necessary pause
}

void MyRoomba::stop()
{
  _serial->write(173);
}

void MyRoomba::readAllData()
{
  byte buf[] = {143, 100};
  byte inByte = 0;
  byte counter = 0;
  long int timeoutTime = millis() + 200;
  _serial->write(buf, 2); // request a group of packets, ALL OF THEM

  while (_serial->available() <= 0) {
    if(millis() > timeoutTime) {
      return;
    }
  } // wait for response
  while (counter < 80) {
    while (_serial->available() <= 0) {} // wait for response
    if(millis() > timeoutTime) {
      return;
    }  
    _inputBuffer[counter] = _serial->read();
    counter++;
  }
  delay(40);
}

void MyRoomba::updateState()
{
  readAllData();
  bumpers = _inputBuffer[0];
}




