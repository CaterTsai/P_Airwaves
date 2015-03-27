#include "AudioChecker.h"

void AudioCheck::setup()
{
	_soundStream.setInput(this);
	_soundStream.setup(0, 2, 44100, 32, 4);
}

//--------------------------------------------------------------
void AudioCheck::audioIn(float * input, int bufferSize, int nChannels)
{
	if(!_bStartCheck)
	{
		return;
	}
	
	float fVol_ = 0.0;
	int numCounted = 0;	
	
	for (int i = 0; i < bufferSize; i++)
	{
		float left_ = input[i*2]*0.5;
		float right_ = input[i*2+1]*0.5;
		fVol_ += left_ * left_;
		fVol_ += right_ * right_;

		numCounted+=2;
	}

	fVol_ /= (float)numCounted;
	fVol_ = sqrt( fVol_ );
	if(fVol_ > cAUDIO_TRIGGER_LIMIT)
	{
		ofNotifyEvent(_AudioEvent, _bStartCheck);
		_bStartCheck = false;
	}
}