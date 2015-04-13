#include "ofxCTImageSequence.h"

//--------------------------------------------------------------
//@CLASS ofxImageSequenceUnit
//--------------------------------------------------------------
void ofxImageSequenceUnit::addFrame(string strFilename, ofPixels& image)
{
	stIMAGE_UNIT newUnit_;
	newUnit_.strFilename = strFilename;
	newUnit_.image = image;
	lock();
	_imageQueue.push(newUnit_);
	unlock();
}

//--------------------------------------------------------------
void ofxImageSequenceUnit::setCropRect(ofRectangle CropRect)
{
	_bNeedCrop = true;
	_CropRect = CropRect;
}

//--------------------------------------------------------------
void ofxImageSequenceUnit::threadedFunction()
{
	while(isThreadRunning())
	{
		if(_imageQueue.size() > 0)
		{
			lock();
			stIMAGE_UNIT imgUnit_ = _imageQueue.front();
			unlock();
			if(_bNeedCrop)
			{
				imgUnit_.image.crop(imgUnit_.image.getWidth() - (_CropRect.x + _CropRect.width), _CropRect.y, _CropRect.width, _CropRect.height);
			}
			
			ofSaveImage(imgUnit_.image, imgUnit_.strFilename, ofImageQualityType::OF_IMAGE_QUALITY_HIGH);
			lock();
			_imageQueue.pop();
			unlock();
		}
		else
		{
			_Condition.wait(_Mutex);
		}
	}
}

//--------------------------------------------------------------
//@CLASS ofxCTImageSequence
//--------------------------------------------------------------
void ofxCTImageSequence::setup(int iThreadNum, string strPrefix, string strFormat)
{
	_strPrefix = strPrefix;
	_strFormat = strFormat;

	_ImgSequenceUnitList.clear();
	for(int idx_ = 0; idx_ < iThreadNum; ++idx_)
	{
		auto NewUnit_ = make_shared<ofxImageSequenceUnit>();
		_ImgSequenceUnitList.push_back(NewUnit_);
	}

	//Start all thread
	for(auto& Iter_ : _ImgSequenceUnitList)
	{
		Iter_->start();
	}
	_bIsSetup = true;
}

//--------------------------------------------------------------
void ofxCTImageSequence::update()
{
	
	if(!_bIsSetup)
	{
		return;
	}

	if(!_bStart && _bCheckFinish)
	{
		bool bIsAllFinish_ = true;
		_iUnsaveFrame = 0;
		for(auto& Iter_ : _ImgSequenceUnitList)
		{
			bIsAllFinish_ &= Iter_->IsFinish();
			_iUnsaveFrame += Iter_->getQueueSize();
		}
		
		if(bIsAllFinish_)
		{
			_bCheckFinish = false;
			string strMsg = "SAVE_FINISH";
			ofNotifyEvent(ImageSequenceEvent, strMsg, this);
		}
	}
}

//--------------------------------------------------------------
void ofxCTImageSequence::exit()
{
	for(auto Iter_ : _ImgSequenceUnitList)
	{
		Iter_->signal();
		Iter_->stop();		
	}
}

//--------------------------------------------------------------
void ofxCTImageSequence::setFPS(int iFps)
{
	_iFPS = iFps;
	_fSPF = 1.0/(float)iFps;
}

//--------------------------------------------------------------
void ofxCTImageSequence::startRecode(float fDuration)
{
	if(!_bIsSetup || _bStart)
	{
		return;
	}
	
	ofLog(OF_LOG_NOTICE, "[ofxCTImageSequence] Start recode!!");

	_bStart = true;
	_bCheckFinish = false;
	_iCounter = 0;
	_iUnsaveFrame = 0;
	_iTotalFrame = fDuration * _iFPS;
	_fTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofxCTImageSequence::stopRecode()
{
	if(!_bStart && _iTotalFrame == 0)
	{
		_bStart = false;
	}
}

//--------------------------------------------------------------
void ofxCTImageSequence::addFrame(ofVideoGrabber& refWebcam)
{
	if(!_bIsSetup || !_bStart)
	{
		return;
	}

	this->addFrame(refWebcam.getPixelsRef());
}

//--------------------------------------------------------------
void ofxCTImageSequence::addFrame(ofVideoPlayer& refPlayer)
{
	if(!_bIsSetup || !_bStart)
	{
		return;
	}

	this->addFrame(refPlayer.getPixelsRef());
}

//--------------------------------------------------------------
void ofxCTImageSequence::addFrame(ofPixels	pixel)
{
	char fileName[500];
	sprintf(fileName,  "%s%.4i.%s" , _strPrefix.c_str(), _iCounter, _strFormat.c_str());     
	_iCounter++;
	int iListIndex_ = _iCounter % _ImgSequenceUnitList.size();
	_ImgSequenceUnitList[iListIndex_]->addFrame(fileName, pixel);
	_ImgSequenceUnitList[iListIndex_]->signal();

	if(_iCounter == _iTotalFrame)
	{
		_bStart = false;
		_bCheckFinish = true;

		string strMsg = "RECORD_FINISH";
		ofNotifyEvent(ImageSequenceEvent, strMsg, this);
	}
}

//--------------------------------------------------------------
void ofxCTImageSequence::addFameNow(ofPixels pixel, string strFilename)
{
	if(!_bIsSetup || _bStart)
	{
		//Can't used when recode is start
		return;
	}

	int iListIndex_ = _iCounter % _ImgSequenceUnitList.size();
	_ImgSequenceUnitList[0]->addFrame(strFilename, pixel);
	_ImgSequenceUnitList[0]->signal();
}

//--------------------------------------------------------------
void ofxCTImageSequence::setCropRect(ofRectangle CropRect)
{
	if(_bStart)
	{
		return;
	}

	for(auto& Iter_ : _ImgSequenceUnitList)
	{
		Iter_->setCropRect(CropRect);
	}
}