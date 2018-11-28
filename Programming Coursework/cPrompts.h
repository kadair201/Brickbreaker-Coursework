#ifndef _CPROMPTS_H
#define _CPROMPTS_H
#include "cSprite.h"

class cPrompts : public cSprite
{
public:
	void initialise();
	void update(double deltaTime);
};
#endif
