#pragma once

#include "constParameter.h"
#include "AirwavesTheatre.h"


class AirwavesApp: public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	float	_fMainTimer;
	ofImage	_TmpBG;
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
};
