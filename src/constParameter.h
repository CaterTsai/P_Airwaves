#ifndef AIRWAVES_CONST_PARAMETER
#define AIRWAVES_CONST_PARAMETER

#include "ofMain.h"

const int cWINDOW_WIDTH = 1280;
const int cWINDOW_HEIGHT = 720;

typedef enum eCHARACTER_TYPE
{
	eCHARACTER_ANGEL = 0,
	eCHARACTER_ROMA,
	eCHARACTER_ALIEN,
	eCHARACTER_MONEY,
	eCHARACTER_NUM
};

//Theatre
const eCHARACTER_TYPE cCHARACTER_MAX_TYPE = eCHARACTER_MONEY;
const int cSECOND_TEACHING_TIMEOUT = 5.0;
const int cSECOND_GAMING_TIMEOUT = 10.0;
const int cSECOND_TVC_PLAY = 5.0;

//AudioChecker
const int cAUDIO_BUFFER_SIZE = 32;
const float cAUDIO_TRIGGER_LIMIT = 0.4;

//image recoder setting
static const int cTHREAD_NUM = 3;
static const string cVIDEO_BUFFER = "buffer/videos/";
static const string cPICTURE_BUFFER = "buffer/pic/";
static const int cPICTURE_NUM = 5;
static const string cPHOTO_FORMAT = "jpg";
static const float cRECODE_DURATION = 10.0; //second
static const int cVIDEO_WIDTH = 398;
static const int cVIDEO_HEIGHT = 700;
static const float cCROP_ASPECT_RADIO = 398.0/700.0;

#endif // !AIRWAVES_CONST_PARAMETER
