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
	_Director.AddScenes(NAME_MGR::S_Finish);
#pragma endregion

#pragma region Actor
	//-------------------------------------------------
	//Actor
	//-------------------------------------------------
	//S_Start
	//_Director.AddActor(new ofxImageActor(NAME_MGR::A_StartBG, "images/start_bg.jpg"));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_StartLoop, "videos/start_loop.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_SCREEN));
	
	//S_Character
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_CharacterAngel, "videos/angel/character.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_SCREEN));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_CharacterRoma, "videos/roma/character.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_SCREEN));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_CharacterMoney, "videos/money/character.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_SCREEN));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_CharacterAlien, "videos/alien/character.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_SCREEN));
	
	//S_Teching
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_Countdown10, "videos/countdown10.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_Countdown15, "videos/countdown15.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_Countdown20, "videos/countdown20.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));

	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingTitle, "videos/teaching_title.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_SCREEN));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingSuccess, "videos/teaching_success.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));

	////Angel
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingAngelIcon1, "videos/angel/teaching_icon1.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingAngelIcon2, "videos/angel/teaching_icon2.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingAngelMessage1, "videos/angel/teaching_message1.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingAngelMessage2, "videos/angel/teaching_message2.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));

	////Alien
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingAlienIcon, "videos/alien/teaching_icon.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingAlienMessage1, "videos/alien/teaching_message1.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingAlienMessage2, "videos/alien/teaching_message2.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));

	////Roma
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingRomaIcon1, "videos/roma/teaching_icon1.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingRomaIcon2, "videos/roma/teaching_icon2.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingRomaMessage1, "videos/roma/teaching_message1.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TeachingRomaMessage2, "videos/roma/teaching_message2.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_ALPHA));
	
	//S_Gaming	
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_GamingAngel, "videos/angel/gaming.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_SCREEN));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_GamingAlien, "videos/alien/gaming.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_SCREEN));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_GamingRoma, "videos/roma/gaming.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_SCREEN));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_GamingMoney, "videos/money/gaming.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), eBLEND_SCREEN));

	//S_Finish
	_Director.AddActor(new ofxImageActor(NAME_MGR::A_FinishBG, "images/finish_bg.jpg"));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_FinishTVC, "videos/kv.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));

#pragma endregion

#pragma region Plane
	//-------------------------------------------------
	//Plane
	//-------------------------------------------------
	_Director.AddPlane(NAME_MGR::S_Start, NAME_MGR::P_Start, 0);
	_Director.AddPlane(NAME_MGR::S_Character, NAME_MGR::P_Character, 0);
	_Director.AddPlane(NAME_MGR::S_Teching, NAME_MGR::P_Teaching, 3);
	_Director.AddPlane(NAME_MGR::S_Teching, NAME_MGR::P_TeachingMessage1, 2, ofPoint(0, 0), cWINDOW_WIDTH, cWINDOW_HEIGHT, false);
	_Director.AddPlane(NAME_MGR::S_Teching, NAME_MGR::P_TeachingMessage2, 1, ofPoint(0, 0), cWINDOW_WIDTH, cWINDOW_HEIGHT, false);
	_Director.AddPlane(NAME_MGR::S_Gaming, NAME_MGR::P_Gaming, 0);
	_Director.AddPlane(NAME_MGR::S_Finish, NAME_MGR::P_Finish, 0);
#pragma endregion

#pragma region Element
	//-------------------------------------------------
	//Element
	//-------------------------------------------------
	//S_Start
	//_Director.AddElement(NAME_MGR::E_StartBG, NAME_MGR::P_Start, NAME_MGR::A_StartBG);
	_Director.AddElement(NAME_MGR::E_StartLoop, NAME_MGR::P_Start, NAME_MGR::A_StartLoop);

	//S_Character
	_Director.AddElement(NAME_MGR::E_CharacterAngel, NAME_MGR::P_Character, NAME_MGR::A_CharacterAngel);
	_Director.AddElement(NAME_MGR::E_CharacterRoma, NAME_MGR::P_Character, NAME_MGR::A_CharacterRoma);
	_Director.AddElement(NAME_MGR::E_CharacterAlien, NAME_MGR::P_Character, NAME_MGR::A_CharacterAlien);
	_Director.AddElement(NAME_MGR::E_CharacterMoney, NAME_MGR::P_Character, NAME_MGR::A_CharacterMoney);

	//S_Teaching (defualt is roma)
	_Director.AddElement(NAME_MGR::E_TeachingTitle, NAME_MGR::P_Teaching, NAME_MGR::A_TeachingTitle);
	_Director.AddElement(NAME_MGR::E_TeachingCountdown, NAME_MGR::P_Teaching, NAME_MGR::A_Countdown15, 1, ofPoint(cWINDOW_WIDTH/2.0 - 120.0/2, 5), false);
	_Director.AddElement(NAME_MGR::E_TeachingSuccess, NAME_MGR::P_Teaching, NAME_MGR::A_TeachingSuccess, 2, ofPoint(cWINDOW_WIDTH/2.0 - 800.0/2, cWINDOW_HEIGHT - 200), false);

	_Director.AddElement(NAME_MGR::E_TeachingIcon1, NAME_MGR::P_TeachingMessage1, NAME_MGR::A_TeachingRomaIcon1, 1, ofPoint(330, 380));
	_Director.AddElement(NAME_MGR::E_TeachingMessage1, NAME_MGR::P_TeachingMessage1, NAME_MGR::A_TeachingRomaMessage1, 2, ofPoint(cWINDOW_WIDTH/2.0 - 800.0/2, cWINDOW_HEIGHT - 200));
	_Director.AddElement(NAME_MGR::E_TeachingIcon2, NAME_MGR::P_TeachingMessage2, NAME_MGR::A_TeachingRomaIcon2, 1, ofPoint(330, 380));
	_Director.AddElement(NAME_MGR::E_TeachingMessage2, NAME_MGR::P_TeachingMessage2, NAME_MGR::A_TeachingRomaMessage2, 2, ofPoint(cWINDOW_WIDTH/2.0 - 800.0/2, cWINDOW_HEIGHT - 200));
	
	//S_Gaming (defualt is roma)
	_Director.AddElement(NAME_MGR::E_GameTitle, NAME_MGR::P_Gaming, NAME_MGR::A_GamingRoma);
	_Director.AddElement(NAME_MGR::E_GameCountdown, NAME_MGR::P_Gaming, NAME_MGR::A_Countdown10, 1, ofPoint(cWINDOW_WIDTH/2.0 - 120.0/2, 5), false);

	//S_Finish
	_Director.AddElement(NAME_MGR::E_FinishBG, NAME_MGR::P_Finish, NAME_MGR::A_FinishBG);
	_Director.AddElement(NAME_MGR::E_FinishTVC, NAME_MGR::P_Finish, NAME_MGR::A_FinishTVC);
#pragma endregion

#pragma region Translate Element
	_Director.AddTransititonVideo(NAME_MGR::T_Start2Character, "videos/start2character.mov", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), 0.4, eBLEND_SCREEN);
#pragma endregion
	
#pragma region Element setting
	//-------------------------------------------------
	//Element Setting
	//-------------------------------------------------	
	//Video
	ofxVideoElement* pVideoElement_ = nullptr;
	_Director.GetElementPtr(NAME_MGR::E_StartLoop, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(true);

	//Character
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

	//Teaching
	_Director.GetElementPtr(NAME_MGR::E_TeachingTitle, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(true);

	_Director.GetElementPtr(NAME_MGR::E_TeachingCountdown, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MGR::E_TeachingIcon1, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MGR::E_TeachingMessage1, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MGR::E_TeachingIcon2, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MGR::E_TeachingMessage2, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MGR::E_TeachingSuccess, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(true);

	//Gaming
	_Director.GetElementPtr(NAME_MGR::E_GameTitle, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(true);

	_Director.GetElementPtr(NAME_MGR::E_GameCountdown, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(false);

	//Finish
	_Director.GetElementPtr(NAME_MGR::E_FinishTVC, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(true);

#pragma endregion

	//Default
	_eCharacterType = eCHARACTER_ROMA;
	_bCanFinish = false;

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
	_bCanFinish = false;
	_Director.TransitTo();
}

//--------------------------------------------------------------
void AirwavesTheatre::TheatreAnimInit(string strName)
{
	ofxBaseElement* pElementPtr_ = nullptr;
	ofxPlane* pPlanePtr_ = nullptr;
	if(strName == NAME_MGR::AS_FadeInTeaching1)
	{
		//Fadeout Title
		_Director.GetElementPtr(NAME_MGR::E_TeachingTitle, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_Teching, 0, new ofxFadeOutAnimation(NAME_MGR::ANIM_TeachingTitleFadeOut, pElementPtr_, 0, 0, 0));

		_Director.GetPlanePtr(NAME_MGR::P_TeachingMessage1, pPlanePtr_);
		_Director.AddAnimation(NAME_MGR::S_Teching, 0, new ofxFadeInAnimation(NAME_MGR::ANIM_TeachingeFadeIn1, pPlanePtr_, 0.5, 0, 0));
	}
	else if(strName == NAME_MGR::AS_FadeInTeaching2)
	{
		_Director.GetPlanePtr(NAME_MGR::P_TeachingMessage2, pPlanePtr_);
		_Director.AddAnimation(NAME_MGR::S_Teching, 0, new ofxFadeInAnimation(NAME_MGR::ANIM_TeachingeFadeIn2, pPlanePtr_, 0.5, 0, 0));
	}
	else if(strName == NAME_MGR::AS_FadeOutTeaching1)
	{
		_Director.GetPlanePtr(NAME_MGR::P_TeachingMessage1, pPlanePtr_);
		_Director.AddAnimation(NAME_MGR::S_Teching, 0, new ofxFadeOutAnimation(NAME_MGR::ANIM_TeachingeFadeOut1, pPlanePtr_, 0.5, 0.0, 0));
	}
	else if(strName == NAME_MGR::AS_FadeOutTeaching2)
	{
		_Director.GetPlanePtr(NAME_MGR::P_TeachingMessage2, pPlanePtr_);
		_Director.AddAnimation(NAME_MGR::S_Teching, 0, new ofxFadeOutAnimation(NAME_MGR::ANIM_TeachingeFadeOut2, pPlanePtr_, 0.5, 0.0, 0));
	}
	else if(strName == NAME_MGR::AS_DisplaySuccess1)
	{
		_Director.GetElementPtr(NAME_MGR::E_TeachingSuccess, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_Teching, 0, new ofxFadeInAnimation(NAME_MGR::ANIM_TeachingeSuccessFadeIn1, pElementPtr_, 0.3, 0, 0));
		_Director.AddAnimation(NAME_MGR::S_Teching, 0, new ofxFadeOutAnimation(NAME_MGR::ANIM_TeachingeSuccessFadeOut1, pElementPtr_, 0.3, 2.0, 0));
	}
	else if(strName == NAME_MGR::AS_DisplaySuccess2)
	{
		_Director.GetElementPtr(NAME_MGR::E_TeachingSuccess, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_Teching, 0, new ofxFadeInAnimation(NAME_MGR::ANIM_TeachingeSuccessFadeIn2, pElementPtr_, 0.3, 0, 0));
		_Director.AddAnimation(NAME_MGR::S_Teching, 0, new ofxFadeOutAnimation(NAME_MGR::ANIM_TeachingeSuccessFadeOut2, pElementPtr_, 0.3, 2.0, 0));
	}
	else if(strName == NAME_MGR::AS_FadeOutGamingTitle)
	{
		//Fadeout Title
		_Director.GetElementPtr(NAME_MGR::E_GameTitle, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_Gaming, 0, new ofxFadeOutAnimation(NAME_MGR::ANIM_GamingTitleFadeOut, pElementPtr_, 0, 0, 0));
	}
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
		ofxVideoElement* pGamingVideo_ = nullptr;
		_Director.GetElementPtr(NAME_MGR::E_GameTitle, pGamingVideo_);

		this->setCharacterType( (eCHARACTER_TYPE)(rand() % cCHARACTER_MAX_TYPE) );
		//this->setCharacterType( eCHARACTER_TYPE::eCHARACTER_ANGEL );
		switch(_eCharacterType)
		{
		case eCHARACTER_TYPE::eCHARACTER_ANGEL:
			{
				if(_Director.GetElementPtr(NAME_MGR::E_CharacterAngel, pCharacterVideo_))
				{
					pCharacterVideo_->PlayVideo();
				}
				pGamingVideo_->ChangeVideoActor(dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_GamingAngel)));
			}
			break;
		case eCHARACTER_TYPE::eCHARACTER_ALIEN:
			{
				if(_Director.GetElementPtr(NAME_MGR::E_CharacterAlien, pCharacterVideo_))
				{
					pCharacterVideo_->PlayVideo();
				}
				pGamingVideo_->ChangeVideoActor(dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_GamingAlien)));
			}
			break;
		case eCHARACTER_TYPE::eCHARACTER_ROMA:
			{
				if(_Director.GetElementPtr(NAME_MGR::E_CharacterRoma, pCharacterVideo_))
				{
					pCharacterVideo_->PlayVideo();
				}
				pGamingVideo_->ChangeVideoActor(dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_GamingRoma)));
			}
			break;
		}
		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::S_Teching)
	{
		//Setting Video
		ofxVideoElement* pVideoElement_ = nullptr;
		ofxVideoActor* pVideoActor_ = nullptr;
		switch(_eCharacterType)
		{
		case eCHARACTER_TYPE::eCHARACTER_ANGEL:
			{
				//Icon 1
				pVideoActor_ = dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_TeachingAngelIcon1));
				_Director.GetElementPtr(NAME_MGR::E_TeachingIcon1, pVideoElement_);
				pVideoElement_->ChangeVideoActor(pVideoActor_);
				pVideoElement_->PlayVideo();

				//Message 1
				pVideoActor_ = dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_TeachingAngelMessage1));
				_Director.GetElementPtr(NAME_MGR::E_TeachingMessage1, pVideoElement_);
				pVideoElement_->ChangeVideoActor(pVideoActor_);
				pVideoElement_->PlayVideo();

				//Icon 2
				pVideoActor_ = dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_TeachingAngelIcon2));
				_Director.GetElementPtr(NAME_MGR::E_TeachingIcon2, pVideoElement_);
				pVideoElement_->ChangeVideoActor(pVideoActor_);
				pVideoElement_->PlayVideo();

				//Message 2
				pVideoActor_ = dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_TeachingAngelMessage2));
				_Director.GetElementPtr(NAME_MGR::E_TeachingMessage2, pVideoElement_);
				pVideoElement_->ChangeVideoActor(pVideoActor_);
				pVideoElement_->PlayVideo();

			}
			break;
		case eCHARACTER_TYPE::eCHARACTER_ALIEN:
			{
				//Icon 1
				pVideoActor_ = dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_TeachingAlienIcon));
				_Director.GetElementPtr(NAME_MGR::E_TeachingIcon1, pVideoElement_);
				pVideoElement_->ChangeVideoActor(pVideoActor_);
				pVideoElement_->PlayVideo();

				//Message 1
				pVideoActor_ = dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_TeachingAlienMessage1));
				_Director.GetElementPtr(NAME_MGR::E_TeachingMessage1, pVideoElement_);
				pVideoElement_->ChangeVideoActor(pVideoActor_);
				pVideoElement_->PlayVideo();

				//Message 2
				pVideoActor_ = dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_TeachingAlienMessage2));
				_Director.GetElementPtr(NAME_MGR::E_TeachingMessage2, pVideoElement_);
				pVideoElement_->ChangeVideoActor(pVideoActor_);
				pVideoElement_->PlayVideo();
			}
			break;
		case eCHARACTER_TYPE::eCHARACTER_ROMA:
			{
				//Icon 1
				pVideoActor_ = dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_TeachingRomaIcon1));
				_Director.GetElementPtr(NAME_MGR::E_TeachingIcon1, pVideoElement_);
				pVideoElement_->ChangeVideoActor(pVideoActor_);
				pVideoElement_->PlayVideo();

				//Icon 1
				pVideoActor_ = dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_TeachingRomaIcon2));
				_Director.GetElementPtr(NAME_MGR::E_TeachingIcon2, pVideoElement_);
				pVideoElement_->ChangeVideoActor(pVideoActor_);
				pVideoElement_->PlayVideo();

				//Message 1
				pVideoActor_ = dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_TeachingRomaMessage1));
				_Director.GetElementPtr(NAME_MGR::E_TeachingMessage1, pVideoElement_);
				pVideoElement_->ChangeVideoActor(pVideoActor_);
				pVideoElement_->PlayVideo();

				//Message 2
				pVideoActor_ = dynamic_cast<ofxVideoActor*>(_Director.GetActor(NAME_MGR::A_TeachingRomaMessage2));
				_Director.GetElementPtr(NAME_MGR::E_TeachingMessage2, pVideoElement_);
				pVideoElement_->ChangeVideoActor(pVideoActor_);
				pVideoElement_->PlayVideo();
			}
			break;
		}

		string strEventMsg_ = NAME_MGR::EVENT_StartTeaching;
		ofNotifyEvent(AirwavesTheaterEvent, strEventMsg_, this);

		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::S_Gaming)
	{
		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::S_Finish)
	{
		string strEventMsg_ = NAME_MGR::EVENT_StartUpload;
		ofNotifyEvent(AirwavesTheaterEvent, strEventMsg_, this);
		bReturnCheck_ = true;

	}
	if(bReturnCheck_)
	{
		return;
	}
#pragma endregion

#pragma region Animation event
	if(e.strMessage == NAME_MGR::ANIM_TeachingeSuccessFadeOut1)
	{
		this->TheatreAnimInit(NAME_MGR::AS_FadeInTeaching2);
		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::ANIM_TeachingeSuccessFadeOut2)
	{
		string strEventMsg_ = NAME_MGR::EVENT_TeachingFinish;
		ofNotifyEvent(AirwavesTheaterEvent, strEventMsg_, this);
		bReturnCheck_ = true;
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
	else if(e.strMessage == NAME_MGR::E_TeachingTitle)
	{
		this->TheatreAnimInit(NAME_MGR::AS_FadeInTeaching1);

		//Start countdown
		ofxVideoElement* pCountdown_ = nullptr;
		_Director.GetElementPtr(NAME_MGR::E_TeachingCountdown, pCountdown_);
		pCountdown_->SetVisible(true);
		pCountdown_->PlayVideo();

		string strEventMsg_ = NAME_MGR::EVENT_BackgoundDisable;
		ofNotifyEvent(AirwavesTheaterEvent, strEventMsg_, this);
		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::E_TeachingCountdown)
	{
		string strEventMsg_ = NAME_MGR::EVENT_TeachingTimeout;
		ofNotifyEvent(AirwavesTheaterEvent, strEventMsg_, this);
		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::E_GameTitle)
	{
		this->TheatreAnimInit(NAME_MGR::AS_FadeOutGamingTitle);
		
		//Fade out Background
		string strEventMsg_ = NAME_MGR::EVENT_BackgoundDisable;
		ofNotifyEvent(AirwavesTheaterEvent, strEventMsg_, this);

		//Start game
		strEventMsg_ = NAME_MGR::EVENT_StartGaming;
		ofNotifyEvent(AirwavesTheaterEvent, strEventMsg_, this);

		//Start countdown
		ofxVideoElement* pCountdown_ = nullptr;
		_Director.GetElementPtr(NAME_MGR::E_GameCountdown, pCountdown_);
		pCountdown_->SetVisible(true);
		pCountdown_->PlayVideo();

		//set recode timer
		this->addTimerTrigger(
			cSECOND_GAMING_RECODEING,
			[] (AirwavesTheatre* ptr){
				string strEventMsg_ = NAME_MGR::EVENT_StartRecord;
				ofNotifyEvent(ptr->AirwavesTheaterEvent, strEventMsg_, ptr);
			}
		);
		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::E_GameCountdown)
	{
		this->nextScence();
		bReturnCheck_ = true;
	}
	else if(e.strMessage == NAME_MGR::E_FinishTVC)
	{	
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
