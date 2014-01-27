#ifndef __Player_h_
#define __Player_h_

#include "stdafx.h"
class Player 
{
public:
	static void playerUpdate(Ogre::Vector2 &pos, std::set<OIS::KeyCode> keyPresses);
};

#endif // #ifndef __Game_h_