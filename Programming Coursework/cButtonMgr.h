
/*
==========================================================================
cButtonMgr.h
==========================================================================
*/


#ifndef _BUTTONMGR_H
#define _BUTTONMGR_H

// OpenGL Headers
#include "GameConstants.h"
#include "cButton.h"


using namespace std;

class cButtonMgr
{
private:
	// initialise instance
	static cButtonMgr* pInstance;

protected:
	// initialise methods
	cButtonMgr();
	~cButtonMgr();
	map <LPCSTR, cButton*> gameBtns;

public:
	// initialise methods and variables
	void add(LPCSTR btnName, cButton* theBtn);
	cButton* getBtn(LPCSTR btnName);
	void deleteBtn();
	static cButtonMgr* getInstance();
};
#endif
