/*
-----------------------------------------------------------------------------
Filename:    Game.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __Game_h_
#define __Game_h_

#include "BaseApplication.h"

class Game : public BaseApplication
{
public:
	Game(void);
	virtual ~Game(void);
	std::set<OIS::KeyCode> keyList;

protected:
    virtual void createScene(void);
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};

#endif // #ifndef __Game_h_
