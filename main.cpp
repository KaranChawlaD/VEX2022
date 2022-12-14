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
motor armMotor = motor(PORT3, ratio36_1, false);

motor LeftDriveSmart = motor(PORT4, ratio6_1, false);
motor RightDriveSmart = motor(PORT5, ratio6_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 317.5, 117.475, mm, 1);

motor FlyWheelMotorA = motor(PORT1, ratio6_1, false);
motor FlyWheelMotorB = motor(PORT2, ratio6_1, true);
motor_group FlyWheel = motor_group(FlyWheelMotorA, FlyWheelMotorB);




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
competition Competition;

void armSpinForward() {armMotor.setVelocity(100, percent);}
void armSpinStop() {armMotor.setVelocity(0, percent);}
void armSpinReverse() {armMotor.setVelocity(-100, percent);}
void flyWheelForward() {FlyWheel.setVelocity(100, percent); FlyWheel.spin(forward);}
void flyWheelStop() {FlyWheel.stop();}

void runOnAutonomous(void) {
  Brain.Screen.print("Running auto");

  armSpinForward();
  armMotor.spin(forward);
  Drivetrain.driveFor(forward, 24, inches);
  Drivetrain.turnFor(right, 210, degrees);
  armSpinStop();
  armMotor.spin(forward);
  flyWheelForward();
  wait (1, seconds);
  armSpinForward();
  armMotor.spin(forward);
  wait (3, seconds);
  flyWheelStop();
  Drivetrain.turnFor(left, 210, degrees);
  Drivetrain.driveFor(forward, 4, inches);
  Drivetrain.turnFor(right, 230, degrees);
  armSpinStop();
  armMotor.spin(forward);
  flyWheelForward();
  wait (1, seconds);
  armSpinForward();
  armMotor.spin(forward);
  wait (3, seconds);
  flyWheelStop();
  armSpinStop();
  armMotor.spin(forward);
}

void runOnDriverControl(void) {
  Brain.Screen.print("Running teleop");
  armMotor.setVelocity(0, percent);

  while (true) {

    //drivetrain
    if (Controller1.Axis3.position() > 0.0) {
      LeftDriveSmart.setVelocity((Controller1.Axis3.position() + Controller1.Axis4.position())/1.5, percent);
      RightDriveSmart.setVelocity((Controller1.Axis3.position() - Controller1.Axis4.position())/1.5, percent);
    }

    else {
      RightDriveSmart.setVelocity((Controller1.Axis3.position() + Controller1.Axis4.position())/1.5, percent);
      LeftDriveSmart.setVelocity((Controller1.Axis3.position() - Controller1.Axis4.position())/1.5, percent);
    }
    
    LeftDriveSmart.spin(forward);
    RightDriveSmart.spin(forward); 
    
    
    //arm motor
    Controller1.ButtonR1.pressed(armSpinForward);
    Controller1.ButtonR1.released(armSpinStop);
    Controller1.ButtonL1.pressed(armSpinReverse);
    Controller1.ButtonL1.released(armSpinStop);

    armMotor.spin(forward);

    //flywheel
    Controller1.ButtonR2.pressed(flyWheelForward);
    Controller1.ButtonR2.released(flyWheelStop);

    // flyWheelForward();
  }

}

int main() {
  
  // runOnAutonomous();
  // Competition.autonomous(runOnAutonomous);
  Competition.drivercontrol(runOnDriverControl);

  while (true) {
    wait(0.05, seconds);
  }

}
