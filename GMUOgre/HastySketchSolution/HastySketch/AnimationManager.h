#ifndef ANIMATION2D_H
#define ANIMATION2D_H

using namespace Ogre;

class Animation2D
{

public:
	std::vector<Ogre::MaterialPtr> materials;
	std::string name;

	void setAnimations(Ogre::StringVectorPtr filenames)
	{
		for (int i = 0; i < filenames->size(); i++)
		{
			MaterialPtr mPtr = Ogre::MaterialManager::getSingleton().create(filenames->at(i), "General");
			mPtr->setSceneBlending(SBT_TRANSPARENT_ALPHA);

			TextureUnitState *state = mPtr->getTechnique(0)->getPass(0)->createTextureUnitState("DynamicTexture");
			state->setAlphaOperation(LBX_MODULATE, LBS_TEXTURE, LBS_CURRENT);

			Ogre::TexturePtr mTex = Ogre::TextureManager::getSingleton().load(filenames->at(i), "General");
			state->setTexture(mTex);

			mPtr->setDepthCheckEnabled(false);

			materials.push_back(mPtr);
		}
	}

	Animation2D()
	{
	}
	~Animation2D()
	{
	}

};

class AnimationManager
{
public:

	std::string actorName;
	std::vector<Animation2D> animations;

	void addAnimation(Animation2D animation2D);

	AnimationManager();
	AnimationManager(std::string actorName);
	~AnimationManager();
};

#endif
