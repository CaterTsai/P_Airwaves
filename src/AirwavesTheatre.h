#ifndef _AIRWAVES_THEATRE_
#define _AIRWAVES_THEATRE_

#include "constParameter.h"
#include "NameManager.h"
#include "ofxTheatreDirector.h"
#include "ofGstVideoPlayer.h"
#include "ofxHapPlayer.h"

class AirwavesTheatre
{
public:
	void setupTheatre();
	void updateTheatre(float fDelta);
	void drawTheatre();
	void resetTheatre();

	void TheatreAnimInit(string strName);
	void onTheatreEvent(ofxTheatreEventArgs& e);

	void nextScence();

public:
	bool			_bCanFinish;
	ofxDirector		_Director;
	int				_Counter;
//-------------------------------
//Character
//-------------------------------
public:
	inline void setCharacterType(eCHARACTER_TYPE type)
	{
		_eCharacterType = type;
	}
	inline eCHARACTER_TYPE getCharacterType() const
	{
		return _eCharacterType;
	}

private:
	eCHARACTER_TYPE	_eCharacterType;

//-------------------------------
// Timer Trigger
//-------------------------------
private:
	void setupTimerTrigger();
	void updateTimerTrigger(float fDelta);

	void addTimerTrigger(float fTimer, function<void(AirwavesTheatre*)> triggerEvent );	
	void removeTimerTrigger();
private:
	bool								_bEnableTimer;
	float								_fTimer;
	function<void(AirwavesTheatre*)>	_trigger;

//-------------------------------
//Event
//-------------------------------
public:
	ofEvent<string>	AirwavesTheaterEvent;
};

#endif //_AIRWAVES_THEATRE_