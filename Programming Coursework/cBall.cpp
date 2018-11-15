#include "cBall.h"

/*
=================================================================
Initialise the sprite variables
=================================================================
*/

void cBall::initialise()
{
	xVelocity = 2;
	yVelocity = 2;
	isMoving = false;
	cout << isMoving;
}

void cBall::update(double deltaTime)
{
	SDL_Rect currentPos = this->getSpritePos();

	if (isMoving) 
	{
		if (currentPos.x < 730) {
			currentPos.x += (xVelocity);
			currentPos.y -= (yVelocity);
		}
		else
		{
			xVelocity = -2;
		}

		if (currentPos.x > 0) {
			currentPos.x += (xVelocity);
			currentPos.y -= (yVelocity);
		}
		else
		{
			xVelocity = 2;
		}

		if (currentPos.y < 480) {
			currentPos.x += (xVelocity);
			currentPos.y -= (yVelocity);
		}
		else
		{
			yVelocity = 2;
		}

		if (currentPos.y > 0) {
			currentPos.x += (xVelocity);
			currentPos.y -= (yVelocity);
		}
		else
		{
			yVelocity = -2;
		}
	}

	if (!(isMoving)) {

		int moveSpeed = 12;

		if ((isGoingRight) && (currentPos.x < 690)) {
			currentPos.x += moveSpeed;
		}
		else
		{
			isGoingRight = false;
		}

		if ((isGoingLeft) && (currentPos.x > 40)) {
			currentPos.x -= moveSpeed;
		}
		else
		{
			isGoingLeft = false;
		}
	}
	
	this->setSpritePos(currentPos);
}