# MyRoomba

I needed a quick Arduino library for a Roomba based project. The spec is : 
[Roomba Open Interface](https://www.irobotweb.com/~/media/MainSite/PDFs/About/STEM/Create/iRobot_Roomba_600_Open_Interface_Spec.pdf).  The significant prior art is [Apocrathia's thorough library](https://github.com/Apocrathia/Roomba).  It didn't work with Arduino Leonardo and Roomba 650, so I made my simpler version.

## Methods
* driveDirect(velocityRight, velocityLeft)
* drivePWM(torqueRight, torqueLeft)
* driveStandard(velocity, radius)
* playSong()
* setupSong()
* startSafe() 
* stop()
* updateLeds()

## Structs
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
* Add means to read out Roomba sensor / state, bumpers, battery, odometry
* restructure the project so it can be consumed by the Arduino IDE auto-registration