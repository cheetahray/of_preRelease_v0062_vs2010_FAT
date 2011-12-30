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
#define INTERVAL "Interval"
#define SPEEDIVIDER "SpeedDivider"
#define JSON "json.txt"

#define UP 0
#define LEFT 1
#define RIGHT 2
#define ALL 3
//dl,dn,ds,ed
#define MIDDLE 0
#define FIRSTINDEX "a0"

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
#define PORT 90123

//--------------------------------------------------------------
void testApp::setup()
{
	franklinBook.loadFont("frabk.ttf", 128);
	
	ofBackground(127,127,127);
	readJSON();

	#ifdef _PLAY_
	#ifdef _MOVIE_
	vocals.loadMovie("MVI_8225.mp4");
	#else
	vocals.loadSound("MVI_0091.mp3");
	//vocals.setMultiPlay(false);
	#endif
	#endif

	gui = new GuiHandler;
	int idx = 0;

	GuiPanel*  Panel1 = gui->addPanel("Button",0,500,350,500);
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
		#ifndef _ILAN_		
        Panel1->addTextField("Velocity",140,20, "150", 50, &myValue50);
		Panel1->addButton("Set PN Speed",100,20,"TRIGGER"/*"SWITCH"*/,true, 56, &myValue56);
		Panel1->addButton("Get Down",100,20,"TRIGGER"/*"SWITCH"*/,true, 34, &myValue34);
	    Panel1->addButton("Get DownI",100,20,"TRIGGER"/*"SWITCH"*/,true, 35, &myValue35);
	    Panel1->addButton("Get Up",100,20,"TRIGGER"/*"SWITCH"*/,true, 36, &myValue36);
	    
	GuiPanel*  Panel2 = gui->addPanel("TOP",350, 500,1000,500);

        //Panel2->addFloatSlider("slider1",140,10, 26.8, 100, 4, &myValue4);
        Panel2->addIntSlider("0. Horizontal", 300, 10, root[FIRSTINDEX]["?t0pe"][2].asInt(), root[FIRSTINDEX]["?t0pe"][2].asInt() << 1, 4, &upValue0);
        Panel2->addIntSlider("1. Vertical", 300, 10, root[FIRSTINDEX]["?t1pe"][2].asInt(), root[FIRSTINDEX]["?t1pe"][2].asInt() << 1, 5, &upValue1);
		Panel2->addIntSlider("2. Head Rotation", 300, 10, root[FIRSTINDEX]["?t2pe"][2].asInt(), root[FIRSTINDEX]["?t2pe"][2].asInt() << 1, 6, &upValue2);
        Panel2->addIntSlider("3. Body Rotation", 300, 10, root[FIRSTINDEX]["?t3pe"][2].asInt(), root[FIRSTINDEX]["?t3pe"][2].asInt() << 1, 7, &upValue3);
		Panel2->addIntSlider("4. Right Head", 300, 10, root[FIRSTINDEX]["?t4pe"][2].asInt(), root[FIRSTINDEX]["?t4pe"][2].asInt() << 1, 8, &upValue4);
		Panel2->addIntSlider("5. Left Head", 300, 10, root[FIRSTINDEX]["?t5pe"][2].asInt(), root[FIRSTINDEX]["?t5pe"][2].asInt() << 1, 9, &upValue5);
		Panel2->addIntSlider("6. Back Head", 300, 10, root[FIRSTINDEX]["?t6pe"][2].asInt(), root[FIRSTINDEX]["?t6pe"][2].asInt() << 1, 10, &upValue6);
        //Panel2->addButton("Reset H",100,20,"TRIGGER"/*"SWITCH"*/,true, 33, &myValue33);
		Panel2->addButton("NOP",100,20,"TRIGGER"/*"SWITCH"*/,true, 64, &myValue64);
	    Panel2->addButton("Max Currency",100,20,"TRIGGER"/*"SWITCH"*/,true, 51, &myValue51);
		
		Panel2->addRadio("Hands and Legs",25, 11, 58, &myValue58);
			/*
            Panel2->addRadioElement(58,"Right Hand");
            Panel2->addRadioElement(58,"Left Wave");
            Panel2->addRadioElement(58,"Left Hand");
            Panel2->addRadioElement(58,"Right Leg");
			Panel2->addRadioElement(58,"Left Leg");
            Panel2->addRadioElement(58,"Surrender");
            Panel2->addRadioElement(58,"Salute");
			Panel2->addRadioElement(58,"Kick");
			Panel2->addRadioElement(58,"HandShaking");
			*/
			Panel2->addRadioElement(58,"But");
            Panel2->addRadioElement(58,"Shoulder");
            Panel2->addRadioElement(58,"Knee");
			Panel2->addRadioElement(58,"Elbow");
            Panel2->addRadioElement(58,"Hand");
            Panel2->addRadioElement(58,"Head");
			
			Panel2->addRadioElement(58,"None");
			Panel2->addRadioElement(58,"None");
			Panel2->addRadioElement(58,"None");

		Panel2->bindKey(58,OF_KEY_RIGHT);
        Panel2->bindKey2(58,OF_KEY_LEFT);
		//Panel2->addButton("Do it!!",100,20,"TRIGGER"/*"SWITCH"*/,true, 32, &myValue32);
		Panel2->addButton("Down",100,20,"TRIGGER"/*"SWITCH"*/,true, 32, &myValue32);
		Panel2->addButton("Up",100,20,"TRIGGER"/*"SWITCH"*/,true, 42, &myValue42);
		#endif	
		/*
        GuiPanel*  Panel3 = gui->addPanel("panel 3",640,70,250,250);

		Panel3->addFileList("fileBrowse",200,200,"files",10, &myString3);
			Panel3->bindKey(10,']');
            Panel3->bindKey2(10,'[');
		*/

	GuiPanel*  Panel3 = gui->addPanel("LEFT", 0,0,350,500);
		#ifndef _ILAN_
        //Panel2->addFloatSlider("slider1",140,10, 26.8, 100, 4, &myValue4);
        Panel3->addIntSlider("0. Foot Back", 300, 10, root[FIRSTINDEX]["?t0pe"][idx].asInt(), root[FIRSTINDEX]["?t0pe"][idx].asInt() << 1, 11, &lValue0);
        Panel3->addIntSlider("1. But", 300, 10, root[FIRSTINDEX]["?t1pe"][idx].asInt(), root[FIRSTINDEX]["?t1pe"][idx].asInt() << 1, 12, &lValue1);
        Panel3->addIntSlider("2. Shoulder", 300, 10, root[FIRSTINDEX]["?t2pe"][idx].asInt(), root[FIRSTINDEX]["?t2pe"][idx].asInt() << 1, 13, &lValue2);
        Panel3->addIntSlider("3. Chest", 300, 10, root[FIRSTINDEX]["?t3pe"][idx].asInt(), root[FIRSTINDEX]["?t3pe"][idx].asInt() << 1, 14, &lValue3);
        Panel3->addIntSlider("4. Knee", 300, 10, root[FIRSTINDEX]["?t4pe"][idx].asInt(), root[FIRSTINDEX]["?t4pe"][idx].asInt() << 1, 15, &lValue4);
        Panel3->addIntSlider("5. Foot Front", 300, 10, root[FIRSTINDEX]["?t5pe"][idx].asInt(), root[FIRSTINDEX]["?t5pe"][idx].asInt() << 1, 16, &lValue5);
        Panel3->addIntSlider("6. Hand Left/Right", 300, 10, root[FIRSTINDEX]["?t6pe"][idx].asInt(), root[FIRSTINDEX]["?t6pe"][idx].asInt() << 1, 17, &lValue6);
        Panel3->addIntSlider("7. Elbow", 300, 10, root[FIRSTINDEX]["?t7pe"][idx].asInt(), root[FIRSTINDEX]["?t7pe"][idx].asInt() << 1, 18, &lValue7);
        Panel3->addIntSlider("8. Foot Side", 300, 10, root[FIRSTINDEX]["?t8pe"][idx].asInt(), root[FIRSTINDEX]["?t8pe"][idx].asInt() << 1, 19, &lValue8);
        Panel3->addIntSlider("9. Hand Forward/Backward", 300, 10, root[FIRSTINDEX]["?t9pe"][idx].asInt(), root[FIRSTINDEX]["?t9pe"][idx].asInt() << 1, 20, &lValue9);
        Panel3->addIntSlider("10. Hand UP/Down", 300, 10, root[FIRSTINDEX]["?t10pe"][idx].asInt(), root[FIRSTINDEX]["?t10pe"][idx].asInt() << 1, 41, &lValue10);
		Panel3->addRadio("UP/LEFT/RIGHT",25, 4, 40, &myValue40);
            Panel3->addRadioElement(40,"UP");
            Panel3->addRadioElement(40,"LEFT");
            Panel3->addRadioElement(40,"RIGHT");
        Panel3->addTextField("CommandLine",140,20, "", 38, &myValue38);
		Panel3->addButton("Command",100,20,"TRIGGER"/*"SWITCH"*/,true, 39, &myValue39);
		Panel3->addButton("Go to Pose",100,20,"TRIGGER"/*"SWITCH"*/,true, 57, &myValue57);
	    
	GuiPanel*  Panel4 = gui->addPanel("RIGHT", 350, 0,350,500);

        //Panel2->addFloatSlider("slider1",140,10, 26.8, 100, 4, &myValue4);
        Panel4->addIntSlider("0. Foot Back", 300, 10, root[FIRSTINDEX]["?t0pe"][1].asInt(), root[FIRSTINDEX]["?t0pe"][1].asInt() << 1, 21, &rValue0);
        Panel4->addIntSlider("1. But", 300, 10, root[FIRSTINDEX]["?t1pe"][1].asInt(), root[FIRSTINDEX]["?t1pe"][1].asInt() << 1, 22, &rValue1);
        Panel4->addIntSlider("2. Shoulder", 300, 10, root[FIRSTINDEX]["?t2pe"][1].asInt(), root[FIRSTINDEX]["?t2pe"][1].asInt() << 1, 23, &rValue2);
        Panel4->addIntSlider("3. Body Back", 300, 10, root[FIRSTINDEX]["?t3pe"][1].asInt(), root[FIRSTINDEX]["?t3pe"][1].asInt() << 1, 24, &rValue3);
        Panel4->addIntSlider("4. Knee", 300, 10, root[FIRSTINDEX]["?t4pe"][1].asInt(), root[FIRSTINDEX]["?t4pe"][1].asInt() << 1, 25, &rValue4);
        Panel4->addIntSlider("5. Foot Front", 300, 10, root[FIRSTINDEX]["?t5pe"][1].asInt(), root[FIRSTINDEX]["?t5pe"][1].asInt() << 1, 26, &rValue5);
		Panel4->addIntSlider("6. Hand Left/Right", 300, 10, root[FIRSTINDEX]["?t6pe"][1].asInt(), root[FIRSTINDEX]["?t6pe"][1].asInt() << 1, 27, &rValue6);
        Panel4->addIntSlider("7. Elbow", 300, 10, root[FIRSTINDEX]["?t7pe"][1].asInt(), root[FIRSTINDEX]["?t7pe"][1].asInt() << 1, 28, &rValue7);
        Panel4->addIntSlider("8. Foot Side", 300, 10, root[FIRSTINDEX]["?t8pe"][1].asInt(), root[FIRSTINDEX]["?t8pe"][1].asInt() << 1, 29, &rValue8);
        Panel4->addIntSlider("9. Hand Forward/Backward", 300, 10, root[FIRSTINDEX]["?t9pe"][1].asInt(), root[FIRSTINDEX]["?t9pe"][1].asInt() << 1, 30, &rValue9);
        Panel4->addIntSlider("10. Hand UP/Down", 300, 10, root[FIRSTINDEX]["?t10pe"][1].asInt(), root[FIRSTINDEX]["?t10pe"][1].asInt() << 1, 31, &rValue10);
		Panel4->addButton("Get DownII",100,20,"TRIGGER"/*"SWITCH"*/,true, 60, &myValue60);
		Panel4->addButton("Get UpII",100,20,"TRIGGER"/*"SWITCH"*/,true, 37, &myValue37);
	    Panel4->addButton("Get UpIII",100,20,"TRIGGER"/*"SWITCH"*/,true, 59, &myValue59);
		Panel4->addButton("Home",100,20,"TRIGGER"/*"SWITCH"*/,true, 61, &myValue61);
	    //Panel4->addIntSlider("10. Heand UP/Down", 300, 10, 10000, 20000, 31, &rValue10);
		#else
		Panel3->addButton(STOP_STR,100,20,"TRIGGER"/*"SWITCH"*/,true, 2, &myValue2);
		#endif
	//serial.enumerateDevices();
	//----------------------------------- note:
	// < this should be set
	// to whatever com port
	// your serial device is
	// connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....

	#ifdef _TWO_
	serialL.setup(/**/"\\\\.\\COM13",9600);  						  // windows example
	serialR.setup(/**/"\\\\.\\COM5",9600);  						  // windows example
	#endif
	#ifdef _UP_
	//serial.setup(/**/"\\\\.\\COM15",9600);  						  // windows example
	serial.setup(/**/"\\\\.\\COM14",9600);  						  // windows example
	#endif
	#ifdef _IR_
	serialA.setup(/**/"\\\\.\\COM6",9600);
	#endif 
	cptr = bytes;
	upValue0=ouValue0=upValue1=ouValue1=upValue2=ouValue2=upValue3=ouValue3=upValue4=ouValue4=upValue5=ouValue5=upValue6=ouValue6=lValue0=olValue0=lValue1=olValue1=lValue2=olValue2=lValue3=olValue3=lValue4=olValue4=lValue5=olValue5=lValue6=olValue6=lValue7=olValue7=lValue8=olValue8=lValue9=olValue9=lValue10=olValue10=rValue0=orValue0=rValue1=orValue1=rValue2=orValue2=rValue3=orValue3=rValue4=orValue4=rValue5=orValue5=rValue6=orValue6=rValue7=orValue7=rValue8=orValue8=rValue9=orValue9=rValue10=orValue10=0;
	preventStupid = readyBreak = waitRes = false;	
	trigIndex = -1;
	deltaTime = connectTime = 0;
	#ifdef _LUMI_
	weConnected = tcpClient.setup(SERVER,PORT);
	tcpClient.setVerbose(true);
	#else
	DMX.setup(/**/"\\\\.\\COM16",9600);
	#endif
	#ifdef _KINECT_
	kinectConnected = kinectClient.setup("127.0.0.1",11999);
	kinectClient.setVerbose(true);
	#endif
	InPn = true;
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
		/*			
		if(!msgRx.empty())
		{

			found=msgRx.find("9 : ");
			if (found!=string::npos && msgRx.at(found + 4) != 'X' )
			{
				xxxx[9] = ofToFloat(msgRx.substr(found + 4,9));
				found=msgRx.find("\t",found+1);
				yyyy[9] = ofToFloat(msgRx.substr(found + 1,9));
				found=msgRx.find("\t",found+1);
				zzzz[9] = ofToFloat(msgRx.substr(found + 1,9));
				lValue9 = mapRay(zzzz[9],25,90,-13000,100000);
				if(0 == olValue9)
				{
					olValue9 = lValue9;
				}
				if(lValue9 != olValue9)
				{
					//reqAT(T9,"T9IFOFF", LEFT);
					reqSlider(T9,IMA_STR, lValue9,LEFT);
					olValue9 = lValue9;
				}
			}

			found=msgRx.find("15 : ");
			if (found!=string::npos && msgRx.at(found + 5) != 'X' )
			{
				xxxx[15] = ofToFloat(msgRx.substr(found + 4,9));
				found=msgRx.find("\t",found+1);
				yyyy[15] = ofToFloat(msgRx.substr(found + 1,9));
				found=msgRx.find("\t",found+1);
				zzzz[15] = ofToFloat(msgRx.substr(found + 1,9));
				rValue9 = mapRay(zzzz[15],30,100,-10000,103000);
				if(0 == orValue9)
				{
					orValue9 = rValue9;
				}
				if(rValue9 != orValue9)
				{
					//reqAT(T9,"T9IFOFF", LEFT);
					reqSlider(T9, IMA_STR, rValue9, RIGHT);
					orValue9 = rValue9;
				}
			}
		}
		*/

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
				reqAT(T0,"pn10=50",UP);
				ofSleepMillis(100);
				reqAT(T1,"pn10=50",UP);
				ofSleepMillis(100);
				reqAT(T2,"pn10=50",UP);
				ofSleepMillis(100);
				reqAT(T3,"pn10=50",UP);
				ofSleepMillis(100);
				reqAT(T4,myValue50.insert(0,"pn10="),UP);
				ofSleepMillis(100);
				reqAT(T5,myValue50,UP);
				ofSleepMillis(100);
				reqAT(T6,myValue50,UP);
				ofSleepMillis(100);
				reqBatch(myValue50,LEFT);
				ofSleepMillis(750);
				reqBatch(myValue50,RIGHT);
				ofSleepMillis(750);
				reqBatch("save",ALL);
				ofSleepMillis(1500);
				preventStupid = true;
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
				totalSec = 0;
				preventStupid = false;
				motorMember = root.getMemberNames();
				it = motorMember.begin();
				while( (*it).find(myValue55)==string::npos )
				{
					if(it == motorMember.end())
					{
						it = motorMember.begin();
						break;
					}
					else
					{
						totalSec += root[(*it)][INTERVAL].asDouble()/1000;
						it++;
					}
				}
				ContinueTimer();
				#ifdef _PLAY_
				vocals.play();
				vocals.setSpeed(185.0/237.0);
				vocals.setPosition((double)(totalSec+secShift)/(double)1094);
				#endif
		}
		#ifndef _ILAN_
		else if (gui->listenForTrigger(56) == true)
		{
			myValue54 = 0;
			reqAT(T0,"pn10=50",UP);
			ofSleepMillis(100);
			reqAT(T1,"pn10=50",UP);
			ofSleepMillis(100);
			reqAT(T2,"pn10=50",UP);
			ofSleepMillis(100);
			reqAT(T3,"pn10=50",UP);
			ofSleepMillis(100);
			reqAT(T4,myValue50.insert(0,"pn10="),UP);
			ofSleepMillis(100);
			reqAT(T5,myValue50,UP);
			ofSleepMillis(100);
			reqAT(T6,myValue50,UP);
			ofSleepMillis(100);
			reqBatch(myValue50,LEFT);
			ofSleepMillis(750);
			reqBatch(myValue50,RIGHT);
			ofSleepMillis(750);
			reqBatch("pn05=H0101",ALL);
			ofSleepMillis(1500);
			reqBatch("pn11=10",ALL);
			ofSleepMillis(1500);
			reqBatch("pn24=2000",ALL);
			ofSleepMillis(1500);
			reqBatch("save",ALL);
			preventStupid = true;
		}
		else if (gui->listenForTrigger(59) == true)
		{
			myValue54 = 0;
			reqBatch("mr-2000",ALL);
			/*		
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
			*/
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
				request(myValue38, UP);
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
			reqAT(T4,"mr2000",UP);
			ofSleepMillis(100);
			reqAT(T5,"mr2000",UP);
			ofSleepMillis(100);
			reqAT(T6,"mr2000",UP);
			ofSleepMillis(100);
			reqAT(T0,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T0,"mr2000",RIGHT);
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
			reqAT(T5,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T5,"mr2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T7,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T7,"mr2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T8,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T8,"mr2000",RIGHT);
			ofSleepMillis(100);
			reqAT(T10,"mr2000",LEFT);
			ofSleepMillis(100);
			reqAT(T10,"mr2000",RIGHT);

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

			reqBatch("pn23=300",LEFT);
			ofSleepMillis(500);
			reqBatch("pn23=300",RIGHT);
			ofSleepMillis(500);
			
			reqAT(T4,"pn23=300",UP);
			ofSleepMillis(100);
			reqAT(T5,"pn23=300",UP);
			ofSleepMillis(100);
			reqAT(T6,"pn23=300",UP);
			ofSleepMillis(100);
			reqAT(T0,"pn23=50",UP);
			ofSleepMillis(100);
			reqAT(T1,"pn23=50",UP);
			ofSleepMillis(100);
			reqAT(T2,"pn23=50",UP);
			ofSleepMillis(100);
			reqAT(T3,"pn23=50",UP);
			ofSleepMillis(100);
			
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
		else if (gui->listenForTrigger(32) == true)
		{
			myValue54 = 0;
			preventStupid = false;
			motorMember = root.getMemberNames();
			it = motorMember.begin();
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
				reqAT(T4,"mr2000",LEFT);
				ofSleepMillis(100);
				reqAT(T4,"mr2000",RIGHT);
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
				/*
				while((*it).at(0) != 'd')
					it++;
				trigIndex = 325;
				*/
				break;
			case 6:
				/*
				while((*it).at(0) != 'f')
					it++;
				trigIndex = 326;
				*/
				break;
			case 7:
				/*
				while((*it).at(0) != 'h')
					it++;
				trigIndex = 327;
				*/
				break;
			case 8:
				/*
				while((*it).at(0) != 'i')
					it++;
				trigIndex = 328;
				*/
				break;
			}
			ContinueTimer();		
		}
		else if (gui->listenForTrigger(42) == true)
		{
			myValue54 = 0;
			preventStupid = false;
			motorMember = root.getMemberNames();
			it = motorMember.begin();
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
				reqAT(T4,"mr-2000",LEFT);
				ofSleepMillis(100);
				reqAT(T4,"mr-2000",RIGHT);
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
				/*
				while((*it).at(0) != 'd')
					it++;
				trigIndex = 325;
				*/
				break;
			case 6:
				/*
				while((*it).at(0) != 'f')
					it++;
				trigIndex = 326;
				*/
				break;
			case 7:
				/*
				while((*it).at(0) != 'h')
					it++;
				trigIndex = 327;
				*/
				break;
			case 8:
				/*
				while((*it).at(0) != 'i')
					it++;
				trigIndex = 328;
				*/
				break;
			}
			ContinueTimer();		
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

	ofSetColor(0xffffff);
	gui->draw();
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
	if ( serialA.available() > 0)
	{
		if ( -1 == trigIndex )
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
				totalSec = 0;
				preventStupid = false;
				motorMember = root.getMemberNames();
				it = motorMember.begin();
				ContinueTimer();
				#ifdef _PLAY_
				vocals.play();
				vocals.setSpeed(185.0/237.0);
				vocals.setPosition((double)(totalSec+secShift)/(double)1094);
				#endif
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

		/*
		int result = serial.readBytes( bytes, bytesRequired );
		bytes[bytesRequired - 1] = 0;
		// check for error code
		if ( result == OF_SERIAL_ERROR )
		{
			//error handling
			ofLog( OF_LOG_ERROR, "unrecoverable error reading from serial" );
		}
		else if ( result == OF_SERIAL_NO_DATA )
		{
			//error handling
		}
		else
		{
			bytes[result] = 0;
		}
		*/	
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
	
	/*
	if(!myString.empty())
	{stop
		ofDrawBitmapString(myString, 400 ,10);
	}
	ofDrawBitmapString(ofToString(zzzz[9]), 700 ,30);
	ofDrawBitmapString(ofToString(zzzz[15]), 700 ,10);

	*/
	franklinBook.drawString(msgRx, 700, 150);
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
	else if(key == 'u')
	{
		myValue54 = 0;
		reqBatch("mr-2000",ALL);
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

void testApp::reqAT(string realCmd, string b, int which){
	//reqflush(which);
	realCmd.append(b);
	int guan = 0;
	switch(which)
	{
	case UP:
		#ifdef _TWO_
		guan = realCmd.at(1) - '0'; 
		if( guan <= 6 
			#ifdef _GUAN_
			&& guan >= 2 
			#endif
			)
		{
			if( realCmd.at(2) != '0' )
		#endif
				request(realCmd,UP);
		#ifdef _TWO_
		}
		#endif
		break;
	case LEFT:
		//if( realCmd.at(1) != '1' || realCmd.at(2) == '0')
			request(realCmd,LEFT);
		break;
	case RIGHT:
		request(realCmd,RIGHT);
		break;
	case ALL:
		guan = realCmd.at(1) - '0'; 
		if( guan <= 6 
			#ifdef _GUAN_
			&& guan >= 2 
			#endif
			)
		{
			if( realCmd.at(2) != '0' )
			request(realCmd,UP);
		}
		//if( realCmd.at(1) != '1' || realCmd.at(2) == '0' )
			request(realCmd,LEFT);
		request(realCmd,RIGHT);
		break;
	}
	
}

void testApp::resAT(string realCmd, string b, int which){
	realCmd.append(b);
	int guan = 0;
	switch(which)
	{
	case UP:
		guan = realCmd.at(1) - '0'; 
		if( guan <= 6 
			#ifdef _GUAN_
			&& guan >= 2 
			#endif
			)
		{
			if( realCmd.at(2) != '0' )
				cmdQuene.push_back(realCmd);
		}
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
		guan = realCmd.at(1) - '0'; 
		if( guan <= 6 
			#ifdef _GUAN_
			&& guan >= 2 
			#endif
			)
		{
			if( realCmd.at(2) != '0' )
				cmdQuene.push_back(realCmd);
		}
		break;
	}
	
}

void testApp::reqFAQ(string realCmd, string b, int which){
	realCmd.append(b);
	int guan = 0;
	switch(which)
	{
	case UP:
		guan = realCmd.at(2) - '0'; 
		if( guan <= 6 
			#ifdef _GUAN_
			&& guan >= 2 
			#endif
			)
		{
			if( realCmd.at(3) != '0' )
				cmdQuene.push_back(realCmd);
		}
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
		guan = realCmd.at(2) - '0'; 
		if( guan <= 6 
			#ifdef _GUAN_
			&& guan >= 2 
			#endif
			)
		{
			if( realCmd.at(3) != '0' )
				cmdQuene.push_back(realCmd);
		}
		break;
	}
	
}

void testApp::request(string buffer, int which)
{

	buffer.append(LFCR);
	switch(which)
	{
	#ifdef _UP_
	case UP:
		serial.writeBytes((unsigned char *)buffer.c_str(),buffer.length());
		break;
	#endif
	#ifdef _TWO_
	case LEFT:
		serialL.writeBytes((unsigned char *)buffer.c_str(),buffer.length());
		break;
	case RIGHT:
		if (buffer.find("t0")!=string::npos)
		{
			which = which;
		}
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
	
	// See this page for all of the ways to access data in a Json::Value
	// http://jsoncpp.sourceforge.net/class_json_1_1_value.html
	
	/*
	Json::Value text = root["widget"]["text"];
	result += "text members: " + ofToString((int)text.size()) + "\n";
	result += "data: " + text["data"].asString() + "\n";

	*/
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
					timeInt /= 32;
					if(lastss.empty() == false && timeInt != 0)
					{
						difference = ABS( plugins[index].asInt() - lastplugins[index].asInt() );
						int _pn = difference / timeInt;
						_pn = _pn < 50 && _pn > 0  ? 50 : _pn;
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
					timeInt /= 32;
					if(lastss.empty() == false && timeInt != 0)
					{
						difference = ABS( plugins[index].asInt() - lastplugins[index].asInt() );
						int _pn = difference / timeInt;
						_pn = _pn < 50 && _pn > 0  ? 50 : _pn;
						if(difference > 0 && _pn > 0)
							reqJSON( strsub , "pn10=", ofToString( _pn ), RIGHT);
					}
					break;
				case 2:
					strsub = iiit.substr(1,2);
					switch(strsub.at(1))
					{
					case '0':
						timeInt /= 32; // 後退 << 2 掛點
						break;
					case '1':
						timeInt /= 320; // 後退 << 2 掛點
						break;
					case '2':
						timeInt /= 32; // 轉頭 >> 2 還是掛點
						break;
					case '3':
						timeInt /= 32; // 轉身怕掉下來
						break;
					default:
						timeInt /= 32;
						break;
					}
					if(lastss.empty() == false && timeInt != 0)
					{
						difference = ABS( plugins[index].asInt() - lastplugins[index].asInt() );
						int _pn = difference / timeInt;
						_pn = _pn < 50 && _pn > 0 ? 50 : _pn;
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
	
	// See this page for all of the ways to access data in a Json::Value
	// http://jsoncpp.sourceforge.net/class_json_1_1_value.html
	
	/*
	Json::Value text = root["widget"]["text"];
	result += "text members: " + ofToString((int)text.size()) + "\n";
	result += "data: " + text["data"].asString() + "\n";

	*/
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
		#else
		if(5 == RGB)
			RGB = 2;
		string bufferDMX = "t" + ofToString(thatInt) + "c" + ofToString(RGB++) + "w";
		DMX.writeBytes((unsigned char *)bufferDMX.c_str(),bufferDMX.length());
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
				reqAT(T0,"pn10=50",UP);
				ofSleepMillis(100);
				reqAT(T1,"pn10=50",UP);
				ofSleepMillis(100);
				reqAT(T2,"pn10=50",UP);
				ofSleepMillis(100);
				reqAT(T3,"pn10=50",UP);
				ofSleepMillis(100);
				reqAT(T4,myValue50.insert(0,"pn10="),UP);
				ofSleepMillis(100);
				reqAT(T5,myValue50,UP);
				ofSleepMillis(100);
				reqAT(T6,myValue50,UP);
				ofSleepMillis(100);
				reqBatch(myValue50,LEFT);
				ofSleepMillis(750);
				reqBatch(myValue50,RIGHT);
				ofSleepMillis(750);
				reqBatch("save",ALL);
				preventStupid = true;
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
				reqAT(T0,"pn10=50",UP);
				ofSleepMillis(100);
				reqAT(T1,"pn10=50",UP);
				ofSleepMillis(100);
				reqAT(T2,"pn10=50",UP);
				ofSleepMillis(100);
				reqAT(T3,"pn10=50",UP);
				ofSleepMillis(100);
				reqAT(T4,myValue50.insert(0,"pn10="),UP);
				ofSleepMillis(100);
				reqAT(T5,myValue50,UP);
				ofSleepMillis(100);
				reqAT(T6,myValue50,UP);
				ofSleepMillis(100);
				reqBatch(myValue50,LEFT);
				ofSleepMillis(750);
				reqBatch(myValue50,RIGHT);
				ofSleepMillis(750);
				reqBatch("save",ALL);
				preventStupid = true;
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
	if(true == InPn)
	{
		MaTimer();
		++it;
		InPn = false;
	}
	else
	{
		ContinueTimer();
		InPn = true;
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
		#endif
		break;
	}

}