/*
=================
cPaddle.cpp
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
	// set the bounding rectangle for cPaddle
	setBoundingRect();
	// reset the hasMoved variable so the instruction prompts will show
	hasMoved = false;
}

/*
=================================================================
Paddle Movement
=================================================================
*/

void cPaddle::update(double deltaTime)
{
	// get the current position on the screen
	SDL_Point currentPos = { this->getSpritePos().x, this->getSpritePos().y };
	// set the movement speed of the paddle
	int moveSpeed = 12;

	// check if the paddle isGoingRight is true and the paddle is within the boundaries of the game
	if ((isGoingRight) && (currentPos.x < 650)) 
	{
		currentPos.x += moveSpeed; // modify the current position on the x axis
	}
	else
	{
		isGoingRight = false; // stop movement once the paddle reaches the boundary
	}

	if ((isGoingLeft) && (currentPos.x > 0)) {
		currentPos.x -= moveSpeed;
	}
	else
	{
		isGoingLeft = false;
	}

	// update the sprite and bounding rectangle for the paddle
	this->setSpritePos(currentPos);
	setBoundingRect();
}
