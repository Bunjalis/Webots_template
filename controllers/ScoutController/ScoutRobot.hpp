
#include "BaseRobot.hpp"


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

	
	// add additional members as needed
	// test to make sure github is working properly
	// a second test to make sure all is working smoothly
	// one last test to make everything perfect
};