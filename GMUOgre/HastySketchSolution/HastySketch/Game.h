/*
-----------------------------------------------------------------------------
Filename:    Game.h
-----------------------------------------------------------------------------
Main Game Code
*/
#ifndef __Game_h_
#define __Game_h_

#include "BaseApplication.h"

class Game : public BaseApplication
{
public:
	Game(void);
	virtual ~Game(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __Game_h_
