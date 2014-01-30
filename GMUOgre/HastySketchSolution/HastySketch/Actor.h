#ifndef __Actor_h_
#define __Actor_h_

#include "stdafx.h"
class Actor
{
public:
	Actor(){
		angularVelocityVect = Ogre::Vector3(0, 0, 0);
		angularVelocityAngle = 0;
	}
	Actor(Ogre::SceneManager * mSceneMgr) //throw sinbad in the fire
	{
		actorEnt = mSceneMgr->createEntity("actorEntity", "Sinbad.mesh");
		//mSceneMgr->getRootSceneNode()->attachObject(ent);
		actorNode = mSceneMgr->createSceneNode("actorNode");
		mSceneMgr->getRootSceneNode()->addChild(actorNode);
		actorNode->attachObject(actorEnt);

		Ogre::Vector3 pos = getPosition3();
		setPosition(Ogre::Vector3(pos.x, pos.y, pos.z + 13));
		velocity = Ogre::Vector3(0, 0, 0);
		angularVelocityVect = Ogre::Vector3(0, 0, 0);
		angularVelocityAngle = 0;
	};
	Actor(Ogre::Entity *ent, Ogre::SceneNode *node, Ogre::Vector3 position = Ogre::Vector3(-100000, 0, 0)) //reset position's default parameter to global variable detailing origin
	{
		actorEnt = ent;
		actorNode = node;
		velocity = Ogre::Vector3(0, 0, 0);
		if (position.x != -100000)
		{
			setPosition(position);
		}
		angularVelocityVect = Ogre::Vector3(5, 0, 0);
		angularVelocityAngle = 66;
	};


	static Actor * cloneActor(Ogre::SceneManager * sceneManager, Actor * source, Ogre::Vector3 changeInPosition);
	static int CloneNum;

	virtual void Update(std::set<OIS::KeyCode> keyPresses);
	Ogre::Entity* actorEnt;
	Ogre::SceneNode* actorNode;
	Ogre::Vector3 velocity;
	Ogre::Vector3 angularVelocityVect;
	Ogre::Radian angularVelocityAngle;


	virtual void setVelocity(Ogre::Vector3 vel)
	{
		velocity = vel;
	}
	virtual void setPosition(Ogre::Vector3 position)
	{
		actorNode->setPosition(position);
	}
	virtual void setPosition(Ogre::Vector2 position)
	{
		actorNode->setPosition(Ogre::Vector3(position.x, position.y, getPosition3().z));
	}
	virtual Ogre::Vector3 getPosition3()
	{
		return actorNode->getPosition();
	}
	virtual Ogre::Vector2 getPosition()
	{
		Ogre::Vector3 v = actorNode->getPosition();
		return Ogre::Vector2(v.x, v.y);
	}

//private:
	


};



#endif // #ifndef __Game_h_