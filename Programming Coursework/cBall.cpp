#include "cBall.h"

/*
=================================================================
Initialise the sprite variables
=================================================================
*/

void cBall::initialise()
{
	// set the velocities of the ball
	xVelocity = -1;
	yVelocity = 1;
	// reset isMoving so the instruction prompts will show
	isMoving = false;
	// reset outOfBounds so the lose condition isn't immediately triggered
	outOfBounds = false;
	// set the bounding rectangle for the ball
	setBoundingRect();
}

void cBall::update(double deltaTime)
{
	// get the current position of the sprite
	SDL_Point currentPos = { this->getSpritePos().x, this->getSpritePos().y };

	// if the ball is moving
	if (isMoving) 
	{
		// if not in contact with the right wall
		if (currentPos.x < 730) 
		{
			// increase both x and y velocities
			currentPos.x += (xVelocity);
			currentPos.y -= (yVelocity);
		}
		else // if the ball hits the right wall
		{
			// reverse the x velocity
			xVelocity = -1;
		}

		// if the ball isn't in contact with the left wall
		if (currentPos.x > 0) 
		{
			currentPos.x += (xVelocity);
			currentPos.y -= (yVelocity);
		}
		else // if the ball hits the left wall
		{
			// reverse the x velocity
			xVelocity = 1;
		}

		// if the ball is not in contact with the bottom boundary
		if (currentPos.y < 480) 
		{
			currentPos.x += (xVelocity);
			currentPos.y -= (yVelocity);
		}
		else // if the ball reaches the bottom boundary
		{
			// set out of bounds to true, which triggers the lose condition
			outOfBounds = true;
		}

		// if the ball hits the top boundary
		if (currentPos.y > 0) 
		{
			currentPos.x += (xVelocity);
			currentPos.y -= (yVelocity);
		}
		else 
		{
			// reverse the y velocity
			yVelocity = -1;
		}
	}

	// before the launch from the paddle
	if (!(isMoving)) 
	{
		// set move speed to match the paddle move speed
		int moveSpeed = 12;

		// move with the paddle 
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
	
	// update the sprite position and the bounding rectangle
	this->setSpritePos(currentPos);
	setBoundingRect();
	
}