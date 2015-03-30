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
const int cSECOND_GAMING_RECODEING = 4.0;
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
static const float cRECODE_DURATION = 5.0; //second

//Video creater
static const string cVIDEO_PATH = "results/";
static const int cVIDEO_WIDTH = 640;
static const int cVIDEO_HEIGHT = 480;
static const string cVIDEO_SIZE = "640:480";
static const float cCROP_ASPECT_RADIO = 640;

static const string cCREATE_IMAGE_SLIDER_CMD = "ffmpeg -y -loop 1 -i data/buffer/pic/1.jpg \
												-loop 1 -i data/buffer/pic/2.jpg \
												-loop 1 -i data/buffer/pic/3.jpg \
												-loop 1 -i data/buffer/pic/4.jpg \
												-loop 1 -i data/buffer/pic/5.jpg \
												-filter_complex \" \
												[0:v]trim=duration=1,fade=t=in:st=0:d=0.1:color=white[v0]; \
												[1:v]trim=duration=1,fade=t=in:st=0:d=0.1:color=white[v1]; \
												[2:v]trim=duration=1,fade=t=in:st=0:d=0.1:color=white[v2]; \
												[3:v]trim=duration=1,fade=t=in:st=0:d=0.1:color=white[v3]; \
												[4:v]trim=duration=1,fade=t=in:st=0:d=0.1:color=white,fade=t=out:st=0.9:d=0.1:color=white[v4]; \
												[v0][v1][v2][v3][v4]concat=n=5:v=1:a=0,hflip,format=yuv420p[v]\" \
												 -r 24 -map \"[v]\"data/buffer/output1.mp4";

static const string cCREATE_VIDEO_CMD = "ffmpeg -y -i data/" + cVIDEO_BUFFER + "%4d.jpg \
										 -vf \"scale=" + cVIDEO_SIZE + ", hflip\" -c:v libx264 -profile:v main -r 24 -pix_fmt yuv420p \
										 -threads 4 data/buffer/output2.mp4";

static const string cSLIDER_TO_MPEG = "ffmpeg -y -i data/buffer/output1.mp4 -r 24 -c copy -bsf:v h264_mp4toannexb -an -f mpegts data/buffer/output1";
static const string cVIDEO_TO_MPEG = "ffmpeg -y -i data/buffer/output2.mp4 -r 24 -c copy -bsf:v h264_mp4toannexb -an -f mpegts data/buffer/output2";

static const string cCOMBIND_VIDEO_CMD = "ffmpeg -y -i \"concat:data/buffer/output1|data/buffer/output2\" data/results/test.mp4";
static const string cCLEAR_VIDEO_BUFFER_CMD = "del .\\data\\buffer\\pic\\*.jpg";
static const string cCLEAR_IMAGE_BUFFER_CMD = "del .\\data\\buffer\\videos\\*.jpg";

#endif // !AIRWAVES_CONST_PARAMETER
