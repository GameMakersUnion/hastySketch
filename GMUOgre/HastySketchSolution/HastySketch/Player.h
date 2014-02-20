#ifndef __Player_h_
#define __Player_h_

#include "stdafx.h"
#include "Actor.h"
class Player : public Actor
{


public:
	
	Ogre::Rect * sceneRect;
	Player(){ oldPosition = Ogre::Vector3(0, 0, 0); } //apparently we can't call default constructors from other constructors, we need to make an INIT method for common code (later)
	Player(Ogre::SceneManager * mSceneMgr, Ogre::Entity * ent, Ogre::SceneNode * scenenode, Ogre::Rect * sceneR)
	{
		sceneRect = sceneR;
		oldPosition = Ogre::Vector3(0, 0, 0);
		
		actorEnt = ent;
		actorNode = scenenode;
		velocity = Ogre::Vector3(0, 0, 0);

		walking_speed = 0.2;
		total_speed=0.0;
		run_speed = 0.0;
		max_spd = 0.5;
		min_spd = 0.02;
		acc_inc = 0.01;
		//actorNode = mSceneMgr->createSceneNode("actorNode");
		//mSceneMgr->getRootSceneNode()->addChild(actorNode);
		//actorNode->attachObject(actorEnt);

		//Ogre::Vector3 pos = getPosition3();
		//setPosition(Ogre::Vector3(pos.x, pos.y, pos.z + 13));
		//velocity = Ogre::Vector3(0, 0, 0);
	};
	Player(Ogre::Entity *ent, Ogre::SceneNode *node, Ogre::Vector3 position = Ogre::Vector3(-100000, 0, 0)) //reset position's default parameter to global variable detailing origin
	{
		actorEnt = ent;
		actorNode = node;
		velocity = Ogre::Vector3(0, 0, 0);
		if (position.x != -100000)
		{
			setPosition(position);
		}
	};
	void Update(std::set<OIS::KeyCode> keyPresses);
	//Ogre::Entity* actorEnt;
	//Ogre::SceneNode* actorNode;
	Ogre::Vector3 oldPosition;


	void setVelocity(Ogre::Vector3 vel)
	{
		velocity = vel;
	}
	void setPosition(Ogre::Vector3 position)
	{
		actorNode->setPosition(position);
	}
	void setPosition(Ogre::Vector2 position)
	{
		actorNode->setPosition(Ogre::Vector3(position.x, position.y, getPosition3().z));
	}
	Ogre::Vector3 getPosition3()
	{
		return actorNode->getPosition();
	}
	Ogre::Vector2 getPosition()
	{
		Ogre::Vector3 v = actorNode->getPosition();
		return Ogre::Vector2(v.x, v.y);
	}

private:
	Ogre::Vector3 velocity;
	//float fall_global;
	float playerHeight;
	float speed;
	float walking_speed;
	float total_speed;
	float run_speed;
	float max_spd;
	float min_spd;
	float acc_inc;
};

#endif // #ifndef __Game_h_