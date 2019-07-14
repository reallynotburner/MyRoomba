/**
 * The floor cliff sensors read a value from 0 to 4096
 * So they are sending an infrared beam out and measuring the brightness 
 * of the reflection from the floor.  When it gets very low reflection,
 * the floor is missing, therefore that's a cliff to avoid falling from.
 */
#include "MyRoomba.h"

void setup() {
  Serial.begin(115200); // use this port to read out debugging data from the Roomba
  Serial1.begin(115200); // we need this separate port to talk to the Roomba
  startSafe(); // this command puts the roomba into hacking mode and will follow Asimov's Third Law
  updateLeds();
}

void exitRoomba() { // it's over
  stop(); // call stop, returning Roomba back to normal consumer operation, startSafe() will go back into hack mode
  while (true) {} // INFINITE LOOP!
}

void loop() {
  updateRoombaState(); // you MUST call this in your program loops to know what the Roomba is doing

  Serial.print("Analog Cliff Left: ");
  Serial.print(RoombaState.cliffAnalogLeft);
  Serial.print(" Front Left: ");
  Serial.print(RoombaState.cliffAnalogFrontLeft);
  Serial.print(" Front Right: ");
  Serial.print(RoombaState.cliffAnalogFrontRight);
  Serial.print(" Right: ");
  Serial.println(RoombaState.cliffAnalogRight);
}