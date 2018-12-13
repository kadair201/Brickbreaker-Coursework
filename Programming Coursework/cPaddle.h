/*
=================
cPaddle.h
=================
*/
#ifndef _CPADDLE_H
#define _CPADDLE_H
#include "cSprite.h"

class cPaddle : public cSprite
{
public:
	// variables for movement
	bool isGoingLeft;
	bool isGoingRight;
	bool hasMoved;

	// methods
	void initialise();
	void update(double deltaTime);
};

#endif