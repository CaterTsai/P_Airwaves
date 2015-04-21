#ifndef AIRWAVES_AUDIO_CHECKER
#define AIRWAVES_AUDIO_CHECKER

#include "constParameter.h"

class AudioCheck : public ofBaseSoundInput
{
public:
	void setup(float fAudioThreshold = cAUDIO_TRIGGER_LIMIT);
	void audioIn(float * input, int bufferSize, int nChannels);

public:
	inline void setCheck(const bool bValue)
	{
		_bStartCheck = bValue;
	}

public:
	ofEvent<bool>	_AudioEvent;

private:
	bool			_bStartCheck;
	float			_fAudioThreshold;
	ofSoundStream	_soundStream;
};

#endif // !AIRWAVES_AUDIO_CHECKER