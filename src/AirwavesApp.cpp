#include "AirwavesApp.h"

//--------------------------------------------------------------
void AirwavesApp::setup()
{
	ofBackground(0);
	ofSetVerticalSync(true);

	//Theatre
	this->initTheatre();


	_TmpBG.loadImage("images/Temp.jpg");
	_fMainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void AirwavesApp::update()
{
	float fDelta_ = ofGetElapsedTimef() - _fMainTimer;
	_fMainTimer += fDelta_;

	_Theatre.updateTheatre(fDelta_);
}

//--------------------------------------------------------------
void AirwavesApp::draw()
{
	this->drawBeforeTheatre();
	_Theatre.drawTheatre();
	this->drawAfterTheatre();
}

//--------------------------------------------------------------
void AirwavesApp::keyPressed(int key)
{

	switch(key)
	{
	case 'n':
		{
			_Theatre.nextScence();
		}
	}
}

#pragma region Theatre
//-------------------------------------------------
//Theatre
//-------------------------------------------------
void AirwavesApp::initTheatre()
{
	_Theatre.setupTheatre();
	ofAddListener(_Theatre.AirwavesTheaterEvent, this, &AirwavesApp::onTheatreEvent);
}

//--------------------------------------------------------------
void AirwavesApp::drawBeforeTheatre()
{
	ofPushStyle();
	{
		ofSetColor(255);
		_TmpBG.draw(0, 0);
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void AirwavesApp::drawAfterTheatre()
{
}

//--------------------------------------------------------------
void AirwavesApp::onTheatreEvent(string& e)
{
}
#pragma endregion


