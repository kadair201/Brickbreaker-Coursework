#include "cBlock.h"

int initCount = 0;

void cBlock::initialise() {
	setBoundingRect();
	isActive = true;
}

void cBlock::update(double deltaTime) {

}