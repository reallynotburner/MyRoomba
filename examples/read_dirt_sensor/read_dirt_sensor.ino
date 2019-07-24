/**
 * reading out dirt sensor
 * view serial monitor,
 * When the roomba sucks up dirt, this will show you with lights and with serial port
 */
#include "MyRoomba.h"

void setup() {
  Serial.begin(115200); // use this port to read out debugging data from the Roomba
  Serial1.begin(115200); // we need this separate port to talk to the Roomba
  startSafe(); // this command puts the roomba into hacking mode and will follow Asimov's Third Law
  ledState.powerColor = 255;  // make that light red
}

void allLightsStateTrue() {
  ledState.debris = true;
  ledState.spot = true;
  ledState.dock = true;
  ledState.check = true;
}

void allLightsStateFalse() {
  ledState.debris = false;
  ledState.spot = false;
  ledState.dock = false;
  ledState.check = false;
}

void exitRoomba() { // it's over
  stop(); // call stop, returning Roomba back to normal consumer operation, startSafe() will go back into hack mode
  while (true) {} // INFINITE LOOP!
}

void loop() {

  updateLeds();
  updateRoombaState(); // you MUST call this in your program loops to know what the Roomba is doing
  ledState.powerBrightness = RoombaState.dirtDetect;

  if (RoombaState.dirtDetect > 100) {
    allLightsStateTrue();
    Serial.println("DIRTY");
  } else  {
    allLightsStateFalse();
    Serial.println("clean");
  }

  if (RoombaState.dockButton) {
    exitRoomba();
  }
}