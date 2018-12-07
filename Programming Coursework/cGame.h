#ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
==================================================================================
*/

#include <SDL.h>

// Game specific includes
#include "breakoutGame.h"


using namespace std;

class cGame
{
public:
	cGame();

	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre);
	void update();
	void update(double deltaTime);
	bool getInput(bool theLoop);
	double getElapsedSeconds();
	int numberOfBlocks;
	int playerScore;
	string strScore;
	cBlock blocks[16][9];

	static cGame* getInstance();

private:

	static cGame* pInstance;
	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;

	// game related variables
	// Sprites for displaying background
	cSprite spriteBkgd;
	cPaddle paddleSprite;
	cBall ballSprite;
	cPrompts LpromptSprite;
	cPrompts RpromptSprite;
	cPrompts SpromptSprite;
	vector<LPCSTR> textName;
	vector<LPCSTR> texturesToUse;
	
	// Fonts to use
	vector<LPCSTR> fontList;
	vector<LPCSTR> fontsToUse;
	// Text for Game
	vector<LPCSTR> gameTextList;
	// Game Sounds
	vector<LPCSTR> soundList;
	vector<soundType> soundTypes;
	vector<LPCSTR> soundsToUse;
	// Create vector array of button textures
	vector<LPCSTR> btnNameList;
	vector<LPCSTR> btnTexturesToUse;
	vector<SDL_Point> btnPos;
	vector <cButton> theButtons;
	// Game objects
	int renderWidth, renderHeight;
	gameState theGameState;
	btnTypes theBtnType;
	SDL_Rect pos;
	FPoint scale;
	cTexture* tempTextTexture;
	SDL_Point theAreaClicked;
	bool loop;
	bool playingAgain;
	int highScore;
	void resetGame();
};

#endif
