#pragma once

#include "constParameter.h"
#include "AirwavesTheatre.h"
#include "ofxCTKinectV2.h"
#include "ProjectorView.h"

class AirwavesApp: public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);

private:
	float	_fMainTimer;
//-------------------------------------------------
//Theatre
//-------------------------------------------------
public:
	void initTheatre();
	void drawBeforeTheatre();
	void drawAfterTheatre();
	void onTheatreEvent(string& e);

private:
	AirwavesTheatre		_Theatre;

//-------------------------------------------------
//Kinect
//-------------------------------------------------
public:
	bool initKinect();
	void updateKinect();
	void drawKinect();

	void startKinect();
	void stopKinect();

private:
	bool				_bHaveUser;
	stSCREEN_SKELETON	_Skeleton;
	CTKinectV2			_Kinect;
	ofImage				_ColorFrame;

//-------------------------------------------------
//Projector
//-------------------------------------------------
private:
	ProjectorView	_ProjectorView;
};
