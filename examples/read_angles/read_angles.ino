/**
 * You can drive the roomba around using the minute, hour day buttons
 * Let's read out what the roomba thinks the angle of rotation is!
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

void loop() {
  updateLeds();
  updateRoombaState(); // you MUST call this in your program loops to know what the Roomba is doing

  // You can drive the roomba around using the minute, hour day buttons
  if (RoombaState.minuteButton) {
    drivePWM(-100, 100);
  } else if (RoombaState.dayButton) {
    drivePWM(100, -100);
  } else if (RoombaState.dockButton) {
    exitRoomba();
  } else {
    drivePWM(0, 0);
  }

  Serial.print("My Rotation in degrees is: ");
  Serial.println(RoombaState.angle);
}