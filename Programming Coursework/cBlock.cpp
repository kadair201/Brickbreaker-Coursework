#include "cBlock.h"


void cBlock::initialise() 
{
	// set the bounding rectangle
	setBoundingRect();
	// allow the blocks to render
	isActive = true;
}

void cBlock::update(double deltaTime) 
{

}