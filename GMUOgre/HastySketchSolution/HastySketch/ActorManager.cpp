#include "stdafx.h"
#include "ActorManager.h"

void ActorManager::importActors()
{
	ResourceGroupManager::ResourceLocation* baseDir = ResourceGroupManager::getSingletonPtr()->getResourceLocationList("Animations").front();
	std::string baseDirName = baseDir->archive->getName();

	actorNameList = baseDir->archive->list(false, true);

	for (int i = 0; i < actorNameList->size(); i++)
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(baseDirName + "/" + actorNameList->at(i), "FileSystem", "Actors");
	}

	ResourceGroupManager::LocationList actorDirList = ResourceGroupManager::getSingletonPtr()->getResourceLocationList("Actors");
	
	int counter = 0;

	for (auto it = actorDirList.begin(); it != actorDirList.end(); it++)
	{
		std::string actorName = actorNameList->at(counter++);
		
		StringVectorPtr animNameList = (*it)->archive->list(false, true);
		for (int j = 0; j < animNameList->size(); j++)
		{
			//std::unique_ptr<Animation2D> animation2D(new Animation2D());

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(baseDirName + "/" + actorName + "/" + animNameList->at(j), "FileSystem", actorName);

			// We added animation directories to resource groups named by their actors
			// We want the files in the animation directories
			//AnimationManager animationManager;


			//frameMap[actorName].push_back(animNameList->at(j));
			//system("pause");
			
		}
		//std::cout << actorName << "--------\n";

		AnimationManager animationManager(actorName);

		int counter2 = 0;

		// Now for each actor, go through each animation directory and get filenames
		ResourceGroupManager::LocationList animationDirList = ResourceGroupManager::getSingletonPtr()->getResourceLocationList(actorName);
		for (auto it = animationDirList.begin(); it != animationDirList.end(); it++)
		{
			//std::cout << frameMap[actorName].at(counter2++) <<"*****" << std::endl;

			StringVectorPtr filenames = (*it)->archive->list(true, false);

			Animation2D animation2D;
			animation2D.setAnimations(filenames);

			animationManager.addAnimation(animation2D);

			//for (int k = 0; k < filenames->size();k++)
				//std::cout << filenames->at(k) << "\n";

		}

		frameMap[actorName] = animationManager;
	}
	
	//for (auto it = frameMap.begin(); it != frameMap.end(); it++)
	//{
	//	std::string name = it->first;
	//	AnimationManager animationManager = it->second;

	//	std::cout << animationManager.actorName << "---------" << std::endl;

	//	//std::cout << animationManager.animations.size();
	//	for (int i = 0; i < animationManager.animations.size(); i++)
	//	{
	//		Animation2D anim = animationManager.animations.at(i);
	//		std::cout << animationManager.animations.at(i).materials.size() << "\n";

	//		for (int j = 0; j < animationManager.animations.at(i).materials.size(); j++)
	//		{
	//			std::cout << animationManager.animations.at(i).materials.at(j)->getName() << "\n";
	//		}
	//	}

	//
	//}
}

ActorManager::~ActorManager()
{

}

ActorManager::ActorManager()
{

}