#ifndef OFX_CT_IMAGE_SEQUENCE
#define OFX_CT_IMAGE_SEQUENCE

#include "ofMain.h"

typedef	struct _stIMAGE_UNIT
{
	string		strFilename;
	ofPixels	image;
}stIMAGE_UNIT;

///////////////////////////////////////
//@CLASS ofxImageSequenceUnit
///////////////////////////////////////
class ofxImageSequenceUnit : ofThread
{
public:
	ofxImageSequenceUnit():_bNeedCrop(false){}

	void addFrame(string strFilename, ofPixels& image);
	void setCropRect(ofRectangle CropRect);

	void threadedFunction();

	void signal()
	{
		_Condition.signal();
	}

	inline void start()
	{
		startThread(true, false);
	}
	inline void stop()
	{
		stopThread();
	}
	inline bool IsFinish()
	{
		return _imageQueue.empty();
	}
	inline int getQueueSize()
	{
		return _imageQueue.size();
	}
private:
	bool				_bNeedCrop;
	ofRectangle			_CropRect;

	queue<stIMAGE_UNIT>	_imageQueue;
	ofMutex				_Mutex;
	Poco::Condition		_Condition;
};

///////////////////////////////////////
//@CLASS ofxCTImageSequence
///////////////////////////////////////
class ofxCTImageSequence
{
public:
	ofxCTImageSequence()
		:_bIsSetup(false)
		,_bStart(false)
		,_bCheckFinish(false)
		,_iTotalFrame(-1)
		,_iFPS(24)
		,_fSPF(1.0/24.0)
		,_iCounter(0)
		,_iUnsaveFrame(0)
	{}
	void setup(int iThreadNum, string strPrefix, string strFormat);
	void update();
	void exit();

	void setFPS(int iFps);

	void startRecode(float fDuration = 0.0);
	void stopRecode();

	void addFrame(ofVideoGrabber& refWebcam);
	void addFrame(ofVideoPlayer& refPlayer);
	void addFrame(ofPixels	pixel);

	void addFameNow(ofPixels pixel, string strFilename);

	//Crop
	void setCropRect(ofRectangle);

	//inline
	inline bool getIsStart()
	{
		return _bStart;
	}

	inline int getUnsaveFrameNum()
	{
		return _iUnsaveFrame;
	}

private:
	bool	_bIsSetup;
	bool	_bStart, _bCheckFinish;

	int		_iCounter;
	int		_iUnsaveFrame;
	string	_strPrefix, _strFormat;

	int		_iFPS, _iTotalFrame;
	float	_fSPF;
	float	_fTimer;
	vector<shared_ptr<ofxImageSequenceUnit>>	_ImgSequenceUnitList;

////////////////////////////
//Event
////////////////////////////
public:
	ofEvent<string>	ImageSequenceEvent;
};

#endif // !OFX_CT_IMAGE_SEQUENCE
