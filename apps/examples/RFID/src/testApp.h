#ifndef _TEST_APP
#define _TEST_APP
#define IDLen 11
#define movNum 2
#include "ofMain.h"

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		//ofTrueTypeFont		font;
		
		ofSerial	serial;
		int			movIndex;
		ofVideoPlayer 		fingerMovie[2];
		bool                frameByframe;
};

#endif	

