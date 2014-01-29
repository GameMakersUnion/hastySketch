#include "stdafx.h"

#include "Player.h"



void Player::playerUpdate(std::set<OIS::KeyCode> keyPresses)
{
	Ogre::Vector2 pos = getPosition();

	const float spd = 0.2;
	if (keyPresses.count(OIS::KC_W)){
		pos = Ogre::Vector2(pos.x, pos.y + spd);
	}if (keyPresses.count(OIS::KC_A)){
		pos = Ogre::Vector2(pos.x - spd, pos.y);
	}if (keyPresses.count(OIS::KC_S)){
		pos = Ogre::Vector2(pos.x, pos.y - spd);
	}if (keyPresses.count(OIS::KC_D)){
		pos = Ogre::Vector2(pos.x + spd, pos.y);
	}
	
	std::cout << pos.x << ", " << pos.y << getPosition3().z << "\n";

	setPosition(Ogre::Vector3(pos.x, pos.y, getPosition3().z ));
	
}