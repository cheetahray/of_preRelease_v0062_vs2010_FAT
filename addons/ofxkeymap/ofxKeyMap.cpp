#include "ofxKeyMap.h"

bool ofxKeyMap::isAltDown() 
{
	#ifdef TARGET_WIN32
    isAlt = ((GetKeyState( VK_MENU ) & 0x80) > 0);
	//#else
    //return (glutGetModifiers() & GLUT_ACTIVE_ALT);
	#endif
    return isAlt;
}

bool ofxKeyMap::isShiftDown() {
	#ifdef TARGET_WIN32
    isShift = ((GetKeyState( VK_SHIFT ) & 0x80) > 0);
	//#else
    //return (glutGetModifiers() & GLUT_ACTIVE_SHIFT);
	#endif
    return isShift;
}

bool ofxKeyMap::isControlDown() {
	#ifdef TARGET_WIN32
	isCtrl = ((GetKeyState( VK_CONTROL ) & 0x80) > 0);
	//#else
    //return (glutGetModifiers() & GLUT_ACTIVE_CTRL);
    #endif
    return isCtrl;
}

