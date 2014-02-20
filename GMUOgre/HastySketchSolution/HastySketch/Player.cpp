#include "stdafx.h"

#include "Player.h"
#include "Game.h"


void Player::Update(std::set<OIS::KeyCode> keyPresses)
{
	//return;
	Actor::Update(keyPresses);
	Ogre::Vector2 pos = getPosition();
	Ogre:: Rect * box=sceneRect;
	
	

	//acceleration
	if (keyPresses.count(OIS::KC_LSHIFT) || keyPresses.count(OIS::KC_RSHIFT )){
		run_speed += acc_inc;
		if (run_speed > max_spd){
			run_speed = max_spd;
		}
	}
	else
	{
		run_speed -= acc_inc;
		if (run_speed < 0){
			run_speed = 0;
		}
	}
	//else speed=0.2;

	//gravity
	playerWidth = actorEnt->getBoundingBox().getHalfSize().x;
	playerHeight = actorEnt->getBoundingBox().getHalfSize().z;
	if ((pos.y-playerHeight)>(box->bottom)){
		pos.y-=velocity.y;
		velocity.y+=Game::fall_global;
		std::cout << velocity.y << ", " << Game::fall_global << "\n";
	}
	else velocity.y=0.0;

	//std::cout << walking_speed << ", " << run_speed << "\n";
	
	total_speed = walking_speed + run_speed;

	if (keyPresses.count(OIS::KC_W) && (box->top)>(pos.y+playerHeight)){
		pos = Ogre::Vector2(pos.x, pos.y + total_speed);
	}if (keyPresses.count(OIS::KC_A) && (box->left)<(pos.x-playerWidth)){
		pos = Ogre::Vector2(pos.x - total_speed, pos.y);
	}if (keyPresses.count(OIS::KC_S) && (box->bottom)<(pos.y-playerHeight)){
		pos = Ogre::Vector2(pos.x, pos.y - total_speed);
	}if (keyPresses.count(OIS::KC_D) && (box->right)>(pos.x+playerWidth)){
		pos = Ogre::Vector2(pos.x + total_speed, pos.y);
	}
	Ogre::Vector3 vect = Ogre::Vector3(pos.x, pos.y, getPosition3().z);

	if (oldPosition.x != vect.x || oldPosition.y != vect.y || oldPosition.z != vect.z)
	{
		//std::cout << vect.x << ", " << vect.y << vect.z << "\n";
	}

	oldPosition = vect;

	//setPosition(Ogre::Vector3(pos.x, pos.y, getPosition3().z + 0.2));
	setPosition(Ogre::Vector2(pos.x, pos.y));

	
}