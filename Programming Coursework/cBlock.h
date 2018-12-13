#ifndef _CBLOCK_H
#define _CBLOCK_H
#include "cSprite.h"

class cBlock : public cSprite
{
public:
	// initialise methods
	void initialise();		
	void update(double deltaTime);		
	
	// initialise variables
	bool isActive;
	int scoreValue;
};

#endif