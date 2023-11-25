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
  : BaseRobot(), keyActive {keyboardCheck()}, 
     frontLeftMotor{getMotor("front left wheel motor")},
	   frontRightMotor{getMotor("front right wheel motor")},
	   rearLeftMotor{getMotor("rear left wheel motor")},
	   rearRightMotor{getMotor("rear right wheel motor")}{
      rearLeftMotor->setPosition(INFINITY);
      rearRightMotor->setPosition(INFINITY);
      frontLeftMotor->setPosition(INFINITY);
      frontRightMotor->setPosition(INFINITY);
      
     }



  bool LeaderRobot::keyboardCheck() {
    std::ifstream inputFile("KeyboardConfig.txt");
    std::string line;
    std::string strTrue {"keyboardControl=true"};
    std::string strFalse {"keyboardControl=false"};
    std::getline(inputFile, line);

    if ( line == strTrue) {
        return true;
    }
    else if (line == strFalse) {
        return false;
    }
    else {
        std::cout << "wrong text in KeyboardConfig.txt\n";
        return false;
    }
  }
     

LeaderRobot::~LeaderRobot(){};

void LeaderRobot::keyboard() {
  webots::Keyboard kb;
	kb.enable(TIME_STEP);
	while (step(TIME_STEP) != -1) {
  
		int key = kb.getKey();

		if (key == 87){
			move(3);
		}
		else if (key == 83){
			move(-3);
		}
		else if (key == 68) {
			rotate(-3);
		}
		else if (key == 65){
			rotate(3);
		}
		else {
			move(0);
		}
  	};
}

void LeaderRobot::run() {
  if (keyActive == true) {
    keyboard();
    return;
  }
  while (step(TIME_STEP) != -1) {
  rearLeftMotor->setVelocity(-3);
  rearRightMotor->setVelocity(3);
  frontLeftMotor->setVelocity(-3);
  frontRightMotor->setVelocity(3);
		
		
  	};
};

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