#include "AirwavesApp.h"

#pragma region Base method
//--------------------------------------------------------------
void AirwavesApp::setup()
{
	ofBackground(0);
	ofSetVerticalSync(true);

	//Theatre
	this->initTheatre();
	
	//Connector
	_Connector.initConnector("127.0.0.1", 5566, 2233);
	ofAddListener(_Connector.AirwavesConnectorEvent, this, &AirwavesApp::onConnectorEvent);

	_fMainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void AirwavesApp::update()
{
	float fDelta_ = ofGetElapsedTimef() - _fMainTimer;
	_fMainTimer += fDelta_;
	
	//Theatre
	_Theatre.updateTheatre(fDelta_);

	//Connector
	_Connector.updateConnector();

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void AirwavesApp::draw()
{
	this->drawBeforeTheatre();
	_Theatre.drawTheatre();
	this->drawAfterTheatre();
}

//--------------------------------------------------------------
void AirwavesApp::exit()
{
}

//--------------------------------------------------------------
void AirwavesApp::keyPressed(int key)
{
	switch(key)
	{
	case 'n':
		{
			_Theatre.nextScence();
			break;
		}
	case 's':
		{
			_Connector.sendCMD(eCONNECTOR_CMD::eD2P_CHARACTOR, "D2P");
			break;
		}

	}
}
#pragma endregion

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
	if(e == NAME_MGR::S_Teching)
	{
		//TODO:start kinect
	}
	else if(e == NAME_MGR::S_Upload)
	{
		//TODO:stop kinect
	}
}

#pragma endregion

#pragma region Connector

void AirwavesApp::onConnectorEvent(string& e)
{
	cout<<e<<endl;
}

#pragma endregion
