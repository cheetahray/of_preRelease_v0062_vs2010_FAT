#ifndef _TEST_APP
#define _TEST_APP


#define OF_ADDON_USING_OFXOPENCV
//#define OF_ADDON_USING_OFXOBJLOADER
//#define OF_ADDON_USING_OFXDIRLIST
#define OF_ADDON_USING_OFXVECTORMATH
//#define OF_ADDON_USING_OFXNETWORK
//#define OF_ADDON_USING_OFXVECTORGRAPHICS
//#define OF_ADDON_USING_OFXOSC
//#define OF_ADDON_USING_OFXTHREAD
#define OF_ADDON_USING_OFXXMLSETTINGS

//#define _IMAGE_ 
#define _TCP_

#ifdef _IMAGE_
#define movWidth 1024
#define movHeight 768
#else
#define movWidth 1680
#define movHeight 1050
#endif

#include "ofMain.h"
#include "ofAddons.h"
#include "renderManager.h"
#include "ofxNetwork.h"
#include "ofxKeyMap.h"

class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void xxyy(int key);
        renderManager rm;

        ofRectangle guiIn;
        ofRectangle guiOut;
		
		int index[2], firstTime;
		
        bool toggleImage, showString, bPause, xAdjust, yAdjust, bSelect, maximum, moveall;
        
		#ifdef _IMAGE_
		
		ofImage twoScreenImage;
		
		#else
		
		ofVideoPlayer 		fingerMovie;
		
		#endif
		
		#ifdef _TCP_
		ofxTCPClient tcpClient;
		#endif
	
		int connectTime;
		int deltaTime;
		int synFrame;
		int mWidth, mHeight;
		bool weConnected;

		ofxKeyMap ofkey;
};

#endif

