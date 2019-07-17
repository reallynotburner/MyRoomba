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

struct RoombaPacket {
  byte position;      // where in the stream of bytes reported from the roomba does it begin?
  byte length;        // how many bytes long is it?
  bool signed_status; // is it +/- signed or is it from zero to max
};
<<<<<<< HEAD
=======
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
Packet lightBumpers{31, 56, 2};

/**
   define the structure of the roomba data
*/
struct Roomba600StateStruct {
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
  float batteryVoltage;
  uint16_t cliffAnalogLeft;
  uint16_t cliffAnalogFrontLeft;
  uint16_t cliffAnalogFrontRight;
  uint16_t cliffAnalogRight;
  byte lightBumpers; // this is all the light bumpers together
  bool lightBumperLeft;
  bool lightBumperFrontLeft;
  bool lightBumperCenterLeft;
  bool lightBumperCenterRight;
  bool lightBumperFrontRight;
  bool lightBumperRight;
};

// name the Roomba600StateStruct and give the default values
Roomba600StateStruct RoombaState {
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
  0,
  0,
  0,
  0,
  0,
  0,
  false,
  false,
  false,
  false,
  false,
  false
};

/**
 * call for ALL DATA, it's like 80 bytes long!
 */
void readAllData() {
  byte readSensors[] = {
    sensor_packet_group, // send us a sensor sensor group please
    big_group, // which packet group you want, 0 is packets 7 to 26, big_group is ALL OF THEM
  };
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

// convert Roomba response stream to bumper bytes to RoombaState
void responseToBumper() {
  bool right = bitRead(responseFromRoomba[bumper.position], 0);
  bool left = bitRead(responseFromRoomba[bumper.position], 1);
  RoombaState.bumperRight = right;
  RoombaState.bumperLeft = left;
}
void responseToWheelDrop() {
  bool right = bitRead(responseFromRoomba[bumper.position], 2);
  bool left = bitRead(responseFromRoomba[bumper.position], 3);
  RoombaState.wheelDropRight = right;
  RoombaState.wheelDropLeft = left;
}
void responseToCliffSensors() {
  RoombaState.cliffLeft = bitRead(responseFromRoomba[cliffLeft.position], 0);
  RoombaState.cliffFrontLeft = bitRead(responseFromRoomba[cliffFrontLeft.position], 0);
  RoombaState.cliffFrontRight = bitRead(responseFromRoomba[cliffFrontRight.position], 0);
  RoombaState.cliffRight = bitRead(responseFromRoomba[cliffRight.position], 0);
}
void responseToButtons() {
  RoombaState.cleanButton = bitRead(responseFromRoomba[buttons.position], 0);
  RoombaState.spotButton = bitRead(responseFromRoomba[buttons.position], 1);
  RoombaState.dockButton = bitRead(responseFromRoomba[buttons.position], 2);
  RoombaState.hourButton = bitRead(responseFromRoomba[buttons.position], 4);
  RoombaState.dayButton = bitRead(responseFromRoomba[buttons.position], 5);
  RoombaState.minuteButton = bitRead(responseFromRoomba[buttons.position], 3);
  RoombaState.scheduleButton = bitRead(responseFromRoomba[buttons.position], 6);
  RoombaState.clockButton = bitRead(responseFromRoomba[buttons.position], 7);
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
  uint8_t highbyte = responseFromRoomba[voltage.position];
  uint8_t lowbyte = responseFromRoomba[voltage.position+1];
  uint16_t batteryVoltage = highbyte * 256 + lowbyte;
  RoombaState.batteryVoltage = batteryVoltage / 1000.0;
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
void responseToLightBumpers() {
  byte bumpers = responseFromRoomba[lightBumpers.position];
  RoombaState.lightBumpers = bumpers;
  RoombaState.lightBumperLeft = bitRead(bumpers, 0);
  RoombaState.lightBumperFrontLeft = bitRead(bumpers, 1);
  RoombaState.lightBumperCenterLeft = bitRead(bumpers, 2);
  RoombaState.lightBumperCenterRight = bitRead(bumpers, 3);
  RoombaState.lightBumperFrontRight = bitRead(bumpers, 4);
  RoombaState.lightBumperRight = bitRead(bumpers, 5);
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
  responseToLightBumpers();
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
>>>>>>> master

class MyRoomba
{
  public:
  MyRoomba(HardwareSerial* serialArg, long int baud);
    void dot();
    void dash();
    void startSafe();
    void startFull();
    void stop();
    void updateState();
    uint8_t bumpers;
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
    byte lightBumpers; // this is all the light bumpers together
    bool lightBumperLeft;
    bool lightBumperFrontLeft;
    bool lightBumperCenterLeft;
    bool lightBumperCenterRight;
    bool lightBumperFrontRight;
    bool lightBumperRight;

  private:
    HardwareSerial* _serial;
    byte _inputBuffer[80]; // a place to store the response from the roomba
    RoombaPacket bumperPacket{0, 1, false};
    void readAllData();
};

#endif