#ifndef AIRWAVE_PROJECTOR_VIEW
#define AIRWAVE_PROJECTOR_VIEW

#include "constParameter_projector.h"
#include "SkeletonHandler.h"

class ProjectorView
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	void setJoint(bool bHaveUser, ofVec2f (&Joints)[JointType_Count]);

private:
	SkeletonHandler		_SkeletonHandler;

};

#endif // !AIRWAVE_PROJECTOR_VIEW
