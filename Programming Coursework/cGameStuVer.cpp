/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();

/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}


void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	this->m_lastTime = high_resolution_clock::now();

	// add textures from the images folder
	theTextureMgr->setRenderer(theRenderer);
	theTextureMgr->addTexture("theBackground", "Images\\background.png");
	
	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

	theTextureMgr->addTexture("thePaddle", "Images\\tile.png");
	// position the paddle sprite at the bottom of the screen
	paddleSprite.setSpritePos({ (375-((theTextureMgr->getTexture("thePaddle")->getTWidth())/2)), 450 });
	paddleSprite.setTexture(theTextureMgr->getTexture("thePaddle"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("thePaddle")->getTWidth(), theTextureMgr->getTexture("thePaddle")->getTHeight());

	// declare variables representing the size of each block
	int xPos = 40;
	int yPos = 20;
	
	// add textures for the coloured blocks
	theTextureMgr->addTexture("theRedBlock", "Images\\Red.png");
	theTextureMgr->addTexture("theOrangeBlock", "Images\\Orange.png");
	theTextureMgr->addTexture("theYellowBlock", "Images\\Yellow.png");
	theTextureMgr->addTexture("theGreenBlock", "Images\\Green.png");
	theTextureMgr->addTexture("theBlueBlock", "Images\\Blue.png");
	theTextureMgr->addTexture("theDarkBlueBlock", "Images\\BlueAGAIN.png");
	theTextureMgr->addTexture("thePurpleBlock", "Images\\Purple.png");
	theTextureMgr->addTexture("thePinkBlock", "Images\\Pink.png");
	theTextureMgr->addTexture("theMagentaBlock", "Images\\PinkAGAIN.png");

	// for each block in the 16x9 array 
	for (int i = 0; i < 16; i++) 
	{
		for (int j = 0; j < 9; j++)
		{
			// position the block according to i and j values
			blocks[i][j].setSpritePos({ (i * xPos)+55,(j*yPos)+55 });
			// add to the number of blocks
			numberOfBlocks++;

			// switch statement to determine which colour is assigned to the block, depending on the row (j)
			switch (j) 
			{
				case 0:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theRedBlock"));
				}
				break;
				case 1:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theOrangeBlock"));
				}
				break;
				case 2:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theYellowBlock"));
				}
				break;
				case 3:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theGreenBlock"));
				}
				break;
				case 4:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theBlueBlock"));
				}
				break;
				case 5:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theDarkBlueBlock"));
				}
				break;
				case 6:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("thePurpleBlock"));
				}
				break;
				case 7:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("thePinkBlock"));
				}
				break;
				case 8:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theMagentaBlock"));
				}
				break;
			}
			blocks[i][j].initialise();
			
		}
		
	}
	
	theTextureMgr->addTexture("theBall", "Images\\ball.png");
	ballSprite.setSpritePos({ (375 - ((theTextureMgr->getTexture("theBall")->getTWidth()) / 2)), (450-(theTextureMgr->getTexture("theBall")->getTHeight())) });
	ballSprite.setTexture(theTextureMgr->getTexture("theBall"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBall")->getTWidth(), theTextureMgr->getTexture("theBall")->getTHeight());

	ballSprite.initialise();
	paddleSprite.initialise();

	cout << numberOfBlocks;
}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	bool loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
	paddleSprite.render(theRenderer, &paddleSprite.getSpriteDimensions(), &paddleSprite.getSpritePos(), NULL, &paddleSprite.getSpriteCentre(), paddleSprite.getSpriteScale());
	ballSprite.render(theRenderer, &ballSprite.getSpriteDimensions(), &ballSprite.getSpritePos(), NULL, &ballSprite.getSpriteCentre(), ballSprite.getSpriteScale());
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			blocks[i][j].render(theRenderer, &blocks[i][j].getSpriteDimensions(), &blocks[i][j].getSpritePos(), NULL, &blocks[i][j].getSpriteCentre(), blocks[i][j].getSpriteScale());
		}
	}
	SDL_RenderPresent(theRenderer);
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	paddleSprite.update(deltaTime);
	ballSprite.update(deltaTime);

	vector<cBlock> collidedBlocks;
	SDL_Rect ballBoundingBlock = ballSprite.getBoundingRect();

	for (int i = 0; i < 16; i++) 
	{
		for (int j = 0; j < 9; j++)
		{
			SDL_Rect blockBoundingBlock = blocks[i][j].getBoundingRect();

			if (blocks[i][j].collidedWith(&blockBoundingBlock, &ballBoundingBlock))
			{
				collidedBlocks.push_back(blocks[i][j]);
			}
		}
	}

	SDL_Rect paddleBoundingBlock = paddleSprite.getBoundingRect();

	if (ballSprite.collidedWith(&paddleBoundingBlock, &ballBoundingBlock))
	{
		SDL_Point paddleCentre = paddleSprite.getSpriteCentre() + paddleSprite.getSpritePos();
		SDL_Point ballCentre = ballSprite.getSpriteCentre() + ballSprite.getSpritePos();

		SDL_Point entryDirection = paddleCentre - ballCentre;

		int pushBackIterations = 0;
		do {
			pushBackIterations++;
			if (pushBackIterations > 100) continue;

			// move back a little bit
			SDL_Point entryDirectionStep = entryDirection / 5;

			SDL_Rect ballPos = ballSprite.getSpritePos();

			ballPos.x -= entryDirectionStep.x;
			ballPos.y -= entryDirectionStep.y;

			ballSprite.setSpritePos(ballPos);

			// update bounding block
			ballSprite.setBoundingRect();
			paddleSprite.setBoundingRect();

			ballBoundingBlock = ballSprite.getBoundingRect();
			paddleBoundingBlock = paddleSprite.getBoundingRect();

		} while (paddleSprite.collidedWith(&paddleBoundingBlock, &ballBoundingBlock));

		ballSprite.yVelocity *= -1;
	}

	if (collidedBlocks.size() > 0)
	{
		cBlock collidedBlock = collidedBlocks[0];
		
		for (int i = 1; i < collidedBlocks.size(); i++)
		{
			SDL_Point ballCentre = ballSprite.getSpriteCentre();
			SDL_Point firstCollidedBlockCentre = collidedBlock.getSpriteCentre();
			SDL_Point secondCollidedBlockCentre = collidedBlocks[i].getSpriteCentre();

			SDL_Point direction1 = {
				ballCentre.x - firstCollidedBlockCentre.x,
				ballCentre.y - firstCollidedBlockCentre.y
			};

			SDL_Point direction2 = {
				ballCentre.x - secondCollidedBlockCentre.x,
				ballCentre.y - secondCollidedBlockCentre.y
			};

			float distance1 = (float)sqrt((direction1.x * direction1.x) + (direction1.y * direction1.y));
			float distance2 = (float)sqrt((direction2.x * direction2.x) + (direction2.y * direction2.y));

			if (distance1 > distance2)
			{
				collidedBlock = collidedBlocks[i];
			}
		}

		SDL_Point blockCentre = collidedBlock.getSpriteCentre() + collidedBlock.getSpritePos();
		SDL_Point ballCentre = ballSprite.getSpriteCentre() + ballSprite.getSpritePos();

		SDL_Point entryDirection = blockCentre - ballCentre;

		int pushBackIterations = 0;
		do {
			pushBackIterations++;
			if (pushBackIterations > 100) continue;

			// move back a little bit
			SDL_Point entryDirectionStep = entryDirection / 5;

			SDL_Rect ballPos = ballSprite.getSpritePos();

			ballPos.x -= entryDirectionStep.x;
			ballPos.y -= entryDirectionStep.y;

			ballSprite.setSpritePos(ballPos);

			// update bounding block
			ballSprite.setBoundingRect();

			ballBoundingBlock = ballSprite.getBoundingRect();

		} while (collidedBlock.collidedWith(&collidedBlock.getBoundingRect(), &ballBoundingBlock));

		if (ballCentre.y > blockCentre.y) {
			// Hit from or right below, flip x
			if (ballCentre.x < blockCentre.x - 20 || ballCentre.x > blockCentre.x + 20) {
				ballSprite.xVelocity *= -1;
			}
			else {
				// Hit from directly below, flip y
				ballSprite.yVelocity *= -1;
			}
		}

		if (ballCentre.y < blockCentre.y) {
			// Hit from or right above, flip x
			if (ballCentre.x < blockCentre.x - 20 || ballCentre.x > blockCentre.x + 20) {
				ballSprite.xVelocity *= -1;
			}
			else {
				// Hit from directly above, flip y
				ballSprite.yVelocity *= -1;
			}
		}
	}
}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym) {

			case SDLK_LEFT:
				paddleSprite.isGoingLeft = false;
				if (!(ballSprite.isMoving))
				{
					ballSprite.isGoingLeft = false;
				}
				break;

			case SDLK_RIGHT:
				paddleSprite.isGoingRight = false;
				if (!(ballSprite.isMoving))
				{
					ballSprite.isGoingRight = false;
				}
				break;

			default:
				break;
			}
		}
			

		if (event.type == SDL_KEYDOWN)
		{
			SDL_Rect currentPos = paddleSprite.getSpritePos();

			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				theLoop = false;
				break;

			case SDLK_LEFT:
				paddleSprite.isGoingLeft = true;
				if (!(ballSprite.isMoving))
				{
					ballSprite.isGoingLeft = true;
				}
				break; 
			
			case SDLK_RIGHT:
				paddleSprite.isGoingRight = true;
				if (!(ballSprite.isMoving))
				{
					ballSprite.isGoingRight = true;
				}
				break;

			case SDLK_SPACE:
				ballSprite.isMoving = true;
				cout << ballSprite.isMoving;
				break;

			default:
				break;
			}
		}
	}
	return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

