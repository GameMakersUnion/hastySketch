/*
-----------------------------------------------------------------------------
Filename:    Game.h
-----------------------------------------------------------------------------
Main Game Code
*/
#ifndef __Game_h_
#define __Game_h_

#include "BaseApplication.h"
#include "Actor.h"
#include "Player.h"

#include "DotSceneLoader.h"

class Game : public BaseApplication
{
public:
	Ogre::SceneManager* currentPage;
	Ogre::SceneManager* nextPage;
	Ogre::SceneManager* prevPage;
	Ogre::Camera* currentPageCamera;

	Game(void);
	virtual ~Game(void);
	std::set<OIS::KeyCode> keyList;
	Player player;
	std::set<Actor*> ActorSet;
	std::vector<Actor> ActorList;

protected:
	virtual void createCamera(void);
	virtual void chooseSceneManager(void);
	virtual void createScene(void);
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};


#endif // #ifndef __Game_h_
