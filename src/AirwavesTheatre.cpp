#include "AirwavesTheatre.h"

void AirwavesTheatre::setupTheatre()
{
	_Director.SetStageSize(ofGetWindowWidth(), ofGetWindowHeight());

#pragma region Scenes
	//-------------------------------------------------
	//Scenes
	//-------------------------------------------------
	_Director.AddScenes(NAME_MGR::S_Start);
	_Director.AddScenes(NAME_MGR::S_Character);
	_Director.AddScenes(NAME_MGR::S_Teching);
	_Director.AddScenes(NAME_MGR::S_Gaming);
	_Director.AddScenes(NAME_MGR::S_Upload);
	_Director.AddScenes(NAME_MGR::S_Finish);
#pragma endregion

#pragma region Actor
	//-------------------------------------------------
	//Actor
	//-------------------------------------------------
	//S_Start
	_Director.AddActor(new ofxImageActor(NAME_MGR::A_StartBG, "images/start_bg.jpg"));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_StartLoop, "videos/start_loop.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_ALPHA));
	
	//S_Character
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_CharacterAngel, "videos/character_angel.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_CharacterRoma, "videos/character_roma.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_CharacterMoney, "videos/character_money.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_CharacterAlien, "videos/character_alien.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	

	//S_Teching
	_Director.AddActor(new ofxImageActor(NAME_MGR::A_TeachingTitle, "images/teaching_title.png", eBLEND_ALPHA));

	//S_Gaming	
	_Director.AddActor(new ofxImageActor(NAME_MGR::A_GamingTitle, "images/gaming_title.png", eBLEND_ALPHA));
	_Director.AddActor(new ofxAnimationImageActor(NAME_MGR::A_GameCountdown, "images/timer/", eBLEND_ALPHA));

	//S_Upload
	_Director.AddActor(new ofxImageActor(NAME_MGR::A_UploadBG, "images/upload_bg.jpg"));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_UploadLoop, "videos/upload_loop.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_ALPHA));

	//S_Finish
	_Director.AddActor(new ofxImageActor(NAME_MGR::A_FinishBG, "images/finish_bg.jpg"));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_FinishTVC, "videos/tvc.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
#pragma endregion

#pragma region Plane
	//-------------------------------------------------
	//Plane
	//-------------------------------------------------
	_Director.AddPlane(NAME_MGR::S_Start, NAME_MGR::P_Start, 0);
	_Director.AddPlane(NAME_MGR::S_Character, NAME_MGR::P_Character, 0);
	_Director.AddPlane(NAME_MGR::S_Teching, NAME_MGR::P_Teaching, 0);
	_Director.AddPlane(NAME_MGR::S_Gaming, NAME_MGR::P_Gaming, 0);
	_Director.AddPlane(NAME_MGR::S_Upload, NAME_MGR::P_Upload, 0);
	_Director.AddPlane(NAME_MGR::S_Finish, NAME_MGR::P_Finish, 0);
#pragma endregion

#pragma region Element
	//-------------------------------------------------
	//Element
	//-------------------------------------------------
	//S_Start
	_Director.AddElement(NAME_MGR::E_StartBG, NAME_MGR::P_Start, NAME_MGR::A_StartBG);
	_Director.AddElement(NAME_MGR::E_StartLoop, NAME_MGR::P_Start, NAME_MGR::A_StartLoop);

	//S_Character
	_Director.AddElement(NAME_MGR::E_CharacterAngel, NAME_MGR::P_Character, NAME_MGR::A_CharacterAngel);
	_Director.AddElement(NAME_MGR::E_CharacterRoma, NAME_MGR::P_Character, NAME_MGR::A_CharacterRoma);
	_Director.AddElement(NAME_MGR::E_CharacterAlien, NAME_MGR::P_Character, NAME_MGR::A_CharacterAlien);
	_Director.AddElement(NAME_MGR::E_CharacterMoney, NAME_MGR::P_Character, NAME_MGR::A_CharacterMoney);

	//S_Teaching
	_Director.AddElement(NAME_MGR::E_TeachingTitle, NAME_MGR::P_Teaching, NAME_MGR::A_TeachingTitle);

	//S_Gaming	
	_Director.AddElement(NAME_MGR::E_GameTitle, NAME_MGR::P_Gaming, NAME_MGR::A_GamingTitle);
	_Director.AddElement(NAME_MGR::E_GameCountdown, NAME_MGR::P_Gaming, NAME_MGR::A_GameCountdown);

	//S_Upload
	_Director.AddElement(NAME_MGR::E_UploadBG, NAME_MGR::P_Upload, NAME_MGR::A_UploadBG);
	_Director.AddElement(NAME_MGR::E_UploadLoop, NAME_MGR::P_Upload, NAME_MGR::A_UploadLoop);

	//S_Finish
	_Director.AddElement(NAME_MGR::E_FinishBG, NAME_MGR::P_Finish, NAME_MGR::A_FinishBG);
	_Director.AddElement(NAME_MGR::E_FinishTVC, NAME_MGR::P_Finish, NAME_MGR::A_FinishTVC);
#pragma endregion

#pragma region Translate Element
	_Director.AddTransititonVideo(NAME_MGR::T_Start2Character, "videos/start2character.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), 0.75, true);
#pragma endregion
	
#pragma region Element String
	//-------------------------------------------------
	//Element Setting
	//-------------------------------------------------	
	//Animation
	ofxAnimationImageElement* pAnimElementPtr_ = nullptr;
	_Director.GetElementPtr(NAME_MGR::E_GameCountdown, pAnimElementPtr_);
	pAnimElementPtr_->SetSPF(1.0);

	//Video
	ofxVideoElement* pVideoElement_ = nullptr;
	_Director.GetElementPtr(NAME_MGR::E_StartLoop, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(true);

	_Director.GetElementPtr(NAME_MGR::E_CharacterAngel, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MGR::E_CharacterMoney, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MGR::E_CharacterAlien, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MGR::E_CharacterRoma, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MGR::E_UploadLoop, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(true);

	_Director.GetElementPtr(NAME_MGR::E_FinishTVC, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(false);
#pragma endregion

	//Default
	_eCharacterType = eCHARACTER_ROMA;

	this->setupTimerTrigger();

	ofAddListener(ofxTheatreEventArgs::TheatreEvent, this, &AirwavesTheatre::onTheatreEvent);
	_Director.Play();
}

//--------------------------------------------------------------
void AirwavesTheatre::updateTheatre(float fDelta)
{
	this->updateTimerTrigger(fDelta);
	_Director.update();
}

//--------------------------------------------------------------
void AirwavesTheatre::drawTheatre()
{
	ofPushStyle();
	{
		ofSetColor(255);
		_Director.draw();
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void AirwavesTheatre::resetTheatre()
{
	string strEventMsg_ = NAME_MGR::EVENT_Reset;
	ofNotifyEvent(AirwavesTheaterEvent, strEventMsg_, this);

	_Director.TransitTo();
}

//--------------------------------------------------------------
void AirwavesTheatre::TheatreAnimInit(string strName)
{
}

//--------------------------------------------------------------
void AirwavesTheatre::onTheatreEvent(ofxTheatreEventArgs& e)
{
	bool bReturnCheck_ = false;

#pragma region Scence event
	//Scence Event
	if(e.strMessage == NAME_MGR::S_Character)
	{
		ofxVideoElement* pCharacterVideo_ = nullptr;
		//this->setCharacterType( (eCHARACTER_TYPE)(rand() % cCHARACTER_MAX_TYPE) );
		this->setCharacterType( eCHARACTER_TYPE::eCHARACTER_ROMA );
		switch(_eCharacterType)
		{
		case eCHARACTER_TYPE::eCHARACTER_ANGEL:
			{
				if(_Director.GetElementPtr(NAME_MGR::E_CharacterAngel, pCharacterVideo_))
				{
					pCharacterVideo_->PlayVideo();
				}
			}
			break;
		case eCHARACTER_TYPE::eCHARACTER_ALIEN:
			{
				if(_Director.GetElementPtr(NAME_MGR::E_CharacterAlien, pCharacterVideo_))
				{
					pCharacterVideo_->PlayVideo();
				}
			}
			break;
		case eCHARACTER_TYPE::eCHARACTER_ROMA:
			{
				if(_Director.GetElementPtr(NAME_MGR::E_CharacterRoma, pCharacterVideo_))
				{
					pCharacterVideo_->PlayVideo();
				}
			}
			break;
		}
		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::S_Teching)
	{
		//this->addTimerTrigger(
		//	cSECOND_TEACHING_TIMEOUT,
		//	[] (AirwavesTheatre* ptr){
		//		ptr->nextScence();
		//	});

		string strEventMsg_ = NAME_MGR::S_Teching;
		ofNotifyEvent(AirwavesTheaterEvent, strEventMsg_, this);

		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::S_Gaming)
	{
		ofxAnimationImageElement* pAnimPtr_;
		_Director.GetElementPtr(NAME_MGR::E_GameCountdown, pAnimPtr_);
		pAnimPtr_->PlayAnimation();

		this->addTimerTrigger(
			cSECOND_GAMING_TIMEOUT,
			[] (AirwavesTheatre* ptr){
				ptr->nextScence();
			}
		);
		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::S_Upload)
	{
		string strEventMsg_ = NAME_MGR::S_Upload;
		ofNotifyEvent(AirwavesTheaterEvent, strEventMsg_, this);
		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::S_Finish)
	{
		this->addTimerTrigger(
			cSECOND_TVC_PLAY,
			[] (AirwavesTheatre* ptr){
				ofxVideoElement* pVideoElement_ = nullptr;
				if(ptr->_Director.GetElementPtr(NAME_MGR::E_FinishTVC, pVideoElement_))
				{
					pVideoElement_->PlayVideo();
				}
			}
		);
	}
	if(bReturnCheck_)
	{
		return;
	}
#pragma endregion

#pragma region Video event
	if(	e.strMessage == NAME_MGR::E_CharacterAngel || e.strMessage == NAME_MGR::E_CharacterMoney ||
		e.strMessage == NAME_MGR::E_CharacterAlien || e.strMessage == NAME_MGR::E_CharacterRoma)
	{
		this->nextScence();
		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::E_FinishTVC)
	{
		this->nextScence();
		bReturnCheck_ = true;
	}
	
	if(bReturnCheck_)
	{
		return;
	}
#pragma endregion

}

//--------------------------------------------------------------
void AirwavesTheatre::nextScence()
{
	string strNowScence_ = _Director.GetNowScenes()->GetScenesName();

	if(strNowScence_ == NAME_MGR::S_Start)
	{
		_Director.TransitByVideo(NAME_MGR::S_Character, NAME_MGR::T_Start2Character);
	}
	else if(strNowScence_ == NAME_MGR::S_Finish)
	{
		this->resetTheatre();
	}
	else
	{
		_Director.TransitTo(TRANSITION_TYPE::eTRANSITION_NONE);
	}
}

#pragma region Timer Trigger
void AirwavesTheatre::setupTimerTrigger()
{
	_fTimer = .0;
	_bEnableTimer = false;
}

//-------------------------------------------------
void AirwavesTheatre::updateTimerTrigger(float fDelta)
{
	if(_bEnableTimer)
	{
		_fTimer -= fDelta;

		if(_fTimer < 0.0)
		{
			_bEnableTimer = false;
			_trigger(this);
		}
	}
}

//-------------------------------------------------
void AirwavesTheatre::addTimerTrigger(float fTimer, function<void(AirwavesTheatre*)> triggerEvent )
{
	if(!_bEnableTimer)
	{
		_fTimer = fTimer;
		_trigger = triggerEvent;
		_bEnableTimer = true;
	}
}

//-------------------------------------------------
void AirwavesTheatre::removeTimerTrigger()
{
	if(_bEnableTimer)
	{
		_fTimer = .0;
		_bEnableTimer = false;
	}
}
#pragma endregion
