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
	CREATE_VALUE(S_Upload);
	CREATE_VALUE(S_Finish);

///////////////////////////////////////
// Actor
///////////////////////////////////////
	CREATE_VALUE(A_StartBG);
	CREATE_VALUE(A_StartLoop);
	CREATE_VALUE(A_CharacterAngel);
	CREATE_VALUE(A_CharacterAlien);
	CREATE_VALUE(A_CharacterRoma);
	CREATE_VALUE(A_CharacterMoney);

	CREATE_VALUE(A_TeachingTitle);
	
	CREATE_VALUE(A_GamingTitle);
	CREATE_VALUE(A_GameCountdown);

	CREATE_VALUE(A_UploadBG);
	CREATE_VALUE(A_UploadLoop);
	CREATE_VALUE(A_FinishBG);
	CREATE_VALUE(A_FinishTVC);

///////////////////////////////////////
// Plane
///////////////////////////////////////
	CREATE_VALUE(P_Start);
	CREATE_VALUE(P_Character);
	CREATE_VALUE(P_Teaching);
	CREATE_VALUE(P_Gaming);
	CREATE_VALUE(P_Upload);
	CREATE_VALUE(P_Finish);

///////////////////////////////////////
// Element
///////////////////////////////////////
	CREATE_VALUE(E_StartBG);
	CREATE_VALUE(E_StartLoop);

	CREATE_VALUE(E_CharacterAngel);
	CREATE_VALUE(E_CharacterRoma);
	CREATE_VALUE(E_CharacterAlien);
	CREATE_VALUE(E_CharacterMoney);

	CREATE_VALUE(E_TeachingTitle);

	CREATE_VALUE(E_GameTitle);
	CREATE_VALUE(E_GameCountdown);
	
	CREATE_VALUE(E_UploadBG);
	CREATE_VALUE(E_UploadLoop);

	CREATE_VALUE(E_FinishBG);
	CREATE_VALUE(E_FinishTVC);

///////////////////////////////////////
// Translate
///////////////////////////////////////
	CREATE_VALUE(T_Start2Character);

///////////////////////////////////////
// Event
///////////////////////////////////////
	CREATE_VALUE(EVENT_Reset);
};

#endif // !AIRWAVES_NAME_MANAGER