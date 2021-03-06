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
	//----------------------Jabir

	

	
	//----------------------endJabir
	count = 0;
	
}
//-------------------------------------------------------------------------------------
Game::~Game(void)
{
}
//
float Game::fall_global = 0.01;


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
	currentPageCamera->setPosition(Ogre::Vector3(0, 0, -58));
	// Look back along -Z
	currentPageCamera->lookAt(Ogre::Vector3(0, 0, 0));
	currentPageCamera->setNearClipDistance(.001);

	//currentPageCamera->setFOVy((Radian)30);

}
void Game::createScene(void)
{
    // create your scene here :)
	
	actorManager.importActors();

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

	//player = Player(mSceneMgr);
	//mCameraMan->setTarget(player.actorNode);
	//mCameraMan->setYawPitchDist((Radian)0, (Radian)0, 50);
	

	// Create the camera
	Ogre::Camera *mCamera2 = mSceneMgr->createCamera("PaperCam");

	// Position it at 500 in Z direction
	mCamera2->setPosition(Ogre::Vector3(0, 0, 15));
	// Look back along -Z
	mCamera2->lookAt(Ogre::Vector3(0, 0, 300));
	mCamera2->setNearClipDistance(.001);







	//---------------Page Scenes INITIALIZATION
	
	// Make a bunch of materials
	MaterialPtr mPtr = Ogre::MaterialManager::getSingleton().create("StickmanMaterial2", "General");
	mPtr->setSceneBlending(SBT_TRANSPARENT_ALPHA);

	TextureUnitState *state = mPtr->getTechnique(0)->getPass(0)->createTextureUnitState("DynamicTexture");
	state->setAlphaOperation(LBX_MODULATE, LBS_TEXTURE, LBS_CURRENT);

	Ogre::TexturePtr mTex = Ogre::TextureManager::getSingleton().load("stickman2.png", "General");
	state->setTexture(mTex);


	DotSceneLoader loader;
	loader.parseDotScene("TestScene2.scene", "General", currentPage);
	Entity * playa = currentPage->getEntity("Player");
	playa->setMaterial(mPtr);
	
	

	Entity * top = currentPage->getEntity("topplane");
	Entity * bottom = currentPage->getEntity("bottomplane");
	Entity * left = currentPage->getEntity("leftplane");		//these are not errors, I swear.
	Entity * right = currentPage->getEntity("rightplane");

	Real xmin = left->getParentSceneNode()->getPosition().x;
	Real xmax = right->getParentSceneNode()->getPosition().x;
	Real ymin = top->getParentSceneNode()->getPosition().y;
	Real ymax = bottom->getParentSceneNode()->getPosition().y;
	Real zz = 0;
	//

	std::cout << xmin << " " << xmax << " " << ymin << " " << ymax << std::endl;

	sceneRect = Rect(xmin, ymin, xmax, ymax);
	



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
	
	Ogre::Vector3 topleft(-20, -15, 13);
	Ogre::Vector3 bottomright(20, 15, 13);

	viewportRect = Rect(topleft.x, topleft.y, bottomright.x, bottomright.y);

	man->position(topleft.x, topleft.y,  topleft.z);
	man->textureCoord(0, 1);
	man->position(bottomright.x, topleft.y, topleft.z);
	man->textureCoord(1, 1);
	man->position(bottomright.x, bottomright.y, topleft.z);
	man->textureCoord(1, 0);
	man->position(topleft.x, bottomright.y, topleft.z);
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

	//Entity* actorEnt = mSceneMgr->createEntity("actorEntity", "Sinbad.mesh");
	//playa->getParentNode()->removeChild(playa->getName());
	player = Player(mSceneMgr, playa, playa->getParentSceneNode(), &sceneRect);

	playerWorldCoordNode = mSceneMgr->createSceneNode();
	mSceneMgr->getRootSceneNode()->addChild(playerWorldCoordNode);
	Entity* sinbad = mSceneMgr->createEntity("sinbad", "Sinbad.mesh");
	playerWorldCoordNode->attachObject(sinbad);


	//mCameraMan->setTarget(player.actorNode);
	//mCameraMan->setTarget(playerWorldCoordNode);
	//mCameraMan->setYawPitchDist((Radian)0, (Radian)0, 50);


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

void Game::ConvertSceneToWorld()
{
	//std::cout << player.getPosition().x << " " << player.getPosition().y << std::endl;
	Real scenex = player.getPosition().x; Real sceney = player.getPosition().y;
	Real ratiox = (Real)abs(scenex - sceneRect.left) / (Real)abs(sceneRect.left - sceneRect.right);
	Real ratioy = (Real)abs(sceney - sceneRect.bottom) / (Real)abs(sceneRect.bottom - sceneRect.top);

	Real worldx = (Real)viewportRect.left + (Real)ratiox * (Real)abs(viewportRect.left - viewportRect.right);
	Real worldy = (Real)viewportRect.top + (Real)ratioy * (Real)abs(viewportRect.top - viewportRect.bottom);

	worldx = -worldx;
	worldy = worldy;
	Vector3 worldpos = Vector3(worldx, worldy, 0);
	playerWorldCoordNode->setPosition(worldpos);

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
bool Game::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	switch (id)
	{
	case OIS::MB_Left:

		break;
	case OIS::MB_Right:

		break;
	case OIS::MB_Middle:

		break;
	case OIS::KC_SCROLL:
		
		break;
	default:
		break;
	}
	return BaseApplication::mousePressed(arg, id);
}
bool Game::mouseMoved(const OIS::MouseEvent &arg){
	if (arg.state.buttonDown(OIS::MB_Right))
	{

	}


	int newscroll = arg.state.Z.rel;
	if (newscroll > 0)
	{
		Vector3 pos = mSceneMgr->getCamera("PlayerCam")->getPosition();
		mSceneMgr->getCamera("PlayerCam")->setPosition(pos.x, pos.y, pos.z - 10);
	}
	else if (newscroll < 0)
	{
		Vector3 pos = mSceneMgr->getCamera("PlayerCam")->getPosition();
		mSceneMgr->getCamera("PlayerCam")->setPosition(pos.x, pos.y, pos.z + 10);
	}

	//std::cout << arg.state.X.rel << " : " << arg.state.Y.rel << std::endl;

	return true;
}


bool Game::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

	Ogre::Timer timer;
	timer.reset();

	bool ret = BaseApplication::frameRenderingQueued(evt);
	player.Update(keyList);

	Camera* cam = mSceneMgr->getCamera("PlayerCam");
	Ogre::Vector3 pos3 = player.getPosition3();
	//cam->setPosition(Vector3(pos3.x, pos3.y, cam->getPosition().z));

	//Camera* cam2 = mSceneMgr->getCamera("PaperCam");
	//cam2->rotate(Vector3(0, 1, 0), (Radian)0.001);

	UpdateActors();
	
	ConvertSceneToWorld();
	currentPageCamera->lookAt(-player.getPosition3().x / 2, -player.getPosition3().y / 2, player.getPosition3().z);
	currentPageCamera->setPosition(player.getPosition3().x * 2, player.getPosition3().y * 2, currentPageCamera->getPosition().z);
	mCamera->setPosition(playerWorldCoordNode->getPosition().x, playerWorldCoordNode->getPosition().y, mCamera->getPosition().z);


	//if (timer.getMilliseconds() < 1000.0 / 30.0)
	//{
		//Sleep((1000.0 / 60.0) - timer.getMilliseconds());
	//}
	//else
	//{
	//Sleep(60.0);
		
		if (count >= actorManager.frameMap["enemy"].animations.at(1).materials.size())
			count = 0;

		Ogre::MaterialPtr mPtr = actorManager.frameMap["enemy"].animations.at(1).materials.at(count++);
		currentPage->getEntity("Player")->setMaterial(mPtr);

		
	//}



	return ret;

}
void Game::UpdateActors()
{

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
