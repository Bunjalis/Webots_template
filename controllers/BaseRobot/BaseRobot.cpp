// File:          BaseRobot.cpp
// Date:          XX/XX/XXXX
// Description:   Implementation of BaseRobot to be inherited by the Leader and Scout robots classes.
// Author:        XXX XXX
// zID:           z1234567
// Modifications:

#include "BaseRobot.hpp"

BaseRobot::BaseRobot()
    : ID{ getName() }
    , receiver{ getReceiver("receiver") }
    , emitter{ getEmitter("emitter") }
    , gps{getGPS("gps")}
    , compass{getCompass("compass")} {
    receiver->enable(TIME_STEP), gps->enable(TIME_STEP), compass->enable(TIME_STEP);
}

BaseRobot::~BaseRobot(){};

void keyboardControl();



void BaseRobot::updateCurrentPosition() {
    currentPositionX = gps->getValues()[1];
    currentPositionY = -1 * gps->getValues()[0];
    currentYaw = bearing();
}



void BaseRobot::setTargetPosition(double x, double y){
    targetPositionX = x;
    targetPositionY = y;
}

bool BaseRobot::moveToTarget(double stopDistance) {
    getHeading();
    // std::cout << "robot: " << ID << "has a targe"<<"\n";
    // std::cout << "current yaw is: " << currentYaw << "\n";
    //std::cout << "robot: " << ID << " target yaw is: " << targetYaw << "\n";
    //std::cout <<"robot: " << ID << " current yaw is: " << currentYaw << "\n";
    moveTarget(stopDistance);

    if (distance() < stopDistance) {
        return true;
    }
    else {
        return false;
    }
}

void BaseRobot::sendMessage(const std::string& ID, const std::string& data0, const std::string& data1) {
    std::cout << "Sending message to " << ID << std::endl;
    std::string message{};
    message.append(ID);
    message.append("|");
    message.append(data0);
    message.append("|");
    message.append(data1);
    emitter->send(message.c_str(), (int)strlen(message.c_str()) + 1);
}


std::pair<std::string, std::string> BaseRobot::receiveMessage() {
    if (receiver->getQueueLength() > 0) {
        std::string message{ static_cast<const char*>(receiver->getData()) };
        receiver->nextPacket();

        std::istringstream iss{ message };
        std::string incomingId{};
        std::getline(iss, incomingId, '|');

        if (ID.compare(incomingId) == 0) {
            // ID matches, now extract data0 and data1
            std::string data0{};
            std::string data1{};
            if (std::getline(iss, data0, '|') && std::getline(iss, data1, '|')) {
                std::cout << "Received message with matching ID: " << message << std::endl;
                return std::make_pair(data0, data1);
            }
        }
    }
    // If the ID doesn't match or the format is incorrect, return an empty pair
    return std::make_pair("", "");
}

double BaseRobot::bearing() {
  const double *north = compass->getValues();
  double rad = atan2(north[1], north[0]);
  double bearing = (rad - 1.5708) / PI * 180.0;
  if (bearing < 0.0) {
    bearing = bearing + 360.0;
  }
  return bearing;
}

double BaseRobot::distance() {
    double determinant {pow(currentPositionX - targetPositionX, 2) + pow(currentPositionY - targetPositionY, 2)};
    double res {sqrt(determinant)};
    return res;
}

void BaseRobot::getHeading() {
    updateCurrentPosition();
    if (targetPositionX >= currentPositionX && targetPositionY >= currentPositionY) {
        targetYaw = 180/PI * atan((targetPositionX - currentPositionX) / (targetPositionY - currentPositionY));
    }
    else if (targetPositionX < currentPositionX && targetPositionY < currentPositionY) {
        targetYaw = 180 + 180/PI * atan((currentPositionX - targetPositionX) / (currentPositionY - targetPositionY));
    }
    else if (targetPositionX >= currentPositionX && targetPositionY < currentPositionY) {
        targetYaw = 90 + 180/PI * atan((currentPositionY - targetPositionY) / (targetPositionX - currentPositionX));
    }
    else if (targetPositionX < currentPositionX && targetPositionY >= currentPositionY) {
        targetYaw = 360 - 180/PI * atan((currentPositionX - targetPositionX) / (targetPositionY - currentPositionY));
    }
    targetYaw = (targetYaw + 180);
    if (targetYaw >= 360) {
        targetYaw -= 360.0;
    }
}
