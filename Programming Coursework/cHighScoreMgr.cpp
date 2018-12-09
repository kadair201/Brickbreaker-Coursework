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

vector<int> cHighScoreMgr::GetHighScores()
{
	cout << "Reading file" << endl;
	ifstream highScoresFile("Data\\HighScore.txt");
	string line;
	vector<int> highScores;

	if (highScoresFile.is_open())
	{
		while (getline(highScoresFile, line))
		{
			highScores.push_back(stoi(line));
			cout << line << endl;
		}
		highScoresFile.close();
	}

	cout << "Stop reading file" << endl;

	return highScores;
}

void cHighScoreMgr::SetHighScores(int newScore)
{
	vector<int> scores = GetHighScores();
	int position = scores.size();

	for (int i = (scores.size() - 1); i >= 0; i--) 
	{
		// if the new score is greater than the score at position i
		if (newScore > scores[i]) 
		{
			// set position to i
			position = i;
		}
	}

	// if the new score is on the board
	if (position != scores.size())
	{
		int newestScore = newScore;
		for (int i = position; i < scores.size(); i++)
		{
			int currentScore = scores[i];
			scores[i] = newestScore;
			newestScore = currentScore;
		}
	}

	ofstream highScores;
	highScores.open("Data\\HighScore.txt", ios::trunc);
	for (int i = 0; i < 3; i++)
	{
		highScores << scores[i] << endl;
	}
	highScores.close();
}

