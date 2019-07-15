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

class MyRoomba
{
  public:
    MyRoomba(HardwareSerial* serialArg);
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