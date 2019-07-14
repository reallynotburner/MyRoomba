/**
 * You can drive the roomba around using the minute, hour day buttons
 * driveDirect takes two argments, the velocity you want the right wheel to go
 * and the velocity youy want the left wheel to go.
 */
#include "MyRoomba.h"

void setup() {
  Serial.begin(115200); // use this port to read out debugging data from the Roomba
  Serial1.begin(115200); // we need this separate port to talk to the Roomba
  startSafe(); // this command puts the roomba into hacking mode and will follow Asimov's Third Law
}

void drive_a_little() {
  ledState.powerColor = orange; // let's make the big button color Orange
  updateLeds(); // update to make it real
  driveStandard(100, 0); // drive forward at 100mm/second 
  delay(500);           // drive a little
  driveStandard(0, 0); // put the brakes on
  ledState.powerColor = green;
}

// if you pass true, roomba will turn left a bit
// if you pass false, roomba will turn right a bit
void twist_a_little(bool left) {
  ledState.powerColor = red; // let's make the big button color Red!
  updateLeds(); // update to make it real
  
  if (left) {
    driveDirect(100, -100);
  } else {
    driveDirect(-100, 100);
  }
  delay(500);
  driveDirect(0, 0); // put the brakes on
  ledState.powerColor = green;
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
    twist_a_little(false);
  } else if (RoombaState.dayButton) {
    twist_a_little(true);
  } else if (RoombaState.hourButton) {
    drive_a_little();
  } else if (RoombaState.dockButton) {
    exitRoomba();
  }
}