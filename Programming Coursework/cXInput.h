#ifndef _CXINPUT_H
#define _CXINPUT_H

class cXInput
{
private:
	
	static cXInput* pInstance;

public:
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
