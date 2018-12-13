/*
=================
cButton.h
=================
*/
#ifndef _CBUTTON_H
#define _CBUTTON_H
#include "cSprite.h"

class cButton : public cSprite
{

private:
	// initialise variables
	SDL_Point buttonClickedRC;
	bool clicked = false;

public:
	// initialise methods and variables
	cButton();

	gameState update(gameState theCurrentGameState, gameState newGameState, SDL_Point theAreaClicked);

	bool getClicked();
	void setClicked(bool state);

};
#endif