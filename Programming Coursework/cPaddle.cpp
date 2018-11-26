/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cPaddle.h"

/*
=================================================================
Initialise the sprite variables
=================================================================
*/

void cPaddle::initialise()
{
	setBoundingRect();
}

/*
=================================================================
Paddle Movement
=================================================================
*/

void cPaddle::update(double deltaTime)
{
	SDL_Rect currentPos = this->getSpritePos();
		
	int moveSpeed = 12;

	if ((isGoingRight) && (currentPos.x < 650)) {
		currentPos.x += moveSpeed;
	}
	else
	{
		isGoingRight = false;
	}

	if ((isGoingLeft) && (currentPos.x > 0)) {
		currentPos.x -= moveSpeed;
	}
	else
	{
		isGoingLeft = false;
	}

	this->setSpritePos(currentPos);
	setBoundingRect();
}
