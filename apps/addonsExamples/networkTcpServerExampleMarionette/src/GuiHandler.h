#ifndef GUIHANDLER_H_INCLUDED
#define GUIHANDLER_H_INCLUDED

//--------------------------------------------------------------
#include "ofMain.h"


#define OF_ADDON_USING_OFXDIRLIST
#define OF_ADDON_USING_OFXVECTORMATH
#define OF_ADDON_USING_OFXXMLSETTINGS

#include "ofMain.h"
#include "ofAddons.h"

#include "GuiPanel.h"

class   GuiHandler//: public ofSimpleApp public ofMouseListener, public ofKeyListener, public ofAppListener
{
    //Handles overall control of the User interface.

    private:
        //VARIABLES:--------------------------------------------------
        bool    isHidden;
        int     hideKey;
        bool    keysWhileHidden;
        bool    isTypingBlocked;


    public:
        GuiHandler();                           //constructor
        ~GuiHandler();                          //destructor
        void             initialize();          //initialize objects.

        //METHODS:--------------------------------------------------------

        bool            updateBool(int idNum);
        float           updateFloat(int idNum);
        string          updateString(int idNum);
        int             updateInt(int idNum);
        bool            listenForTrigger(int idNum);

        // bool            update(int idNum);
        void            draw(int x, int y);
        vector          <GuiPanel*> panelList;
        GuiPanel*       addPanel(string name,int x,int y,int w, int h);
        void            draw();


  	//void	keyPressed(int key);
	//void	mouseMoved(int x, int y);
//	void	mousePressed(int x, int y, int button);

		void _mouseMoved(ofMouseEventArgs &e);
        void _mousePressed(ofMouseEventArgs &e);
		void _mouseDragged(ofMouseEventArgs &e);
		void _mouseReleased(ofMouseEventArgs &e);
		//Key Events
		void _keyPressed(ofKeyEventArgs &e);
		void _keyReleased(ofKeyEventArgs &e);
	
        void            mouseMoved(int x, int y);
        void            mousePressed(int x, int y, int button);
        void            mouseDragged(int x, int y, int button);
        void            mouseReleased();
        void            keyPressed(int key );
        void            keyReleased(int key);

        void            hide();
        void            unHide();
        void            setHideKey(int key);

      //  void            setKeysWhileHidden(bool yesNo);
        bool             isSafeToType();
        void             disableKeys();
        void             enableKeys();
        bool             isGuiHidden();
        //void            mouseDragged(x, y, button);
        //void            mouseReleased(mouseX, mouseY, button);

};



#endif // GUIHANDLER_H_INCLUDED
