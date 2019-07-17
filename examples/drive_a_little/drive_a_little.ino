#include "MyRoomba.h"

MyRoomba roomba(&Serial1, 115200);

void setup() {
  // this command puts the roomba into hacking mode and will follow Asimov's Third Law
  roomba.startSafe();
}

void drive_a_little() {
  roomba.driveStandard(100, 0); // drive forward at 100mm/second 
  delay(500);           // drive a little
  roomba.driveStandard(0, 0); // put the brakes on
}

void exitRoomba() { // it's over
  roomba.stop(); // call stop, returning Roomba back to normal consumer operation, startSafe() will go back into hack mode
  while (true) {} // INFINITE LOOP!
}

// the loop routine runs over and over again forever:
void loop() {
  drive_a_little();
  delay(5000);
}