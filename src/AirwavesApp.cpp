#include "AirwavesApp.h"

#pragma region Base method
//--------------------------------------------------------------
void AirwavesApp::setup()
{
	ofBackground(0);
	ofSetVerticalSync(true);

	//Config
	this->loadconfig();

	//Image Recoder
	this->setupImageRecoder();

	//Theatre
	this->initTheatre();
	
	//Audio
	_MicChecker.setup();
	ofAddListener(_MicChecker._AudioEvent, this, &AirwavesApp::onAudioEvent);
	_MicChecker.setCheck(true);

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
	
	//Image Reocder
	this->updateImageRecoder();

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

	//Debug
	this->drawCropRecoder();
}

//--------------------------------------------------------------
void AirwavesApp::exit()
{
	_ImageRecorder.exit();
}

//--------------------------------------------------------------
void AirwavesApp::reset()
{
	//reset picture conuter
	_iPictureCounter = 0;

	//open micphone checker
	_MicChecker.setCheck(true);
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
	case 'd':
		{
			if(_Theatre._Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_Start)
			{
				_bDrawCropRect ^= true;
			}
		}
		break;
	case '1':
		{
			if(_bDrawCropRect)
			{
				this->updateCropRect(1.05);
			}
		}
		break;
	case '2':
		{
			if(_bDrawCropRect)
			{
				this->updateCropRect(0.95);
			}
		}
		break;
	case OF_KEY_LEFT:
		{
			if(_bDrawCropRect)
			{
				ofPoint Pos_ = _CropRect.getCenter();
				Pos_.x -= 2;
				this->updateCropRect(Pos_);
			}
		}
		break;
	case OF_KEY_RIGHT:
		{
			if(_bDrawCropRect)
			{
				ofPoint Pos_ = _CropRect.getCenter();
				Pos_.x += 2;
				this->updateCropRect(Pos_);
			}
		}
		break;
	case OF_KEY_UP:
		{
			if(_bDrawCropRect)
			{
				ofPoint Pos_ = _CropRect.getCenter();
				Pos_.y -= 2;
				this->updateCropRect(Pos_);
			}
		}
		break;
	case OF_KEY_DOWN:
		{
			if(_bDrawCropRect)
			{
				ofPoint Pos_ = _CropRect.getCenter();
				Pos_.y += 2;
				this->updateCropRect(Pos_);
			}
		}
		break;
	case 's':
		{
			this->saveconfig();
			ofLog(OF_LOG_NOTICE, "[Main] Save config complete");
		}
		break;
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
		this->drawImageRecoder();

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
		eCHARACTER_TYPE Type_ = _Theatre.getCharacterType();
		_Connector.sendCMD(eCONNECTOR_CMD::eD2P_SET_CHARACTOR, ofToString(Type_));

		//Display webcam
		this->setDisplay(true);
	}
	else if(e == NAME_MGR::S_Upload)
	{
		_Connector.sendCMD(eCONNECTOR_CMD::eD2P_GAME_TIMEOUT, "");

		//Close webcam
		this->setDisplay(false);
	}
	else if(e == NAME_MGR::EVENT_Reset)
	{
		this->reset();
	}
}

#pragma endregion

#pragma region Audio checker
//--------------------------------------------------------------
void AirwavesApp::onAudioEvent(bool& e)
{
	if(_Theatre._Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_Start)
	{
		_Theatre.nextScence();
	}
}
#pragma endregion

#pragma region Image Recoder
//--------------------------------------------------------------
//Image Recoder
void AirwavesApp::setupImageRecoder()
{
	//Webcam
	_Cam.setDesiredFrameRate(24);
	_Cam.setPixelFormat(ofPixelFormat::OF_PIXELS_RGB);
	_bIsWebcamSetup = _Cam.initGrabber(1280, 720);
	_bDisplayWebcam = false;

	if(!_bIsWebcamSetup)
	{
		ofLog(OF_LOG_ERROR, "[Image Recoder] Setup webcam failed!!");
		return;
	}

	//Crop Rect
	_bDrawCropRect = false;
	_fCropScale = 1.0;
	_CropRect.set(_exCropRect.x, _exCropRect.y, _exCropRect.width, _exCropRect.height);

	//Image Recoder	
	_ImageRecorder.setup(cTHREAD_NUM, cVIDEO_BUFFER, cPHOTO_FORMAT);
	_ImageRecorder.setCropRect(_CropRect);

	//finish event
	ofAddListener(_ImageRecorder.ImageSequenceEvent, this, &AirwavesApp::onImageRecoderEvent);

	_iPictureCounter = 0;
}

//--------------------------------------------------------------
void AirwavesApp::updateImageRecoder()
{
	if(!_bIsWebcamSetup)
	{
		return;
	}

	_ImageRecorder.update();
	
	if(_bDisplayWebcam || _bDrawCropRect)
	{
		_Cam.update();
		if(_Cam.isFrameNew() && _ImageRecorder.getIsStart())
		{
			this->processImg();
		}
	}
}

//--------------------------------------------------------------
void AirwavesApp::drawImageRecoder()
{
	if(!_bIsWebcamSetup)
	{
		return;
	}

	if(_bDisplayWebcam)
	{
		ofPushMatrix();
		{
			ofSetColor(255);
			ofTranslate(cWINDOW_WIDTH, 0);
			ofScale(-1, 1);
			ofTranslate(cWINDOW_WIDTH/2, cWINDOW_HEIGHT/2);
			_Cam.draw(-_Cam.getWidth()/2, -_Cam.getHeight()/2);
		}
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void AirwavesApp::drawCropRecoder()
{
	//Draw Crop
	if(_bDrawCropRect)
	{
		ofPushStyle();
		{
			ofSetColor(255);
			ofPushMatrix();
			{
				ofTranslate(cWINDOW_WIDTH, 0);
				ofScale(-1, 1);
				ofTranslate(cWINDOW_WIDTH/2, cWINDOW_HEIGHT/2);
				_Cam.draw(-_Cam.getWidth()/2, -_Cam.getHeight()/2);
			}
			ofPopMatrix();

			ofNoFill();
			ofSetLineWidth(5);
			ofSetColor(255, 0, 0);
			ofRect(_CropRect);
		}
		ofPopStyle();
	}
}

//--------------------------------------------------------------
void AirwavesApp::saveImage()
{
	if(!_bIsWebcamSetup || !_bDisplayWebcam)
	{
		return;
	}

	if(_iPictureCounter > cPICTURE_NUM)
	{
		ofLog(OF_LOG_WARNING, "[ofxCTImageSequence] over picture num");
		return;
	}
	_iPictureCounter++;
	string strFilename_ = cPICTURE_BUFFER + ofToString(_iPictureCounter) + ".jpg";

	_ImageRecorder.addFameNow(_Cam.getPixelsRef(), strFilename_);
}

//--------------------------------------------------------------
void AirwavesApp::setDisplay(bool bValue)
{
	_bDisplayWebcam = bValue;
}

//--------------------------------------------------------------
void AirwavesApp::onImageRecoderEvent(string& e)
{
	if(e == "SAVE_FINISH")
	{
		ofLog(OF_LOG_NOTICE, "[ofxCTImageSequence] save finish");
		//this->setupFFmpegCmd();
	}
	else if(e == "RECORD_FINISH")
	{		
		ofLog(OF_LOG_NOTICE, "[ofxCTImageSequence] Record Finish!!");
		this->setDisplay(false);
	}
}

//--------------------------------------------------------------
void AirwavesApp::processImg()
{
	if(!_bIsWebcamSetup)
	{
		return;
	}
	_ImageRecorder.addFrame(_Cam);
}

//--------------------------------------------------------------
void AirwavesApp::updateCropRect(ofPoint Center)
{
	if(!_bIsWebcamSetup)
	{
		return;
	}

	if(	Center.x + _CropRect.width/2 > cWINDOW_WIDTH || Center.x - _CropRect.width/2 < 0 ||
		Center.y + _CropRect.height/2 > cWINDOW_HEIGHT || Center.y - _CropRect.height/2 < 0)
	{
		return;
	}

	_CropRect.setFromCenter(Center, _CropRect.width, _CropRect.height);

}

//--------------------------------------------------------------
void AirwavesApp::updateCropRect(float fUpdateScale)
{
	if(!_bIsWebcamSetup)
	{
		return;
	}

	_fCropScale *= fUpdateScale;
	_CropRect.scaleFromCenter(fUpdateScale);

}
#pragma endregion

#pragma region Connector
void AirwavesApp::onConnectorEvent(pair<eCONNECTOR_CMD, string>& e)
{
	switch(e.first)
	{
	case eP2D_TEACHING_END:
		{
			if(_Theatre._Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_Teching)
			{
				_Theatre.nextScence();
			}
		}
		break;
	case eP2D_TAKE_PICTURE:
		{
			if(_Theatre._Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_Teching)
			{
				this->saveImage();
			}
		}
		break;
	default:
		{
			ofLog(OF_LOG_WARNING, "Unkown protocol : " + ofToString(e.first));
		}
		break;
	}
}

#pragma endregion

#pragma region Config file
//--------------------------------------------------------------
void AirwavesApp::loadconfig()
{
	ofxXmlSettings	config_;
	if(!config_.loadFile("_config.xml"))
	{
		ofLog(OF_LOG_ERROR, "[Config file]Load config.xml failed");
		_exCropRect.set(0, 0, cWINDOW_WIDTH, cWINDOW_HEIGHT);
		return;
	}

	int	iCropX_, iCropY_, iCropWidth_, iCropHeight_;
	iCropX_ = config_.getValue("CROP:X", 0, 0);
	iCropY_ = config_.getValue("CROP:Y", 0, 0);
	iCropWidth_ = config_.getValue("CROP:WIDTH", cVIDEO_WIDTH, 0);
	iCropHeight_ = config_.getValue("CROP:HEIGHT", cVIDEO_HEIGHT, 0);
	
	_exCropRect.set(iCropX_, iCropY_, iCropWidth_, iCropHeight_);
}

//--------------------------------------------------------------
void AirwavesApp::saveconfig()
{
	ofxXmlSettings	config_;
	config_.setValue("CROP:X", _CropRect.x);
	config_.setValue("CROP:Y", _CropRect.y);
	config_.setValue("CROP:WIDTH", _CropRect.width);
	config_.setValue("CROP:HEIGHT", _CropRect.height);
	config_.saveFile("_config.xml");
}
#pragma endregion
