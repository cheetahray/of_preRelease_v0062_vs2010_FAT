#include "ofMain.h"
#include "testApp.h"


//========================================================================
int main( ){

	ofSetupOpenGL(1280,1024, OF_WINDOW);			// <-------- setup the GL context
	ofSetWindowPosition(0,-1000);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:

	ofRunApp(new testApp());

}
