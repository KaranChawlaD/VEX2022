#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
controller Controller1 = controller(primary);
motor LeftMotor = motor(PORT1, ratio18_1, false);

motor RightMotor = motor(PORT2, ratio18_1, true);

motor armMotor = motor(PORT3, ratio6_1, false);




// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {Merivale High School}                                    */
/*    Created:      {11/23/2022}                                              */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;
// competition Competition;

// #define armSpinForward armMotor.setVelocity(100, percent)

void armSpinForward() {
  armMotor.setVelocity(100, percent);
}

void armSpinStop() {
  armMotor.setVelocity(0, percent);
}

void armSpinReverse() {
  armMotor.setVelocity(-100, percent);
}

void runOnAutonomous() {
  Brain.Screen.print("Running auto");

}

void runOnDriverControl() {
  Brain.Screen.print("Running teleop");
  armMotor.setVelocity(0, percent);

  while (true) {

    //drivetrain
    LeftMotor.setVelocity((Controller1.Axis3.position() + Controller1.Axis4.position()), percent);
    RightMotor.setVelocity((Controller1.Axis3.position() - Controller1.Axis4.position()), percent);
    LeftMotor.spin(forward);
    RightMotor.spin(forward); 

    //arm motor

    Controller1.ButtonR1.pressed(armSpinForward);
    Controller1.ButtonR1.released(armSpinStop);
    Controller1.ButtonL1.pressed(armSpinReverse);
    Controller1.ButtonL1.released(armSpinStop);
    armMotor.spin(forward);

  }

}

int main() {

  // runOnAutonomous();
  runOnDriverControl();

  while (true) {
    wait(0.05, seconds);
  }

}
