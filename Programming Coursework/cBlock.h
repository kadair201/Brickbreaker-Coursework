#ifndef _CBLOCK_H
#define _CBLOCK_H
#include "cSprite.h"

class cBlock : public cSprite
{
public:
	void initialise();		// Default render function
	void update(double deltaTime);		// block update method
	
	bool isActive;
	int scoreValue;
};

#endif