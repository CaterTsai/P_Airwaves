#pragma once

#include "constParameter.h"
#include "ofxCTKinectV2.h"
#include "ofxCTImageSequence.h"
#include "ofxCTSystemCaller.h"
#include "ofxXmlSettings.h"
#include "ofxHttpUtils.h"
#include "ofxAnimatableFloat.h"

#include "AirwavesTheatre.h"
#include "AirwavesConnector.h"
#include "AudioChecker.h"



class AirwavesApp: public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();
	void reset();
	void keyPressed(int key);

private:
	float	_fMainTimer;
	string	_UserID;
//-------------------------------------------------
//Theatre
//-------------------------------------------------
public:
	void initTheatre();
	void drawBeforeTheatre();
	void drawAfterTheatre();
	void onTheatreEvent(string& e);

public:
	inline void enableBackground()
	{
		if(!_AnimBGAlpha.isAnimating())
		{
			_AnimBGAlpha.animateFromTo(0, 255);
		}
	}

	inline void disableBackground()
	{
		if(!_AnimBGAlpha.isAnimating())
		{
			_AnimBGAlpha.animateFromTo(255, 0);
		}
	}

private:
	AirwavesTheatre		_Theatre;
	ofImage				_Background;
	ofxAnimatableFloat	_AnimBGAlpha;

//-------------------------------------------------
//Audio checker
//-------------------------------------------------
public:
	void onAudioEvent(bool& e);

private:
	AudioCheck	_MicChecker;

//-------------------------------------------------
//Image Recoder
//-------------------------------------------------
public:
	void setupImageRecoder();
	void updateImageRecoder();
	void drawImageRecoder();
	void drawCropRecoder();
	void saveImage();
	void setDisplay(bool bValue);
	void onImageRecoderEvent(string& e);
	
private:
	void processImg();
	void updateCropRect(ofPoint Center);
	void updateCropRect(float fUpdateScale);

private:
	bool				_bIsWebcamSetup;
	bool				_bDisplayWebcam;
	ofVideoGrabber		_Cam;

	bool				_bDrawCropRect;
	float				_fCropScale;
	ofRectangle			_CropRect;
	
	int					_iPictureCounter;

	ofxCTImageSequence	_ImageRecorder;

//-------------------------------------------------
//Video Create
//-------------------------------------------------
public:
	void startVideoCreate();
	void onVideoCreateEvent(string& e);
private:
	ofxCTSystemCaller	_VideoCreate;

//-------------------------------------------------
//Video Uploader
//-------------------------------------------------
public:
	void setupVideotUploader();
	void uploadVideo();
	void onHttpResponse(ofxHttpResponse& response);

private:
	ofxHttpUtils	_VideoUploader;

//-------------------------------------------------
//Connector
//-------------------------------------------------
public:
	void onConnectorEvent(pair<eCONNECTOR_CMD, string>& e);
private:
	AirwavesConnector	_Connector;

//-------------------------------------------------
//Config file
//-------------------------------------------------
public:
	void loadconfig();
	void saveconfig();

private:
	ofRectangle	_exCropRect;
	string		_exActionUrl;
};
