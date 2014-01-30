#include "stdafx.h"

#include "Actor.h"



void Actor::Update(std::set<OIS::KeyCode> keyPresses)
{
	//if (*actorNode == null)
	actorNode->rotate(angularVelocityVect, angularVelocityAngle);

}

Actor * Actor::cloneActor(Ogre::SceneManager * sceneManager, Actor * source, Ogre::Vector3 changeInPosition)
{
	Ogre::String number = Ogre::StringConverter::toString(CloneNum++);
	Ogre::String newName = "clone" + number;
	std::cout << newName;
	Ogre::Entity * ent = source->actorEnt->clone(newName);
	Ogre::SceneNode *node = sceneManager->createSceneNode(newName);
	node->setPosition(source->actorNode->getPosition() + changeInPosition);
	node->setScale(source->actorNode->getScale());
	node->setOrientation(source->actorNode->getOrientation());

	source->actorNode->getParentSceneNode()->addChild(node);
	node->attachObject(ent);
	return &Actor(ent, node);
}
int Actor::CloneNum = 0;