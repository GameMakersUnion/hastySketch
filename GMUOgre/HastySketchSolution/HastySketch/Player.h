#ifndef __Player_h_
#define __Player_h_

#include "stdafx.h"
class Player 
{
public:
	Player(){ }
	Player(Ogre::SceneManager * mSceneMgr)
	{
		playerEnt = mSceneMgr->createEntity("PlayerEntity", "Sinbad.mesh");
		//mSceneMgr->getRootSceneNode()->attachObject(ent);
		playerNode = mSceneMgr->createSceneNode("PlayerNode");
		mSceneMgr->getRootSceneNode()->addChild(playerNode);
		playerNode->attachObject(playerEnt);

		Ogre::Vector3 pos = getPosition3();
		setPosition(Ogre::Vector3(pos.x, pos.y, pos.z + 13));
		velocity = Ogre::Vector3(0, 0, 0);
	};
	void playerUpdate(std::set<OIS::KeyCode> keyPresses);
	Ogre::Entity* playerEnt;
	Ogre::SceneNode* playerNode;


	void setVelocity(Ogre::Vector3 vel)
	{
		velocity = vel;
	}
	void setPosition(Ogre::Vector3 position)
	{
		playerNode->setPosition(position);
	}
	void setPosition(Ogre::Vector2 position)
	{
		playerNode->setPosition(Ogre::Vector3(position.x, position.y, getPosition3().z));
	}
	Ogre::Vector3 getPosition3()
	{
		return playerNode->getPosition();
	}
	Ogre::Vector2 getPosition()
	{
		Ogre::Vector3 v = playerNode->getPosition();
		return Ogre::Vector2(v.x, v.y);
	}

private:
	Ogre::Vector3 velocity;


};

#endif // #ifndef __Game_h_