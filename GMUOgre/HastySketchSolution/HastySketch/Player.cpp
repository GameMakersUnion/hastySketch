#include "stdafx.h"

#include "Player.h"



void Player::Update(std::set<OIS::KeyCode> keyPresses)
{
	//return;
	Actor::Update(keyPresses);
	Ogre::Vector2 pos = getPosition();
	Ogre:: Rect * box=sceneRect;

	const float spd = 0.2; // should be spd=speed;
	float max_spd = 0.1;
	float min_spd = 0.02;
	float acc_inc = 0.001;
	float acc_dec = 0.0001;

	//acceleration
	if (keyPresses.count(OIS::KC_LSHIFT) || keyPresses.count(OIS::KC_RSHIFT )){
		if (speed < max_spd){
			speed += acc_inc;
			//std::cout << speed;
			printf("%f", speed);
			DBOUT(speed << std::endl);			
		}
	}
	else {
		if (speed > min_spd)
			speed=0.07;
	}

	//gravity
	playerHeight=0;
	if (pos.y>(box->bottom)){
		//pos.y-=fall;
		fall+=0.0001;
	}
	else fall=0.0;

	if (keyPresses.count(OIS::KC_W) && (box->top)>pos.y){
		pos = Ogre::Vector2(pos.x, pos.y + spd);
	}if (keyPresses.count(OIS::KC_A) && (box->left)<pos.x){
		pos = Ogre::Vector2(pos.x - spd, pos.y);
	}if (keyPresses.count(OIS::KC_S) && (box->bottom)<pos.y){
		pos = Ogre::Vector2(pos.x, pos.y - spd);
	}if (keyPresses.count(OIS::KC_D) && (box->right)>pos.x){
		pos = Ogre::Vector2(pos.x + spd, pos.y);
	}
	Ogre::Vector3 vect = Ogre::Vector3(pos.x, pos.y, getPosition3().z);

	if (oldPosition.x != vect.x || oldPosition.y != vect.y || oldPosition.z != vect.z)
		std::cout << vect.x << ", " << vect.y << vect.z << "\n";

	oldPosition = vect;

	//setPosition(Ogre::Vector3(pos.x, pos.y, getPosition3().z + 0.2));
	setPosition(Ogre::Vector2(pos.x, pos.y));

	
}