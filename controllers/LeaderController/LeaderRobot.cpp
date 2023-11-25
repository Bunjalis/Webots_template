// File:          my_controller.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include "LeaderRobot.hpp"



// All the webots classes are defined in the "webots" namespace
using namespace webots;


LeaderRobot::LeaderRobot() 
  : BaseRobot(), 
     frontLeftMotor{getMotor("front left wheel motor")},
	   frontRightMotor{getMotor("front right wheel motor")},
	   rearLeftMotor{getMotor("rear left wheel motor")},
	   rearRightMotor{getMotor("rear right wheel motor")}{
      
     }

    

LeaderRobot::~LeaderRobot(){};

void keyboardControl();

void run();

void LeaderRobot::move(double speed) {
  rearLeftMotor->setVelocity(speed);
  rearRightMotor->setVelocity(speed);
  frontLeftMotor->setVelocity(speed);
  frontRightMotor->setVelocity(speed);
};

void LeaderRobot::rotate(double speed) {
  rearLeftMotor->setVelocity(-speed);
  rearRightMotor->setVelocity(speed);
  frontLeftMotor->setVelocity(-speed);
  frontRightMotor->setVelocity(speed);
}

void scanLidarData();
void fileOutput(const std::string& output);
// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node

  // Enter here exit cleanup code.