#pragma once
#include "Action.h"
class DeleteObjectAction :
	public Action
{
public:
	DeleteObjectAction(ApplicationManager *pApp);

	virtual void ReadActionParameters();
	virtual void Execute();

	~DeleteObjectAction();
};

