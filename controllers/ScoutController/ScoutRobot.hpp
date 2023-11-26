
#include "../BaseRobot/BaseRobot.hpp"
#include <webots/Camera.hpp>
#include <webots/distanceSensor.hpp>


class ScoutRobot : public BaseRobot {
public:
    ScoutRobot();
    ~ScoutRobot();

    virtual void run() override;
    virtual void move(double speed) override;
    virtual void rotate(double speed) override;

    bool readColour();

protected:


	// add additional members as needed
  
private:

	std::unique_ptr<webots::Motor> leftMotor{};
    std::unique_ptr<webots::Motor> rightMotor{};

    std::unique_ptr<webots::Camera> camera{};
    std::unique_ptr<webots::DistanceSensor> distanceSensor{};
	// add additional members as needed
	// test to make sure github is working properly
	// a second test to make sure all is working smoothly
	// one last test to make everything perfect
};