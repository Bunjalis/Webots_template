
#include "../BaseRobot/BaseRobot.hpp"

class LeaderRobot : public BaseRobot {
public:
    LeaderRobot();
    virtual ~LeaderRobot();

    bool keyboardCheck();
    void keyboard();
    virtual void run() override;
    virtual void move(double speed) override;
    virtual void rotate(double speed) override;

    void scanLidarData();
    void fileOutput(const std::string& output);

protected:
    bool keyActive;

	// add additional members as needed
  
private:

    std::unique_ptr<webots::Motor> frontLeftMotor{};
    std::unique_ptr<webots::Motor> frontRightMotor{};
    std::unique_ptr<webots::Motor> rearLeftMotor{};
    std::unique_ptr<webots::Motor> rearRightMotor{};

   

	// add additional members as needed
	// test to make sure github is working properly
	// a second test to make sure all is working smoothly
	// one last test to make everything perfect
};