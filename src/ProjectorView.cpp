#include "ProjectorView.h"

void ProjectorView::setup()
{
	_SkeletonHandler.setDisplay(true);
}

//--------------------------------------------------------------
void ProjectorView::update()
{
	
}

//--------------------------------------------------------------
void ProjectorView::draw()
{
	_SkeletonHandler.drawSkeleton();
}

//--------------------------------------------------------------
void ProjectorView::keyPressed(int key)
{
	ofPoint StartPos_ = _SkeletonHandler.getStartPos();
	float fScale_ = _SkeletonHandler.getScale();

	switch(key)
	{
	//Translate
	case OF_KEY_UP:
		StartPos_.set(StartPos_.x, StartPos_.y - 1);
		_SkeletonHandler.setStartPos(StartPos_);
		break;
	case OF_KEY_DOWN:
		StartPos_.set(StartPos_.x, StartPos_.y + 1);
		_SkeletonHandler.setStartPos(StartPos_);
		break;
	case OF_KEY_LEFT:
		StartPos_.set(StartPos_.x - 1, StartPos_.y);
		_SkeletonHandler.setStartPos(StartPos_);
		break;
	case OF_KEY_RIGHT:
		StartPos_.set(StartPos_.x + 1, StartPos_.y);
		_SkeletonHandler.setStartPos(StartPos_);
		break;

	//Scale
	case '1':
		if( (fScale_ - 0.05) >= .0)
		{
			_SkeletonHandler.setScale(fScale_ - 0.05);
		}
		break;
	case '2':
		_SkeletonHandler.setScale(fScale_ + 0.05);
		break;
	}
}

//--------------------------------------------------------------
void ProjectorView::setJoint(bool bHaveUser, ofVec2f (&Joints)[JointType_Count])
{
	_SkeletonHandler.updateSkeleton(bHaveUser, Joints);
}