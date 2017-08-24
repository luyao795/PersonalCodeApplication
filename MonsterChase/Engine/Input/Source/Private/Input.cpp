#include <Windows.h>
#include <stdio.h>
#include "Input.h"
#include "GLib.h"
#include "Point2D.h"

using namespace std;

namespace Engine
{
	bool Input::isAdown = false;
	bool Input::isDdown = false;
	bool Input::isSdown = false;
	bool Input::isWdown = false;
	bool Input::isQDown = false;

	Input::Input()
	{
		ResetState();
	}

	void Input::ResetState()
	{
		isAdown = false;
		isDdown = false;
		isSdown = false;
		isWdown = false;
		isQDown = false;
	}

	void Input::MoveKeyCallback(unsigned int i_VKeyID, bool bWentDown)
	{
		if (bWentDown)
		{
			ReadKey(i_VKeyID);
		}
		else
		{
			if (i_VKeyID == A)
				isAdown = false;
			if (i_VKeyID == D)
				isDdown = false;
			if (i_VKeyID == S)
				isSdown = false;
			if (i_VKeyID == W)
				isWdown = false;
			if (i_VKeyID == Q)
				isQDown = false;
		}
	}

	void Input::Read()
	{
		GLib::SetKeyStateChangeCallback(MoveKeyCallback);
	}

	void Input::ReadKey(char key)
	{
		if (key == A)
			isAdown = true;
		if (key == D)
			isDdown = true;
		if (key == S)
			isSdown = true;
		if (key == W)
			isWdown = true;
		if (key == Q)
			isQDown = true;
	}

	bool Input::IsDown(char key)
	{
		if (key == A)
			return isAdown;
		if (key == D)
			return isDdown;
		if (key == S)
			return isSdown;
		if (key == W)
			return isWdown;
		if (key == Q)
			return isQDown;
		else
			return false;
	}
}