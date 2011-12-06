#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxNetwork.h"

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
		void ultostr(char *buf, unsigned long uval, int base , int uppercase);
		ofVideoPlayer 		fingerMovie;
		bool                frameByframe;
	
		ofxTCPClient tcpClient;
	
		int connectTime;
		int deltaTime;
		int firstTime;
		bool weConnected;
	
};

#endif