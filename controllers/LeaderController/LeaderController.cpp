#include "LeaderRobot.hpp"



int main(int argc, char **argv) {
	
	LeaderRobot* newBot = new LeaderRobot();
	webots::Keyboard kb;

	// newBot->frontLeftMotor->setPosition(INFINITY);
	// newBot->frontRightMotor->setPosition(INFINITY);
	// newBot->rearLeftMotor->setPosition(INFINITY);
	// newBot->rearRightMotor->setPosition(INFINITY);

	kb.enable(TIME_STEP);
	


	while (newBot->step(TIME_STEP) != -1) {
  
		int key = kb.getKey();

		if (key == 87){
			newBot->move(3);
		}
		else if (key == 83){
			newBot->move(-3);
		}
		else if (key == 68) {
			newBot->rotate(3);
		}
		else if (key == 65){
			newBot->rotate(-3);
		}
		else {
			newBot->move(0);
		}
  	};
}