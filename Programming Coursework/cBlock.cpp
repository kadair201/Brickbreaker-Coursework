#include "cBlock.h"

int initCount = 0;

void cBlock::initialise() {
	setBoundingRect();
	cout << getBoundingRect().w;
}

void cBlock::update(double deltaTime) {

}