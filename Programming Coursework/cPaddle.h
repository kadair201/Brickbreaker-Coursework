/*
=================
cPaddle.h
- Header file for class definition - SPECIFICATION
- Header file for the paddle class which is a child of cSprite class
=================
*/
#ifndef _CPADDLE_H
#define _CPADDLE_H
#include "cSprite.h"

class cPaddle : public cSprite
{
public:
	bool isGoingLeft;
	bool isGoingRight;

	void initialise();		// Default render function
	void update(double deltaTime);		// Paddle update method
};

#endif