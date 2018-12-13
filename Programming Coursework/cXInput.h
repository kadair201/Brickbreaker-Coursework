#ifndef _CXINPUT_H
#define _CXINPUT_H

class cXInput
{
private:
	// initialise instance
	static cXInput* pInstance;

public:
	// initialise methods and variables
	static cXInput* getInstance();

	cXInput();
	~cXInput();

	void CheckController();

	bool controllerConnected;
	bool l1Pressed;
	bool r1Pressed;
	bool bPressed;
	bool aPressed;
};

#endif
