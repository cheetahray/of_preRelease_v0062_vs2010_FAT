#include "testApp.h"

#define PORT 11999
#define mini 599
//--------------------------------------------------------------
void testApp::setup(){
	//ofBackground(255,255,255);
	
	frameByframe = false;
    if( XML.loadFile("mySettings.xml") )
    {
		miniSeconds = XML.getValue("CONFIG:miniSeconds", mini);
        fingerMovie.loadMovie(XML.getValue("CONFIG:file", "fingers.mp4"));
        xx = XML.getValue("CONFIG:x", 1024);
        yy = XML.getValue("CONFIG:y", 768);
        iftcp = XML.getValue("CONFIG:iftcp", false);
        howmuch = XML.getValue("CONFIG:howmany", 3);
	}
    else{
		miniSeconds = mini;
        fingerMovie.loadMovie("fingers.mp4");
        xx = 1024;
        yy = 768;
        iftcp = false;
        howmuch = 3;
	}
   
    count = lastFrame = nowFrame = firstTime = 0;
	while(count < howmuch)
    {
        index[count++] = false;
    }
    if(true == iftcp)
    {                          
        TCP.setup(PORT);
    }
    else
    {
        fingerMovie.play();
        fingerMovie.setLoopState(OF_LOOP_NORMAL);                          
    }
}

//--------------------------------------------------------------
void testApp::update(){
    
    fingerMovie.idleMovie();
	
    if(true == iftcp)
    {
    
        nowFrame = fingerMovie.getCurrentFrame();
        
        if( 1 == firstTime && ( nowFrame < lastFrame ) )
        {    
            //fingerMovie.firstFrame();
            fingerMovie.setPaused(true);
            firstTime = 2;
        }
        
        //if( 0 == firstTime || nowFrame < 300 || (nowFrame > totalFrame - 300) )
        {
            for(int i = 0; i < TCP.getNumClients(); i++)
            {
                string str = TCP.receive(i);
		 
                if( str.length() > 0 )
                {
                    if(1 == ofToInt(str))
                    {
                        index[i] = true;
                    }
                }	
            }

        }
        
        bool totalBool = true;
        count = 0;
        while (count < howmuch) {
            if(false == index[count++])
            {
                totalBool = false;
                break;
            }
        }
        
        if(true == totalBool)
        {
            
            count = 0;
            while(count < howmuch)
            {
                TCP.send(count++, "5");
            }
            
            ofSleepMillis(miniSeconds);

            if(firstTime == 0)
            {
                fingerMovie.play();
                fingerMovie.setLoopState(OF_LOOP_NORMAL);
            }
            else
            {
                fingerMovie.setPaused(false);
            }
            firstTime = 1;
        
            count = 0;
            while(count < howmuch)
            {
                index[count++] = false;
            }
            
        }
        
        lastFrame = nowFrame;
    }
}

//--------------------------------------------------------------
void testApp::draw(){

	//ofSetColor(0xFFFFFF);




    fingerMovie.draw(0,0,xx,yy);
    /*
	ofSetColor(0x000000);
    unsigned char * pixels = fingerMovie.getPixels();
    // let's move through the "RGB" char array
    // using the red pixel to control the size of a circle.
    for (int i = 4; i < 320; i+=8){
        for (int j = 4; j < 240; j+=8){
            unsigned char r = pixels[(j * 320 + i)*3];
            float val = 1 - ((float)r / 255.0f);
            ofCircle(400 + i,20+j,10*val);
        }
    }


    ofSetColor(0x000000);
	ofDrawBitmapString("press f to change",20,320);
    if(frameByframe) ofSetColor(0xCCCCCC);
    ofDrawBitmapString("mouse speed position",20,340);
    if(!frameByframe) ofSetColor(0xCCCCCC); else ofSetColor(0x000000);
    ofDrawBitmapString("keys <- -> frame by frame " ,190,340);
    ofSetColor(0x000000);

    ofDrawBitmapString("frame: " + ofToString(fingerMovie.getCurrentFrame()) + "/"+ofToString(fingerMovie.getTotalNumFrames()),20,380);
    ofDrawBitmapString("duration: " + ofToString(fingerMovie.getPosition()*fingerMovie.getDuration(),2) + "/"+ofToString(fingerMovie.getDuration(),2),20,400);
    ofDrawBitmapString("speed: " + ofToString(fingerMovie.getSpeed(),2),20,420);

    if(fingerMovie.getIsMovieDone()){
        ofSetColor(0xFF0000);
        ofDrawBitmapString("end of movie",20,440);
    }
	 char mytime[11];
	 ultostr(mytime+10, ofGetSystemTime(), 10, 0);
	 ofDrawBitmapString(mytime, 1700, 40);	*/
	//ofDrawBitmapString(ofToString(fingerMovie.getCurrentFrame()),0,10);
	
}
/*
void testApp::ultostr(char *buf, unsigned long uval, int base, int uppercase)
{
	int digit;
	if((base < 2) || (base > 36))
	{
		return;
	}
	*buf = '\0';
	do {
		digit = uval % base;
		uval /= base;
		*--buf = '0' + digit;
		if(digit > 9)
		{
			*buf = (uppercase ? 'A' :'a') + digit - 10;
		}
	} while (uval);
}
*/
//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    switch(key){
        case 'f':
            frameByframe=!frameByframe;
            fingerMovie.setPaused(frameByframe);
        break;
        case OF_KEY_LEFT:
            fingerMovie.previousFrame();
        break;
        case OF_KEY_RIGHT:
            fingerMovie.nextFrame();
        break;
        case '0':
            fingerMovie.firstFrame();
        break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	/*
	if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        float speed = (2 * pct - 1) * 5.0f;
        fingerMovie.setSpeed(speed);
	}
	*/
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	/*
	if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        fingerMovie.setPosition(pct);
	}
	*/
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	/*
	if(!frameByframe){
        fingerMovie.setPaused(true);
	}
	*/
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	/*
	if(!frameByframe){
        fingerMovie.setPaused(false);
	}
	*/
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}
