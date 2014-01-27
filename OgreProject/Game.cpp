/*
-----------------------------------------------------------------------------
Filename:    Game.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "Game.h"
#include <iostream>
#include "Player.h"
using namespace Ogre;

//using namespace std;
//-------------------------------------------------------------------------------------
Game::Game(void) //entry
{
	std::cout << "1" << std::endl;
	Game::keyList;// = new list<OIS::KeyCode>;
}
//-------------------------------------------------------------------------------------
Game::~Game(void) //exit
{
	std::cout << "2" << std::endl;
}

//-------------------------------------------------------------------------------------
void Game::createScene(void)
{
    // create your scene here :)

	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(.5f, .5f, .5f));

	// Create an Entity
	//Ogre::Entity* ent = mSceneMgr->createEntity("MyEntity", "Sinbad.mesh");
	//// Create a SceneNode and attach the Entity to it
	//Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
	//headNode->attachObject(ogreHead); 
	Entity* desk = mSceneMgr->createEntity("myDesk", "Box006.mesh");
	SceneNode* deskNode = mSceneMgr->createSceneNode("myDesk1");
	mSceneMgr->getRootSceneNode()->addChild(deskNode);
	deskNode->attachObject(desk);



	Entity* ent = mSceneMgr->createEntity("MyEntity", "Sinbad.mesh");
	//mSceneMgr->getRootSceneNode()->attachObject(ent);
	SceneNode* node = mSceneMgr->createSceneNode("Node1");
	mSceneMgr->getRootSceneNode()->addChild(node);
	node->attachObject(ent);
	Vector3 pos = node->getPosition();
	node->setPosition(Vector3(pos.x, pos.y, pos.z + 13));


	mCameraMan->setTarget(node);
	mCameraMan->setYawPitchDist((Radian)0, (Radian)0, 50);
	
	//mCameraMan->setYawPitchDist()

	TexturePtr rtt_texture = TextureManager::getSingleton().createManual("RttTex",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, 640, 480, 0,
		PF_R8G8B8, TU_RENDERTARGET);
	
	RenderTexture * renderTexture = rtt_texture->getBuffer()->getRenderTarget();
	renderTexture->addViewport(mCamera);
	renderTexture->getViewport(0)->setClearEveryFrame(true);
	renderTexture->getViewport(0)->setBackgroundColour(ColourValue::Blue);
	renderTexture->getViewport(0)->setOverlaysEnabled(false);
	//RenderTarget * renderT2;
	// Create a Light and set its position

	Rectangle2D * surface = new Rectangle2D(true);
	surface->setCorners(0.5f, -0.5f, 1.0f, -1.0f);
	surface->setBoundingBox(AxisAlignedBox(-100000.0f * Vector3::UNIT_SCALE, 100000.0f * Vector3::UNIT_SCALE));

	SceneNode * miniSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MiniSceneNode");
	miniSceneNode->attachObject(surface);
	MaterialPtr renderMaterial =
		MaterialManager::getSingleton().create("RttMat",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	renderMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	renderMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("RttTex");

	surface->setMaterial("RttMat");

	Light* light = mSceneMgr->createLight("MainLight");
	light->setType(Light::LightTypes::LT_POINT);
	
	light->setPosition(20.0f, 80.0f, 50.0f);

	std::cout << "3" << std::endl;
}
bool Game::keyPressed(const OIS::KeyEvent &arg)
{
	keyList.insert(arg.key);
	return BaseApplication::keyPressed(arg);
}
bool Game::keyReleased(const OIS::KeyEvent &arg)
{
	keyList.erase(arg.key);
	return BaseApplication::keyReleased(arg);
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	bool ret = BaseApplication::frameRenderingQueued(evt);

	SceneNode* sn = mSceneMgr->getSceneNode("Node1");
	Vector2 pos = Vector2(sn->getPosition().x, sn->getPosition().y);
	
	

	Player::playerUpdate(pos, keyList);

	sn->setPosition(Vector3(pos.x, pos.y, sn->getPosition().z));

	

	Camera* cam = mSceneMgr->getCamera("PlayerCam");
	cam->setPosition(Vector3(pos.x, pos.y, cam->getPosition().z));

	//Vector3 pos3 = sn->getPosition();
	//sn->setPosition(pos3.x, pos3.y + 0.01, pos3.z); //ascend
	
	return ret;
}

//void Game::go()
//{
//	node->setPosition(Vector3(node->getPosition().x + 1, node->getPosition().y, node->getPosition().z));
//}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
		Game app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
