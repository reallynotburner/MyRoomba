/**
 * reading out the status of the light bumpers
 * view serial monitor,
 * get your hand really close to the bumper and move it across the dark strip on bumper
 * observe changes in serial monitor.
 */
#include "MyRoomba.h"

void setup() {
  Serial.begin(115200); // use this port to read out debugging data from the Roomba
  Serial1.begin(115200); // we need this separate port to talk to the Roomba
  startSafe(); // this command puts the roomba into hacking mode and will follow Asimov's Third Law
}

void exitRoomba() { // it's over
  stop(); // call stop, returning Roomba back to normal consumer operation, startSafe() will go back into hack mode
  while (true) {} // INFINITE LOOP!
}

void simpleManualDrive() {
  if (RoombaState.spotButton) {
    drivePWM(100, 100);
  } else if (RoombaState.cleanButton) {
    drivePWM(-100, -100);
  } else {
    drivePWM(0, 0);
  }
}

void loop() {
  updateLeds();
  updateRoombaState(); // you MUST call this in your program loops to know what the Roomba is doing
  simpleManualDrive();

  Serial.print("What the Roomba sees: ");
  Serial.print(RoombaState.lightBumperLeft);
  Serial.print(RoombaState.lightBumperFrontLeft);
  Serial.print(RoombaState.lightBumperCenterLeft);
  Serial.print(RoombaState.lightBumperCenterRight);
  Serial.print(RoombaState.lightBumperFrontRight);
  Serial.print(RoombaState.lightBumperRight);
  Serial.print(" All Light Bumpers: ");
  Serial.println(RoombaState.lightBumpers);

  if (RoombaState.dockButton) {
    exitRoomba();
  }
}