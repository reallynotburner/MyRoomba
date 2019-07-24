/**
 * reading out dirt sensor
 * view serial monitor,
 * When the roomba sucks up dirt, this will show you with lights and with serial port
 */
#include "MyRoomba.h"

// wait here forever until someone pushes the button
void waitToClean() {
  ledState.powerColor = orange;  // make that light orange to show we changed state
  updateLeds();
  
  while (!RoombaState.cleanButton) {
    // you must update state, or RoombaState.cleanButton will not show that you're pushing it
    updateRoombaState();
  }

  // Begin the cleaning!
  delay(1000); // dramatic pause!
  clean();
}

void setup() {
  Serial.begin(115200); // use this port to read out debugging data from the Roomba
  Serial1.begin(115200); // we need this separate port to talk to the Roomba
  startSafe(); // this command puts the roomba into hacking mode and will follow Asimov's Third Law
  waitToClean();
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

void dirtDetectFunction() {
  ledState.powerBrightness = RoombaState.dirtDetect;

  if (RoombaState.dirtDetect > 100) {
    allLightsStateTrue();
    Serial.println("DIRTY");
  } else  {
    allLightsStateFalse();
    Serial.println("clean");
  }

  updateLeds();
}

void loop() {
  updateLeds();
  updateRoombaState(); // you MUST call this in your program loops to know what the Roomba is doing
  dirtDetectFunction();

  if (RoombaState.dockButton) {
    exitRoomba();
  }
}