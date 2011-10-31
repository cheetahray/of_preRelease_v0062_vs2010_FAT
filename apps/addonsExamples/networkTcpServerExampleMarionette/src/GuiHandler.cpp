/*---------------------------------------------------
Open Frameworks 0.05
graphical user interface - Dennis Rosenfeld-2008
*///--------------------------------
#include "GuiHandler.h"


GuiHandler::GuiHandler()//constructor
{
    initialize();
}


GuiHandler::~GuiHandler()//destructor
{
}


void    GuiHandler::initialize()
{

    isHidden = false;
    hideKey = 'h';
    keysWhileHidden = true;

    isTypingBlocked = false;
    //ofMouseEvents.addListener(this);
	//ofKeyEvents.addListener(this);
	ofAddListener(ofEvents.mousePressed, this, &GuiHandler::_mousePressed);
	ofAddListener(ofEvents.mouseMoved, this, &GuiHandler::_mouseMoved);
	ofAddListener(ofEvents.mouseDragged, this, &GuiHandler::_mouseDragged);
	ofAddListener(ofEvents.mouseReleased, this, &GuiHandler::_mouseReleased);
	ofAddListener(ofEvents.keyPressed, this, &GuiHandler::_keyPressed);
	ofAddListener(ofEvents.keyReleased, this, &GuiHandler::_keyReleased);

	//ofAppEvents.addListener(this);
    //PanelList = new GuiPanel[5];
}

GuiPanel*   GuiHandler::addPanel(string name,int x,int y,int w, int h)
{
    GuiPanel* newPanel = new GuiPanel;
    newPanel->initialize(name,x,y,w,h);
    panelList.push_back(newPanel);

    return newPanel;
}

bool    GuiHandler::updateBool(int idNum)
{
    bool tempVal;

    for (int i = 0; i < panelList.size(); i++ )
    {
        for (int j = 0; j < panelList[i]->elements.size(); j++ )
        {
            if ( idNum == panelList[i]->elements[j]->getID() )
            {
                tempVal = panelList[i]->elements[j]->getValueBool();
            }
        }
    }
    return tempVal;
}


float    GuiHandler::updateFloat(int idNum)
{
    float tempVal;

    for (int i = 0; i < panelList.size(); i++ )
    {
        for (int j = 0; j < panelList[i]->elements.size(); j++ )
        {
            if ( idNum == panelList[i]->elements[j]->getID() )
            {
                tempVal = panelList[i]->elements[j]->getValueFloat();
            }
        }
    }
    return tempVal;
}

string    GuiHandler::updateString(int idNum)
{
    string tempVal;

    for (int i = 0; i < panelList.size(); i++ )
    {
        for (int j = 0; j < panelList[i]->elements.size(); j++ )
        {
            if ( idNum == panelList[i]->elements[j]->getID() )
            {
                tempVal = panelList[i]->elements[j]->getValueString();
            }
        }
    }
    return tempVal;
}

int    GuiHandler::updateInt(int idNum)
{
    int tempVal;

    for (int i = 0; i < panelList.size(); i++ )
    {
        for (int j = 0; j < panelList[i]->elements.size(); j++ )
        {
            if ( idNum == panelList[i]->elements[j]->getID() )
            {
                tempVal = panelList[i]->elements[j]->getValueInt();
            }
        }
    }
    return tempVal;
}

void    GuiHandler::draw()
{
    if (isHidden == false)
    {
        for (int i = 0; i < panelList.size(); i++ )
        {
            panelList[i]->draw();
        }
    }
}

void    GuiHandler::hide()
{
    isHidden = true;
    isTypingBlocked = true;

}

void    GuiHandler::unHide()
{
    isHidden = false;
    isTypingBlocked = false;
}

void GuiHandler::_mouseMoved(ofMouseEventArgs &e)
{
	mouseMoved(e.x,e.y); //guilistener
}

void    GuiHandler::mouseMoved(int x, int y)
{
    if (isHidden == false)
    {
        for (int i = 0; i < panelList.size(); i++ )
        {
          if ( panelList[i]->checkBoundaries(x,y) == true)
          {
            panelList[i]->setLine(true);
            panelList[i]->mouseMoved(x,y);
          }
          else
            {
            panelList[i]->setLine(false);
          }
        }
    }
}

void GuiHandler::_mousePressed(ofMouseEventArgs &e)
{
	mousePressed(e.x, e.y, e.button); //guilistener
}

void    GuiHandler::mousePressed(int x, int y, int button)
{
    if (isHidden == false)
    {
        for (int i = 0; i < panelList.size(); i++ )
        {
          if ( panelList[i]->checkBoundaries(x,y) == true)
          {
            panelList[i]->mousePressed(x,y,button);
          }

          else //not in boundaries.
          {
            //check elements for textfields and depress them.
            for (int j = 0; j < panelList[i]->elements.size(); j++ )
            {
                if ( panelList[i]->elements[j]->checkType() == "TEXTFIELD")
                {
                   panelList[i]->elements[j]->dePress();
                }
            }
          }

         }//end panel size.
    }
}

void GuiHandler::_mouseReleased(ofMouseEventArgs &e)
{
	mouseReleased(); //guilistener
}

void    GuiHandler::mouseReleased()
{
    if (isHidden == false)
    {
        for (int i = 0; i < panelList.size(); i++ )
        {
            panelList[i]->mouseReleased();
        }
    }
}

void GuiHandler::_mouseDragged(ofMouseEventArgs &e)
{
	mouseDragged(e.x, e.y, e.button); //guilistener
}

void    GuiHandler::mouseDragged(int x, int y, int button)
{
    if (isHidden == false)
    {
        for (int i = 0; i < panelList.size(); i++ )
        {
          if ( panelList[i]->checkBoundaries(x,y) == true)
          {
            panelList[i]->mouseDragged(x,y,button);
          }

        }
    }
}

void GuiHandler::_keyPressed(ofKeyEventArgs &e)
{
	keyPressed(e.key); //guilistener
}

void GuiHandler::keyPressed(int key)
{

    bool keypressOK = true;
    if (isTypingBlocked == false)
    {
            for (int i = 0; i < panelList.size(); i++ )
            {
                for (int j = 0; j < panelList[i]->elements.size(); j++ )
                {

                    if ( panelList[i]->elements[j]->checkType() == "TEXTFIELD")
                    {
                        if( panelList[i]->elements[j]->keyPressOK() == false)
                        {
                            keypressOK = false;
                            panelList[i]->elements[j]->keyPressed(key);//only pass keys to the textbox.
                        }
                    }
                }
            }
            if (keypressOK == true)
            {
                if (key == hideKey)
                {
                    if ( isHidden == false)
                    {
                     isHidden = true;
                    }
                    else if ( isHidden == true)
                    {
                     isHidden = false;
                    }

                }

                if (isHidden == false || keysWhileHidden == true)
                {
                    for (int i = 0; i < panelList.size(); i++ )
                    {
                        for (int j = 0; j < panelList[i]->elements.size(); j++ )
                        {
                            panelList[i]->elements[j]->keyPressed(key);
                            //cout<<"typing test";
                        }
                    }
                }
            }
    }
}

void GuiHandler::_keyReleased(ofKeyEventArgs &e)
{
	keyReleased(e.key); //guilistener
}

void GuiHandler::keyReleased(int key)
{
    if (isHidden == false)
    {
        for (int i = 0; i < panelList.size(); i++ )
        {
            for (int j = 0; j < panelList[i]->elements.size(); j++ )
            {
                   panelList[i]->elements[j]->keyReleased(key);
            }
        }
    }
}

void GuiHandler::setHideKey(int key)
{
    hideKey = key;
}


bool    GuiHandler::listenForTrigger(int idNum)
{
    int tempVal;

    for (int i = 0; i < panelList.size(); i++ )
    {
        for (int j = 0; j < panelList[i]->elements.size(); j++ )
        {
            if ( idNum == panelList[i]->elements[j]->getID() )
            {
                tempVal = panelList[i]->elements[j]->listenForTrigger();
            }
        }
    }
    return tempVal;
}


bool   GuiHandler::isSafeToType()
{
    bool keypressOK = true;
    for (int i = 0; i < panelList.size(); i++ )
    {
        for (int j = 0; j < panelList[i]->elements.size(); j++ )
        {
            if ( panelList[i]->elements[j]->checkType() == "TEXTFIELD")
            {
                if( panelList[i]->elements[j]->keyPressOK() == false)
                {
                    keypressOK = false;
                }
            }
        }
    }
    return keypressOK;
}

bool      GuiHandler::isGuiHidden()
{
 return isHidden;
}



void        GuiHandler::disableKeys()
{
    isTypingBlocked = true;
}
void        GuiHandler::enableKeys()
{
    isTypingBlocked = false;
}


