#ifndef OFX_KEY_MAP
#define OFX_KEY_MAP

/************************************************************

OpenFrameworks Library

File: 			ofxKeyMap.h
Description: 	Keeps track of pressed keys
Notes:

Last Modified: 2009.09.17
Creator: Rick Companje

************************************************************/

#include "ofMain.h"

//#define NUM_KEYS 512

class ofxKeyMap {
public:

	bool isAltDown();
    bool isShiftDown();
    bool isControlDown();
    bool isAlt, isShift, isCtrl;
	/*
    inline bool & operator [] (int i) { return keys[i]; }
	bool isKeyDown(int key);

private:
    bool keys[NUM_KEYS];
	 */
	
};

#endif
