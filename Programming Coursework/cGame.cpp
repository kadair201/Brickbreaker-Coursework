/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance();
static cHighScoreMgr* theHighScoreMgr = cHighScoreMgr::getInstance();
static cXInput* theXInput = cXInput::getInstance();


// controls the colours of the text
Uint8 colourVal = 150;

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

	// initialise the font and sound managers
	theFontMgr->initFontLib();
	theSoundMgr->initMixer();

	// initalise the font list
	fontList = { "ka1" };
	fontsToUse = { "Fonts/ka1.ttf" };  // https://www.dafont.com/karmatic-arcade.font
	for (int fonts = 0; fonts < (int)fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 36);
	}
	// initialise the game text list
	gameTextList = { "Breakout!", "Score: " };
	strScore = gameTextList[1];
	strScore += to_string(playerScore).c_str();

	// Load game sounds
	soundList = { "theme", "click", "bounce" };
	soundTypes = { soundType::music, soundType::sfx, soundType::sfx };
	soundsToUse = { "Audio/BackgroundMusic.wav", "Audio/ClickSound.wav", "Audio/BounceSound.wav" };
	for (unsigned int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}
	theSoundMgr->getSnd("theme")->play(-1);

	// reset player score
	playerScore = 0;  
	// initalise the size of the blocks
	int xPos = 40;
	int yPos = 20;

	// check if the controller is attached
	theXInput->CheckController();

	// load background textures
	theTextureMgr->setRenderer(theRenderer);
	theTextureMgr->addTexture("theBackground", "Images\\background.png");
	theTextureMgr->addTexture("menuBackground", "Images\\menu.png");
	theTextureMgr->addTexture("scoresBackground", "Images\\scores.png");
	theTextureMgr->addTexture("winBackground", "Images\\winScreen.png");
	theTextureMgr->addTexture("loseBackground", "Images\\loseScreen.png");
	// load controller textures
	theTextureMgr->addTexture("controllerConnected", "Images\\controllerConnected.png");
	theTextureMgr->addTexture("controllerNotConnected", "Images\\controllerNotConnected.png");
	theTextureMgr->addTexture("controllerControls", "Images\\controllerControls.png");
	// load the paddle and ball textures
	theTextureMgr->addTexture("thePaddle", "Images\\tile.png");
	theTextureMgr->addTexture("theBall", "Images\\ball.png");
	// load the font textures
	theTextureMgr->addTexture("Title", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, gameTextList[0], textType::solid, { colourVal, colourVal, colourVal, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("playerScore", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, strScore.c_str(), textType::solid, { colourVal, colourVal, colourVal, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("score1", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, "score1", textType::solid, { 0,0,0,225 }, { 0,0,0,0 }));
	theTextureMgr->addTexture("score2", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, "score2", textType::solid, { 0,0,0,225 }, { 0,0,0,0 }));
	theTextureMgr->addTexture("score3", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, "score3", textType::solid, { 0,0,0,225 }, { 0,0,0,0 }));
	// load the prompt textures
	theTextureMgr->addTexture("leftArrow", "Images\\left.png");
	theTextureMgr->addTexture("rightArrow", "Images\\right.png");
	theTextureMgr->addTexture("spacebar", "Images\\space.png");
	// load the block textures
	theTextureMgr->addTexture("theRedBlock", "Images\\Red.png");
	theTextureMgr->addTexture("theOrangeBlock", "Images\\Orange.png");
	theTextureMgr->addTexture("theYellowBlock", "Images\\Yellow.png");
	theTextureMgr->addTexture("theGreenBlock", "Images\\Green.png");
	theTextureMgr->addTexture("theBlueBlock", "Images\\Teal.png");
	theTextureMgr->addTexture("theDarkBlueBlock", "Images\\Blue.png");
	theTextureMgr->addTexture("thePurpleBlock", "Images\\Purple.png");
	theTextureMgr->addTexture("thePinkBlock", "Images\\Magenta.png");
	theTextureMgr->addTexture("theMagentaBlock", "Images\\Pink.png");
	
	// set up the sprite backgrounds
	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());
	// set up the paddle sprite
	paddleSprite.setSpritePos({ (375-((theTextureMgr->getTexture("thePaddle")->getTWidth())/2)), 450 }); 
	paddleSprite.setTexture(theTextureMgr->getTexture("thePaddle"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("thePaddle")->getTWidth(), theTextureMgr->getTexture("thePaddle")->getTHeight());
	// set up the ball sprite
	ballSprite.setSpritePos({ (375 - ((theTextureMgr->getTexture("theBall")->getTWidth()) / 2)), (450 - (theTextureMgr->getTexture("theBall")->getTHeight())) });
	ballSprite.setTexture(theTextureMgr->getTexture("theBall"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBall")->getTWidth(), theTextureMgr->getTexture("theBall")->getTHeight());
	// set up the left arrow prompt sprite
	LpromptSprite.setSpritePos({ (375 - ((theTextureMgr->getTexture("spacebar")->getTWidth())) - (theTextureMgr->getTexture("leftArrow")->getTWidth())), 350 });
	LpromptSprite.setTexture(theTextureMgr->getTexture("leftArrow"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("leftArrow")->getTWidth(), theTextureMgr->getTexture("leftArrow")->getTHeight());
	// set up the right arrow prompt sprite
	RpromptSprite.setSpritePos({ (375 + ((theTextureMgr->getTexture("spacebar")->getTWidth()) / 2) + theTextureMgr->getTexture("rightArrow")->getTWidth()), 350 });
	RpromptSprite.setTexture(theTextureMgr->getTexture("rightArrow"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("rightArrow")->getTWidth(), theTextureMgr->getTexture("rightArrow")->getTHeight());
	// set up the controller prompt sprite
	controllerPromptSprite.setSpritePos({ 275, 250 });
	controllerPromptSprite.setTexture(theTextureMgr->getTexture("controllerControls"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("controllerControls")->getTWidth(), theTextureMgr->getTexture("controllerControls")->getTHeight());
	// set up the spacebar prompt sprite
	SpromptSprite.setSpritePos({ (375 - ((theTextureMgr->getTexture("spacebar")->getTWidth()) / 2)), 300 });
	SpromptSprite.setTexture(theTextureMgr->getTexture("spacebar"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("spacebar")->getTWidth(), theTextureMgr->getTexture("spacebar")->getTHeight());
	// set up the controller prompt sprite
	controllerSprite.setSpritePos({ 670,210 });
	controllerSprite.setTexture(theTextureMgr->getTexture("controllerNotConnected"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("controllerNotConnected")->getTWidth(), theTextureMgr->getTexture("controllerNotConnected")->getTHeight());

	// set up the buttons
	btnNameList = { "play_btn", "scores_btn", "quit_btn", "menu_btn", "replay_btn" };
	// set up button textures and positions
	btnTexturesToUse = { "Images\\GoButton.png", "Images\\ScoresButton.png", "Images\\QuitButton.png", "Images\\MenuButton.png", "Images\\ReplayButton.png" };
	btnPos = { { 500, 250 }, { 500, 325 }, { 500, 400 }, { 10, 400 }, {250,400} };
	for (unsigned int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		theTextureMgr->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]);
	}
	for (unsigned int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		cButton * newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture(btnNameList[bCount]));
		newBtn->setSpritePos(btnPos[bCount]);
		newBtn->setSpriteDimensions(theTextureMgr->getTexture(btnNameList[bCount])->getTWidth(), theTextureMgr->getTexture(btnNameList[bCount])->getTHeight());
		theButtonMgr->add(btnNameList[bCount], newBtn);
	}
	theGameState = gameState::menu;
	theBtnType = btnTypes::exit;
	
	// initialise the blocks textures and scores
	for (int i = 0; i < 16; i++) // for each block in the 16x9 array 
	{
		for (int j = 0; j < 9; j++)
		{
			blocks[i][j].setSpritePos({ (i * xPos)+55,(j*yPos)+60 });  // position the block according to i and j values
	

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

	ballSprite.initialise(); // set the bounding rectangles from cBall and cPaddle
	paddleSprite.initialise();

	// set high score to -1 so that it doesn't go on the scoreboard
	theHighScoreMgr->SetHighScores(-1);

	// create a vector of scores from GetHighScores()
	vector<int> scores = theHighScoreMgr->GetHighScores();

	// score textures are deleted
	theTextureMgr->deleteTexture("score1");
	theTextureMgr->deleteTexture("score2");
	theTextureMgr->deleteTexture("score3");

	// score textures are re-assigned so they are accurate
	string tempScore = "1. " + to_string(scores[0]);
	theTextureMgr->addTexture("score1", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, tempScore.c_str(), textType::solid, { colourVal, colourVal, colourVal,255 }, { 0, 0, 0, 0 }));
	tempScore = "2. " + to_string(scores[1]);
	theTextureMgr->addTexture("score2", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, tempScore.c_str(), textType::solid, { colourVal, colourVal, colourVal,255 }, { 0, 0, 0, 0 }));
	tempScore = "3. " + to_string(scores[2]);
	theTextureMgr->addTexture("score3", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, tempScore.c_str(), textType::solid, { colourVal, colourVal, colourVal,255 }, { 0, 0, 0, 0 }));

}

/*
=================================================================================
Run
=================================================================================
*/

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	loop = true;

	while (loop)
	{
		double elapsedTime = this->getElapsedSeconds(); // get the time that passed since the last frame

		loop = this->getInput(loop);
		this->update(elapsedTime, theRenderer);
		this->render(theSDLWND, theRenderer);
		theXInput->CheckController();
		
	}
}

/*
================================================================================================================================================================================================
Render
================================================================================================================================================================================================
*/

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	// clear render
	SDL_RenderClear(theRenderer);

	// switch statement for game states
	switch (theGameState)
	{
		case (gameState::menu):
		{
			// load the menu background 
			spriteBkgd.setTexture(theTextureMgr->getTexture("menuBackground"));
			// render it 
			spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
			// render the play button
			theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
			// render the scores button
			theButtonMgr->getBtn("scores_btn")->render(theRenderer, &theButtonMgr->getBtn("scores_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("scores_btn")->getSpritePos(), theButtonMgr->getBtn("scores_btn")->getSpriteScale());
			// render the quit button
			theButtonMgr->getBtn("quit_btn")->render(theRenderer, &theButtonMgr->getBtn("quit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("quit_btn")->getSpritePos(), theButtonMgr->getBtn("quit_btn")->getSpriteScale());

			// if the controller is connected
			if (theXInput->controllerConnected)
			{
				// set the sprite indicator to green
				controllerSprite.setTexture(theTextureMgr->getTexture("controllerConnected"));
			}
			else
			{
				// set the sprite indicator to red
				controllerSprite.setTexture(theTextureMgr->getTexture("controllerNotConnected"));
			}
			// render the indicator
			controllerSprite.render(theRenderer, &controllerSprite.getSpriteDimensions(), &controllerSprite.getSpritePos(), NULL, &controllerSprite.getSpriteCentre(), controllerSprite.getSpriteScale());
		}
		break;

		case (gameState::playing):
		{
			spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
			spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());

			// render the paddle and ball
			paddleSprite.render(theRenderer, &paddleSprite.getSpriteDimensions(), &paddleSprite.getSpritePos(), NULL, &paddleSprite.getSpriteCentre(), paddleSprite.getSpriteScale());
			ballSprite.render(theRenderer, &ballSprite.getSpriteDimensions(), &ballSprite.getSpritePos(), NULL, &ballSprite.getSpriteCentre(), ballSprite.getSpriteScale());
			
			// if the controller is not attached, show the keyboard controls
			if (!(theXInput->controllerConnected))
			{
				if (!(paddleSprite.hasMoved)) // check if the right or left arrow keys have been pressed
				{
					// if not, render the left and right arrow key prompts
					LpromptSprite.render(theRenderer, &LpromptSprite.getSpriteDimensions(), &LpromptSprite.getSpritePos(), NULL, &LpromptSprite.getSpriteCentre(), LpromptSprite.getSpriteScale());
					RpromptSprite.render(theRenderer, &RpromptSprite.getSpriteDimensions(), &RpromptSprite.getSpritePos(), NULL, &RpromptSprite.getSpriteCentre(), RpromptSprite.getSpriteScale());
				}

				if (!(ballSprite.isMoving)) // check if the ball has been launched from the paddle
				{
					// if not, render the spacebar prompt
					SpromptSprite.render(theRenderer, &SpromptSprite.getSpriteDimensions(), &SpromptSprite.getSpritePos(), NULL, &SpromptSprite.getSpriteCentre(), SpromptSprite.getSpriteScale());
				}
			}
			else // if the controller is plugged in, show the controller controls
			{
				if (!(paddleSprite.hasMoved) && !(ballSprite.isMoving))
				{
					controllerPromptSprite.render(theRenderer, &controllerPromptSprite.getSpriteDimensions(), &controllerPromptSprite.getSpritePos(), NULL, &controllerPromptSprite.getSpriteCentre(), controllerPromptSprite.getSpriteScale());
				}

			}

			// go through the array of blocks 
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					// check if each block is active
					if (blocks[i][j].isActive)
					{
						// if so, render the block
						blocks[i][j].render(theRenderer, &blocks[i][j].getSpriteDimensions(), &blocks[i][j].getSpritePos(), NULL, &blocks[i][j].getSpriteCentre(), blocks[i][j].getSpriteScale());
					}
				}
			}
			theTextureMgr->deleteTexture("playerScore");
			strScore = gameTextList[1];
			strScore += to_string(playerScore).c_str();
			theTextureMgr->addTexture("playerScore", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, strScore.c_str(), textType::solid, { colourVal, colourVal, colourVal,255 }, { 0, 0, 0, 0 }));

			cTexture* tempTextTexture1 = theTextureMgr->getTexture("Title");
			cTexture* tempTextTexture2 = theTextureMgr->getTexture("playerScore");
			SDL_Rect pos1 = { 10, 10, tempTextTexture1->getTextureRect().w, tempTextTexture1->getTextureRect().h };
			SDL_Rect pos2 = { (740 - tempTextTexture2->getTextureRect().w), 10, tempTextTexture2->getTextureRect().w, tempTextTexture2->getTextureRect().h };
			FPoint scale = { 1,1 };
			tempTextTexture1->renderTexture(theRenderer, tempTextTexture1->getTexture(), &tempTextTexture1->getTextureRect(), &pos1, scale);
			tempTextTexture2->renderTexture(theRenderer, tempTextTexture2->getTexture(), &tempTextTexture2->getTextureRect(), &pos2, scale);
		}
		break;

		case gameState::scores:
		{
			// set the background
			spriteBkgd.setTexture(theTextureMgr->getTexture("scoresBackground"));
			// render the background
			spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
			// render the menu button
			theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());

			// get the list of high scores from the file
			theHighScoreMgr->GetHighScores();

			// texture and position these high scores
			tempTextTexture = theTextureMgr->getTexture("score1");
			pos = { 350, 300, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			// render the high score
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

			// texture and position the second score
			tempTextTexture = theTextureMgr->getTexture("score2");
			pos = { 350, 350, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			// render the second score
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

			// texture and position the third score
			tempTextTexture = theTextureMgr->getTexture("score3");
			pos = { 350, 400, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			// render the third score
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		}
		break;
		
		case gameState::end:
		{
			// if the player won the game
			if (playerScore >= 7200)
			{
				// render the 'win' background
				spriteBkgd.setTexture(theTextureMgr->getTexture("winBackground"));
				spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
			}
			else 
			{
				// render the 'lose' background
				spriteBkgd.setTexture(theTextureMgr->getTexture("loseBackground"));
				spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
			}
		
			// render the replay button
			theButtonMgr->getBtn("replay_btn")->render(theRenderer, &theButtonMgr->getBtn("replay_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("replay_btn")->getSpritePos(), theButtonMgr->getBtn("replay_btn")->getSpriteScale());
			// render the quit button
			theButtonMgr->getBtn("quit_btn")->render(theRenderer, &theButtonMgr->getBtn("quit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("quit_btn")->getSpritePos(), theButtonMgr->getBtn("quit_btn")->getSpriteScale());
			// render the menu button
			theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());

			// render the player's score to the screen
			theTextureMgr->addTexture("playerScore", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, strScore.c_str(), textType::solid, { colourVal, colourVal, colourVal,255 }, { 0, 0, 0, 0 }));
			cTexture* tempTextTexture = theTextureMgr->getTexture("playerScore");
			// position and scale the player score
			SDL_Rect pos = { (700 - tempTextTexture->getTextureRect().w), 300, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			FPoint scale = { 1,1 };
			// render the score
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		}
		break;
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

/*
=================================================================================
Update 
=================================================================================
*/

void cGame::update(double deltaTime, SDL_Renderer* theRenderer)
{
	// switch statement for game states
	switch (theGameState)
	{
		
	case gameState::menu:
	{
		// act when the play button is clicked, turn to the 'playing' gamestate
		theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, gameState::playing, theAreaClicked);
		// act when the quit button is clicked, turn to the 'exit' gamestate
		theGameState = theButtonMgr->getBtn("quit_btn")->update(theGameState, gameState::exit, theAreaClicked);
		// act when the scores button is clicked, turn to the 'scores' gamestate
		theGameState = theButtonMgr->getBtn("scores_btn")->update(theGameState, gameState::scores, theAreaClicked);
	}
	break;

	case gameState::scores:
	{
		// act when the menu button is clicked, transition to the 'menu' gamestate
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, gameState::menu, theAreaClicked);
	}
	break;

	case gameState::playing:
	{
		// check if the controller is connected
		if (theXInput->controllerConnected) 
		{
			// if it is, use the Xinput controls
			XInputControls(loop);
		}
		
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
						theSoundMgr->getSnd("bounce")->play(0); // audio feedback
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
			theSoundMgr->getSnd("bounce")->play(0); // audio feedback

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
				SDL_Point ballPos = { ballSprite.getSpritePos().x,ballSprite.getSpritePos().y };

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
				SDL_Point ballPos = { ballSprite.getSpritePos().x,ballSprite.getSpritePos().y };

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

		

		// check if the player has won
		if (playerScore >= 7200)
		{
			// go through the high scores again
			theHighScoreMgr->SetHighScores(playerScore);

			// redo the scores to update the scoreboard
			vector<int> scores = theHighScoreMgr->GetHighScores();

			// delete the current textures
			theTextureMgr->deleteTexture("score1");
			theTextureMgr->deleteTexture("score2");
			theTextureMgr->deleteTexture("score3");

			// redo the new scores with updated textures
			string tempScore = "1. " + to_string(scores[0]);
			theTextureMgr->addTexture("score1", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, tempScore.c_str(), textType::solid, { colourVal, colourVal, colourVal,255 }, { 0, 0, 0, 0 }));
			tempScore = "2. " + to_string(scores[1]);
			theTextureMgr->addTexture("score2", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, tempScore.c_str(), textType::solid, { colourVal, colourVal, colourVal,255 }, { 0, 0, 0, 0 }));
			tempScore = "3. " + to_string(scores[2]);
			theTextureMgr->addTexture("score3", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, tempScore.c_str(), textType::solid, { colourVal, colourVal, colourVal,255 }, { 0, 0, 0, 0 }));

			// if the player choses to replay
			if (theGameState == gameState::playing) ResetGame();

			// go to the end screen
			theGameState = gameState::end;
		}

		// if the ball goes out of bounds
		if (ballSprite.outOfBounds)
		{
			// do the same as above with the high scores
			theHighScoreMgr->SetHighScores(playerScore);

			vector<int> scores = theHighScoreMgr->GetHighScores();

			theTextureMgr->deleteTexture("score1");
			theTextureMgr->deleteTexture("score2");
			theTextureMgr->deleteTexture("score3");

			string tempScore = "1. " + to_string(scores[0]);
			theTextureMgr->addTexture("score1", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, tempScore.c_str(), textType::solid, { colourVal, colourVal, colourVal,255 }, { 0, 0, 0, 0 }));
			tempScore = "2. " + to_string(scores[1]);
			theTextureMgr->addTexture("score2", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, tempScore.c_str(), textType::solid, { colourVal, colourVal, colourVal,255 }, { 0, 0, 0, 0 }));
			tempScore = "3. " + to_string(scores[2]);
			theTextureMgr->addTexture("score3", theFontMgr->getFont("ka1")->createTextTexture(theRenderer, tempScore.c_str(), textType::solid, { colourVal, colourVal, colourVal,255 }, { 0, 0, 0, 0 }));

			if (theGameState == gameState::playing) ResetGame();
			theGameState = gameState::end;
		}
	}
	break;

	case gameState::end:
	{
		// if the replay, quit or menu buttons are clicked, change the gamestate accordingly
		theGameState = theButtonMgr->getBtn("replay_btn")->update(theGameState, gameState::playing, theAreaClicked);
		theGameState = theButtonMgr->getBtn("quit_btn")->update(theGameState, gameState::exit, theAreaClicked);
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, gameState::menu, theAreaClicked);
		
	}
	break;

	case gameState::exit:
	{
		// end the game
		loop = false;
	}
	break;
	}

}

// controls for if the controller is connected
bool cGame::XInputControls(bool theLoop)
{
	// if moving left
	if (theXInput->l1Pressed)
	{
		// update paddle sprite variables
		paddleSprite.isGoingLeft = true;
		paddleSprite.hasMoved = true;
		// if the ball hasn't launched from the pad
		if (!(ballSprite.isMoving))
		{
			// update ball variable
			ballSprite.isGoingLeft = true;
		}
	}
	// if not moving left
	else
	{
		// update the isGoingLeft variables for both sprites
		paddleSprite.isGoingLeft = false;
		ballSprite.isGoingLeft = false;
	}

	// if going right 
	if (theXInput->r1Pressed)
	{
		// update paddleSprite variables
		paddleSprite.isGoingRight = true;
		paddleSprite.hasMoved = true;
		// is ball hasn't launched
		if (!(ballSprite.isMoving))
		{
			// move right with paddle
			ballSprite.isGoingRight = true;
		}
	}
	else
	{
		// update sprite variables
		paddleSprite.isGoingRight = false;
		ballSprite.isGoingRight = false;
	}

	// if A has been pressed, i.e. the ball has been launched
	if (theXInput->aPressed)
	{
		// launch the ball
		ballSprite.isMoving = true;
	}

	// if B is pressed
	if (theXInput->bPressed)
	{
		// exit the game 
		theLoop = false;
	}
	
	return theLoop;
}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	// in the controller is connected
	if (theXInput->controllerConnected)
	{
		// if b is pressed
		if (theXInput->bPressed)
		{
			// exit the game
			theLoop = false;
		}
	}

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}
		
		theAreaClicked = { 0,0 }; // set areaclicked back to nothing first otherwise a mouse click will persist after the update

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				theSoundMgr->getSnd("click")->play(0);
				theAreaClicked = { event.motion.x, event.motion.y };
			}
			break;
			case SDL_BUTTON_RIGHT:
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
			}
			break;
			case SDL_BUTTON_RIGHT:
				break;
			default:
				break;
			}
			break;
		default:
			break;
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
				theSoundMgr->getSnd("click")->play(0);
				cout << ballSprite.isMoving;
				break;

				// "cheat" for testing end screens
			case SDLK_q:
				playerScore = 7200;
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

void cGame::ResetGame()
{
	playerScore = 0;

	paddleSprite.setSpritePos({ (375 - ((theTextureMgr->getTexture("thePaddle")->getTWidth()) / 2)), 450 });
	paddleSprite.setTexture(theTextureMgr->getTexture("thePaddle"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("thePaddle")->getTWidth(), theTextureMgr->getTexture("thePaddle")->getTHeight());
	ballSprite.setSpritePos({ (375 - ((theTextureMgr->getTexture("theBall")->getTWidth()) / 2)), (450 - (theTextureMgr->getTexture("theBall")->getTHeight())) });
	ballSprite.setTexture(theTextureMgr->getTexture("theBall"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBall")->getTWidth(), theTextureMgr->getTexture("theBall")->getTHeight());

	ballSprite.outOfBounds = false;
	ballSprite.isMoving = false;

	int xPos = 40; // declare variables representing the size of each block
	int yPos = 20;

	for (int i = 0; i < 16; i++) // for each block in the 16x9 array 
	{
		for (int j = 0; j < 9; j++)
		{
			blocks[i][j].setSpritePos({ (i * xPos) + 55,(j*yPos) + 60 });  // position the block according to i and j values

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

