
#include "BaseRobot.hpp"


class LeaderRobot : public BaseRobot {
public:
    LeaderRobot();
    ~LeaderRobot();

    virtual void run() override;
    virtual void move(double speed) override;
    virtual void rotate(double speed) override;

    void scanLidarData();
    void fileOutput(const std::string& output);

protected:


	// add additional members as needed
  
private:

	
	// add additional members as needed
	// test to make sure github is working properly
	// a second test to make sure all is working smoothly
	// one last test to make everything perfect
};