/**
   MyRoomba.h
   v0.0.1
   Joshua Brown 2019

   For a more complete Roomba library with iCreate support see:
   https://github.com/Apocrathia/Roomba

   I would have used it, but I didn't figure out how to get it to compile
   with Arduino 1.8.5 MacOs to an Arduino Micro, so I wrote my own.
*/
#ifndef MyRoomba_H
#define MyRoomba_H
#include "Arduino.h"

#define start 128 // go to Passive mode
#define roomba_reset 7 // as if you pulled the battery and reinserted it
#define roomba_stop 173 // when you are done working with the Roomba, send this
#define baud_set 129 // for custom serial speeds, the 650 takes 115200
#define safe 131 // robot will protect it's own existence
#define full 132 // robot will ignore cliff and battery sensors, breaking itself to obey
#define clean 135 // robot will start the normal clean program
#define clean_max 136 // robot will do the clean program until it runs out of battery
#define clean_spot 134
#define seek_dock 143 // robot will clean until it finds a dock, then park and charge itself
#define power_down 133
#define drive_standard 137 // high-level, robot speed and radius of turn
#define drive_direct 145 // right and left wheel speeds
#define drive_pwm 146 // directly control right and left wheel torque
#define led_code 139 // program the led's to do something
#define play_song 141 // play one of the stored songs
#define enter_song 140 // enter a song deinition
#define sensor_packet_group 142 // ask for a group of sensor packets
#define sensor_query_list 149 // ask for a series of sensor packets, or just one
#define big_group 100
#define orange 128
#define green 0
#define red 255

byte responseFromRoomba[80];

byte convertPacketToPosition (byte packet) {
  return packet - 7;
}

/**
   This is the human-readable way to define the data packets and how they are gotten from the Roomba
*/
struct Packet {
  byte number; // the documentation will say it's packet "7" or something
  byte position; // the position in the stream of bytes from the Roomba that this packet is
  byte length; // how many bytes long is this packet?  
};
Packet bumper{7, convertPacketToPosition(7), 1};
Packet cliffLeft{9, convertPacketToPosition(9), 1};
Packet cliffFrontLeft{10, convertPacketToPosition(10), 1};
Packet cliffFrontRight{11, convertPacketToPosition(11), 1};
Packet cliffRight{12, convertPacketToPosition(12), 1};
Packet buttons{18, convertPacketToPosition(18), 1};
Packet distance{19, convertPacketToPosition(19), 2};
Packet angle{20, 14, 2};
Packet voltage{22, 17, 2};

Packet cliffAnalogLeft{28, 28, 2};
Packet cliffAnalogFrontLeft{29, 30, 2};
Packet cliffAnalogFrontRight{30, 32, 2};
Packet cliffAnalogRight{31, 34, 2};

/**
   define the structure of the roomba data
*/
struct RoombaStateStructure {
  bool bumperRight;
  bool bumperLeft;
  bool wheelDropRight;
  bool wheelDropLeft;
  bool cliffLeft;
  bool cliffFrontLeft;
  bool cliffFrontRight;
  bool cliffRight;
  bool cleanButton;
  bool spotButton;
  bool dockButton;
  bool dayButton;
  bool hourButton;
  bool minuteButton;
  bool scheduleButton;
  bool clockButton;
  long int distance;
  long int angle;
  uint16_t batteryVoltage;
  uint16_t cliffAnalogLeft;
  uint16_t cliffAnalogFrontLeft;
  uint16_t cliffAnalogFrontRight;
  uint16_t cliffAnalogRight;
};

// name the RoombaStateStructure and give the default values
RoombaStateStructure RoombaState {
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  0,
  0,
  0
};

/**
 * call for ALL DATA, it's like 80 bytes long!
 */
void readAllData() {
  byte readSensors[] = {
    sensor_packet_group, // send us a sensor sensor group please
    big_group, // which packet group you want, 0 is packets 7 to 26, big_group is ALL OF THEM
  };
  byte inByte = 0;
  byte counter = 0;
  Serial1.write(readSensors, 2);
  while (Serial1.available() <= 0) {} // wait for response
  while (counter < 80) {
    while (Serial1.available() <= 0) {} // wait for response
    responseFromRoomba[counter] = Serial1.read();
    counter++;
  }
  // just a tiny delay so you can call this safely.  When you keep mashing it too quicky, it crashes.
  delay(40); 
}

// convert Roomba response stream to bumper byte to RoombaState, etc....
void responseToBumper() {
  bool right = bitRead(responseFromRoomba[bumper.position], 0) ? true : false;
  bool left = bitRead(responseFromRoomba[bumper.position], 1) ? true : false;
  RoombaState.bumperRight = right;
  RoombaState.bumperLeft = left;
}
void responseToWheelDrop() {
  bool right = bitRead(responseFromRoomba[bumper.position], 2) ? true : false;
  bool left = bitRead(responseFromRoomba[bumper.position], 3) ? true : false;
  RoombaState.wheelDropRight = right;
  RoombaState.wheelDropLeft = left;
}
void responseToCliffSensors() {
  RoombaState.cliffLeft = bitRead(responseFromRoomba[cliffLeft.position], 0) ? true : false;
  RoombaState.cliffFrontLeft = bitRead(responseFromRoomba[cliffFrontLeft.position], 0) ? true : false;
  RoombaState.cliffFrontRight = bitRead(responseFromRoomba[cliffFrontRight.position], 0) ? true : false;
  RoombaState.cliffRight = bitRead(responseFromRoomba[cliffRight.position], 0) ? true : false;
}
void responseToButtons() {
  RoombaState.cleanButton = bitRead(responseFromRoomba[buttons.position], 0) ? true : false;
  RoombaState.spotButton = bitRead(responseFromRoomba[buttons.position], 1) ? true : false;
  RoombaState.dockButton = bitRead(responseFromRoomba[buttons.position], 2) ? true : false;
  RoombaState.hourButton = bitRead(responseFromRoomba[buttons.position], 4) ? true : false;
  RoombaState.dayButton = bitRead(responseFromRoomba[buttons.position], 5) ? true : false;
  RoombaState.minuteButton = bitRead(responseFromRoomba[buttons.position], 3) ? true : false;
  RoombaState.scheduleButton = bitRead(responseFromRoomba[buttons.position], 6) ? true : false;
  RoombaState.clockButton = bitRead(responseFromRoomba[buttons.position], 7) ? true : false;
}
void responseToDistance() {
  int highbyte = responseFromRoomba[distance.position];
  int lowbyte = responseFromRoomba[distance.position+1];
  int distanceDelta = highbyte * 256 + lowbyte;
  RoombaState.distance += distanceDelta;
}
void responseToAngle() {
  int highbyte = responseFromRoomba[angle.position];
  int lowbyte = responseFromRoomba[angle.position+1];
  int angleDelta = highbyte * 256 + lowbyte;
  RoombaState.angle += angleDelta;
}
void responseToBatteryVoltage() {
  uint8_t highbyte = responseFromRoomba[angle.position];
  uint8_t lowbyte = responseFromRoomba[angle.position+1];
  uint16_t batteryVoltage = highbyte * 256 + lowbyte;
  RoombaState.batteryVoltage = batteryVoltage;
}
void responseToCliffAnalogSensors() {
  byte position = cliffAnalogLeft.position;
  uint8_t highbyte = responseFromRoomba[position];
  uint8_t lowbyte = responseFromRoomba[position + 1];
  RoombaState.cliffAnalogLeft = highbyte * 256 + lowbyte;
  highbyte = responseFromRoomba[position + 2];
  lowbyte = responseFromRoomba[position + 3];
  RoombaState.cliffAnalogFrontLeft = highbyte * 256 + lowbyte;
  highbyte = responseFromRoomba[position + 4];
  lowbyte = responseFromRoomba[position + 5];
  RoombaState.cliffAnalogFrontRight = highbyte * 256 + lowbyte;
  highbyte = responseFromRoomba[position + 6];
  lowbyte = responseFromRoomba[position + 7];
  RoombaState.cliffAnalogRight = highbyte * 256 + lowbyte;
}

void updateRoombaState() {
  readAllData();
  responseToBumper();
  responseToWheelDrop();
  responseToCliffSensors();
  responseToButtons();
  responseToDistance();
  responseToAngle();
  responseToBatteryVoltage();
  responseToCliffAnalogSensors();
}

/**
   settings a boolean LED status will turn that LED on when the updateLed's helper is run
*/
struct LedStatus {
  bool debris;
  bool spot;
  bool dock;
  bool check;
  byte powerColor; // 0 is green, 128 is orange, 255 is red
  byte powerBrightness; // 0 is off, 255 is max brightness
};
LedStatus ledState{false, false, false, false, 0, 255};

void updateLeds () {
  byte ledCommand[] = {led_code, 0, ledState.powerColor, ledState.powerBrightness};
  byte leds = 0;
  leds += ledState.debris ? 1 : 0; // todo: maybe bitshifting would be more succinct?
  leds += ledState.spot ? 2 : 0;
  leds += ledState.dock ? 4 : 0;
  leds += ledState.check ? 8 : 0;
  ledCommand[1] = leds;

  Serial1.write(ledCommand, 4);
}

// this command puts the roomba into hacking mode and will follow Asimov's Third Law
void startSafe()
{
  Serial1.write(start);  //Start
  Serial1.write(safe);  //Safe mode
  delay(1000);
}

// this command puts the roomba into hacking mode and will viloate Asimov's Third Law
void startFull()
{
  Serial1.write(start);  //Start
  Serial1.write(full);  //Safe mode
  delay(1000);
}

void stop() {
  Serial1.write(roomba_stop);
  delay(1000);
}

void reset() {
  Serial1.write(roomba_reset);
  delay(1000);
}

// +/- 500 mm/s and radius in mm
// Serial sequence: [137] [Velocity high byte] [Velocity low byte] [Radius high byte] [Radius low byte]
// Desired value -> two’s complement and convert to hex -> split into 2 bytes -> convert to decimal
void driveStandard (int velocity, int radius) {
  byte driveCommand[] = {drive_standard, 0, 0, 0, 0};

  int velocityMSD = highByte(velocity);
  int velocityLSD = lowByte(velocity);
  int radiusMSD = highByte(radius);
  int radiusLSD = lowByte(radius);

  driveCommand[1] = velocityMSD;
  driveCommand[2] = velocityLSD;
  driveCommand[3] = radiusMSD;
  driveCommand[4] = radiusLSD;

  Serial1.write(driveCommand, 5); // execute the buffer
}

// +/- 500 mm/second
void driveDirect(int rightVelocity, int leftVelocity) {
  byte driveCommand[] = {drive_direct, 0, 0, 0, 0};

  int velocityRightMSD = highByte(rightVelocity);
  int velocityRightLSD = lowByte(rightVelocity);
  int velocityLeftMSD = highByte(leftVelocity);
  int velocityLeftLSD = lowByte(leftVelocity);

  driveCommand[1] = velocityRightMSD;
  driveCommand[2] = velocityRightLSD;
  driveCommand[3] = velocityLeftMSD;
  driveCommand[4] = velocityLeftLSD;

  Serial1.write(driveCommand, 5); // execute the buffer
}

// +/- 255 where 255 is full power
void drivePWM(int rightPWM, int leftPWM) {
  byte driveCommand[] = {145, 0, 0, 0, 0};

  int pwmRightMSD = highByte(rightPWM);
  int pwmRightLSD = lowByte(rightPWM);
  int pwmLeftMSD = highByte(leftPWM);
  int pwmLeftLSD = lowByte(leftPWM);

  driveCommand[1] = pwmRightMSD;
  driveCommand[2] = pwmRightLSD;
  driveCommand[3] = pwmLeftMSD;
  driveCommand[4] = pwmLeftLSD;

  Serial1.write(driveCommand, 5); // execute the buffer
}

void off() {
  Serial1.write(power_down);
  delay(1000);
}


// the Roomba 650 might not have the range of songs that the 600 iCreate has.
// I can only get song 1, 2, 3 to play.  0 and 4 are unaavailable.
// songs with multiple notes don't seem to play.  They persist after power is turned off.
// so you don't need to have it run each time, the songs are still there to be played
/*
  void setupSongs() {
  byte song[] = {
    enter_song,
    0,
    1,
    40,
    16
  };


  Serial1.write(song, 5);
  delay(250);
  byte songCounter = 0;
  for (songCounter = 1; songCounter < 5; songCounter++) {
    song[1] += 1;
    song[3] += 5;
    Serial1.write(song, 5);
    delay(250);
  }
  }
*/

void playSong(byte song) {
  byte songCommand[] = {play_song, song};
  Serial1.write(songCommand, 2);
}

/**
 * sample of how to do a read of a packet,
 * see the Roomba OI spec on how to read multiple packets.
 */
byte readBumbers() {
  //  [149] [2] [7]
  byte readSensors[] = {
    sensor_query_list,
    1, // # of bytes expectedjust one byte comes with packet 7
    7  // which sensor byte you want
  };
  byte inByte = 0;
  Serial1.write(readSensors, 3);
  delay(30);
  if (Serial1.available() > 0) {
    inByte = Serial1.read();
    Serial.println(inByte);
  }
  return inByte;
}

#endif