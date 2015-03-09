#include "AirwavesApp.h"

#pragma region Base method
//--------------------------------------------------------------
void AirwavesApp::setup()
{
	ofBackground(0);
	ofSetVerticalSync(true);

	//Theatre
	this->initTheatre();

	//Kinect
	if(!this->initKinect())
	{
		ofLog(OF_LOG_ERROR, "Initial Kinect failed");
		getchar();
		std::exit(1);
	}

	//Projector
	_ProjectorView.setup();
	
	_fMainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void AirwavesApp::update()
{
	float fDelta_ = ofGetElapsedTimef() - _fMainTimer;
	_fMainTimer += fDelta_;
	
	//Theatre
	_Theatre.updateTheatre(fDelta_);

	//Kinect
	this->updateKinect();

	//Projector
	_ProjectorView.update();

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void AirwavesApp::draw()
{
	this->drawBeforeTheatre();
	_Theatre.drawTheatre();
	this->drawAfterTheatre();

	//Projector
	this->drawKinect();
	_ProjectorView.draw();
}

//--------------------------------------------------------------
void AirwavesApp::exit()
{
	this->stopKinect();
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
	case 'k':
		{
			if(_Kinect.isThreadRunning())
			{
				_Kinect.stopThread();
			}
			else
			{
				_Kinect.startThread();
			}
			break;
		}
	}

	_ProjectorView.keyPressed(key);
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
		this->drawKinect();
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
		this->startKinect();
	}
	else if(e == NAME_MGR::S_Upload)
	{
		this->stopKinect();
	}
}

#pragma endregion

#pragma region Kinect
//-------------------------------------------------
//Kinect
bool AirwavesApp::initKinect()
{
	bool bResult_ = _Kinect.initialKinectV2();
	
	if(bResult_)
	{
		_bHaveUser = false;
		_Kinect.enableSkeleton();
		_Kinect.enableColorFrame();
	}

	return bResult_;
}

//-------------------------------------------------
void AirwavesApp::updateKinect()
{
	if(!_Kinect.isThreadRunning())
	{
		return;
	}

	_bHaveUser = _Kinect.getSkeleton(_Skeleton);
	_Kinect.getColorFrame(_ColorFrame);

	_ProjectorView.setJoint(_bHaveUser, _Skeleton.aJoints);
}

//-------------------------------------------------
void AirwavesApp::drawKinect()
{
	if(!_Kinect.isThreadRunning())
	{
		return;
	}

	ofPushStyle();
	{
		ofSetColor(255);
		if(_ColorFrame.isAllocated())
		{
			_ColorFrame.draw(0, 0, cWINDOW_WIDTH, cWINDOW_HEIGHT);
		}
	}
	ofPopStyle();
}

//-------------------------------------------------
void AirwavesApp::startKinect()
{
	if(!_Kinect.isThreadRunning())
	{
		_Kinect.startThread();
	}
};

//-------------------------------------------------
void AirwavesApp::stopKinect()
{
	if(_Kinect.isThreadRunning())
	{
		_Kinect.stopThread();
		_bHaveUser = false;
	}
}
#pragma endregion
