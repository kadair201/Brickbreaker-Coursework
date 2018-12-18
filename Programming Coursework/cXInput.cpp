#include <iostream>
#include <Windows.h>
#include <XInput.h>
#include "cXInput.h"

using namespace std;

#pragma comment(lib, "XInput.lib")

void cXInput::CheckController() {
	
	// allow only one controller
#define XUSER_MAX_COUNT 1

	bool player[XUSER_MAX_COUNT];
	DWORD result;

	// find the status of the controller connection
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) 
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		result = XInputGetState(i, &state);

		// Check if the controller is connected
		if (result == ERROR_SUCCESS)
		{
			// if the controller is connected successfully
			player[i] = true;
			controllerConnected = true;
			cout << "Controller connected successfully" << endl;
		}
		else
		{
			// if the controller is not connected or disconnected mid-game
			player[i] = false;
			controllerConnected = false;
			cout << "Controller not connected" << endl;
		}

		// if the controller is connected, use these controls
		if (player[i])
		{
			XINPUT_STATE _controllerState;
			ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
			XInputGetState(i, &_controllerState);

			// controls for moving the paddle left
			if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				cout << "L1 pressed" << endl;
				l1Pressed = true;
			}
			else
			{
				l1Pressed = false;
			}

			// controls for moving the paddle right 
			if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				cout << "R1 pressed" << endl;
				r1Pressed = true;
			}
			else
			{
				r1Pressed = false;
			}

			// controls for launching the ball from the paddle (spacebar)
			if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				cout << "A pressed" << endl;
				aPressed = true;
			}
			else
			{
				aPressed = false;
			}

			// controls for exiting the game (esc)
			if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				bPressed = true;
				cout << "Exit" << endl;
			}
			else
			{
				bPressed = false;
			}
		}
	}
}

cXInput* cXInput::pInstance = NULL;

cXInput* cXInput::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cXInput();
	}
	return cXInput::pInstance;
}

cXInput::cXInput()
{
}
cXInput::~cXInput()
{
}