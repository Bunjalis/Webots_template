// File:          my_controller.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include "ScoutRobot.hpp"
#include <iostream>



// All the webots classes are defined in the "webots" namespace
using namespace webots;


ScoutRobot::ScoutRobot() 
  : BaseRobot(),
     leftMotor{getMotor("left wheel motor")},
	   rightMotor{getMotor("right wheel motor")},
	   camera{getCamera("camera")},
       distanceSensor{getDistanceSensor("distance")}{
      leftMotor->setPosition(INFINITY);
      rightMotor->setPosition(INFINITY);
      camera->enable(TIME_STEP);
      distanceSensor->enable(TIME_STEP);
     }

     

ScoutRobot::~ScoutRobot(){};

void ScoutRobot::run() {

  move(0);
  rotate(0);
  bool stop {false};
  while (step(TIME_STEP) != -1 && stop == false) {
    std::pair<std::string, std::string> inbox {receiveMessage()};
    if (inbox.first != "") {

        //std::cout << "HERE\n";
        //std::cout << "new coords for robot: " << ID  << ": " << inbox.first << ", " << inbox.second << "\n";
        targetPositionX = std::stod(inbox.first);
        targetPositionY = std::stod(inbox.second);
        //std::cout << "new coords for robot: " << ID  << ": " << targetPositionX << ", " << targetPositionY << "\n";
        stop = true;
    }
    
  }
  moveToTarget(0.5);
  move(0);
  bool green {readColour()};
  if(green == true) {
    sendMessage("0", std::to_string(targetPositionX), std::to_string(targetPositionY));
  }
  while (step(TIME_STEP) != -1) {
    move(0);
  }
};

void ScoutRobot::move(double speed) {
  leftMotor->setVelocity(speed);
  rightMotor->setVelocity(speed);
  
};

void ScoutRobot::rotate(double speed) {
  leftMotor->setVelocity(-speed);
  rightMotor->setVelocity(speed);
}

void ScoutRobot::moveTarget(stopDistance) {
    while (step(TIME_STEP) != -1 && abs(currentYaw - targetYaw) >= 1 ) {
        updateCurrentPosition();
        rotate(0.5);
    }
    while (step(TIME_STEP) != -1 && distance() >= stopDistance) {
        updateCurrentPosition();
        //std::cout << "distance: " << distance() << "\n";
        move(6);
        if (distanceSensor->getMinValue <= 0.3) {
          int steps {90};
          for (int i {0}; i < steps && step(TIME_STEP) != -1 && i <; i++) {
            rotate(1);
          }
          steps = 90;
          for (int i {0}; i < steps && step(TIME_STEP) != -1 && i <; i++) {
            rotate(0);
            move(3);
          }
          moveToTarget(0.5);
        }
    }
}


bool ScoutRobot::readColour () {
    //std::cout << "CHECKING COLOUR\n";
    camera->recognitionEnable(TIME_STEP);
    if (camera->getRecognitionNumberOfObjects() != 0) {
        //std::cout << "COLOUR = GREEN\n";
        return 1;
    }
    else {
        //std::cout << "COLOUR = RED\n";
        return 0;
    }
}
// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node

  // Enter here exit cleanup code.