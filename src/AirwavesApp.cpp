#include "AirwavesApp.h"

#pragma region Base method
//--------------------------------------------------------------
void AirwavesApp::setup()
{
	ofBackground(0);
	ofSetVerticalSync(true);
	//ofLogToFile(ofGetTimestampString("Log_%m%d"), true);

	//Config
	this->loadconfig();

	//Image Recoder
	this->setupImageRecoder();

	//Video Create
	ofAddListener(_VideoCreate.SystemCallerFinishEvent, this, &AirwavesApp::onVideoCreateEvent);
	_VideoCreate.start();

	//Video Uploader
	this->setupVideotUploader();

	//Theatre
	this->initTheatre();
	
	//Audio
	_MicChecker.setup(_exAudioThreshold);
	ofAddListener(_MicChecker._AudioEvent, this, &AirwavesApp::onAudioEvent);

	//Connector
	if(_exUseSerial)
	{
		ofPtr<SerialConnector> pConnector_ = ofPtr<SerialConnector>(new SerialConnector(_exCOM));
		_Connector = pConnector_;
	}
	else
	{
		ofPtr<UDPConnector> pConnector_ = ofPtr<UDPConnector>(new UDPConnector(_exProjectorIP, 5566, 2233));
		_Connector = pConnector_;
	}	
	ofAddListener(_Connector->AirwavesConnectorEvent, this, &AirwavesApp::onConnectorEvent);

	//QR Connector
	_QRConnector.initQRConnector(_exQRPrinterIP, 11999);
	
	//User ID
	_UserID = ofGetTimestampString("%m%d%H%M%S");

	_fConnectionTimer = 0.0;
	_bIsConnecion = false;
	_bCtrlMode = false;
	ofHideCursor();
	ofToggleFullscreen();

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
	_AnimBGAlpha.update(fDelta_);
	_AnimLogoAlpha.update(fDelta_);
	_Theatre.updateTheatre(fDelta_);

	//Connector
	_Connector->updateConnector();

	//Projector check
	if(!_bIsConnecion && _Theatre._Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_Start)
	{
		_fConnectionTimer -= fDelta_;
		if(_fConnectionTimer <= 0)
		{
			_Connector->sendCMD(eCONNECTOR_CMD::eD2P_ARE_U_READY);
			_fConnectionTimer = 3.0;
		}
	}

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
	_Connector->closeConnector();
	_ImageRecorder.exit();
	_VideoCreate.stop();
	_VideoCreate.signal();
}

//--------------------------------------------------------------
void AirwavesApp::reset()
{
	_AnimBGAlpha.reset(255);
	_AnimLogoAlpha.reset(255);
	
	//reset picture conuter
	_iPictureCounter = 0;

	//open micphone checker
	_MicChecker.setCheck(true);

	//Create User ID
	_UserID = ofGetTimestampString("%m%d%H%M%S");

	_Connector->sendCMD(eD2P_RESET);
}

//--------------------------------------------------------------
void AirwavesApp::keyPressed(int key)
{
	switch(key)
	{
	case 'f':
		{
			_bCtrlMode ^= true;
			if(_bCtrlMode)
			{
				ofShowCursor();
			}
			else
			{
				ofHideCursor();
			}
			ofToggleFullscreen();
		}
		break;
	case 'n':
		{
			_Theatre.nextScence();
			_MicChecker.setCheck(false);
			break;
		}
	case 'd':
		{
			if(_Theatre._Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_Start)
			{
				_bDrawCropRect ^= true;

				if(_bDrawCropRect)
				{
					_MicChecker.setCheck(false);
				}
				else
				{
					_MicChecker.setCheck(true);
				}
			}
		}
		break;
	case '1':
		{
			if(_bDrawCropRect)
			{
				this->updateCropRect(1.02);
			}
		}
		break;
	case '2':
		{
			if(_bDrawCropRect)
			{
				this->updateCropRect(0.98);
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
	case 'c':
		{
			if(_bDrawCropRect)
			{
				_Cam.videoSettings();
			}
		}
		break;
	case '=':
		{
			this->saveconfig();
			ofLog(OF_LOG_NOTICE, "[Main] Save config complete");
		}
		break;
	case 'r':
		{
			_Theatre.resetTheatre();
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

	//Background & Logo
	_Background.loadImage("images/background.jpg");
	_AnimBGAlpha.setDuration(cSECOND_BACKGROUND_FADE);
	_AnimBGAlpha.setRepeatType(AnimRepeat::PLAY_ONCE);
	_AnimBGAlpha.reset(255);

	_Logo.loadImage("images/logo.png");
	_AnimLogoAlpha.setDuration(1);
	_AnimLogoAlpha.setRepeatType(AnimRepeat::PLAY_ONCE);
	_AnimLogoAlpha.reset(255);
}

//--------------------------------------------------------------
void AirwavesApp::drawBeforeTheatre()
{
	ofPushStyle();
	{	
		this->drawImageRecoder();

		ofSetColor(255, 255, 255, _AnimBGAlpha.getCurrentValue());
		_Background.draw(0, 0);

		ofSetColor(255, 255, 255, _AnimLogoAlpha.getCurrentValue());
		_Logo.draw(0, 0);		
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void AirwavesApp::drawAfterTheatre()
{	
	ofPushStyle();
	{
		if(_Theatre._Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_Start)
		{
			ofFill();
			if(!_bIsConnecion)
			{
				ofSetColor(255, 0, 0);
				ofCircle(10, 10, 10);
			}
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void AirwavesApp::onTheatreEvent(string& e)
{
	if(e == NAME_MGR::EVENT_StartTeaching)
	{
		eCHARACTER_TYPE Type_ = _Theatre.getCharacterType();
		_Connector->sendCMD(eCONNECTOR_CMD::eD2P_SET_CHARACTOR, ofToString(Type_));

		//Display webcam
		this->setDisplay(true);

		this->disableLogo();
	}
	else if(e == NAME_MGR::EVENT_TeachingTimeout)
	{
		eCHARACTER_TYPE Type_ = _Theatre.getCharacterType();
		_Connector->sendCMD(eCONNECTOR_CMD::eD2P_TEACHING_TIMEOUT, ofToString(Type_));
		
		this->enableBackground();
		_Theatre.nextScence();
	}
	else if(e == NAME_MGR::EVENT_TeachingFinish)
	{
		this->enableBackground();
		_Theatre.nextScence();
	}
	else if(e == NAME_MGR::EVENT_StartGaming)
	{
		_Connector->sendCMD(eCONNECTOR_CMD::eD2P_GAME_START, "");
	}
	else if(e == NAME_MGR::EVENT_StartRecord)
	{
		//ofSetFrameRate(24);
		_ImageRecorder.startRecode(cRECODE_DURATION);
	}
	else if(e == NAME_MGR::EVENT_StartUpload)
	{
		_Connector->sendCMD(eCONNECTOR_CMD::eD2P_GAME_TIMEOUT, "");

		//Close webcam
		this->setDisplay(false);

		_ImageRecorder.stopRecode();
	}
	else if(e == NAME_MGR::EVENT_Reset)
	{
		this->reset();
	}
	else if(e == NAME_MGR::EVENT_BackgoundDisable)
	{
		this->disableBackground();
	}
}

#pragma endregion

#pragma region Audio checker
//--------------------------------------------------------------
void AirwavesApp::onAudioEvent(bool& e)
{
	if(_Theatre._Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_Start)
	{
		ofLog(OF_LOG_NOTICE, "New User : " + _UserID);
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
		//ofLog(OF_LOG_WARNING, "[ofxCTImageSequence] over picture num");
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
		this->startVideoCreate();
	}
	else if(e == "RECORD_FINISH")
	{		
		ofLog(OF_LOG_NOTICE, "[ofxCTImageSequence] Record Finish!!");
		//ofSetFrameRate(60);
		//this->setDisplay(false);
	}
	else if(e == "RECORD_FAILED")
	{
		ofLog(OF_LOG_ERROR, "[ofxCTImageSequence] failed!!");
		this->startVideoCreate();
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
	_ImageRecorder.setCropRect(_CropRect);
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
	_CropRect.width = static_cast<int>(_CropRect.width + 0.5);
	_CropRect.height = static_cast<int>(_CropRect.height + 0.5);

	if((int)_CropRect.width % 2 != 0)
	{
		_CropRect.width--;
	}
	if((int)_CropRect.height % 2 != 0)
	{
		_CropRect.height--;
	}

	_ImageRecorder.setCropRect(_CropRect);
}
#pragma endregion

#pragma region Video Create
//--------------------------------------------------------------
void AirwavesApp::startVideoCreate()
{
	//Create video
	_VideoCreate.addCMD(cCREATE_IMAGE_SLIDER_CMD);
	_VideoCreate.addCMD(cCREATE_VIDEO_CMD);

	_VideoCreate.addCMD(cSLIDER_TO_MPEG);
	_VideoCreate.addCMD(cVIDEO_TO_MPEG);

	switch(_Theatre.getCharacterType())
	{
	case eCHARACTER_ANGEL:
		_VideoCreate.addCMD(cCOMBIND_VIDEO_ANGEL_CMD + _UserID + ".mp4");
		break;
	case eCHARACTER_ROMA:
		_VideoCreate.addCMD(cCOMBIND_VIDEO_ROMA_CMD + _UserID + ".mp4");
		break;
	case eCHARACTER_ALIEN:
		_VideoCreate.addCMD(cCOMBIND_VIDEO_ALIEN_CMD + _UserID + ".mp4");
		break;
	case eCHARACTER_MONEY:
		_VideoCreate.addCMD(cCOMBIND_VIDEO_MONEY_CMD + _UserID + ".mp4");
		break;
	}
	//_VideoCreate.addCMD(cCLEAR_VIDEO_BUFFER_CMD);
	//_VideoCreate.addCMD(cCLEAR_IMAGE_BUFFER_CMD);
	_VideoCreate.signal();
}

//--------------------------------------------------------------
void AirwavesApp::onVideoCreateEvent(string& e)
{
	ofLog(OF_LOG_NOTICE, "[Video Create]Create Video complete");
		
	this->uploadVideo();
}

#pragma endregion

#pragma region Video Uploader
void AirwavesApp::setupVideotUploader()
{
	ofAddListener(_VideoUploader.newResponseEvent, this, &AirwavesApp::onHttpResponse);
	_VideoUploader.start();
}

//--------------------------------------------------------------
void AirwavesApp::uploadVideo()
{
	//get video path
	string strVideoPath_ = ofFilePath::getCurrentExeDir() + "data\\results\\" + _UserID + ".mp4";
	ofxHttpForm	HttpForm_;
	HttpForm_.action = _exActionUrl;
	HttpForm_.method = OFX_HTTP_POST;

	HttpForm_.addFormField("ID", _UserID);
	HttpForm_.addFile("fileToUpload", strVideoPath_);

	_VideoUploader.addForm(HttpForm_);
}

//--------------------------------------------------------------
void AirwavesApp::onHttpResponse(ofxHttpResponse& response)
{
	ofLog(OF_LOG_NOTICE, "[video uploader]Upload success!!");

	//Print QR Code
	_QRConnector.printQR(cFB_SHARE_URL + _UserID);

	_Theatre.nextScence();
}
#pragma endregion

#pragma region Connector
//--------------------------------------------------------------
void AirwavesApp::onConnectorEvent(pair<eCONNECTOR_CMD, string>& e)
{
	switch(e.first)
	{
	case eP2D_IM_READY:
		{
			if(_Theatre._Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_Start)
			{
				_bIsConnecion = true;
				_MicChecker.setCheck(true);
			}
		}
	case eP2D_TEACHING_CHECK:
		{
			if(_Theatre._Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_Teching)
			{
				_Theatre.TheatreAnimInit(NAME_MGR::AS_FadeOutTeaching1);
				_Theatre.TheatreAnimInit(NAME_MGR::AS_DisplaySuccess1);
			}
			
		}
		break;
	case eP2D_TEACHING_END:
		{
			if(_Theatre._Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_Teching)
			{
				_Theatre.TheatreAnimInit(NAME_MGR::AS_FadeOutTeaching2);
				_Theatre.TheatreAnimInit(NAME_MGR::AS_DisplaySuccess2);
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
	_exUseSerial = (config_.getValue("USE_SERIAL", 0, 0) == 1);
	_exCOM = config_.getValue("COM", "COM3", 0);
	_exProjectorIP = config_.getValue("PROJECTOR_IP", cDEFAULT_URL, 0);
	_exQRPrinterIP = config_.getValue("QR_IP", cDEFAULT_URL, 0);
	_exActionUrl = config_.getValue("UPLOAD_URL", cDEFAULT_URL, 0);
	_exVideoPath = config_.getValue("VIDEO_PATH", "", 0);
	_exCropRect.set(iCropX_, iCropY_, iCropWidth_, iCropHeight_);
	_exAudioThreshold = config_.getValue("AUDIO_THRESHOLD", cAUDIO_TRIGGER_LIMIT, 0);
	
}

//--------------------------------------------------------------
void AirwavesApp::saveconfig()
{
	ofxXmlSettings	config_;
	config_.setValue("CROP:X", _CropRect.x);
	config_.setValue("CROP:Y", _CropRect.y);
	config_.setValue("CROP:WIDTH", _CropRect.width);
	config_.setValue("CROP:HEIGHT", _CropRect.height);

	config_.setValue("USE_SERIAL", _exUseSerial);
	config_.setValue("COM", _exCOM);

	config_.setValue("UPLOAD_URL", _exActionUrl);
	config_.setValue("VIDEO_PATH", _exVideoPath);
	config_.setValue("QR_IP", _exQRPrinterIP);
	config_.setValue("PROJECTOR_IP", _exProjectorIP);
	config_.setValue("AUDIO_THRESHOLD", _exAudioThreshold);
	config_.saveFile("_config.xml");
}
#pragma endregion
