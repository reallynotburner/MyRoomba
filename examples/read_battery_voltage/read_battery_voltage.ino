/**
 * reading out battery voltage
 * view serial monitor,
 * There are 12 cells at a nominal 1.2 volts each, so 14.4 is very good
 * A fully charged battery should be almost 18 volts!
 * 10.8 volt is very very low, charge the roomba immediately!
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

  Serial.print("Battery Voltage: ");
  Serial.println(RoombaState.batteryVoltage);

  if (RoombaState.dockButton) {
    exitRoomba();
  }
}