#pragma once

#include "Action.h"
class InputDiceValue :  public Action
{
	int Dice_Num;
public:
	InputDiceValue(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~InputDiceValue(void);
};

