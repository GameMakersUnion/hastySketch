#include "stdafx.h"
#include "boost\foreach.hpp"

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


void Game::chooseSceneManager(void)
{
	BaseApplication::chooseSceneManager();

	// Get the SceneManager, in this case a generic one
	currentPage = mRoot->createSceneManager(Ogre::ST_GENERIC);
}

//-------------------------------------------------------------------------------------

void Game::createCamera(void)
{
	BaseApplication::createCamera();
	
	currentPageCamera = currentPage->createCamera("CurrentPageCam");
	// Position it at 500 in Z direction
	currentPageCamera->setPosition(Ogre::Vector3(0, 0, 58));
	// Look back along -Z
	currentPageCamera->lookAt(Ogre::Vector3(0, 0, 0));
	currentPageCamera->setNearClipDistance(.001);

}
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
	mCameraMan->setTarget(player.actorNode);
	mCameraMan->setYawPitchDist((Radian)0, (Radian)0, 50);
	

	// Create the camera
	Ogre::Camera *mCamera2 = mSceneMgr->createCamera("PaperCam");

	// Position it at 500 in Z direction
	mCamera2->setPosition(Ogre::Vector3(0, 0, 15));
	// Look back along -Z
	mCamera2->lookAt(Ogre::Vector3(0, 0, 300));
	mCamera2->setNearClipDistance(.001);







	//---------------Page Scenes INITIALIZATION

	DotSceneLoader loader;
	loader.parseDotScene("TestScene.scene", "General", currentPage);

	//---------------end Page scenes








	//---------------MINI SCREEN INITIALIZATION

	TexturePtr rtt_texture = TextureManager::getSingleton().createManual("RttTex",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, 1920, 1080, 0,
		PF_R8G8B8, TU_RENDERTARGET);

	RenderTexture * renderTexture = rtt_texture->getBuffer()->getRenderTarget();
	renderTexture->addViewport(currentPageCamera);
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
	
	Ogre::Vector3 tl(-20, -15, 13);
	Ogre::Vector3 br(20, 15, 13);

	man->position(tl.x, tl.y,  tl.z);
	man->textureCoord(0, 1);
	man->position(br.x, tl.y, tl.z);
	man->textureCoord(1, 1);
	man->position(br.x, br.y, tl.z);
	man->textureCoord(1, 0);
	man->position(tl.x, br.y, tl.z);
	man->textureCoord(0, 0);

	//man->position(-5, -5, 13);
	//man->textureCoord(0, 1);
	//man->position(5, -5, 13);
	//man->textureCoord(1, 1);
	//man->position(5, 5, 13);
	//man->textureCoord(1, 0);
	//man->position(-5, 5, 13);
	//man->textureCoord(0, 0);
	
	man->quad(0, 1, 2, 3);
	man->end();
	//mSceneMgr->getRootSceneNode()->attachObject(man);


	SceneNode * miniSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MiniSceneNode");
	miniSceneNode->attachObject(man);
	//miniSceneNode->translate(0, -10, 20);
	//miniSceneNode->scale(2, 2, 1);

	//surface->setMaterial("RttMat");
	

	//------------END MINI-SCREEN

	Entity* nin = mSceneMgr->createEntity("myNinja", "ninja.mesh");
	SceneNode* ninjaNode = mSceneMgr->createSceneNode("myNinjaNode");
	ninjaNode->setPosition(-100, -100, 250);
	ninjaNode->setScale(.5, .5, .5);
	ninjaNode->setOrientation(.5, 0, 1, 0);
	ninjaNode->attachObject(nin);
	mSceneMgr->getRootSceneNode()->addChild(ninjaNode);

	Actor* ninja = new Actor(nin, ninjaNode);
	Real xRot = 0.5; Real xRotChange = 0.5;
	
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
		
			Actor* ninja2 = Actor::cloneActor(mSceneMgr, ninja, Vector3(i * 50, j * 50, 0));
			ninja2->actorNode->setOrientation(.1 + xRot, 0, 1, 0);
			//ActorSet.insert(ninja2);
			
			//Actor act = *ninja2;
			//ActorSet.insert(act);
			ActorList.emplace_back(*ninja2);

			xRot += xRotChange;
		}
	}


	//ActorSet.emplace((Actor)*ninja);
	

	//Actor* ninja2 = Actor::cloneActor(mSceneMgr, ninja, Vector3(10, 0, 0));

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

	player.Update(keyList);

	Camera* cam = mSceneMgr->getCamera("PlayerCam");
	Ogre::Vector3 pos3 = player.getPosition3();

	cam->setPosition(Vector3(pos3.x, pos3.y, cam->getPosition().z));
	//Camera* cam2 = mSceneMgr->getCamera("PaperCam");
	//cam2->rotate(Vector3(0, 1, 0), (Radian)0.001);

	//player.setPosition(Vector3(pos3.x, pos3.y, pos3.z + 0.01)); //ascend
	//player.actorNode->rotate(Vector3(0, 0, 1), (Radian)10, Ogre::Node::TS_LOCAL);
	//mSceneMgr->getSceneNode("myNinjaNode")->rotate(Ogre::Vector3(0,1,0), (Radian) .1);

	//mSceneMgr->getSceneNode("MiniSceneNode")->rotate(Ogre::Vector3(0, 1, 0), (Radian) .01);


	//int c = 0;
	//for (std::vector<Actor>::iterator it = ActorList.begin(); it != ActorList.end(); ++it)
	//{
	//	//it->Update(keyList);
	//	Actor a = *it;
	//	a.Update(keyList);
	//	c++;
	//}
	//std::cout << c << std::endl;

	//for (auto a : ActorSet)
	//{
	//	a->Update(keyList);
	//}

	BOOST_FOREACH(Actor a, ActorList)
	{
		a.Update(keyList);
	}
	 
	//player.actorNode->translate(0, 0, 0.1);

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
