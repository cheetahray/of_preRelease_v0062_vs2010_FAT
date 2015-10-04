#include "testApp.h"

#define IMA_STR "ima"
#define T0 "t0"
#define T1 "t1"
#define T2 "t2"
#define T3 "t3"
#define T4 "t4"
#define T5 "t5"
#define T6 "t6"
#define T7 "t7"
#define T8 "t8"
#define T9 "t9"
#define T10 "t10"
#define QT0 "?t0"
#define QT1 "?t1"
#define QT2 "?t2"
#define QT3 "?t3"
#define QT4 "?t4"
#define QT5 "?t5"
#define QT6 "?t6"
#define QT7 "?t7"
#define QT8 "?t8"
#define QT9 "?t9"
#define QT10 "?t10"
#define STOP_STR "STOP"
#define LFCR "\r\n"
#define INTERVAL "Inter"
#define SPEEDIVIDER "SpeedDivider"
#define JSON "json.txt"
#define FIRSTINDEX "a0c"//"a0c"
#define DownDown "mr1000"
#define DownAll "mr13000"
#define UP 0
#define LEFT 1
#define RIGHT 2
#define UPHEAD 3
#define ALL 4
#define LOWLIMIT 3
//dl,dn,ds,ed
#define MIDDLE 0
#define TIMEINT 32
#define PnInterval 500
#define secShift 83
/*
pn02
pn05
pn10
pn11
pn23
pn24
pn50
tid

*/
#define CntShiftLog 38
#define SERVER "192.168.11.40"
#define PORT 12345

//--------------------------------------------------------------
void testApp::setup()
{
	franklinBook.loadFont("frabk.ttf", 72);
	
	ofBackground(127,127,127);
	readJSON();

	#ifdef _PLAY_
	#ifdef _MOVIE_
	vocals.loadMovie("MVI_8225.mp4");
	#else
	vocals.loadSound("1228M001.mp3");
	//vocals.setMultiPlay(false);
	#endif
	#endif

	gui = new GuiHandler;
	int idx = 0;

	GuiPanel*  Panel1 = gui->addPanel("Button", 0,0, 200,700);
		#ifndef _ILAN_		
        Panel1->addButton(STOP_STR,100,20,"TRIGGER"/*"SWITCH"*/,true, 2, &myValue2);
		Panel1->addRadio("Record?",10, 2, 54, &myValue54);
	    Panel1->addRadioElement(54,"No");
		Panel1->addRadioElement(54,"Yes");
		Panel1->addButton("Get Axises",100,20,"TRIGGER"/*"SWITCH"*/,true, 52, &myValue52);
	    Panel1->addTextField(INTERVAL,140,20, ofToString(root[FIRSTINDEX][INTERVAL].asInt() + 1), 62, &myValue62);
		Panel1->addTextField("Motor Index",140,20, FIRSTINDEX, 55, &myValue55);
		#endif	
		Panel1->addButton("Action!!",100,20,"TRIGGER"/*"SWITCH"*/,true, 53, &myValue53);
		Panel1->addButton("Go to Pose",100,20,"TRIGGER"/*"SWITCH"*/,true, 57, &myValue57);
	    Panel1->addButton("Next Step",100,20,"TRIGGER"/*"SWITCH"*/,true, 79, &myValue79);
	    #ifndef _ILAN_		
        Panel1->addTextField("Velocity",140,20, "150", 50, &myValue50);
		Panel1->addButton("Set PN Speed",100,20,"TRIGGER"/*"SWITCH"*/,true, 56, &myValue56);
		Panel1->addButton("Get Down",100,20,"TRIGGER"/*"SWITCH"*/,true, 34, &myValue34);
	    Panel1->addButton("Get DownI",100,20,"TRIGGER"/*"SWITCH"*/,true, 35, &myValue35);
	    Panel1->addButton("Get DownII",100,20,"TRIGGER"/*"SWITCH"*/,true, 60, &myValue60);
		Panel1->addButton("Get Up",100,20,"TRIGGER"/*"SWITCH"*/,true, 36, &myValue36);
		Panel1->addButton("Get UpII",100,20,"TRIGGER"/*"SWITCH"*/,true, 37, &myValue37);
	    Panel1->addButton("Get UpIII",100,20,"TRIGGER"/*"SWITCH"*/,true, 59, &myValue59);
		Panel1->addButton("Home",100,20,"TRIGGER"/*"SWITCH"*/,true, 61, &myValue61);
	    Panel1->addButton("Get DownIV",100,20,"TRIGGER"/*"SWITCH"*/,true, 74, &myValue74);
	GuiPanel*  Panel2 = gui->addPanel("TOP", 200, 0, 1100,700);
		Panel2->addRadio("LeftI",25, 13, 65, &myValue65);
			Panel2->addRadioElement(65,"l_ankle");
            Panel2->addRadioElement(65,"l_but");
            Panel2->addRadioElement(65,"l_shoulder");
			Panel2->addRadioElement(65,"l_chest");
            Panel2->addRadioElement(65,"l_knee");
            Panel2->addRadioElement(65,"l_foot");
			Panel2->addRadioElement(65,"l_elbow");
            Panel2->addRadioElement(65,"l_leg");
            Panel2->addRadioElement(65,"l_hand");
			Panel2->addRadioElement(65,"R brain");
            Panel2->addRadioElement(65,"L brain");
			Panel2->addButton("Up",100,20,"TRIGGER"/*"SWITCH"*/,true, 69, &myValue69);
			Panel2->addButton("Down",100,20,"TRIGGER"/*"SWITCH"*/,true, 73, &myValue73);
		Panel2->addRadio("RightI",25, 13, 67, &myValue67);
			Panel2->addRadioElement(67,"r_ankle");
            Panel2->addRadioElement(67,"r_but");
            Panel2->addRadioElement(67,"r_shoulder");
			Panel2->addRadioElement(67,"r_back");
            Panel2->addRadioElement(67,"r_knee");
            Panel2->addRadioElement(67,"r_foot");
			Panel2->addRadioElement(67,"r_elbow");
            Panel2->addRadioElement(67,"r_leg");
            Panel2->addRadioElement(67,"r_hand");
            Panel2->addRadioElement(67,"B brain");
			Panel2->addRadioElement(67,"C brain");
			Panel2->addButton("Up",100,20,"TRIGGER"/*"SWITCH"*/,true, 71, &myValue71);
			Panel2->addButton("Down",100,20,"TRIGGER"/*"SWITCH"*/,true, 75, &myValue75);
		
        Panel2->addRadio("Both Hands and Legs",25, 11, 58, &myValue58);
			Panel2->addRadioElement(58,"But");
            Panel2->addRadioElement(58,"Shoulder");
            Panel2->addRadioElement(58,"Knee");
			Panel2->addRadioElement(58,"Elbow");
            Panel2->addRadioElement(58,"Hand");
            Panel2->addRadioElement(58,"Head");
			
			Panel2->addRadioElement(58,"LFoot");
			Panel2->addRadioElement(58,"RFoot");
			Panel2->addRadioElement(58,"FHead");

		Panel2->bindKey(58,OF_KEY_RIGHT);
        Panel2->bindKey2(58,OF_KEY_LEFT);
		//Panel2->addButton("Do it!!",100,20,"TRIGGER"/*"SWITCH"*/,true, 32, &myValue32);
		Panel2->addButton("Up",100,20,"TRIGGER"/*"SWITCH"*/,true, 42, &myValue42);
		Panel2->addButton("Down",100,20,"TRIGGER"/*"SWITCH"*/,true, 32, &myValue32);
		Panel2->addTextField("PosNum",140,20, "", 80, &myValue80);
		//Panel2->addButton("Reset H",100,20,"TRIGGER"/*"SWITCH"*/,true, 33, &myValue33);
		Panel2->addButton("NOP",100,20,"TRIGGER"/*"SWITCH"*/,true, 64, &myValue64);
	    Panel2->addButton("Max Currency",100,20,"TRIGGER"/*"SWITCH"*/,true, 51, &myValue51);
		
		Panel2->addRadio("Segments",25, 11, 77, &myValue77);
			Panel2->addRadioElement(77,"Nothing");
			Panel2->addRadioElement(77,"I");
			Panel2->addRadioElement(77,"Jordan");
			Panel2->addRadioElement(77,"III");
			Panel2->addRadioElement(77,"standup");
			Panel2->addRadioElement(77,"salute");
			Panel2->addRadioElement(77,"The End");
		Panel2->addButton("Go",100,20,"TRIGGER"/*"SWITCH"*/,true, 78, &myValue78);

		Panel2->addRadio("UP/LEFT/RIGHT",25, 4, 40, &myValue40);
            Panel2->addRadioElement(40,"UP");
            Panel2->addRadioElement(40,"LEFT");
            Panel2->addRadioElement(40,"RIGHT");
        Panel2->addTextField("CommandLine",140,20, "", 38, &myValue38);
		Panel2->addButton("Command",100,20,"TRIGGER"/*"SWITCH"*/,true, 39, &myValue39);
		
		#endif	
		/*
        GuiPanel*  Panel3 = gui->addPanel("panel 3",640,70,250,250);

		Panel3->addFileList("fileBrowse",200,200,"files",10, &myString3);
			Panel3->bindKey(10,']');
            Panel3->bindKey2(10,'[');
		*/

	GuiPanel*  Panel3 = gui->addPanel("LEFT",0,700,350,500);
		#ifndef _ILAN_
        //Panel2->addFloatSlider("slider1",140,10, 26.8, 100, 4, &myValue4);
        Panel3->addIntSlider("0. Foot Back", 300, 10, root[FIRSTINDEX]["?t0pe"][idx].asInt(), 136666, 11, &lValue0);
        Panel3->addIntSlider("1. But", 300, 10, root[FIRSTINDEX]["?t1pe"][idx].asInt(), 205215, 12, &lValue1);
        Panel3->addIntSlider("2. Shoulder", 300, 10, root[FIRSTINDEX]["?t2pe"][idx].asInt(), 162302, 13, &lValue2);
        Panel3->addIntSlider("3. Chest", 300, 10, root[FIRSTINDEX]["?t3pe"][idx].asInt(), 152000, 14, &lValue3);
        Panel3->addIntSlider("4. Knee", 300, 10, root[FIRSTINDEX]["?t4pe"][idx].asInt(), 140000, 15, &lValue4);
        Panel3->addIntSlider("5. Foot Front", 300, 10, root[FIRSTINDEX]["?t5pe"][idx].asInt(), 115000, 16, &lValue5);
        Panel3->addIntSlider("6. Hand Left/Right", 300, 10, root[FIRSTINDEX]["?t6pe"][idx].asInt(), 100000, 17, &lValue6);
        Panel3->addIntSlider("7. Elbow", 300, 10, root[FIRSTINDEX]["?t7pe"][idx].asInt(), 186999, 18, &lValue7);
        Panel3->addIntSlider("8. Foot Side", 300, 10, root[FIRSTINDEX]["?t8pe"][idx].asInt(), 168700, 19, &lValue8);
        Panel3->addIntSlider("9. Hand Forward/Backward", 300, 10, root[FIRSTINDEX]["?t9pe"][idx].asInt(), 115000, 20, &lValue9);
        Panel3->addIntSlider("10. Hand UP/Down", 300, 10, root[FIRSTINDEX]["?t10pe"][idx].asInt(), 203000, 41, &lValue10);
		
	GuiPanel*  Panel4 = gui->addPanel("RIGHT",350, 700,1000,500);

        //Panel2->addFloatSlider("slider1",140,10, 26.8, 100, 4, &myValue4);
        Panel4->addIntSlider("0. Foot Back", 300, 10, root[FIRSTINDEX]["?t0pe"][1].asInt(), 125666, 21, &rValue0);
        Panel4->addIntSlider("1. But", 300, 10, root[FIRSTINDEX]["?t1pe"][1].asInt(), 148180, 22, &rValue1);
        Panel4->addIntSlider("2. Shoulder", 300, 10, root[FIRSTINDEX]["?t2pe"][1].asInt(), 170000, 23, &rValue2);
        Panel4->addIntSlider("3. Body Back", 300, 10, root[FIRSTINDEX]["?t3pe"][1].asInt(), 162400, 24, &rValue3);
        Panel4->addIntSlider("4. Knee", 300, 10, root[FIRSTINDEX]["?t4pe"][1].asInt(), 140000, 25, &rValue4);
        Panel4->addIntSlider("5. Foot Front", 300, 10, root[FIRSTINDEX]["?t5pe"][1].asInt(), 148712, 26, &rValue5);
		Panel4->addIntSlider("6. Hand Left/Right", 300, 10, root[FIRSTINDEX]["?t6pe"][1].asInt(), 100000, 27, &rValue6);
        Panel4->addIntSlider("7. Elbow", 300, 10, root[FIRSTINDEX]["?t7pe"][1].asInt(), 164500, 28, &rValue7);
        Panel4->addIntSlider("8. Foot Side", 300, 10, root[FIRSTINDEX]["?t8pe"][1].asInt(), 168700, 29, &rValue8);
        Panel4->addIntSlider("9. Hand Forward/Backward", 300, 10, root[FIRSTINDEX]["?t9pe"][1].asInt(), 115000, 30, &rValue9);
        Panel4->addIntSlider("10. Hand UP/Down", 300, 10, root[FIRSTINDEX]["?t10pe"][1].asInt(), 216000, 31, &rValue10);
		//Panel4->addIntSlider("10. Heand UP/Down", 300, 10, 10000, 20000, 31, &rValue10);
		#else
		Panel3->addButton(STOP_STR,100,20,"TRIGGER"/*"SWITCH"*/,true, 2, &myValue2);
		#endif
	
	GuiPanel*  Panel5 = gui->addPanel("Single", 700,700,350,500);
		//Panel2->addFloatSlider("slider1",140,10, 26.8, 100, 4, &myValue4);
        Panel5->addIntSlider("0. Horizontal", 300, 10, root[FIRSTINDEX]["?t0pe"][2].asInt(), 741660, 4, &upValue0);
        Panel5->addIntSlider("1. Vertical", 300, 10, root[FIRSTINDEX]["?t1pe"][2].asInt(), 297719, 5, &upValue1);
		Panel5->addIntSlider("2. Head Rotation", 300, 10, root[FIRSTINDEX]["?t2pe"][2].asInt(), 9997, 6, &upValue2);
        Panel5->addIntSlider("3. Body Rotation", 300, 10, root[FIRSTINDEX]["?t3pe"][2].asInt(), 118832, 7, &upValue3);
		Panel5->addIntSlider("4. Right Head", 300, 10, root[FIRSTINDEX]["?t4pe"][2].asInt(), 200000, 8, &upValue4);
		Panel5->addIntSlider("5. Left Head", 300, 10, root[FIRSTINDEX]["?t5pe"][2].asInt(), 200000, 9, &upValue5);
		Panel5->addIntSlider("6. Back Head", 300, 10, root[FIRSTINDEX]["?t6pe"][2].asInt(), 200000, 10, &upValue6);
        
	#ifdef _TWO_
	serialL.setup(/**/"\\\\.\\COM24",9600);  						  // windows example
	serialR.setup(/**/"\\\\.\\COM22",9600);  						  // windows example
	#endif
	#ifdef _UP_
	serialH.setup(/**/"\\\\.\\COM21",9600);  						  // windows example
	serial.setup(/**/"\\\\.\\COM23",9600);  						  // windows example
	#endif
	#ifdef _IR_
	serialA.setup(/**/"\\\\.\\COM6",9600);
	#endif 
	cptr = bytes;
	upValue0=ouValue0=upValue1=ouValue1=upValue2=ouValue2=upValue3=ouValue3=upValue4=ouValue4=upValue5=ouValue5=upValue6=ouValue6=lValue0=olValue0=lValue1=olValue1=lValue2=olValue2=lValue3=olValue3=lValue4=olValue4=lValue5=olValue5=lValue6=olValue6=lValue7=olValue7=lValue8=olValue8=lValue9=olValue9=lValue10=olValue10=rValue0=orValue0=rValue1=orValue1=rValue2=orValue2=rValue3=orValue3=rValue4=orValue4=rValue5=orValue5=rValue6=orValue6=rValue7=orValue7=rValue8=orValue8=rValue9=orValue9=rValue10=orValue10=0;
	preventStupid = readyBreak = waitRes = false;	
	trigIndex = -1;
	deltaTime = connectTime = 0, lastxxxx = 0;
	#ifdef _LUMI_
	weConnected = tcpClient.setup(SERVER,PORT);
	tcpClient.setVerbose(true);
	#elif _DMX_
	DMX.setup(/**/"\\\\.\\COM16",9600);
	sendDMX("o");		
	#endif
	#ifdef _KINECT_
	kinectConnected = kinectClient.setup("127.0.0.1",11999);
	kinectClient.setVerbose(true);
	#endif
	#ifdef PUTA
	receiver.setup( PORT );

	current_msg_string = 0;
	#endif
	timer.setup(0,false);
	ofAddListener(timer.TIMER_REACHED, this, &testApp::Interval);

}

//--------------------------------------------------------------
void testApp::update(){

		int found;
		//we are connected - lets send our text and check what we get back
		#ifdef _KINECT_
		if(kinectConnected)
		{
			//kinectClient.send(msgTx);
				
			//if data has been sent lets update our text
			string str = kinectClient.receive();
			if( str.length() > 0 ){
				msgRx = str;
				if(trigIndex == -1)
				{
					#ifdef _LUMI_
					if(true == weConnected)
					{
						//tcpClient.send("!");
						RGB = 2;
						//tcpClient.send("setdmx(3,255)");
					}
					#else
						RGB = 2;
					#endif
					int myValueHere = -1;
					if (msgRx.find("01")!=string::npos)
					{
						myValueHere = 1;
					}
					else if (msgRx.find("04")!=string::npos)
					{
						myValueHere = 0;
					}
					else if (msgRx.find("07")!=string::npos)
					{
						myValueHere = 4;
					}
					else if (msgRx.find("09")!=string::npos)
					{
						myValueHere = 3;
					}
					else if (msgRx.find("11")!=string::npos)
					{
						myValueHere = 5;
					}
					
					myValue54 = 0;
					motorMember = root.getMemberNames();
					it = motorMember.begin();
					switch(myValueHere)
					{
					case 0:
						while((*it).at(0) != 'a')
							it++;
						trigIndex = 320;
						#ifdef _PLAY_
						vocals.play();
						#endif
						break;
					case 1:
						while((*it).at(0) != 'b')
							it++;
						trigIndex = 321;
						#ifdef _PLAY_
						vocals.play();
						#endif
						break;
					case 3:
						while((*it).at(0) != 'e')
							it++;
						trigIndex = 323;
						#ifdef _PLAY_
						vocals.play();
						#endif
						break;
					case 4:
						while((*it).at(0) != 'g')
							it++;
						trigIndex = 324;
						#ifdef _PLAY_
						vocals.play();
						#endif
						break;
					case 5:
						while((*it).at(0) != 'd')
							it++;
						trigIndex = 325;
						#ifdef _PLAY_
						vocals.play();
						#endif
						break;
					case 6:
						while((*it).at(0) != 'f')
							it++;
						trigIndex = 326;
						#ifdef _PLAY_
						vocals.play();
						#endif
						break;
					case 7:
						while((*it).at(0) != 'h')
							it++;
						trigIndex = 327;
						#ifdef _PLAY_
						vocals.play();
						#endif
						break;
					case 8:
						while((*it).at(0) != 'i')
							it++;
						trigIndex = 328;
						#ifdef _PLAY_
						vocals.play();
						#endif
						break;
					}
					ContinueTimer();
				}
			}
		}
		else
		{
			//if we are not connected lets try and reconnect every 5 seconds
			deltaTime = ofGetElapsedTimeMillis() - connectTime;

			if( deltaTime > 5000 ){
				weConnected = kinectClient.setup(SERVER,PORT);
				connectTime = ofGetElapsedTimeMillis();
			}

		}
		#endif
		
		#ifdef PUTA
		while( receiver.hasWaitingMessages() )
		{
			// get the next message
			ofxOscMessage m;
			receiver.getNextMessage( &m );
			int xxxx = m.getArgAsInt32( 0 );
			trigIndex = 53;
			myValue54 = 0;
			preventStupid = false;
			switch(xxxx)
			{
			case 1:
				if(lastxxxx != xxxx)
				{
					lastxxxx = xxxx;
					motorMember = root.getMemberNames();
					it = motorMember.begin();
					while( (*it).find("zb0")==string::npos )
					{
						if(it == motorMember.end())
						{
							it = motorMember.begin();
							break;
						}
						else
						{
							it++;
						}
					}
					InPn = 1;
					ContinueTimer();
					cout << "Segment One.";
				}
				break;
			case 2:
				if(lastxxxx != xxxx)
				{
					lastxxxx = xxxx;
					motorMember = root.getMemberNames();
					it = motorMember.begin();
					while( (*it).find("zfa0")==string::npos )
					{
						if(it == motorMember.end())
						{
							it = motorMember.begin();
							break;
						}
						else
						{
							it++;
						}
					}
					InPn = 1;
					ContinueTimer();
					cout << "Segment Two.";
				}
				break;
			case 3:
				if(lastxxxx != xxxx)
				{
					lastxxxx = xxxx;
					motorMember = root.getMemberNames();
					it = motorMember.begin();
					while( (*it).find("zkk0")==string::npos )
					{
						if(it == motorMember.end())
						{
							it = motorMember.begin();
							break;
						}
						else
						{
							it++;
						}
					}
					InPn = 1;
					ContinueTimer();
					cout << "Segment Three.";
				}
				break;
			}
			/*
			// check for mouse moved message
			if ( m.getAddress() == "/mouse/position" )
			{
				// both the arguments are int32's
				mouseX = m.getArgAsInt32( 0 );
				mouseY = m.getArgAsInt32( 1 );
			}
			// check for mouse button message
			else if ( m.getAddress() == "/mouse/button" )
			{
				// the single argument is a string
				mouseButtonState = m.getArgAsString( 0 ) ;
			}
			*/
		}
		#endif

		//ACTIVATING FUNCTION FROM A BUTTON PRESS:
		//ideally i would like to use an event, but for now:
		#ifndef _ILAN_
		bool fireTrigger = gui->listenForTrigger(51);
		while (fireTrigger == true)
		{
			myValue54 = 0;
			//reqBatch("ma110000",UP);
			reqAT("","ma100000",UP);
			//reqBatch("mr10000",LEFT);
			//reqBatch("mr10000",RIGHT);
			ofSleepMillis(5000);
			//reqBatch("ma2000",UP);
			reqAT("","ma2000",UP);
			//reqBatch("mr-10000",LEFT);
			//reqBatch("mr-10000",RIGHT);
			ofSleepMillis(5000);
		}
		#endif
		if (gui->listenForTrigger(2) == true)
		{
			myValue54 = 0;
			trigIndex = -1;
			#ifdef _PLAY_
			vocals.stop();
			#endif
			reqBatch(STOP_STR,ALL);
			ofSleepMillis(1500);
			if(false == preventStupid)
			{
				set150();
			}
		}
		else if (gui->listenForTrigger(53) == true)
		{
				#ifdef _LUMI_
				if(true == weConnected)
				{
					//tcpClient.send("!");
					RGB = 2;
				}
				#else
					RGB = 2;
				#endif
				trigIndex = 53;
				myValue54 = 0;
				preventStupid = false;
				motorMember = root.getMemberNames();
				it = motorMember.begin();
				while( (*it).find(myValue55)==string::npos || (*it).length() != myValue55.length() )
				{
					if(it == motorMember.end())
					{
						it = motorMember.begin();
						break;
					}
					else
					{
						it++;
					}
				}
				InPn = 1;
				ContinueTimer();
		}
		else if (gui->listenForTrigger(79) == true)
		{
				#ifdef _LUMI_
				if(true == weConnected)
				{
					//tcpClient.send("!");
					RGB = 2;
				}
				#else
					RGB = 2;
				#endif
				trigIndex = 53;
				myValue54 = 0;
				preventStupid = false;
				motorMember = root.getMemberNames();
				it = motorMember.begin();
				while( (*it).find(myValue55)==string::npos || (*it).length() != myValue55.length() )
				{
					if(it == motorMember.end())
					{
						it = motorMember.begin();
						break;
					}
					else
					{
						it++;
					}
				}
				InPn = 3;
				ContinueTimer();
		}
		#ifndef _ILAN_
		else if (gui->listenForTrigger(56) == true)
		{
			set150();
		}
		else if (gui->listenForTrigger(59) == true)
		{
			myValue54 = 0;
			//reqBatch("mr-2000",ALL);
			
			reqAT(T4,"mr-2000",UP);
			reqAT(T5,"mr-2000",UP);
			reqAT(T6,"mr-2000",UP);

			reqAT(T0,"mr-2000",LEFT);
			reqAT(T0,"mr-2000",RIGHT);
			reqAT(T1,"mr-2000",LEFT);
			reqAT(T1,"mr-2000",RIGHT);
			reqAT(T2,"mr-2000",LEFT);
			reqAT(T2,"mr-2000",RIGHT);
			reqAT(T3,"mr-2000",LEFT);
			reqAT(T3,"mr-2000",RIGHT);
			reqAT(T4,"mr-2000",LEFT);
			reqAT(T4,"mr-2000",RIGHT);
			reqAT(T5,"mr-2000",LEFT);
			reqAT(T5,"mr-2000",RIGHT);
			reqAT(T7,"mr-2000",LEFT);
			reqAT(T7,"mr-2000",RIGHT);
			reqAT(T8,"mr-2000",LEFT);
			reqAT(T8,"mr-2000",RIGHT);
			reqAT(T10,"mr-2000",LEFT);
			reqAT(T10,"mr-2000",RIGHT);
		}
		else if (gui->listenForTrigger(36) == true)
		{
			myValue54 = 0;
			reqAT(T4,"mr-2000",UP);
			ofSleepMillis(100);
			reqAT(T5,"mr-2000",UP);
			ofSleepMillis(100);
			reqAT(T6,"mr-2000",UP);
			ofSleepMillis(100);
			reqAT(T1,"mr-2000",LEFT);
			ofSleepMillis(100);
			reqAT(T1,"mr-2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T2,"mr-2000",LEFT);
			ofSleepMillis(100);
			reqAT(T2,"mr-2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T3,"mr-2000",LEFT);
			ofSleepMillis(100);
			reqAT(T3,"mr-2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T7,"mr-2000",LEFT);
			ofSleepMillis(100);
			reqAT(T7,"mr-2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T10,"mr-2000",LEFT);
			ofSleepMillis(100);
			reqAT(T10,"mr-2000",RIGHT);
		}
		else if (gui->listenForTrigger(37) == true)
		{
			myValue54 = 0;
			reqAT(T4,"mr-2000",UP);
			ofSleepMillis(100);
			reqAT(T5,"mr-2000",UP);
			ofSleepMillis(100);
			reqAT(T6,"mr-2000",UP);
			ofSleepMillis(100);
			reqAT(T1,"mr-2000",LEFT);
			ofSleepMillis(100);
			reqAT(T1,"mr-2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T2,"mr-2000",LEFT);
			ofSleepMillis(100);
			reqAT(T2,"mr-2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T3,"mr-2000",LEFT);
			ofSleepMillis(100);
			reqAT(T3,"mr-2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T4,"mr-2000",LEFT);
			ofSleepMillis(100);
			reqAT(T4,"mr-2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T7,"mr-2000",LEFT);
			ofSleepMillis(100);
			reqAT(T7,"mr-2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T10,"mr-2000",LEFT);
			ofSleepMillis(100);
			reqAT(T10,"mr-2000",RIGHT);
		}
		else if (gui->listenForTrigger(39) == true)
		{
			myValue54 = 0;
			switch(myValue40)
			{
			case 0:
				tenSix(myValue38,0,1);
				//request(myValue38, UP);
				break;
			case 1:
				request(myValue38, LEFT);
				break;
			case 2:
				request(myValue38, RIGHT);
				break;
			}
		}
		else if (gui->listenForTrigger(60) == true)
		{
			myValue54 = 0;
			reqAT(T4,DownDown,UP);
			ofSleepMillis(100);
			reqAT(T5,DownDown,UP);
			ofSleepMillis(100);
			reqAT(T6,DownDown,UP);
			ofSleepMillis(100);
			reqAT(T0,DownDown,LEFT);
			ofSleepMillis(100);
			reqAT(T0,DownDown,RIGHT);
			ofSleepMillis(100);
			reqAT(T1,DownDown,LEFT);
			ofSleepMillis(100);
			reqAT(T1,DownDown,RIGHT);
			ofSleepMillis(100);
			reqAT(T2,DownDown,LEFT);
			ofSleepMillis(100);
			reqAT(T2,DownDown,RIGHT);
			ofSleepMillis(100);
			reqAT(T3,DownDown,LEFT);
			ofSleepMillis(100);
			reqAT(T3,DownDown,RIGHT);
			ofSleepMillis(100);
			reqAT(T4,DownDown,LEFT);
			ofSleepMillis(100);
			reqAT(T4,DownDown,RIGHT);
			ofSleepMillis(100);
			reqAT(T5,DownDown,LEFT);
			ofSleepMillis(100);
			reqAT(T5,DownDown,RIGHT);
			ofSleepMillis(100);
			reqAT(T7,DownDown,LEFT);
			ofSleepMillis(100);
			reqAT(T7,DownDown,RIGHT);
			ofSleepMillis(100);
			reqAT(T8,DownDown,LEFT);
			ofSleepMillis(100);
			reqAT(T8,DownDown,RIGHT);
			ofSleepMillis(100);
			reqAT(T10,DownDown,LEFT);
			ofSleepMillis(100);
			reqAT(T10,DownDown,RIGHT);

		}
		else if (gui->listenForTrigger(74) == true)
		{
			myValue54 = 0;
			reqAT(T4,DownAll,UP);
			ofSleepMillis(100);
			reqAT(T5,DownAll,UP);
			ofSleepMillis(100);
			reqAT(T6,DownAll,UP);
			ofSleepMillis(100);
			reqAT(T0,DownAll,LEFT);
			ofSleepMillis(100);
			reqAT(T0,DownAll,RIGHT);
			ofSleepMillis(100);
			reqAT(T1,DownAll,LEFT);
			ofSleepMillis(100);
			reqAT(T1,DownAll,RIGHT);
			ofSleepMillis(100);
			reqAT(T2,DownAll,LEFT);
			ofSleepMillis(100);
			reqAT(T2,DownAll,RIGHT);
			ofSleepMillis(100);
			reqAT(T3,DownAll,LEFT);
			ofSleepMillis(100);
			reqAT(T3,DownAll,RIGHT);
			ofSleepMillis(100);
			reqAT(T4,DownAll,LEFT);
			ofSleepMillis(100);
			reqAT(T4,DownAll,RIGHT);
			ofSleepMillis(100);
			reqAT(T5,DownAll,LEFT);
			ofSleepMillis(100);
			reqAT(T5,DownAll,RIGHT);
			ofSleepMillis(100);
			reqAT(T7,DownAll,LEFT);
			ofSleepMillis(100);
			reqAT(T7,DownAll,RIGHT);
			ofSleepMillis(100);
			reqAT(T8,DownAll,LEFT);
			ofSleepMillis(100);
			reqAT(T8,DownAll,RIGHT);
			ofSleepMillis(100);
			reqAT(T10,DownAll,LEFT);
			ofSleepMillis(100);
			reqAT(T10,DownAll,RIGHT);

		}
		else if (gui->listenForTrigger(34) == true)
		{
			myValue54 = 0;
			reqAT(T4,"mr2000",UP);
			ofSleepMillis(100);
			reqAT(T5,"mr2000",UP);
			ofSleepMillis(100);
			reqAT(T6,"mr2000",UP);
			ofSleepMillis(100);
			reqAT(T1,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T1,"mr2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T2,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T2,"mr2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T3,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T3,"mr2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T7,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T7,"mr2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T10,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T10,"mr2000",RIGHT);
		}
		else if (gui->listenForTrigger(35) == true)
		{
			myValue54 = 0;
			reqAT(T4,"mr2000",UP);
			ofSleepMillis(100);
			reqAT(T5,"mr2000",UP);
			ofSleepMillis(100);
			reqAT(T6,"mr2000",UP);
			ofSleepMillis(100);
			reqAT(T1,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T1,"mr2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T2,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T2,"mr2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T3,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T3,"mr2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T4,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T4,"mr2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T7,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T7,"mr2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T10,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T10,"mr2000",RIGHT);
		}
		else if (gui->listenForTrigger(61) == true)
		{
			myValue54 = 0;
			reqBatch("pn05=H0101",ALL);
			ofSleepMillis(1500);
			/*
			reqBatch("pn23=50",LEFT);
			ofSleepMillis(500);
			reqBatch("pn23=50",RIGHT);
			ofSleepMillis(500);
			
			reqAT(T4,"pn23=50",UP);
			ofSleepMillis(100);
			reqAT(T5,"pn23=50",UP);
			ofSleepMillis(100);
			reqAT(T6,"pn23=50",UP);
			ofSleepMillis(100);
			reqAT(T0,"pn23=50",UP);
			ofSleepMillis(100);
			reqAT(T1,"pn23=50",UP);
			ofSleepMillis(100);
			reqAT(T2,"pn23=50",UP);
			ofSleepMillis(100);
			reqAT(T3,"pn23=50",UP);
			ofSleepMillis(100);
			*/
			reqBatch("save",ALL);
			ofSleepMillis(1500);
			reqBatch("H",ALL);
		}
		else if (gui->listenForTrigger(64) == true)
		{
			myValue54 = 0;
			reqBatch("nop",ALL);
		}
		/*
		else if (gui->listenForTrigger(33) == true)
		{
			myValue54 = 0;
			request("reset h",ALL);
		}
		*/
		else if (gui->listenForTrigger(78) == true)
		{
			trigIndex = 53;
			myValue54 = 0;
			preventStupid = false;
			motorMember = root.getMemberNames();
			it = motorMember.begin();
			switch(myValue77)
			{
			case 1:
				while( (*it).find("zb0")==string::npos )
				{
					if(it == motorMember.end())
					{
						it = motorMember.begin();
						break;
					}
					else
					{
						it++;
					}
				}
				InPn = 1;
				ContinueTimer();
				break;
			case 2:
				while( (*it).find("zfa0")==string::npos )
				{
					if(it == motorMember.end())
					{
						it = motorMember.begin();
						break;
					}
					else
					{
						it++;
					}
				}
				InPn = 1;
				ContinueTimer();
				break;
			case 3:
				while( (*it).find("zkk0")==string::npos )
				{
					if(it == motorMember.end())
					{
						it = motorMember.begin();
						break;
					}
					else
					{
						it++;
					}
				}
				InPn = 1;
				ContinueTimer();
				break;
			case 4:
				while( (*it).find("znd20")==string::npos )
				{
					if(it == motorMember.end())
					{
						it = motorMember.begin();
						break;
					}
					else
					{
						it++;
					}
				}
				InPn = 1;
				ContinueTimer();
				break;
			case 5:
				while( (*it).find("zoh1")==string::npos )
				{
					if(it == motorMember.end())
					{
						it = motorMember.begin();
						break;
					}
					else
					{
						it++;
					}
				}
				InPn = 1;
				ContinueTimer();
				break;
			case 6:
				while( (*it).find("zph0")==string::npos )
				{
					if(it == motorMember.end())
					{
						it = motorMember.begin();
						break;
					}
					else
					{
						it++;
					}
				}
				InPn = 1;
				ContinueTimer();
				break;
			}
		}	
		else if (gui->listenForTrigger(32) == true)
		{
			myValue54 = 0;
			preventStupid = false;
			/*
			motorMember = root.getMemberNames();
			it = motorMember.begin();
			*/
			switch(myValue58)
			{
			case 0:
				reqAT(T1,"mr2000",LEFT);
				ofSleepMillis(100);
				reqAT(T1,"mr2000",RIGHT);
				ofSleepMillis(100);
				/*
				while((*it).at(0) != 'a')
					it++;
				trigIndex = 320;
				*/
				break;
			case 1:
				reqAT(T2,"mr2000",LEFT);
				ofSleepMillis(100);
				reqAT(T2,"mr2000",RIGHT);
				ofSleepMillis(100);
				/*
				while((*it).at(0) != 'b')
					it++;
				trigIndex = 321;
				*/
				break;
			case 2:
				reqAT(T4,"mr1000",LEFT);
				ofSleepMillis(100);
				reqAT(T4,"mr1000",RIGHT);
				ofSleepMillis(100);
				/*
				while((*it).at(0) != 'c')
					it++;
				trigIndex = 322;
				*/
				break;
			case 3:
				reqAT(T7,"mr2000",LEFT);
				ofSleepMillis(100);
				reqAT(T7,"mr2000",RIGHT);
				ofSleepMillis(100);
				/*
				while((*it).at(0) != 'e')
					it++;
				trigIndex = 323;
				*/
				break;
			case 4:
				reqAT(T10,"mr2000",LEFT);
				ofSleepMillis(100);
				reqAT(T10,"mr2000",RIGHT);
				ofSleepMillis(100);
				/*
				while((*it).at(0) != 'g')
					it++;
				trigIndex = 324;
				*/
				break;
			case 5:
				reqAT(T4,"mr2000",UP);
				ofSleepMillis(100);
				reqAT(T5,"mr2000",UP);
				ofSleepMillis(100);
				reqAT(T6,"mr2000",UP);
				ofSleepMillis(100);
				/*
				while((*it).at(0) != 'd')
					it++;
				trigIndex = 325;
				*/
				break;
			case 6:
				reqAT(T0,"mr2000",LEFT);
				ofSleepMillis(100);
				reqAT(T5,"mr2000",LEFT);
				ofSleepMillis(100);
				reqAT(T8,"mr2000",LEFT);
				ofSleepMillis(100);
				break;
			case 7:
				reqAT(T0,"mr2000",RIGHT);
				ofSleepMillis(100);
				reqAT(T5,"mr2000",RIGHT);
				ofSleepMillis(100);
				reqAT(T8,"mr2000",RIGHT);
				ofSleepMillis(100);
				break;
			case 8:
				reqAT(T4,"mr500",UP);
				ofSleepMillis(100);
				reqAT(T5,"mr500",UP);
				ofSleepMillis(100);
				break;
			}
			//ContinueTimer();		
		}
		else if (gui->listenForTrigger(42) == true)
		{
			myValue54 = 0;
			preventStupid = false;
			/*
			motorMember = root.getMemberNames();
			it = motorMember.begin();
			*/
			switch(myValue58)
			{
			case 0:
				reqAT(T1,"mr-2000",LEFT);
				ofSleepMillis(100);
				reqAT(T1,"mr-2000",RIGHT);
				ofSleepMillis(100);
				/*
				while((*it).at(0) != 'a')
					it++;
				trigIndex = 320;
				*/
				break;
			case 1:
				reqAT(T2,"mr-2000",LEFT);
				ofSleepMillis(100);
				reqAT(T2,"mr-2000",RIGHT);
				ofSleepMillis(100);
				/*
				while((*it).at(0) != 'b')
					it++;
				trigIndex = 321;
				*/
				break;
			case 2:
				reqAT(T4,"mr-1000",LEFT);
				ofSleepMillis(100);
				reqAT(T4,"mr-1000",RIGHT);
				ofSleepMillis(100);
				/*
				while((*it).at(0) != 'c')
					it++;
				trigIndex = 322;
				*/
				break;
			case 3:
				reqAT(T7,"mr-2000",LEFT);
				ofSleepMillis(100);
				reqAT(T7,"mr-2000",RIGHT);
				ofSleepMillis(100);
				/*
				while((*it).at(0) != 'e')
					it++;
				trigIndex = 323;
				*/
				break;
			case 4:
				reqAT(T10,"mr-2000",LEFT);
				ofSleepMillis(100);
				reqAT(T10,"mr-2000",RIGHT);
				ofSleepMillis(100);
				/*
				while((*it).at(0) != 'g')
					it++;
				trigIndex = 324;
				*/
				break;
			case 5:
				reqAT(T4,"mr-2000",UP);
				ofSleepMillis(100);
				reqAT(T5,"mr-2000",UP);
				ofSleepMillis(100);
				reqAT(T6,"mr-2000",UP);
				ofSleepMillis(100);
				/*
				while((*it).at(0) != 'd')
					it++;
				trigIndex = 325;
				*/
				break;
			case 6:
				reqAT(T0,"mr-2000",LEFT);
				ofSleepMillis(100);
				reqAT(T5,"mr-2000",LEFT);
				ofSleepMillis(100);
				reqAT(T8,"mr-2000",LEFT);
				ofSleepMillis(100);
				break;
			case 7:
				reqAT(T0,"mr-2000",RIGHT);
				ofSleepMillis(100);
				reqAT(T5,"mr-2000",RIGHT);
				ofSleepMillis(100);
				reqAT(T8,"mr-2000",RIGHT);
				ofSleepMillis(100);
				break;
			case 8:
				reqAT(T4,"mr-500",UP);
				ofSleepMillis(100);
				reqAT(T5,"mr-500",UP);
				ofSleepMillis(100);
				break;
			}
			//ContinueTimer();		
		}
		else if (gui->listenForTrigger(69) == true)
		{
			myValue54 = 0;
			preventStupid = false;
			if(myValue80.size()==0)
			{
				switch(myValue65)
				{
				case 0:
					reqAT(T0,"mr-2000",LEFT);
					ofSleepMillis(100);
					break;
				case 1:
					reqAT(T1,"mr-2000",LEFT);
					ofSleepMillis(100);
					break;
				case 2:
					reqAT(T2,"mr-1000",LEFT);
					ofSleepMillis(100);
					break;
				case 3:
					reqAT(T3,"mr-2000",LEFT);
					ofSleepMillis(100);
					break;
				case 4:
					reqAT(T4,"mr-2000",LEFT);
					ofSleepMillis(100);
					break;
				case 5:
					reqAT(T5,"mr-2000",LEFT);
					ofSleepMillis(100);
					break;
				case 6:
					reqAT(T7,"mr-2000",LEFT);
					ofSleepMillis(100);
					break;
				case 7:
					reqAT(T8,"mr-2000",LEFT);
					ofSleepMillis(100);
					break;
				case 8:
					reqAT(T10,"mr-2000",LEFT);
					ofSleepMillis(100);
					break;
				case 9:
					reqAT(T4,"mr-500",UP);
					ofSleepMillis(100);
					break;
				case 10:
					reqAT(T5,"mr-500",UP);
					ofSleepMillis(100);
					break;
				}
			}
			else
			{
				myValue80 = "mr" + myValue80;
				switch(myValue65)
				{
				case 0:
					reqAT(T0,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 1:
					reqAT(T1,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 2:
					reqAT(T2,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 3:
					reqAT(T3,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 4:
					reqAT(T4,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 5:
					reqAT(T5,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 6:
					reqAT(T7,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 7:
					reqAT(T8,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 8:
					reqAT(T10,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 9:
					reqAT(T4, myValue80,UP);
					ofSleepMillis(100);
					break;
				case 10:
					reqAT(T5, myValue80,UP);
					ofSleepMillis(100);
					break;
				}
				myValue80 = myValue80.substr(2);
			}
		}
		else if (gui->listenForTrigger(73) == true)
		{
			myValue54 = 0;
			preventStupid = false;
			if(myValue80.size()==0)
			{
				switch(myValue65)
				{
				case 0:
					reqAT(T0,"mr2000",LEFT);
					ofSleepMillis(100);
					break;
				case 1:
					reqAT(T1,"mr2000",LEFT);
					ofSleepMillis(100);
					break;
				case 2:
					reqAT(T2,"mr1000",LEFT);
					ofSleepMillis(100);
					break;
				case 3:
					reqAT(T3,"mr2000",LEFT);
					ofSleepMillis(100);
					break;
				case 4:
					reqAT(T4,"mr2000",LEFT);
					ofSleepMillis(100);
					break;
				case 5:
					reqAT(T5,"mr2000",LEFT);
					ofSleepMillis(100);
					break;
				case 6:
					reqAT(T7,"mr2000",LEFT);
					ofSleepMillis(100);
					break;
				case 7:
					reqAT(T8,"mr2000",LEFT);
					ofSleepMillis(100);
					break;
				case 8:
					reqAT(T10,"mr2000",LEFT);
					ofSleepMillis(100);
					break;
				case 9:
					reqAT(T4,"mr500",UP);
					ofSleepMillis(100);
					break;
				case 10:
					reqAT(T5,"mr500",UP);
					ofSleepMillis(100);
					break;
				}
			}
			else
			{
				myValue80 = "mr" + myValue80;
				switch(myValue65)
				{
				case 0:
					reqAT(T0,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 1:
					reqAT(T1,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 2:
					reqAT(T2,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 3:
					reqAT(T3,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 4:
					reqAT(T4,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 5:
					reqAT(T5,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 6:
					reqAT(T7,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 7:
					reqAT(T8,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 8:
					reqAT(T10,myValue80,LEFT);
					ofSleepMillis(100);
					break;
				case 9:
					reqAT(T4, myValue80,UP);
					ofSleepMillis(100);
					break;
				case 10:
					reqAT(T5, myValue80,UP);
					ofSleepMillis(100);
					break;
				}
				myValue80 = myValue80.substr(2);
			}
		}
		else if (gui->listenForTrigger(71) == true)
		{
			myValue54 = 0;
			preventStupid = false;
			if(myValue80.size()==0)
			{
				switch(myValue67)
				{
				case 0:
					reqAT(T0,"mr-2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 1:
					reqAT(T1,"mr-2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 2:
					reqAT(T2,"mr-2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 3:
					reqAT(T3,"mr-2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 4:
					reqAT(T4,"mr-2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 5:
					reqAT(T5,"mr-2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 6:
					reqAT(T7,"mr-2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 7:
					reqAT(T8,"mr-2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 8:
					reqAT(T10,"mr-2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 9:
					reqAT(T6,"mr-500",UP);
					ofSleepMillis(100);
					break;
				case 10:
					reqAT(T2,"mr-500",UP);
					ofSleepMillis(100);
					break;
				}
			}
			else
			{
				myValue80 = "mr" + myValue80;
				switch(myValue67)
				{
				case 0:
					reqAT(T0,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 1:
					reqAT(T1,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 2:
					reqAT(T2,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 3:
					reqAT(T3,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 4:
					reqAT(T4,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 5:
					reqAT(T5,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 6:
					reqAT(T7,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 7:
					reqAT(T8,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 8:
					reqAT(T10,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 9:
					reqAT(T6,myValue80,UP);
					ofSleepMillis(100);
					break;
				case 10:
					reqAT(T2,myValue80,UP);
					ofSleepMillis(100);
					break;
				}
				myValue80 = myValue80.substr(2);
			}
		}
		else if (gui->listenForTrigger(75) == true)
		{
			myValue54 = 0;
			preventStupid = false;
			if(myValue80.size()==0)
			{
				switch(myValue67)
				{
				case 0:
					reqAT(T0,"mr2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 1:
					reqAT(T1,"mr2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 2:
					reqAT(T2,"mr2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 3:
					reqAT(T3,"mr2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 4:
					reqAT(T4,"mr2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 5:
					reqAT(T5,"mr2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 6:
					reqAT(T7,"mr2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 7:
					reqAT(T8,"mr2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 8:
					reqAT(T10,"mr2000",RIGHT);
					ofSleepMillis(100);
					break;
				case 9:
					reqAT(T6,"mr500",UP);
					ofSleepMillis(100);
					break;
				case 10:
					reqAT(T2,"mr500",UP);
					ofSleepMillis(100);
					break;
				}
			}
			else
			{
				myValue80 = "mr" + myValue80;
				switch(myValue67)
				{
				case 0:
					reqAT(T0,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 1:
					reqAT(T1,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 2:
					reqAT(T2,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 3:
					reqAT(T3,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 4:
					reqAT(T4,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 5:
					reqAT(T5,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 6:
					reqAT(T7,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 7:
					reqAT(T8,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 8:
					reqAT(T10,myValue80,RIGHT);
					ofSleepMillis(100);
					break;
				case 9:
					reqAT(T6,myValue80,UP);
					ofSleepMillis(100);
					break;
				case 10:
					reqAT(T2,myValue80,UP);
					ofSleepMillis(100);
					break;
				}
				myValue80 = myValue80.substr(2);
			}
		}
		else if (gui->listenForTrigger(52) == true)
		{
			myValue54 = gui->updateInt(54);
			if(myValue54 == 1)
			{
				tmpBytes[0] = 0;
				//trigIndex = 52;
				//timer.setTimer(5000);
				//timer.startTimer();
				reqQuestion("pe",ALL);
			}
		}
		else if (gui->listenForTrigger(57) == true)
		{
			myValue54 = 0;
			trigIndex = 57;
			parseMaJSON(myValue55);
		}
		else if( upValue0 != ouValue0)
		{
			reqSlider(T0,IMA_STR,upValue0,UP);
			ouValue0 = upValue0;
		}
		else if( lValue0 != olValue0)
		{
			reqSlider(T0,IMA_STR,lValue0,LEFT);
			olValue0 = lValue0;
		}
		else if( rValue0 != orValue0)
		{
			reqSlider(T0,IMA_STR,rValue0,RIGHT);
			orValue0 = rValue0;
		}
		else if( upValue1 != ouValue1)
		{
			reqSlider(T1,IMA_STR,upValue1,UP);
			ouValue1 = upValue1;
		}
		else if( lValue1 != olValue1)
		{
			reqSlider(T1,IMA_STR,lValue1,LEFT);
			olValue1 = lValue1;
		}
		else if( rValue1 != orValue1)
		{
			reqSlider(T1,IMA_STR,rValue1,RIGHT);
			orValue1 = rValue1;
		}
		else if( upValue2 != ouValue2)
		{
			reqSlider(T2,IMA_STR,upValue2,UP);
			ouValue2 = upValue2;
		}
		else if( lValue2 != olValue2)
		{
			reqSlider(T2,IMA_STR,lValue2,LEFT);
			olValue2 = lValue2;
		}
		else if( rValue2 != orValue2)
		{
			reqSlider(T2,IMA_STR,rValue2,RIGHT);
			orValue2 = rValue2;
		}
		else if( upValue3 != ouValue3)
		{
			reqSlider(T3,IMA_STR,upValue3,UP);
			ouValue3 = upValue3;
		}
		else if( lValue3 != olValue3)
		{
			reqSlider(T3,IMA_STR,lValue3,LEFT);
			olValue3 = lValue3;
		}
		else if( rValue3 != orValue3)
		{
			reqSlider(T3,IMA_STR,rValue3,RIGHT);
			orValue3 = rValue3;
		}
		else if( upValue4 != ouValue4)
		{
			reqSlider(T4,IMA_STR,upValue4,UP);
			ouValue4 = upValue4;
		}
		else if( lValue4 != olValue4)
		{
			reqSlider(T4,IMA_STR,lValue4,LEFT);
			olValue4 = lValue4;
		}
		else if( rValue4 != orValue4)
		{
			reqSlider(T4,IMA_STR,rValue4,RIGHT);
			orValue4 = rValue4;
		}
		else if( upValue5 != ouValue5)
		{
			reqSlider(T5,IMA_STR,upValue5,UP);
			ouValue5 = upValue5;
		}
		else if( lValue5 != olValue5)
		{
			reqSlider(T5,IMA_STR,lValue5,LEFT);
			olValue5 = lValue5;
		}
		else if( rValue5 != orValue5)
		{
			reqSlider(T5,IMA_STR,rValue5,RIGHT);
			orValue5 = rValue5;
		}
		else if( upValue6 != ouValue6)
		{
			reqSlider(T6,IMA_STR,upValue6,UP);
			ouValue6 = upValue6;
		}
		else if( lValue6 != olValue6)
		{
			reqSlider(T6,IMA_STR,lValue6,LEFT);
			olValue6 = lValue6;
		}
		else if( rValue6 != orValue6)
		{
			reqSlider(T6,IMA_STR,rValue6,RIGHT);
			orValue6 = rValue6;
		}
		else if( lValue7 != olValue7)
		{
			reqSlider(T7,IMA_STR,lValue7,LEFT);
			olValue7 = lValue7;
		}
		else if( rValue7 != orValue7)
		{
			reqSlider(T7,IMA_STR,rValue7,RIGHT);
			orValue7 = rValue7;
		}
		else if( lValue8 != olValue8)
		{
			reqSlider(T8,IMA_STR,lValue8,LEFT);
			olValue8 = lValue8;
		}
		else if( rValue8 != orValue8)
		{
			reqSlider(T8,IMA_STR,rValue8,RIGHT);
			orValue8 = rValue8;
		}
		else if( lValue9 != olValue9)
		{
			reqSlider(T9,IMA_STR,lValue9,LEFT);
			olValue9 = lValue9;
		}
		else if( rValue9 != orValue9)
		{
			reqSlider(T9,IMA_STR,rValue9,RIGHT);
			orValue9 = rValue9;
		}
		else if( lValue10 != olValue10)
		{
			reqSlider(T10,IMA_STR,lValue10,LEFT);
			olValue10 = lValue10;
		}
		else if( rValue10 != orValue10)
		{
			reqSlider(T10,IMA_STR,rValue10,RIGHT);
			orValue10 = rValue10;
		}
		#endif

		#ifdef _TWO_
		if(cmdQueneL.empty() == false && false == waitRes)
		{
			waitRes = true;
			request(cmdQueneL.back(), LEFT);
			cmdQueneL.pop_back();
		}

		if(cmdQueneR.empty() == false && false == waitRes)
		{
			waitRes = true;
			request(cmdQueneR.back(), RIGHT);
			cmdQueneR.pop_back();
		}
		#endif
		#ifdef _UP_
		if(cmdQueneH.empty() == false && false == waitRes)
		{
			waitRes = true;
			request(cmdQueneH.back(), UPHEAD);
			cmdQueneH.pop_back();
		}
		if(cmdQuene.empty() == false && false == waitRes)
		{
			waitRes = true;
			request(cmdQuene.back(), UP);
			cmdQuene.pop_back();
		}
		#endif
		//Switches:
		/*
		toggle1a = gui->listenForTrigger(7);
		if ( toggle1b != toggle1a)
		{
			if (toggle1a == true)
				{ testFunction(1); }
			else
				{ testFunction(2); }
			toggle1b = toggle1a;
		}
		*/
		#ifdef _MOVIE_
		vocals.idleMovie();
		#else
		ofSoundUpdate();
		#endif
}

//--------------------------------------------------------------
void testApp::draw(){
	#ifndef _ILAN_
	ofSetColor(0xffffff);
	gui->draw();
	#endif
	/*
	if (myValue1 == true)
	{    ofDrawBitmapString("Effect On", 10,10);	}
	else
	{   ofDrawBitmapString("Effect Off", 10,10);	}

    if (myValue2 == true)
	{   ofDrawBitmapString("Triger Pushed Down", 10,40);	}
	else
	{   ofDrawBitmapString("Trigger relased", 10,40);	}

    string temp = ofToString( myValue3 );
    ofDrawBitmapString(temp, 10,70);
    temp = ofToString( myValue6 );
    ofDrawBitmapString(temp, 10,90);

    //ofDrawBitmapString(myValue55, 10,110);
    //ofDrawBitmapString(myString2, 10,130);
    temp = ofToString( myValue4 );
    ofDrawBitmapString(temp, 10,150);
    //ofDrawBitmapString(myString3, 10,170);
	*/
	#ifdef _IR_
	if ( serialA.available() > 0 )
	{
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		strftime (timebuffer[0],4,"%H",timeinfo);
		strftime (timebuffer[1],4,"%w",timeinfo);
		int opening = ofToInt(timebuffer[0]);
		if ( -1 == trigIndex && opening > 9 && opening < 19 && ofToInt(timebuffer[1]) != 1 )
		{
			//franklinBook.drawString(ofToString(serialA.readByte()), 700, 150); // A 65, N 78
			
			if(65 == serialA.readByte())
			{
				#ifdef _LUMI_
				if(true == weConnected)
				{
					//tcpClient.send("!");
					RGB = 2;
					//tcpClient.send("setdmx(3,255)");
				}
				#else
					RGB = 2;
				#endif
				trigIndex = 53;
				myValue54 = 0;
				preventStupid = false;
				motorMember = root.getMemberNames();
				it = motorMember.begin();
				ContinueTimer();
				//connectTime = ofGetElapsedTimeMillis();
			}

		}
		serialA.flush();
	}
	#ifdef _LUMI_
	if(53 == trigIndex && thatInt > 0)
	{
		deltaTime = ofGetElapsedTimeMillis() - connectTime;
		if(abs(now1 - (deltaTime * 256) / thatInt) > 2)

		{
			now1 = (deltaTime * 256) / thatInt;
			if( now1 > 10 )
			{
				if( now1 < 128 )
					tcpClient.send("setdmx(1," + ofToString(now1 << 1) + ")");
				else if( now1 < 256)
					tcpClient.send("setdmx(1," + ofToString( (255 - now1) << 1 ) + ")");
			}
		}
	}
	#endif
	#endif
	#ifdef _UP_
	if ( serialH.available() > 0)
	{
		int result;
		while(result = serialH.readByte())
		{
			*cptr++ = result;
			if(true == readyBreak && 10 == result)
			{
				*(cptr-2) = 0;
				cptr = bytes;
				if(1 == myValue54)
				{
					if('?' == *cptr)
					{
						strcpy(tmpBytes,(char *)bytes);
					}
					else
					{
						int guan = tmpBytes[2] - '0'; 
						switch(guan)
						{
						case 0:
							tmpBytes[2] = '2';
							break;
						case 1:
							tmpBytes[2] = '4';
							break;
						case 2:
							tmpBytes[2] = '5';
							break;
						case 3:
							tmpBytes[2] = '6';
							break;
						}

						root[myValue55][tmpBytes].append(ofToInt((char *)bytes));
						waitRes = false;
						
					}
				}
				else
					waitRes = false;
			}
			if(13 == result)
			{
				readyBreak = true;
			}
		}

	}
	if ( serial.available() > 0)
	{
		int result;
		while(result = serial.readByte())
		{
			*cptr++ = result;
			if(true == readyBreak && 10 == result)
			{
				*(cptr-2) = 0;
				cptr = bytes;
				if(1 == myValue54)
				{
					if('?' == *cptr)
					{
						strcpy(tmpBytes,(char *)bytes);
					}
					else
					{
						int guan = tmpBytes[2] - '0'; 
						switch(guan)
						{
						case 0:
							tmpBytes[2] = '3';
							break;
						case 2:
							tmpBytes[2] = '0';
							break;
						}

						root[myValue55][tmpBytes].append(ofToInt((char *)bytes));
						waitRes = false;

						if(strncmp(tmpBytes, "?t0pe", 5) == 0 )
						{
							if(ofout.is_open() == false )
							{
								ofout.open(ofToDataPath(JSON, true).c_str());
							}
							root[myValue55][INTERVAL] = ofToInt(myValue62);
							//if(myValue50.empty() == false)
								//root[myValue55][SPEEDIVIDER] = ofToInt(myValue50);
							ofout << root;
							ofout.close();
						}

					}
				}
				else
					waitRes = false;
			}
			if(13 == result)
			{
				readyBreak = true;
			}

		}

	}
	#endif
	#ifdef _TWO_
	if ( serialL.available() > 0)
	{
		int result;
		while(result = serialL.readByte())
		{
			*cptr++ = result;
			if(true == readyBreak && 10 == result)
			{
				*(cptr-2) = 0;
				cptr = bytes;
				if(1 == myValue54)
				{
					if('?' == *cptr)
					{
						strcpy(tmpBytes,(char *)bytes);
					}
					else
					{
						if(!root[myValue55][tmpBytes].empty())
							root[myValue55][tmpBytes].clear();
						root[myValue55][tmpBytes].append(ofToInt((char *)bytes));
						waitRes = false;
					}
				}
				else
					waitRes = false;
			}
			if(13 == result)
			{
				readyBreak = true;
			}
		}

	}
	if ( serialR.available() > 0)
	{
		int result;
		while(result = serialR.readByte())
		{
			*cptr++ = result;
			if(true == readyBreak && 10 == result)
			{
				*(cptr-2) = 0;
				cptr = bytes;
				if(1 == myValue54)
				{
					if('?' == *cptr)
					{
						strcpy(tmpBytes,(char *)bytes);
					}
					else
					{
						root[myValue55][tmpBytes].append(ofToInt((char *)bytes));
						waitRes = false;
								
						#ifndef _UP_
						if(strncmp(tmpBytes, "?t0pe", 5) == 0 )
						{
							if(ofout.is_open() == false )
							{
								ofout.open(ofToDataPath(JSON, true).c_str());
							}
							root[myValue55][INTERVAL] = ofToInt(myValue62);
							//if(myValue50.empty() == false)
								//root[myValue55][SPEEDIVIDER] = ofToInt(myValue50);
							ofout << root;
							ofout.close();
						}
						#endif
		
					}
				}
				else
					waitRes = false;
			}
			if(13 == result)
			{
				readyBreak = true;
			}	
		}	

	}
	#endif
	
	franklinBook.drawString(msgRx, 800, 600);

	#ifdef baoPig
	franklinBook.drawString(msgadd, 800, 700);	
	#endif

	#ifdef _MOVIE_
	#ifndef _ILAN_	
		vocals.draw(700, 20);		
	#else
		vocals.draw(25, 10);
	#endif
	#endif	
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key)
{

}

//--------------------------------------------------------------
void testApp::keyReleased  (int key)
{
	if(trigIndex > 0)
	{
		myValue54 = 0;
		trigIndex = -1;
		#ifdef _PLAY_
		vocals.stop();
		#endif
		reqBatch(STOP_STR,ALL);
		ofSleepMillis(1500);
	}
	else if(key == 'U')
	{
		myValue54 = 0;
		reqBatch("mr-2000",ALL);
		/*
		reqAT(T0,"mr-2000",LEFT);
		ofSleepMillis(100);
		reqAT(T4,"mr-2000",LEFT);
		ofSleepMillis(100);
		*/
	}
	else if(key == 'u')
	{
			myValue54 = 0;
			//reqBatch("mr-2000",ALL);
			
			reqAT(T4,"mr-2000",UP);
			reqAT(T5,"mr-2000",UP);
			reqAT(T6,"mr-2000",UP);

			reqAT(T0,"mr-2000",LEFT);
			reqAT(T0,"mr-2000",RIGHT);
			reqAT(T1,"mr-2000",LEFT);
			reqAT(T1,"mr-2000",RIGHT);
			reqAT(T2,"mr-2000",LEFT);
			reqAT(T2,"mr-2000",RIGHT);
			reqAT(T3,"mr-2000",LEFT);
			reqAT(T3,"mr-2000",RIGHT);
			reqAT(T4,"mr-2000",LEFT);
			reqAT(T4,"mr-2000",RIGHT);
			reqAT(T5,"mr-2000",LEFT);
			reqAT(T5,"mr-2000",RIGHT);
			reqAT(T7,"mr-2000",LEFT);
			reqAT(T7,"mr-2000",RIGHT);
			reqAT(T8,"mr-2000",LEFT);
			reqAT(T8,"mr-2000",RIGHT);
			reqAT(T10,"mr-2000",LEFT);
			reqAT(T10,"mr-2000",RIGHT);
	}
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
void testApp::mouseReleased(){

}
//--------------------------------------------------------------

void testApp::testFunction(int setting)
{
    cout << "test function  activated \n";
    string temp = "event num " + ofToString(setting) + "\n";
    cout << temp ;
}

void testApp::reqSlider(string a, string b, int value, int which)
{
	myValue54 = 0;
	reqAT(a.append(b),ofToString(value-MIDDLE), which);
	ofSleepMillis(100);
}

void testApp::reqJSON(string a, string b, string value, int which){
	reqAT(a.append(b), value, which);
}

void testApp::reqBatch(string a, int which){
	reqAT(T0,a,which);
	reqAT(T1,a,which);
	reqAT(T2,a,which);
	reqAT(T3,a,which);
	reqAT(T4,a,which);
	reqAT(T5,a,which);
	reqAT(T6,a,which);
	reqAT(T7,a,which);
	reqAT(T8,a,which);
	reqAT(T9,a,which);
	reqAT(T10,a,which);
}

void testApp::resBatch(string a, int which){
	resAT(T0,a,which);
	resAT(T1,a,which);
	resAT(T2,a,which);
	resAT(T3,a,which);
	resAT(T4,a,which);
	resAT(T5,a,which);
	resAT(T6,a,which);
	resAT(T7,a,which);
	resAT(T8,a,which);
	resAT(T9,a,which);
	resAT(T10,a,which);
}

void testApp::reqQuestion(string a, int which){
	reqFAQ(QT0,a,which);
	reqFAQ(QT1,a,which);
	reqFAQ(QT2,a,which);
	reqFAQ(QT3,a,which);
	reqFAQ(QT4,a,which);
	reqFAQ(QT5,a,which);
	reqFAQ(QT6,a,which);
	reqFAQ(QT7,a,which);
	reqFAQ(QT8,a,which);
	reqFAQ(QT9,a,which);
	reqFAQ(QT10,a,which);
}

void testApp::tenSix(string realCmd, int frontback, int baseIdx)
{
	if(realCmd.at(0) != 't' && realCmd.at(0) != 'T' && realCmd.at(0) != '?')
	{
		realCmd.insert(0,"t0");
	}
	int guan = realCmd.at(baseIdx) - '0'; 
	switch(guan)
	{
	case 0:
		realCmd.replace(baseIdx,1,"2");
		if(0 == frontback)
			request(realCmd,UP);
		else
			cmdQuene.push_back(realCmd);
		break;
	case 1:
		if( realCmd.at(baseIdx+1) != '0' )
		{
			//realCmd.replace(1,1,"2");
			if(0 == frontback)
				request(realCmd,UP);
			else
				cmdQuene.push_back(realCmd);
		}
		break;
	case 2:
		realCmd.replace(baseIdx,1,"0");
		if(0 == frontback)
			request(realCmd,UPHEAD);
		else
			cmdQueneH.push_back(realCmd);
		break;
	case 3:
		realCmd.replace(baseIdx,1,"0");
		//realCmd.substr(realCmd.find(IMA_STR));
		if(0 == frontback)
			request(realCmd,UP);
		else
			cmdQuene.push_back(realCmd);
		break;
	case 4:
		realCmd.replace(baseIdx,1,"1");
		if(0 == frontback)
			request(realCmd,UPHEAD);
		else
			cmdQueneH.push_back(realCmd);
		break;
	case 5:
		realCmd.replace(baseIdx,1,"2");
		if(0 == frontback)
			request(realCmd,UPHEAD);
		else
			cmdQueneH.push_back(realCmd);
		break;
	case 6:
		realCmd.replace(baseIdx,1,"3");
		if(0 == frontback)
			request(realCmd,UPHEAD);
		else
			cmdQueneH.push_back(realCmd);
		break;
	}
}

void testApp::reqAT(string realCmd, string b, int which){
	//reqflush(which);
	realCmd.append(b);
	switch(which)
	{
	case UP:
		tenSix(realCmd,0,1);
		break;
	case LEFT:
		//if( realCmd.at(1) != '1' || realCmd.at(2) == '0')
			request(realCmd,LEFT);
		break;
	case RIGHT:
		request(realCmd,RIGHT);
		break;
	case ALL:
		tenSix(realCmd,0,1);
		//if( realCmd.at(1) != '1' || realCmd.at(2) == '0' )
			request(realCmd,LEFT);
		request(realCmd,RIGHT);
		break;
	}
	
}

void testApp::resAT(string realCmd, string b, int which){
	realCmd.append(b);
	switch(which)
	{
	case UP:
		tenSix(realCmd,1,1);
		break;
	case LEFT:
		//if( realCmd.at(2) != '1' || realCmd.at(3) == '0')
			cmdQueneL.push_back(realCmd);
		break;
	case RIGHT:
		cmdQueneR.push_back(realCmd);
		break;
	case ALL:
		//if( realCmd.at(2) != '1' || realCmd.at(3) == '0')
			cmdQueneL.push_back(realCmd);
		cmdQueneR.push_back(realCmd);
		tenSix(realCmd,1,1);
		break;
	}
	
}

void testApp::reqFAQ(string realCmd, string b, int which){
	realCmd.append(b);
	switch(which)
	{
	case UP:
		tenSix(realCmd,1,2);
		break;
	case LEFT:
		//if( realCmd.at(2) != '1' || realCmd.at(3) == '0')
			cmdQueneL.push_back(realCmd);
		break;
	case RIGHT:
		cmdQueneR.push_back(realCmd);
		break;
	case ALL:
		//if( realCmd.at(2) != '1' || realCmd.at(3) == '0')
			cmdQueneL.push_back(realCmd);
		cmdQueneR.push_back(realCmd);
		tenSix(realCmd,1,2);
		break;
	}
	
}
#ifdef _DMX_
void testApp::sendDMX(string buffer)
{
	//buffer.append(LFCR);
	DMX.writeBytes((unsigned char *)buffer.c_str(),buffer.length());		
}
#endif
void testApp::request(string buffer, int which)
{

	buffer.append(LFCR);
	switch(which)
	{
	#ifdef _UP_
	case UP:
		serial.writeBytes((unsigned char *)buffer.c_str(),buffer.length());
		break;
	case UPHEAD:
		serialH.writeBytes((unsigned char *)buffer.c_str(),buffer.length());
		break;
	#endif
	#ifdef _TWO_
	case LEFT:
		serialL.writeBytes((unsigned char *)buffer.c_str(),buffer.length());
		break;
	case RIGHT:
		/*
		if (buffer.find("t0")!=string::npos)
		{
			which = which;
		}
		*/
		serialR.writeBytes((unsigned char *)buffer.c_str(),buffer.length());
		break;
	#endif
	case ALL:
		#ifdef _TWO_
		serialL.writeBytes((unsigned char *)buffer.c_str(),buffer.length());
		serialR.writeBytes((unsigned char *)buffer.c_str(),buffer.length());
		#endif
		#ifdef _UP_
		serial.writeBytes((unsigned char *)buffer.c_str(),buffer.length());
		serialH.writeBytes((unsigned char *)buffer.c_str(),buffer.length());
		#endif
		break;
	}

}

void testApp::readJSON()
{
	string str,strTotal;
	ifstream in;
	in.open(ofToDataPath(JSON, true).c_str());
	getline(in,str);
	while ( in ) {
		strTotal += str;
		getline(in, str);
	}
	in.close();
	bool parsingSuccessful = reader.parse( strTotal, root );
	if ( !parsingSuccessful ) {
		std::cout  << "Failed to parse JSON\n" << reader.getFormatedErrorMessages();
		return;
	}
	
}

void testApp::parsePnJSON(string ss, int thisInt) {
	
	Json::Value::Members motorMember = root[ss].getMemberNames();
	Json::Value plugins, lastplugins;
	string iiit, strsub, seq;
	msgRx = ss;
	unsigned int ii;
	
	//vector<string>::iterator it;
	
	//seq = root[ss][SEQUENCE].asString();

	//for( it = motorMember.begin() ; it < motorMember.end() ; ++it)
	//for( ii = 0 ; ii < seq.length() ; ii++)
	
	for( ii = 0 ; ii < motorMember.size() ; ii++)
	{
		/*
		int jj = 0;
		
		if(seq.at(ii) == 'a')
			jj = 10;
		else
			jj = seq.at(ii) - '0';
		*/

		iiit = motorMember.at(ii);
		
		if(iiit.at(0) == '?')
		{
			plugins = root[ss][iiit];

			if(lastss.empty() == false)
				lastplugins = root[lastss][iiit];

			for ( int index = 0; index < plugins.size(); index++ )  // Iterates over the sequence elements.
			{
				int difference = -1;
				int timeInt = thisInt;
				switch(index)
				{
				case 0:
					if(iiit.at(3) == '0')
					{
						strsub = iiit.substr(1,3);
					}
					else
					{
						strsub = iiit.substr(1,2);
					}
					timeInt /= TIMEINT;
					if(lastss.empty() == false && timeInt != 0)
					{
						difference = ABS( plugins[index].asInt() - lastplugins[index].asInt() );
						int _pn = difference / timeInt;
						_pn = _pn < LOWLIMIT && _pn > 0  ? LOWLIMIT : _pn;
						if(difference > 0 && _pn > 0)
							reqJSON( strsub , "pn10=", ofToString( _pn ), LEFT);
					}
					break;
				case 1:
					if(iiit.at(3) == '0')
					{
						strsub = iiit.substr(1,3);
					}
					else
					{
						strsub = iiit.substr(1,2);
					}
					timeInt /= TIMEINT;
					if(lastss.empty() == false && timeInt != 0)
					{
						difference = ABS( plugins[index].asInt() - lastplugins[index].asInt() );
						int _pn = difference / timeInt;
						_pn = _pn < LOWLIMIT && _pn > 0  ? LOWLIMIT : _pn;
						if(difference > 0 && _pn > 0)
							reqJSON( strsub , "pn10=", ofToString( _pn ), RIGHT);
					}
					break;
				case 2:
					strsub = iiit.substr(1,2);
					switch(strsub.at(1))
					{
					case '0':
						timeInt /= TIMEINT; // 後退 << 2 掛點
						break;
					case '1':
						timeInt /= TIMEINT; // 後退 << 2 掛點
						break;
					case '2':
						timeInt /= TIMEINT; // 轉頭 >> 2 還是掛點
						break;
					case '3':
						timeInt /= TIMEINT; // 轉身怕掉下來
						break;
					default:
						timeInt /= TIMEINT;
						break;
					}
					if(lastss.empty() == false && timeInt != 0)
					{
						difference = ABS( plugins[index].asInt() - lastplugins[index].asInt() );
						int _pn = difference / timeInt;
						_pn = _pn < LOWLIMIT && _pn > 0 ? LOWLIMIT : _pn;
						if(difference > 0 && _pn > 0)
							reqJSON( strsub , "pn10=", ofToString( _pn ), UP);
					}
					break;
				}
			}
		}
	}

	//strcpy(jsonBytes, /*localResult = */root[ss]["?t0pe"].asString().c_str() );
	lastss = ss;
}

void testApp::parseMaJSON(string ss) {
	
	Json::Value::Members motorMember = root[ss].getMemberNames();
	Json::Value plugins, lastplugins;
	string iiit, strsub, seq;
	msgRx = ss;
	unsigned int ii;
	
	#ifdef _PLAY_
	if (msgRx.find("a0c")!=string::npos)
	{
		vocals.play();
	}
	else if (msgRx.find("dn")!=string::npos)
	{
		if(vocals.getIsPlaying() == false)
		{
			vocals.play();
		}
		vocals.setPosition(0.785939);
	}
	else 
	#endif 
	if (msgRx.length() == 2 && msgRx.find("zb")!=string::npos)
	{
		trigIndex = -1;
	}
	else if (msgRx.length() == 3 && msgRx.find("zfa")!=string::npos)
	{
		trigIndex = -1;
	}
	else if (msgRx.length() == 3 && msgRx.find("zkk")!=string::npos)
	{
		trigIndex = -1;
	}
	else if (msgRx.length() == 4 && msgRx.find("znd2")!=string::npos)
	{
		trigIndex = -1;
	}
	else if (msgRx.length() == 4 && msgRx.find("zoh0")!=string::npos)
	{
		trigIndex = -1;
	}
	else if (msgRx.length() == 3 && msgRx.find("zph")!=string::npos)
	{
		trigIndex = -1;
	}
	#ifdef baoPig
	else if (msgRx.length() == 3 && msgRx.find("7ab")!=string::npos)
	{
		msgadd = "Bao";
	}
	else if (msgRx.length() == 4 && msgRx.find("znc2")!=string::npos)
	{
		msgadd = "Pig";
	}
	#endif
	//vector<string>::iterator it;
	//seq = root[ss][SEQUENCE].asString();

	//for( it = motorMember.begin() ; it < motorMember.end() ; ++it)
	//for( ii = 0 ; ii < seq.length() ; ii++)
	
	for( ii = 0 ; ii < motorMember.size() ; ii++)
	{
		/*
		int jj = 0;
		
		if(seq.at(ii) == 'a')
			jj = 10;
		else
			jj = seq.at(ii) - '0';
		*/

		iiit = motorMember.at(ii);
		
		if(iiit.at(0) == '?')
		{
			plugins = root[ss][iiit];

			if(lastss.empty() == false)
				lastplugins = root[lastss][iiit];

			for ( int index = 0; index < plugins.size(); index++ )  // Iterates over the sequence elements.
			{
				int difference = -1;
				switch(index)
				{
				case 0:
					if(iiit.at(3) == '0')
					{
						strsub = iiit.substr(1,3);
					}
					else
					{
						strsub = iiit.substr(1,2);
					}
					if(difference != 0)
						reqJSON( strsub , IMA_STR, ofToString(plugins[index].asInt()), LEFT);
					break;
				case 1:
					if(iiit.at(3) == '0')
					{
						strsub = iiit.substr(1,3);
					}
					else
					{
						strsub = iiit.substr(1,2);
					}
					if(difference != 0)
						reqJSON( strsub , IMA_STR, ofToString(plugins[index].asInt()), RIGHT);
					break;
				case 2:
					strsub = iiit.substr(1,2);
					if(difference != 0)
						reqJSON( strsub , IMA_STR, ofToString(plugins[index].asInt()), UP);
					break;
				}
			}
		}
	}

	//strcpy(jsonBytes, /*localResult = */root[ss]["?t0pe"].asString().c_str() );
	lastss = ss;
}

void testApp::ContinueTimer()
{

	int thisInt = root[*it][INTERVAL].asInt();
	if(thisInt > 0)
	{
		timer.setTimer(PnInterval);
		timer.startTimer();
		//if(root[*it][SPEEDIVIDER].isNull() == true || root[*it][SPEEDIVIDER].empty() == true)
			parsePnJSON(*it, thisInt);
		//else
			//parseJSON(*it, thisInt / root[*it][SPEEDIVIDER].asInt() );
		#ifdef _LUMI_
		if(5 == RGB)
			RGB = 2;
		rgbValue = ofRandom(32,255);
		tcpClient.send("setdmx(" + ofToString(RGB) + "," + ofToString(rgbValue) + ")");
		#endif    
	}
}

void testApp::MaTimer()
{

	thatInt = root[*it][INTERVAL].asInt();
	if(thatInt > 0)
	{
		timer.setTimer(thatInt-PnInterval);
		timer.startTimer();
		//if(root[*it][SPEEDIVIDER].isNull() == true || root[*it][SPEEDIVIDER].empty() == true)
			parseMaJSON(*it);
		#ifdef _LUMI_
		tcpClient.send("setdmx(" + ofToString(RGB++) + "," + ofToString(rgbValue) + ")");
		#elif _DMX_
		if(5 == RGB)
			RGB = 2;
		if ((*it).find("zz")!=string::npos)
			sendDMX("o");
		else if(true == oneTwentySeven)
		{
			sendDMX(ofToString(thatInt) + "t" + ofToString(RGB++) + "c" + ofToString(ofRandom(0,127)) + "w");
			oneTwentySeven = !oneTwentySeven;
		}
		else
		{
			sendDMX(ofToString(thatInt) + "t" + ofToString(RGB++) + "c" + ofToString(ofRandom(128,255)) + "w");
			oneTwentySeven = !oneTwentySeven;
		}
		#endif    
		//else
			//parseJSON(*it, thisInt / root[*it][SPEEDIVIDER].asInt() );
	}
	connectTime = ofGetElapsedTimeMillis();
}

void testApp::NextTimer()
{

	thatInt = root[*it][INTERVAL].asInt();
	if(thatInt > 0)
	{
		timer.setTimer(thatInt-PnInterval);//(2000);
		timer.startTimer();
		//if(root[*it][SPEEDIVIDER].isNull() == true || root[*it][SPEEDIVIDER].empty() == true)
			parseMaJSON(*it);
		#ifdef _LUMI_
		tcpClient.send("setdmx(" + ofToString(RGB++) + "," + ofToString(rgbValue) + ")");
		#elif _DMX_
		if(5 == RGB)
			RGB = 2;
		if ((*it).find("zz")!=string::npos)
			sendDMX("o");
		else if(true == oneTwentySeven)
		{
			sendDMX(ofToString(thatInt) + "t" + ofToString(RGB++) + "c" + ofToString(ofRandom(0,127)) + "w");
			oneTwentySeven = !oneTwentySeven;
		}
		else
		{
			sendDMX(ofToString(thatInt) + "t" + ofToString(RGB++) + "c" + ofToString(ofRandom(128,255)) + "w");
			oneTwentySeven = !oneTwentySeven;
		}
		#endif    
		//else
			//parseJSON(*it, thisInt / root[*it][SPEEDIVIDER].asInt() );
	}
	connectTime = ofGetElapsedTimeMillis();
}

void testApp::Interval(ofEventArgs &e)
{
	switch(trigIndex)
	{
	case 53:
		if(it < motorMember.end())
		{
			PnMaExchange();
		}
		else
		{
			#ifdef _LUMI_
			if(true == weConnected)
			{
				tcpClient.send("setdmx(1,255)");
			}
			#endif
			if(false == preventStupid)
			{
				set150();
			}
			trigIndex = -1;
			#ifdef _PLAY_
			vocals.stop();
			#endif
		}
		break;
	case 320:
		if((*it).at(0) == 'a')
		{
			PnMaExchange();
		}
		else
		{
			trigIndex = -1;
			#ifdef _PLAY_
			vocals.setPaused(true);
			#endif
		}
		break;
	case 321:
		if((*it).at(0) == 'b')
		{
			PnMaExchange();
		}
		else
		{
			trigIndex = -1;
			#ifdef _PLAY_
			vocals.setPaused(true);
			#endif
		}
		break;
	case 322:
		if((*it).at(0) == 'c')
		{
			PnMaExchange();
		}
		else
		{
			trigIndex = -1;
			#ifdef _PLAY_
			vocals.setPaused(true);
			#endif
		}
		break;
	case 323:
		if((*it).at(0) == 'e')
		{
			PnMaExchange();
			#ifdef _PLAY_
			vocals.setPaused(true);
			#endif
		}
		else
		{
			trigIndex = -1;
			#ifdef _PLAY_
			vocals.setPaused(true);
			#endif
		}
		break;
	case 324:
		if((*it).at(0) == 'g')
		{
			PnMaExchange();
		}
		else
		{
			trigIndex = -1;
			#ifdef _PLAY_
			vocals.setPaused(true);
			#endif
		}
		break;
	case 325:
		if((*it).at(0) == 'd')
		{
			PnMaExchange();
		}
		else
		{
			trigIndex = -1;
			#ifdef _PLAY_
			vocals.setPaused(true);
			#endif
		}
		break;
	case 326:
		if((*it).at(0) == 'f')
		{
			PnMaExchange();
		}
		else
		{
			trigIndex = -1;
			#ifdef _PLAY_
			vocals.setPaused(true);
			#endif
		}
		break;
	case 327:
		if((*it).at(0) == 'h')
		{
			PnMaExchange();
		}
		else
		{
			trigIndex = -1;
			#ifdef _PLAY_
			vocals.setPaused(true);
			#endif
		}
		break;
	case 328:
		if(it < motorMember.end())//((*it).at(0) == 'h')
		{
			PnMaExchange();
		}
		else
		{
			#ifdef _LUMI_
			if(true == weConnected)
			{
				tcpClient.send("setdmx(1,255)");
			}
			#endif
			if(false == preventStupid)
			{
				set150();
			}
			trigIndex = -1;
			#ifdef _PLAY_
			vocals.stop();
			#endif
		}
		break;
	}
}

void testApp::PnMaExchange()
{
	if(0 == InPn)
	{
		ContinueTimer();
		InPn = 1;
	}
	else if(1 == InPn)
	{
		MaTimer();
		++it;
		InPn = 0;
	}/* 
	else if(2 == InPn)
	{
		ContinueTimer();
		InPn = 3;
	}*/
	else if(3 == InPn)
	{
		NextTimer();
		++it;
		InPn = 4;
	}
	else if(4 == InPn)
	{
		ContinueTimer();
		InPn = 5;
	}
	else if(5 == InPn)
	{
		MaTimer();
		//++it;
		InPn = -1;
	}
	else if(-1 == InPn)
	{
			set150();
	}
}

float testApp::mapRay(float value, float dL, float dR, float mL, float mR)
{
	float ratio, ret; 
	if(dR > dL)
	{
		ratio = (value - dL) / (dR - dL);
	}
	else
	{
		ratio = (dL - value) / (dL - dR);
	}

	if(mL > mR)
	{
		ret = mL - ratio * (mL - mR);
	}
	else
	{
		ret = ratio * (mR - mL) + mL;
	}
	return ret;
}


void testApp::reqflush(int which)
{
	switch(which)
	{
	#ifdef _UP_
	case UP:
		if ( serial.available() > 0 )
			serial.flush(true,true);
		if ( serialH.available() > 0 )
			serialH.flush(true,true);
		break;
	#endif
	#ifdef _TWO_
	case LEFT:
		if ( serialL.available() > 0 )
			serialL.flush(true,true);
		break;
	case RIGHT:
		if ( serialR.available() > 0 )
			serialR.flush(true,true);
		break;
	#endif
	case ALL:
		#ifdef _TWO_
		if ( serialL.available() > 0 )
			serialL.flush(true,true);
		if ( serialR.available() > 0 )
			serialR.flush(true,true);
		#endif
		#ifdef _UP_
		if ( serial.available() > 0 )
			serial.flush(true,true);
		if ( serialH.available() > 0 )
			serialH.flush(true,true);
		#endif
		break;
	}

}

void testApp::set150()
{
	myValue54 = 0;
			reqAT(T0,"pn10=50",UP);
			ofSleepMillis(100);
			reqAT(T1,"pn10=50",UP);
			ofSleepMillis(100);
			reqAT(T2,"pn10=25",UP);
			ofSleepMillis(100);
			reqAT(T3,"pn10=50",UP);
			ofSleepMillis(100);
			if(myValue50.at(0) != 'p')
				reqAT(T4,myValue50.insert(0,"pn10="),UP);
			else
				reqAT(T4,myValue50,UP);
			ofSleepMillis(100);
			reqAT(T5,myValue50,UP);
			ofSleepMillis(100);
			reqAT(T6,myValue50,UP);
			ofSleepMillis(100);
			reqAT(T0,myValue50,LEFT);
			ofSleepMillis(100);
			reqAT(T1,myValue50,LEFT);
			ofSleepMillis(100);
			reqAT(T2,myValue50,LEFT);
			ofSleepMillis(100);
			reqAT(T3,myValue50,LEFT);
			ofSleepMillis(100);
			reqAT(T4,myValue50,LEFT);
			ofSleepMillis(100);
			reqAT(T5,myValue50,LEFT);
			ofSleepMillis(100);
			reqAT(T6,myValue50,LEFT);
			ofSleepMillis(100);
			reqAT(T7,myValue50,LEFT);
			ofSleepMillis(100);
			reqAT(T8,myValue50,LEFT);
			ofSleepMillis(100);
			reqAT(T9,myValue50,LEFT);
			ofSleepMillis(100);
			reqAT(T10,myValue50,LEFT);
			ofSleepMillis(100);
			reqAT(T0,myValue50,RIGHT);
			ofSleepMillis(100);
			reqAT(T1,myValue50,RIGHT);
			ofSleepMillis(100);
			reqAT(T2,myValue50,RIGHT);
			ofSleepMillis(100);
			reqAT(T3,myValue50,RIGHT);
			ofSleepMillis(100);
			reqAT(T4,myValue50,RIGHT);
			ofSleepMillis(100);
			reqAT(T5,myValue50,RIGHT);
			ofSleepMillis(100);
			reqAT(T6,myValue50,RIGHT);
			ofSleepMillis(100);
			reqAT(T7,myValue50,RIGHT);
			ofSleepMillis(100);
			reqAT(T8,myValue50,RIGHT);
			ofSleepMillis(100);
			reqAT(T9,myValue50,RIGHT);
			ofSleepMillis(100);
			reqAT(T10,myValue50,RIGHT);
			ofSleepMillis(100);
			/*
			reqBatch("pn05=H0101",ALL);
			ofSleepMillis(1500);
			reqBatch("pn11=10",ALL);
			ofSleepMillis(1500);
			reqBatch("pn24=2000",ALL);
			ofSleepMillis(1500);
			*/
			reqBatch("save",ALL);
			preventStupid = true;
}