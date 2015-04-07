#ifndef AIRWAVES_NAME_MANAGER
#define AIRWAVES_NAME_MANAGER

#include <string>
using namespace std;

#define CREATE_VALUE(NAME) static const string NAME = #NAME;
#define CREATE_VALUE_WITH_VALUE(NAME, VALUE) static const string NAME = VALUE;

namespace NAME_MGR
{
//-------------------------------------------------
//Theatre
//-------------------------------------------------
///////////////////////////////////////
// Scenes
///////////////////////////////////////
	CREATE_VALUE(S_Start);
	CREATE_VALUE(S_Character);
	CREATE_VALUE(S_Teching);
	CREATE_VALUE(S_Gaming);
	CREATE_VALUE(S_Finish);

///////////////////////////////////////
// Actor
///////////////////////////////////////
	CREATE_VALUE(A_StartLoop);
	CREATE_VALUE(A_CharacterAngel);
	CREATE_VALUE(A_CharacterAlien);
	CREATE_VALUE(A_CharacterRoma);
	CREATE_VALUE(A_CharacterMoney);

	CREATE_VALUE(A_Countdown10);
	CREATE_VALUE(A_Countdown15);
	CREATE_VALUE(A_Countdown20);

	CREATE_VALUE(A_TeachingTitle);
	CREATE_VALUE(A_TeachingSuccess);

	CREATE_VALUE(A_TeachingAngelIcon);
	CREATE_VALUE(A_TeachingAngelMessage1);
	
	CREATE_VALUE(A_TeachingAlienIcon);
	CREATE_VALUE(A_TeachingAlienMessage1);
	CREATE_VALUE(A_TeachingAlienMessage2);

	CREATE_VALUE(A_TeachingRomaIcon1);
	CREATE_VALUE(A_TeachingRomaIcon2);
	CREATE_VALUE(A_TeachingRomaMessage1);
	CREATE_VALUE(A_TeachingRomaMessage2);

	//TODO Money
	CREATE_VALUE(A_GamingAngel);
	CREATE_VALUE(A_GamingAlien);
	CREATE_VALUE(A_GamingRoma);
	CREATE_VALUE(A_GamingMoney);

	CREATE_VALUE(A_FinishBG);
	CREATE_VALUE(A_FinishTVC);

///////////////////////////////////////
// Plane
///////////////////////////////////////
	CREATE_VALUE(P_Start);
	CREATE_VALUE(P_Character);
	CREATE_VALUE(P_Teaching);
	CREATE_VALUE(P_TeachingMessage1);
	CREATE_VALUE(P_TeachingMessage2);
	CREATE_VALUE(P_Gaming);
	CREATE_VALUE(P_Finish);

///////////////////////////////////////
// Element
///////////////////////////////////////
	//CREATE_VALUE(E_StartBG);
	CREATE_VALUE(E_StartLoop);

	CREATE_VALUE(E_CharacterAngel);
	CREATE_VALUE(E_CharacterRoma);
	CREATE_VALUE(E_CharacterAlien);
	CREATE_VALUE(E_CharacterMoney);

	CREATE_VALUE(E_TeachingTitle);
	CREATE_VALUE(E_TeachingCountdown);
	CREATE_VALUE(E_TeachingSuccess);

	CREATE_VALUE(E_TeachingIcon1);
	CREATE_VALUE(E_TeachingMessage1);
	CREATE_VALUE(E_TeachingIcon2);
	CREATE_VALUE(E_TeachingMessage2);

	CREATE_VALUE(E_GameTitle);
	CREATE_VALUE(E_GameCountdown);

	CREATE_VALUE(E_FinishBG);
	CREATE_VALUE(E_FinishTVC);

///////////////////////////////////////
// Translate
///////////////////////////////////////
	CREATE_VALUE(T_Start2Character);

///////////////////////////////////////
// Theatre Animation Set
///////////////////////////////////////
	CREATE_VALUE(AS_DisplaySuccess1);
	CREATE_VALUE(AS_DisplaySuccess2);
	
	CREATE_VALUE(AS_FadeInTeaching1);
	CREATE_VALUE(AS_FadeOutTeaching1);
	
	CREATE_VALUE(AS_FadeInTeaching2);
	CREATE_VALUE(AS_FadeOutTeaching2);
	
	CREATE_VALUE(AS_FadeOutGamingTitle);

///////////////////////////////////////
// Theatre Animation
///////////////////////////////////////
	CREATE_VALUE(ANIM_TeachingTitleFadeOut);
	CREATE_VALUE(ANIM_GamingTitleFadeOut);

	CREATE_VALUE(ANIM_TeachingeSuccessFadeIn1);
	CREATE_VALUE(ANIM_TeachingeSuccessFadeOut1);
	CREATE_VALUE(ANIM_TeachingeSuccessFadeIn2);
	CREATE_VALUE(ANIM_TeachingeSuccessFadeOut2);
	
	CREATE_VALUE(ANIM_TeachingeFadeIn1);
	CREATE_VALUE(ANIM_TeachingeFadeOut1);
	CREATE_VALUE(ANIM_TeachingeFadeIn2);
	CREATE_VALUE(ANIM_TeachingeFadeOut2);
	
	

///////////////////////////////////////
// Event
///////////////////////////////////////
	CREATE_VALUE(EVENT_StartTeaching);
	CREATE_VALUE(EVENT_StartGaming);
	CREATE_VALUE(EVENT_StartRecord);
	CREATE_VALUE(EVENT_StartUpload);
	CREATE_VALUE(EVENT_Reset);

	CREATE_VALUE(EVENT_TeachingTimeout);
	CREATE_VALUE(EVENT_TeachingFinish);
	CREATE_VALUE(EVENT_BackgoundDisable);
};

#endif // !AIRWAVES_NAME_MANAGER