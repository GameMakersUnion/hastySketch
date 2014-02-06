#include <iostream>
#include "AnimationManager.h"

using namespace Ogre;

class ActorManager
{
public:
	ActorManager();
	~ActorManager();

	StringVectorPtr actorNameList;

	//void loadFolder();
	 std::map<std::string, AnimationManager > frameMap;
	void importActors();

	//std::vector<MaterialPtr> materials;
};