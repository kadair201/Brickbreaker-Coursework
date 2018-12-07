#ifndef _CBALL_H
#define _CBALL_H
#include "cSprite.h"

class cBall : public cSprite
{
public:
	int xVelocity;
	int yVelocity;
	bool isMoving;
	bool isGoingLeft;
	bool isGoingRight;
	bool outOfBounds;
	int radius;

	void initialise();		// Default render function
	void update(double deltaTime);		// ball update method
};

#endif
