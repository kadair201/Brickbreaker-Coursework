/*
=================
cTexture.h
=================
*/
#ifndef _CTEXTURE_H
#define _CTEXTURE_H
#include "GameConstants.h"

class cTexture
{
private:
	// initialise variables
	SDL_Texture* sdlTextureID;
	int textureWidth;
	int textureHeight;


public:
	// initialise variables and methods
	cTexture();
	cTexture(LPCSTR theFilename, SDL_Renderer *theRenderer);
	~cTexture();
	bool loadTexture(SDL_Texture* theTexture);
	bool loadTexture(LPCSTR theFilename, SDL_Renderer *theRenderer);// create the texture for use.
	void renderTexture(SDL_Renderer* theRenderer, SDL_Texture* ptheTexture, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, FPoint theScaling);
	void renderTexture(SDL_Renderer* theRenderer, SDL_Texture* ptheTexture, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling);
	SDL_Texture* getTexture();						// return the texture.
	SDL_Rect getTextureRect();
	int getTWidth();						// Return width of texture;
	int getTHeight();						// Return height of texture;
};
#endif