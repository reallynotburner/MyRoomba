#include "MyRoomba.h"

void setup() {
  Serial1.begin(115200); // we need this separate port to talk to the Roomba
  // this command puts the roomba into hacking mode and will follow Asimov's Third Law
  startSafe();
}

void drive_a_little() {
  ledState.powerColor = orange; // let's make the big button color Orange
  updateLeds(); // update to make it real
  driveStandard(100, 0); // drive forward at 100mm/second 
  delay(500);           // drive a little
  driveStandard(0, 0); // put the brakes on
  ledState.powerColor = green;
  updateLeds();
}

void exitRoomba() { // it's over
  stop(); // call stop, returning Roomba back to normal consumer operation, startSafe() will go back into hack mode
  while (true) {} // INFINITE LOOP!
}

// the loop routine runs over and over again forever:
void loop() {
  updateLeds();
  updateRoombaState(); // you MUST call this in your program loops to know what the Roomba is doing
  if (RoombaState.dockButton) {
    exitRoomba();
  } else if (RoombaState.cleanButton) {
    drive_a_little();
  }
}