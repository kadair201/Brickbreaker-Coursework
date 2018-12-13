#ifndef _CBALL_H
#define _CBALL_H
#include "cSprite.h"

class cBall : public cSprite
{
public:
	// variables for movement
	int xVelocity;
	int yVelocity;
	bool isMoving;
	bool isGoingLeft;
	bool isGoingRight;
	bool outOfBounds;
	// declaring methods to use
	void initialise();		
	void update(double deltaTime);	
};

#endif
