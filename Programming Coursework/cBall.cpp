#include "cBall.h"

/*
=================================================================
Initialise the sprite variables
=================================================================
*/

void cBall::initialise()
{
	xVelocity = -1;
	yVelocity = 1;
	isMoving = false;
	outOfBounds = false;
	cout << isMoving;
	setBoundingRect();
	radius = 10;
}

void cBall::update(double deltaTime)
{
	SDL_Point currentPos = { this->getSpritePos().x, this->getSpritePos().y };

	if (isMoving) 
	{
		// this relies on the ball being 20x20 pixels - if the ball size changes, these values are changed
		// if the ball 
		if (currentPos.x < 730) {
			currentPos.x += (xVelocity);
			currentPos.y -= (yVelocity);
		}
		else
		{
			xVelocity = -1;
		}

		if (currentPos.x > 0) {
			currentPos.x += (xVelocity);
			currentPos.y -= (yVelocity);
		}
		else
		{
			xVelocity = 1;
		}

		if (currentPos.y < 480) {
			currentPos.x += (xVelocity);
			currentPos.y -= (yVelocity);
		}
		else
		{
			outOfBounds = true;
		}

		if (currentPos.y > 0) {
			currentPos.x += (xVelocity);
			currentPos.y -= (yVelocity);
		}
		else
		{
			yVelocity = -1;
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
	setBoundingRect();
	
}