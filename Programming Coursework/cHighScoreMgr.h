#ifndef _CHIGHSCOREMGR_H
#define _CHIGHSCOREMGR_H
#include "GameConstants.h"

// this code is from my coursemate Ruari McGhee, modified slightly
class cHighScoreMgr
{
private:
	static cHighScoreMgr* pInstance;

public:
	static cHighScoreMgr* getInstance();

	cHighScoreMgr();
	~cHighScoreMgr();

	vector<int> GetHighScores();
	void SetHighScores(int newHighScore);
};

#endif
