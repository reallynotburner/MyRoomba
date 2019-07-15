# MyRoomba

I needed a quick Arduino library for a Roomba based project. The spec is : 
[Roomba Open Interface](https://www.irobotweb.com/~/media/MainSite/PDFs/About/STEM/Create/iRobot_Roomba_600_Open_Interface_Spec.pdf).  The significant prior art is [Apocrathia's thorough library](https://github.com/Apocrathia/Roomba).  It didn't work with Arduino Leonardo and Roomba 650, so I made my simpler version.

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

## TODO's
* move the Roomba to a class, that would remove the global functions and apply them to Roomba scope
