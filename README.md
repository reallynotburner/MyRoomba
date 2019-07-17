# MyRoomba

I needed a quick Arduino library for a Roomba 650 based project. The specification is: 
[Roomba Open Interface](https://www.irobotweb.com/~/media/MainSite/PDFs/About/STEM/Create/iRobot_Roomba_600_Open_Interface_Spec.pdf).  The significant prior art is [Apocrathia's thorough library](https://github.com/Apocrathia/Roomba).  It didn't work with Arduino Leonardo and Roomba 650, so I made my simpler version.  This was tested with a Roomba 650.  You'll have to modify it to work with Roomba 400 series, like the Roomba Discovery.  I'll let you figure out how that's done.

## Usage
See examples folder for how to use this library to do a few simple tasks.

## Methods
* updateRoombaState() so you can access current RoombaState.values
* driveDirect(velocityRight, velocityLeft)
* drivePWM(torqueRight, torqueLeft)
* driveStandard(velocity, radius)
* playSong()
* setupSong()
* startSafe() 
* startFull() -> will viloate Asimov's Third Law!
* stop()
* updateLeds()

## Structs
+ RoombaState
  + bool bumperRight;
  + bool bumperLeft;
  + bool wheelDropRight;
  + bool wheelDropLeft;
  + bool cliffLeft;
  + bool cliffFrontLeft;
  + bool cliffFrontRight;
  + bool cliffRight;
  + bool cleanButton;
  + bool spotButton;
  + bool dockButton;
  + bool dayButton;
  + bool hourButton;
  + bool minuteButton;
  + bool scheduleButton;
  + bool clockButton;
  + long int distance;
  + long int angle;
  + long int distance;
  + long int angle;
  + float batteryVoltage;
  + uint16_t cliffAnalogLeft;
  + uint16_t cliffAnalogFrontLeft;
  + uint16_t cliffAnalogFrontRight;
  + uint16_t cliffAnalogRight;
  + byte lightBumpers; // this is all the light bumpers together
  + bool lightBumperLeft;
  + bool lightBumperFrontLeft;
  + bool lightBumperCenterLeft;
  + bool lightBumperCenterRight;
  + bool lightBumperFrontRight;
  + bool lightBumperRight;
  
  To use:
  ```
    updateRoombaState();
    if (RoombaState.distance >= 1000) { // travelled a meter?  Good Job!
      RoombaState.distance = 0;  // let's reset that value
      driveStandard(0, 0); // and then put the brakes on
    }
    ```
};

* ledState
  + check, boolean, the red exclamation light that makes you worry about your Roomba
  + debris, boolean, blue light that let's you know your floor is chunky
  + dock, boolean friendly green light that says "dock"
  + powerBrightness, byte, the center button's light, like the MAIN Roomba user interface
  + powerColor, byte, 0 is green, 128 is orange, 255 is red, and anything in between
  + To use:
  ```
    // turns on the debris light
    ledState.debris = true;
    // make sure to update the led's to make it real
    udpateLeds();
    ```

## FAQ
* Roomba doesn't go!  What do I do?
  + All the example programs here need the Roomba to be on to work.  So the green light in the center needs to be on.  A quick press of the center button will take the Roomba from being in the "off" state and into the "on" state.  You can hit the reset button on the Arduino and after 8 seconds, it will run it's program again.
  + Verify that you are wired up correctly.  V+ of the Roomba needs to go to Vin of the Arduino.  V- goes to any of the Arduino GND pins.  The TX of the Arduino's Serial1 port goes to the RX of the Roomba.  The RX of the Arduino goes to the TX of the Roomba.  Sounds backwards but it's like a telephone.  My mouth speakig (TX) goes to your ear receiving (RX) and vice versa.

## TODO's
* move the Roomba to a class, that would remove the global functions and apply them to Roomba scope
