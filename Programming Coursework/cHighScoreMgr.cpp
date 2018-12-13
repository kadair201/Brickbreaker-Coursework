#include "cHighScoreMgr.h"
#include <fstream>

cHighScoreMgr* cHighScoreMgr::pInstance = NULL;

cHighScoreMgr* cHighScoreMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cHighScoreMgr();
	}
	return cHighScoreMgr::pInstance;
}

cHighScoreMgr::cHighScoreMgr()
{

}

cHighScoreMgr::~cHighScoreMgr()
{

}

// Some of the following code was given to me by coursemate Ruari McGhee
vector<int> cHighScoreMgr::GetHighScores()
{
	// open the high score file
	ifstream highScoresFile("Data\\HighScore.txt");
	// initialise a string variable to hold the file line contents
	string fileLine;
	// create a vector for the high scores
	vector<int> highScores;


	// read from the file 
	if (highScoresFile.is_open())
	{
		// go through each line and add the contents to the vector of high scores
		while (getline(highScoresFile, fileLine))
		{
			highScores.push_back(stoi(fileLine));
		}
		// close the file
		highScoresFile.close();
	}
	// return the highscores vector
	return highScores;
}

void cHighScoreMgr::SetHighScores(int newScore)
{
	// get the scores from the highscores vector in GetHighScores()
	vector<int> scoresVector = GetHighScores();
	// create variable for the position on the high score table
	int scorePosition = scoresVector.size();

	// scoresVector.size() = 3, as there are three positions on the table
	// subtract 1, since scoresVector is zero indexed
	for (int i = (scoresVector.size() - 1); i >= 0; i--) 
	{
		// if the new score is greater than the score at position i
		if (newScore > scoresVector[i]) 
		{
			// set position to i
			scorePosition = i;
		}
	}

	// if the new score is on the board, i.e. will be in space 0, 1 or 2 of the scores vector
	if (scorePosition != scoresVector.size())
	{
		// create a variable holding the new score
		int newestScore = newScore;
		// go through each position on the scoreboard
		for (int i = scorePosition; i < scoresVector.size(); i++)
		{
			// rearrange the scores to accommodate the new score
			int currentScore = scoresVector[i];
			scoresVector[i] = newestScore;
			newestScore = currentScore;
		}
	}

	// write this to the file
	ofstream highScores;
	highScores.open("Data\\HighScore.txt", ios::trunc);
	for (int i = 0; i < 3; i++)
	{
		highScores << scoresVector[i] << endl;
	}
	highScores.close();
}

