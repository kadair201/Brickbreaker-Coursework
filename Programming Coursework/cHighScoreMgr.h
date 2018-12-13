#ifndef _CHIGHSCOREMGR_H
#define _CHIGHSCOREMGR_H
#include "GameConstants.h"

// this code is from my coursemate Ruari McGhee, modified slightly
class cHighScoreMgr
{
private:
	// initialise instance
	static cHighScoreMgr* pInstance;

public:
	// initialise methods, variables and vector
	static cHighScoreMgr* getInstance();

	cHighScoreMgr();
	~cHighScoreMgr();

	vector<int> GetHighScores();
	void SetHighScores(int newHighScore);
};

#endif
