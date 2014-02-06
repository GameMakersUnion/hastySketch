#include "stdafx.h"

#include "Player.h"



void Player::Update(std::set<OIS::KeyCode> keyPresses)
{
	Actor::Update(keyPresses);
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
	Ogre::Vector3 vect = Ogre::Vector3(pos.x, pos.y, getPosition3().z);

	if (oldPosition.x != vect.x || oldPosition.y != vect.y || oldPosition.z != vect.z)
		std::cout << vect.x << ", " << vect.y << vect.z << "\n";

	oldPosition = vect;

	//setPosition(Ogre::Vector3(pos.x, pos.y, getPosition3().z + 0.2));
	setPosition(Ogre::Vector2(pos.x, pos.y));

	
}