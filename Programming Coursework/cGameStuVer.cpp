/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();

// controls the colours of the text
Uint8 colourVal = 150;

//static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

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

/*
=================================================================================
Initialisation
=================================================================================
*/

void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255); // Clear the buffer with a black background
	SDL_RenderPresent(theRenderer);

	this->m_lastTime = high_resolution_clock::now();

	playerScore = 0;  // reset score

	theTextureMgr->setRenderer(theRenderer);
	theTextureMgr->addTexture("theBackground", "Images\\background.png"); // add textures from the images folder
	
	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

	theTextureMgr->addTexture("thePaddle", "Images\\tile.png");  // position the paddle sprite at the bottom of the screen
	paddleSprite.setSpritePos({ (375-((theTextureMgr->getTexture("thePaddle")->getTWidth())/2)), 450 }); 
	paddleSprite.setTexture(theTextureMgr->getTexture("thePaddle"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("thePaddle")->getTWidth(), theTextureMgr->getTexture("thePaddle")->getTHeight());

	
	int xPos = 40; // declare variables representing the size of each block
	int yPos = 20;
	
	
	theTextureMgr->addTexture("theRedBlock", "Images\\Red.png"); // add textures for the coloured blocks
	theTextureMgr->addTexture("theOrangeBlock", "Images\\Orange.png");
	theTextureMgr->addTexture("theYellowBlock", "Images\\Yellow.png");
	theTextureMgr->addTexture("theGreenBlock", "Images\\Green.png");
	theTextureMgr->addTexture("theBlueBlock", "Images\\Blue.png");
	theTextureMgr->addTexture("theDarkBlueBlock", "Images\\BlueAGAIN.png");
	theTextureMgr->addTexture("thePurpleBlock", "Images\\Purple.png");
	theTextureMgr->addTexture("thePinkBlock", "Images\\Pink.png");
	theTextureMgr->addTexture("theMagentaBlock", "Images\\PinkAGAIN.png");

	theTextureMgr->addTexture("leftArrow", "Images\\left.png");
	theTextureMgr->addTexture("rightArrow", "Images\\right.png");
	theTextureMgr->addTexture("spacebar", "Images\\space.png");
	
	for (int i = 0; i < 16; i++) // for each block in the 16x9 array 
	{
		for (int j = 0; j < 9; j++)
		{
			blocks[i][j].setSpritePos({ (i * xPos)+55,(j*yPos)+55 });  // position the block according to i and j values
			
			numberOfBlocks++;

			// switch statement to determine which colour is assigned to the block, depending on the row (j)
			// each colour has a different score value
			switch (j) 
			{
				case 0:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theRedBlock"));
					blocks[i][j].scoreValue = 90;
				}
				break;
				case 1:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theOrangeBlock"));
					blocks[i][j].scoreValue = 80;
				}
				break;
				case 2:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theYellowBlock"));
					blocks[i][j].scoreValue = 70;
				}
				break;
				case 3:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theGreenBlock"));
					blocks[i][j].scoreValue = 60;
				}
				break;
				case 4:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theBlueBlock"));
					blocks[i][j].scoreValue = 50;
				}
				break;
				case 5:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theDarkBlueBlock"));
					blocks[i][j].scoreValue = 40;
				}
				break;
				case 6:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("thePurpleBlock"));
					blocks[i][j].scoreValue = 30;
				}
				break;
				case 7:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("thePinkBlock"));
					blocks[i][j].scoreValue = 20;
				}
				break;
				case 8:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theMagentaBlock"));
					blocks[i][j].scoreValue = 10;
				}
				break;
			}
			blocks[i][j].initialise(); // set the bounding rectangle for each block from cBlock
			
		}
		
	}
	theFontMgr->initFontLib();
	//theSoundMgr->initMixer();

	fontList = { "digital", "spaceAge" }; // create textures for text
	fontsToUse = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };
	for (int fonts = 0; fonts < (int)fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 36);
	}
	gameTextList = { "Breakout!", "Score: " };
	strScore = gameTextList[1];
	strScore += to_string(playerScore).c_str();
	
	theTextureMgr->addTexture("Title", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[0], textType::solid, { colourVal, colourVal, colourVal, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("playerScore", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, strScore.c_str(), textType::solid, { colourVal, colourVal, colourVal, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("theBall", "Images\\ball.png"); // texture and position the ball on top of the paddle

	ballSprite.setSpritePos({ (375 - ((theTextureMgr->getTexture("theBall")->getTWidth()) / 2)), (450-(theTextureMgr->getTexture("theBall")->getTHeight())) });
	ballSprite.setTexture(theTextureMgr->getTexture("theBall"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBall")->getTWidth(), theTextureMgr->getTexture("theBall")->getTHeight());

	LpromptSprite.setSpritePos({ (375 - ((theTextureMgr->getTexture("spacebar")->getTWidth()) / 2) - (theTextureMgr->getTexture("leftArrow")->getTWidth())), 350 });
	LpromptSprite.setTexture(theTextureMgr->getTexture("leftArrow"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("leftArrow")->getTWidth(), theTextureMgr->getTexture("leftArrow")->getTHeight());

	RpromptSprite.setSpritePos({ (375 + (theTextureMgr->getTexture("spacebar")->getTWidth()) / 2), 350 });
	RpromptSprite.setTexture(theTextureMgr->getTexture("rightArrow"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("rightArrow")->getTWidth(), theTextureMgr->getTexture("rightArrow")->getTHeight());
	
	SpromptSprite.setSpritePos({ (375 - ((theTextureMgr->getTexture("spacebar")->getTWidth()) / 2)), 300 });
	SpromptSprite.setTexture(theTextureMgr->getTexture("spacebar"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("spacebar")->getTWidth(), theTextureMgr->getTexture("spacebar")->getTHeight());
	
	ballSprite.initialise(); // set the bounding rectangles from cBall and cPaddle
	paddleSprite.initialise();

	cout << numberOfBlocks; // output the number of blocks on the screen (should be 144)
}

/*
=================================================================================
Run
=================================================================================
*/

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	bool loop = true;

	while (loop)
	{
		double elapsedTime = this->getElapsedSeconds(); // get the time that passed since the last frame

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

/*
=================================================================================
Render
=================================================================================
*/

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
	paddleSprite.render(theRenderer, &paddleSprite.getSpriteDimensions(), &paddleSprite.getSpritePos(), NULL, &paddleSprite.getSpriteCentre(), paddleSprite.getSpriteScale());
	ballSprite.render(theRenderer, &ballSprite.getSpriteDimensions(), &ballSprite.getSpritePos(), NULL, &ballSprite.getSpriteCentre(), ballSprite.getSpriteScale());

	if (!(paddleSprite.hasMoved))
	{
		LpromptSprite.render(theRenderer, &LpromptSprite.getSpriteDimensions(), &LpromptSprite.getSpritePos(), NULL, &LpromptSprite.getSpriteCentre(), LpromptSprite.getSpriteScale());
	}

	if (!(paddleSprite.hasMoved))
	{
		RpromptSprite.render(theRenderer, &RpromptSprite.getSpriteDimensions(), &RpromptSprite.getSpritePos(), NULL, &RpromptSprite.getSpriteCentre(), RpromptSprite.getSpriteScale());
	}

	if (!(ballSprite.isMoving))
	{
		SpromptSprite.render(theRenderer, &SpromptSprite.getSpriteDimensions(), &SpromptSprite.getSpritePos(), NULL, &SpromptSprite.getSpriteCentre(), SpromptSprite.getSpriteScale());
	}
	
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (blocks[i][j].isActive)
			{
				blocks[i][j].render(theRenderer, &blocks[i][j].getSpriteDimensions(), &blocks[i][j].getSpritePos(), NULL, &blocks[i][j].getSpriteCentre(), blocks[i][j].getSpriteScale());
			}
		}
	}
	theTextureMgr->deleteTexture("playerScore");
	strScore = gameTextList[1];
	strScore += to_string(playerScore).c_str();
	theTextureMgr->addTexture("playerScore", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, strScore.c_str(), textType::solid, { colourVal, colourVal, colourVal,255 }, { 0, 0, 0, 0 }));

	cTexture* tempTextTexture1 = theTextureMgr->getTexture("Title");
	cTexture* tempTextTexture2 = theTextureMgr->getTexture("playerScore");
	SDL_Rect pos1 = { 10, 10, tempTextTexture1->getTextureRect().w, tempTextTexture1->getTextureRect().h };
	SDL_Rect pos2 = {(740-tempTextTexture2->getTextureRect().w), 10, tempTextTexture2->getTextureRect().w, tempTextTexture2->getTextureRect().h };
	FPoint scale = { 1,1 };
	tempTextTexture1->renderTexture(theRenderer, tempTextTexture1->getTexture(), &tempTextTexture1->getTextureRect(), &pos1, scale);
	tempTextTexture2->renderTexture(theRenderer, tempTextTexture2->getTexture(), &tempTextTexture2->getTextureRect(), &pos2, scale);
	SDL_RenderPresent(theRenderer);
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

/*
=================================================================================
Update 
=================================================================================
*/

void cGame::update(double deltaTime)
{
	
	paddleSprite.update(deltaTime); // call the update methods of paddle/ball scripts to allow continuous movement
	ballSprite.update(deltaTime);

	
	vector<cBlock> collidedBlocks; // vector (list) of collided blocks, in case the ball hits more than one

	SDL_Rect ballBoundingBlock = ballSprite.getBoundingRect();

	for (int i = 0; i < 16; i++) 	// for every block in the 16x9 array
	{
		for (int j = 0; j < 9; j++)
		{
			SDL_Rect blockBoundingBlock = blocks[i][j].getBoundingRect();

			if (blocks[i][j].collidedWith(&blockBoundingBlock, &ballBoundingBlock)) // check for collisions between the ball and each block
			{	
				if (blocks[i][j].isActive) // if the block hasn't already been destroyed
				{
					collidedBlocks.push_back(blocks[i][j]); // add the block to the list of collided blocks
					playerScore += blocks[i][j].scoreValue; // add to the score, depending on the value (colour) of the block
					blocks[i][j].isActive = false; // the block is now destroyed
				}
			}
		}
	}

	SDL_Rect paddleBoundingBlock = paddleSprite.getBoundingRect();
	
	// repeat the process, this time checking for collisions between the ball and the paddle
	if (ballSprite.collidedWith(&paddleBoundingBlock, &ballBoundingBlock)) 
	{
		// find the centre of each sprite, plus their position on the screen
		SDL_Point paddleCentre = paddleSprite.getSpriteCentre() + paddleSprite.getSpritePos();  
		SDL_Point ballCentre = ballSprite.getSpriteCentre() + ballSprite.getSpritePos();

		// if the ball is moving too fast and clips through the paddle, find the entry direction first
		SDL_Point entryDirection = paddleCentre - ballCentre;

		// slowly push the ball sprite back from the entry direction until the ball is no longer clipped through the paddle
		// The following 4 lines came from my coursemate Josh Lee
		int pushBackIterations = 0;
		do {
			pushBackIterations++;
			if (pushBackIterations > 100) continue;

			SDL_Point entryDirectionStep = entryDirection / 5;  // move back a little bit
			SDL_Rect ballPos = ballSprite.getSpritePos();

			ballPos.x -= entryDirectionStep.x;
			ballPos.y -= entryDirectionStep.y;

			ballSprite.setSpritePos(ballPos);

			ballSprite.setBoundingRect(); // update bounding block
			paddleSprite.setBoundingRect();

			ballBoundingBlock = ballSprite.getBoundingRect();
			paddleBoundingBlock = paddleSprite.getBoundingRect();

			// repeat this continuously while the ball is colliding with the paddle
		} while (paddleSprite.collidedWith(&paddleBoundingBlock, &ballBoundingBlock));

		// now that the ball has hit the paddle, bounce with negative velocity
		ballSprite.yVelocity *= -1;
	}

	// if the collidedBlocks vector is greater than zero, i.e. there has been a recorded collision with a block
	if (collidedBlocks.size() > 0)
	{
		cBlock collidedBlock = collidedBlocks[0];
		
		for (int i = 1; i < collidedBlocks.size(); i++)
		{
			// find the shortest distance between the ball and the centre of both collided blocks
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

			// if the distance between block 1 is bigger than block 2, make block 2 the current closest block
			if (distance1 > distance2)
			{
				collidedBlock = collidedBlocks[i];
			}
		}

		// only act on the closest block - don't bounce off both
		SDL_Point blockCentre = collidedBlock.getSpriteCentre() + collidedBlock.getSpritePos();
		SDL_Point ballCentre = ballSprite.getSpriteCentre() + ballSprite.getSpritePos();

		// repeat the same process of the ball hitting the paddle, this time with the block
		SDL_Point entryDirection = blockCentre - ballCentre;

		// The following 4 lines came from my coursemate Josh Lee
		int pushBackIterations = 0;
		do {
			pushBackIterations++;
			if (pushBackIterations > 100) continue;

			SDL_Point entryDirectionStep = entryDirection / 5; // move back a little bit

			SDL_Rect ballPos = ballSprite.getSpritePos();

			ballPos.x -= entryDirectionStep.x;
			ballPos.y -= entryDirectionStep.y;

			ballSprite.setSpritePos(ballPos);
			
			ballSprite.setBoundingRect();  // update bounding block

			ballBoundingBlock = ballSprite.getBoundingRect();

		} while (collidedBlock.collidedWith(&collidedBlock.getBoundingRect(), &ballBoundingBlock));

		// The following two if statements are from my coursemate Ruari McGhee
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
				paddleSprite.hasMoved = true;
				break; 
			
			case SDLK_RIGHT:
				paddleSprite.isGoingRight = true;
				if (!(ballSprite.isMoving))
				{
					ballSprite.isGoingRight = true;
				}
				paddleSprite.hasMoved = true;
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

