// File:          robooooot.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/Keyboard.hpp>

// All the webots classes are defined in the "webots" namespace
using namespace webots;

#define TIME_STEP 64
#define MAX_SPEED 6
// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();
  Motor *leftMotor = robot->getMotor("left wheel motor");
  Motor *rightMotor = robot->getMotor("right wheel motor");
  Keyboard kb;
  
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);

  // get the time step of the current world.
  //int timeStep = (int)robot->getBasicTimeStep();

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  //  Motor *motor = robot->getMotor("motorname");
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  kb.enable(TIME_STEP);
  double leftSpeed {0};
  double rightSpeed {0};

  while (robot->step(TIME_STEP) != -1) {
  
  int key = kb.getKey();

  if (key == 87){
    leftSpeed = 3;
    rightSpeed = 3;
  }
  else if (key == 83){
  leftSpeed = -3;
  rightSpeed = -3;
  }
  else if (key == 68) {
    leftSpeed = 3;
    rightSpeed = -3;
  }
  else if (key == 65){
    leftSpeed = -3;
    rightSpeed = 3;
  }
  else {
  leftSpeed = 0;
  rightSpeed = 0;
  }
  
  
 
  leftMotor->setVelocity(leftSpeed);
  rightMotor->setVelocity(rightSpeed);
  
    // Read the sensors:
    // Enter here functions to read sensor data, like:
    //  double val = ds->getValue();
  
    // Process sensor data here.

    // Enter here functions to send actuator commands, like:
    //  motor->setPosition(10.0);
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
