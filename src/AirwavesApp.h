#pragma once

#include "constParameter.h"
#include "AirwavesTheatre.h"
#include "AirwavesConnector.h"

#include "ofxCTKinectV2.h"

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
//Connector
//-------------------------------------------------
public:
	void onConnectorEvent(string& e);
private:
	AirwavesConnector	_Connector;
};
