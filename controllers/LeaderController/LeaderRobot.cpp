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
#include <iostream>
#include <string>



// All the webots classes are defined in the "webots" namespace
using namespace webots;


LeaderRobot::LeaderRobot() 
  : BaseRobot(), keyActive {keyboardCheck()}, 
     frontLeftMotor{getMotor("front left wheel motor")},
	   frontRightMotor{getMotor("front right wheel motor")},
	   rearLeftMotor{getMotor("rear left wheel motor")},
	   rearRightMotor{getMotor("rear right wheel motor")},
     lidar{getLidar("lidar")}{
      rearLeftMotor->setPosition(INFINITY);
      rearRightMotor->setPosition(INFINITY);
      frontLeftMotor->setPosition(INFINITY);
      frontRightMotor->setPosition(INFINITY);
      lidar->enable(TIME_STEP);
      
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
  bool stop  {false};
  move(0);
  rotate(0);
  scanLidarData();
  rotate(0);
  int rob {0};
  while (ooi.size() != 0) {
    sendMessage(std::to_string(3 - (rob % 3) ), std::to_string(ooi[ooi.size() - 1].first), std::to_string(ooi[ooi.size() - 1].second));
    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "Target pose x:<" << std::to_string(ooi[ooi.size() - 1].first) << "> y:<" << std::to_string(ooi[ooi.size() - 1].second) << "> sent to robot <" << std::to_string(3 - (rob % 3) ) << ">\n";
    std::cout << "Target pose x:<" << std::to_string(ooi[ooi.size() - 1].first) << "> y:<" << std::to_string(ooi[ooi.size() - 1].second) << "> sent to robot <" << std::to_string(3 - (rob % 3) ) << ">\n";
    ooi.pop_back();
    rob++;
  }
  move(0);
  while (step(TIME_STEP) != -1 && stop == false) {
    std::pair<std::string, std::string> inbox {receiveMessage()};
    if (inbox.first != "") {

        //std::cout << "HERE\n";
        //std::cout << "new coords for robot: " << ID  << ": " << inbox.first << ", " << inbox.second << "\n";
        
        targetPositionX = std::stod(inbox.first);
        targetPositionY = std::stod(inbox.second);
       // std::cout << "new coords for robot: " << ID  << ": " << targetPositionX << ", " << targetPositionY << "\n";
        stop = true;
    }
    move(0);
  }
  moveToTarget(1);
  while (step(TIME_STEP) != -1) {
    move(0);
  }
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

void LeaderRobot::moveTarget(stopDistance) {
    while (step(TIME_STEP) != -1 && abs(currentYaw - targetYaw) >= 1 ) {
        updateCurrentPosition();
        rotate(0.5);
    }
    while (step(TIME_STEP) != -1 && distance() >= stopDistance) {
        updateCurrentPosition();
        //std::cout << "distance: " << distance() << "\n";
        move(6);
    }
}

void LeaderRobot::scanLidarData() {
  rotate(1);
  int steps {310};
  bool oi = true;
  for (int i {0}; i < steps && step(TIME_STEP) != -1; i++) {
    auto out {lidar->getRangeImage()};
    
    if (*out != INFINITY && oi == true) {
      updateCurrentPosition();
      std::pair<double, double> newOoi;
      if (currentYaw >= 0 && currentYaw < 90) {
        newOoi.first = *out * sin(currentYaw * PI/180) + currentPositionX;
        newOoi.second = *out * cos(currentYaw * PI/180) + currentPositionY;
      }
      else if (currentYaw >= 90 && currentYaw < 180) {
        newOoi.first = *out * cos((currentYaw - 90) * PI/180) + currentPositionX;
        newOoi.second = *out * sin((currentYaw - 90) * PI/180) * -1 + currentPositionY;
      }
      else if (currentYaw >= 180 && currentYaw < 270) {
        newOoi.first = *out * sin((currentYaw - 180) * PI/180) * -1 + currentPositionX;
        newOoi.second = *out * cos((currentYaw - 180) * PI/180) * -1 + currentPositionY;
      }
      else if (currentYaw >= 270 && currentYaw <= 360) {
        newOoi.first = *out * sin((360 - currentYaw ) * PI/180) * -1 + currentPositionX;
        newOoi.second = *out * cos((360 - currentYaw) * PI/180) + currentPositionY;
      }
    
      ooi.push_back(newOoi);
      std::ofstream outputFile("output.txt", std::ios::app);
      outputFile << "OOI discovered at x:<" << newOoi.first << "> y:<" << newOoi.second << ">\n";
      std::cout << "OOI discovered at x:<" << newOoi.first << "> y:<" << newOoi.second << ">\n";
      targetPositionX = newOoi.first;
      targetPositionY = newOoi.second;
      oi = false;
      //std::cout << "Lidar distance: " << *out << "\n";
      //std::cout << "position (" << currentPositionX << ", " << currentPositionY << ")\n";
      //std::cout << "Heading: " << currentYaw << "\n";
    }
    else if (*out == INFINITY){
      oi = true;
    }
    //updateCurrentPosition();
     //std::cout << "Lidar distance: " << *out << "\n";
      //std::cout << "position (" << currentPositionX << ", " << currentPositionY << ")\n";
      //std::cout << "Heading: " << currentYaw << "\n";
  }
  rotate(0);
  
}
void fileOutput(const std::string& output);
// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node

  // Enter here exit cleanup code.