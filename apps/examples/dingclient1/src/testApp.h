#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxXmlSettings.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void resized(int w, int h);
		//void ultostr(char *buf, unsigned long uval, int base , int uppercase);
		ofVideoPlayer 		fingerMovie;
		bool                frameByframe, iftcp, weConnected;
        string  Server;
		ofxTCPClient tcpClient;
        ofxXmlSettings XML;
		int connectTime, miniSeconds, deltaTime, firstTime, lastFrame, nowFrame;
        float xx, yy;
};

#endif
