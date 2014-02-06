#include "StdAfx.h"
#include "AnimationManager.h"

AnimationManager::AnimationManager(std::string actorName0) : actorName(actorName0)
{
}

AnimationManager::AnimationManager()
{
}
AnimationManager::~AnimationManager()
{
}

void AnimationManager::addAnimation(Animation2D animation2D)
{
	animations.push_back(animation2D);
}
