#include "AudioChecker.h"

void AudioCheck::setup(float fAudioThreshold)
{
	_soundStream.setInput(this);
	_soundStream.setup(0, 2, 44100, 32, 4);

	_fAudioThreshold = fAudioThreshold;
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
		float left_ = input[i*2];

		fVol_ += left_ * left_;


		numCounted+=1;
	}

	fVol_ /= (float)numCounted;
	fVol_ = sqrt( fVol_ );
	
	if(fVol_ > _fAudioThreshold)
	{
		
		ofNotifyEvent(_AudioEvent, _bStartCheck);
		_bStartCheck = false;
	}
}