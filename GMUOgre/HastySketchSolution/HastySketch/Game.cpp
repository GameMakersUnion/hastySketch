#include "stdafx.h"

/*
-----------------------------------------------------------------------------
Filename:    Game.cpp
-----------------------------------------------------------------------------
Main Game Code source
-----------------------------------------------------------------------------
*/
#include "Game.h"
using namespace Ogre;
//-------------------------------------------------------------------------------------
Game::Game(void)
{
}
//-------------------------------------------------------------------------------------
Game::~Game(void)
{
}

//-------------------------------------------------------------------------------------
void Game::createScene(void)
{
    // create your scene here :)

	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	// Create a Light and set its position
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setType(Ogre::Light::LightTypes::LT_POINT);
	light->setPosition(20.0f, 80.0f, 50.0f);


	//ACTUAL SCENEBUILDING
	Entity* desk = mSceneMgr->createEntity("myDesk", "Box006.mesh");
	SceneNode* deskNode = mSceneMgr->createSceneNode("myDesk1");
	mSceneMgr->getRootSceneNode()->addChild(deskNode);
	deskNode->attachObject(desk);

	player = Player(mSceneMgr);
	mCameraMan->setTarget(player.playerNode);
	mCameraMan->setYawPitchDist((Radian)0, (Radian)0, 50);

	//---------------MINI SCREEN INITIALIZATION

	TexturePtr rtt_texture = TextureManager::getSingleton().createManual("RttTex",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, 640, 480, 0,
		PF_R8G8B8, TU_RENDERTARGET);

	RenderTexture * renderTexture = rtt_texture->getBuffer()->getRenderTarget();
	renderTexture->addViewport(mCamera);
	renderTexture->getViewport(0)->setClearEveryFrame(true);
	renderTexture->getViewport(0)->setBackgroundColour(ColourValue::White);
	renderTexture->getViewport(0)->setOverlaysEnabled(false);

	//Rectangle2D * surface = new Rectangle2D(true);
	//surface->setCorners(0.5f, -0.5f, 1.0f, -1.0f);
	//surface->setBoundingBox(AxisAlignedBox(-100000.0f * Vector3::UNIT_SCALE, 100000.0f * Vector3::UNIT_SCALE));

	MaterialPtr renderMaterial =
		MaterialManager::getSingleton().create("RttMat",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	renderMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	renderMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("RttTex");

	int mapSize = 16;
	Ogre::ManualObject *man = mSceneMgr->createManualObject("Paper");
	man->begin("RttMat", Ogre::RenderOperation::OT_TRIANGLE_LIST);

	man->position(-19, 9,  13);
	man->textureCoord(0, 0);
	man->position(31, 9,   13);
	man->textureCoord(1, 0);
	man->position(31, 42, 13);
	man->textureCoord(1, 1);

	man->position(-19, 42, 13);
	man->textureCoord(0, 1);

	
	man->quad(0, 1, 2, 3);
	man->end();
	//mSceneMgr->getRootSceneNode()->attachObject(man);


	SceneNode * miniSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MiniSceneNode");
	miniSceneNode->attachObject(man);
	

	//surface->setMaterial("RttMat");


	//------------END MINI-SCREEN
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

	player.playerUpdate(keyList);

	Camera* cam = mSceneMgr->getCamera("PlayerCam");
	Ogre::Vector3 pos3 = player.getPosition3();

	cam->setPosition(Vector3(pos3.x, pos3.y, cam->getPosition().z));

	//player.setPosition(Vector3(pos3.x, pos3.y, pos3.z + 0.01)); //ascend
	//player.playerNode->rotate(Vector3(0, 0, 1), (Radian)10, Ogre::Node::TS_LOCAL);

	return ret;
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
//#else
    int main(int argc, char *argv[])
//#endif
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
