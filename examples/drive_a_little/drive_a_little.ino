#include "MyRoomba.h"

void setup() {
  Serial.begin(115200); // use this port to read out debugging data from the Roomba
  delay(100);
  Serial1.begin(115200); // we need this separate port to talk to the Roomba
  // this command puts the roomba into hacking mode and will follow Asimov's Third Law
  startSafe();
}

void drive_a_little() {
  driveStandard(100, 0); // drive forward at 100mm/second 
  delay(500);           // drive a little
  driveStandard(0, 0); // put the brakes on
}

void exitRoomba() { // it's over
  stop(); // call stop, returning Roomba back to normal consumer operation, startSafe() will go back into hack mode
  while (true) {} // INFINITE LOOP!
}

// the loop routine runs over and over again forever:
void loop() {
  updateRoombaState(); // you MUST call this in your program loops to know what the Roomba is doing
  if (RoombaState.dockButton) {
    exitRoomba();
  } else if (RoombaState.spotButton) {
    drive_a_little();
  }
}