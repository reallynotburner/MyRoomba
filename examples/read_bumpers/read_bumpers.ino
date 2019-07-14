#include "MyRoomba.h"

void setup() {
  Serial.begin(115200); // use this port to read out debugging data from the Roomba
  Serial1.begin(115200); // we need this separate port to talk to the Roomba
  startSafe(); // this command puts the roomba into hacking mode and will follow Asimov's Third Law
}

void twist_a_little(bool left) {
  ledState.powerColor = orange; // let's make the big button color Orange
  updateLeds(); // update to make it real
  
  if (left) {
    driveDirect(100, -100);
  } else {
    driveDirect(-100, 100);
  }
  delay(500);           // twist a little
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
  if (RoombaState.minuteButton) {
    twist_a_little(true);
  } else if (RoombaState.dayButton) {
    twist_a_little(false);
  } else if (RoombaState.dockButton) {
    exitRoomba();
  }
}