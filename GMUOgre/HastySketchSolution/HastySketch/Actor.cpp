#include "stdafx.h"

#include "Actor.h"



void Actor::Update(std::set<OIS::KeyCode> keyPresses)
{
	//if (*actorNode == null)
	actorNode->rotate(angularVelocityVect, angularVelocityAngle);
}
int Actor::CloneNum = 0;
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

	//source->actorNode->getParentSceneNode()->addChild(node);
	Ogre::SceneNode *sn = source->actorNode->getParentSceneNode();
	sn->addChild(node);
	//std::cout << "STUFF: " << sn->numChildren() << std::endl;
	node->attachObject(ent);
	//Actor * a = (Actor*)malloc(sizeof(Actor));
	//*a = Actor(ent, node);

	//std::unique_ptr<Actor> a(new Actor(ent, node));

	Actor * a = new Actor(ent, node);
	//delete(a);

	std::cout << ent->getName() << " =?=" << a->GetName() << std::endl;

	//return &Actor(ent, node);
	return a;
}
