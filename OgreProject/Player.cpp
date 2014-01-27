#include "Player.h"



void Player::playerUpdate(Ogre::Vector2 &pos, std::set<OIS::KeyCode> keyPresses)
{
	const float spd = 0.05;
	if (keyPresses.count(OIS::KC_W)){
		pos = Ogre::Vector2(pos.x, pos.y + spd);
	}if (keyPresses.count(OIS::KC_A)){
		pos = Ogre::Vector2(pos.x - spd, pos.y);
	}if (keyPresses.count(OIS::KC_S)){
		pos = Ogre::Vector2(pos.x, pos.y - spd);
	}if (keyPresses.count(OIS::KC_D)){
		pos = Ogre::Vector2(pos.x + spd, pos.y);
	}
	
	
}