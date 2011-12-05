#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	 

	ofSetVerticalSync(true);
	ofBackground(255,255,255);	
	
	serial.enumerateDevices();
	movIndex = -1;
	//----------------------------------- note:
	// < this should be set
	// to whatever com port
	// your serial device is
	// connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....

	//serial.setup("COM4");  						  // windows example
	serial.setup("/dev/cu.usbserial-A600ehce",2400); // mac osx example
	//serial.setup("/dev/ttyUSB0", 9600);			  //linux example

	//----------------------------------- 
	//font.loadFont("DIN.otf",64);
	
	frameByframe = false;

	fingerMovie[0].loadMovie("movies/fingers.mov");
	fingerMovie[1].loadMovie("movies/test.mov");
}

//--------------------------------------------------------------
void testApp::update(){
	
	if (false == frameByframe)
	{
		// (1) write the letter "a" to serial:
		//serial.writeByte('a');
		
		// (2) read
		// now we try to read 3 bytes
		// since we might not get them all the time 3 - but sometimes 0, 6, or something else,
		// we will try to read three bytes, as much as we can
		// otherwise, we may have a "lag" if we don't read fast enough
		// or just read three every time. now, we will be sure to 
		// read as much as we can in groups of three...
		// we want to read 8 bytes
		
		int bytesRequired = IDLen;
		
		unsigned char bytes[bytesRequired];
		
		// loop until we've read everything
		
			// check for data
			
			if ( serial.available() > 0 )
				
			{
				
				// try to read - note offset into the bytes[] array, this is so
				
				// that we don't overwrite the bytes we already have
				
				int result = serial.readBytes( bytes,
											  
											  bytesRequired );
				
				
				
				// check for error code
				
				if ( result == OF_SERIAL_ERROR )
					
				{
					
					// something bad happened
					
					ofLog( OF_LOG_ERROR, "unrecoverable error reading from serial" );
					
					// bail out
					
				}
				
				else if ( result == OF_SERIAL_NO_DATA )
					
				{
					cout << "OF_SERIAL_NO_DATA" << endl;
					// nothing was read, try again
					
				}
				
				else
					
				{
					
					// we read some data!
					if( 0 == strncmp( (const char *) bytes, "28001D4F9C", 10) )
						movIndex = 0;
					else if( 0 == strncmp( (const char *) bytes, "2300CB9EAB", 10) )
						movIndex = 1;
					else
						movIndex = -1;
					
					if( movIndex > -1 )
					{	
						fingerMovie[movIndex].stop();
						fingerMovie[movIndex].play();
						fingerMovie[movIndex].setLoopState(OF_LOOP_NONE);
						frameByframe = true;
					}
					
				}
				
			}
			
			ofSleepMillis(300);
			
	}
	else
	{
		if ( serial.available() > 0 )
		{
			int result = 0;
			while ( result = serial.readByte() ) {
				if ( result == OF_SERIAL_ERROR )
					
				{
					
					// something bad happened
					
					break;
					// bail out
					
				}
				
				else if ( result == OF_SERIAL_NO_DATA )
					
				{
					cout << "OF_SERIAL_NO_DATA" << endl;
					// nothing was read, try again
					break;
				}
				
				else
					
				{
					;
				}
					
			}
		}
		fingerMovie[movIndex].update();
	}

}

//--------------------------------------------------------------
void testApp::draw()
{

	if( true == frameByframe )
	{
	
		if( true == fingerMovie[movIndex].getIsMovieDone() )
		{
			frameByframe = false;
		}

	}
	
	if(movIndex >= 0)
		fingerMovie[movIndex].draw(20,20);

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

