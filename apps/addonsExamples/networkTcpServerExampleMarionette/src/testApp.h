#ifndef _TEST_APP
#define _TEST_APP

//#define OF_ADDON_USING_OFXOPENCV
//#define OF_ADDON_USING_OFXOBJLOADER
#define OF_ADDON_USING_OFXDIRLIST
//#define OF_ADDON_USING_OFXVECTORMATH
//#define OF_ADDON_USING_OFXNETWORK
//#define OF_ADDON_USING_OFXVECTORGRAPHICS
//#define OF_ADDON_USING_OFXOSC
//#define OF_ADDON_USING_OFXTHREAD
//#define OF_ADDON_USING_OFXXMLSETTINGS

#define bytesRequired 1024

#define _TWO_
#define _UP_
//#define _ILAN_

//#define _IR_
//#define _NOTURN_
//#define _GUAN_
//#define _LUMI_
//#define PUTA

#ifndef _IR_
//#define _KINECT_
#endif

//#define _PLAY_
//#define _MOVIE_

#include "ofMain.h"
#include "ofAddons.h"
#include "GuiHandler.h"
#include "ofxNetwork.h"
#include "json.h"
#include <iostream>
#include "ofxTimer.h"

#ifdef PUTA
#include "ofxOsc.h"
#endif

class testApp : public ofSimpleApp
{

	public:

		void setup();

		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();

		void testFunction(int setting);
		void reqAT(string a, string b, int which);
		void resAT(string a, string b, int which);
		void reqSlider(string a, string b, int value, int which);
		void reqJSON(string a, string b, string value, int which);
		void ContinueTimer();
		void MaTimer();
		void reqBatch(string a, int which);
		void resBatch(string a, int which);
		void reqQuestion(string a, int which);
		void sendDMX(string buffer);
		void tenSix(string realCmd, int frontback, int baseIdx);
		void request(string cmd, int which);
		void reqFAQ(string a, string b, int which);
		void Interval(ofEventArgs &e);
		void readJSON();
		void parsePnJSON(string ss, int timeInt);
		void parseMaJSON(string ss);
		void reqflush(int which);
		void PnMaExchange();
		float mapRay(float value, float dL, float dR, float mL, float mR);

		GuiHandler*         gui;

        bool    myValue1,myValue2,myValue3,myValue4,myValue5, myValue51, myValue52, myValue53, myValue56, myValue57, myValue59, preventStupid, InPn, oneTwentySeven, myValue73, myValue74, myValue75, myValue76;
		bool	myValue34, myValue35, myValue36, myValue37, myValue60, myValue61, readyBreak, waitRes, timeOutContinue, myValue64, myValue32, myValue33, myValue39, myValue42, myValue69, myValue70, myValue71, myValue72;
        bool	myValue78;
		int     upValue0,ouValue0;
        int     upValue1,ouValue1;
        int     upValue2,ouValue2;
		int     upValue3,ouValue3;
		int     upValue4,ouValue4;
		int     upValue5,ouValue5;
		int     upValue6,ouValue6;
		int     lValue0,olValue0;
		int     lValue1,olValue1;
		int     lValue2,olValue2;
		int     lValue3,olValue3;
		int     lValue4,olValue4;
		int     lValue5,olValue5;
		int     lValue6,olValue6;
		int     lValue7,olValue7;
		int     lValue8,olValue8;
		int     lValue9,olValue9;
		int     lValue10,olValue10;
		int     rValue0,orValue0;
		int     rValue1,orValue1;
		int     rValue2,orValue2;
		int     rValue3,orValue3;
		int     rValue4,orValue4;
		int     rValue5,orValue5;
		int     rValue6,orValue6;
		int     rValue7,orValue7;
		int     rValue8,orValue8;
		int     rValue9,orValue9;
		int     rValue10,orValue10;
		
        int which, myValue54, myValue58, myValue65, myValue66, myValue67, myValue68, trigIndex, myValue40, thatInt;
		int myValue77;
		/*
        bool toggle1a;
        bool toggle1b;
		string  myString3;
		*/
		int connectTime, deltaTime, now1, RGB, rgbValue;
		#ifdef _LUMI_
		ofxTCPClient tcpClient;
		bool weConnected;
		#elif _DMX_
		ofSerial	DMX;
		#endif
		#ifdef _KINECT_
		ofxTCPClient kinectClient;
		bool kinectConnected;
		#endif
		#ifdef _UP_
		ofSerial	serial,serialH;
		#endif
		#ifdef _TWO_
		ofSerial	serialL,serialR;
		#endif	
		#ifdef _IR_
		ofSerial serialA;
		#endif
		string msgRx, myValue50, myValue55, myValue62, lastss, myValue63, myValue38;
		unsigned char bytes[bytesRequired];
		char tmpBytes[bytesRequired];
		char jsonBytes[bytesRequired];
		//float xxxx[30],yyyy[30],zzzz[30];
		unsigned char * cptr;
		vector<string> cmdQuene;
		vector<string> cmdQueneH;
		vector<string> cmdQueneL;
		vector<string> cmdQueneR;
		Json::Value root;   // will contains the root value after parsing.
		Json::Reader reader;
		vector<string>::iterator it;
		Json::Value::Members motorMember;
		ofstream ofout;
		ofxTimer timer;

		#ifdef _PLAY_
		#ifdef _MOVIE_
		ofVideoPlayer 		vocals;
		#else
		ofSoundPlayer  vocals;
		#endif
		#endif

		float 			synthPosition;
		ofTrueTypeFont  franklinBook;

		time_t rawtime;
		struct tm * timeinfo;
		char timebuffer [2][4];

		#ifdef PUTA
		ofxOscReceiver	receiver;

		int			current_msg_string;
		string		msg_strings[32];
		#endif
		
};

#endif