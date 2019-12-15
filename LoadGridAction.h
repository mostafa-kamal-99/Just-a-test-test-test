#pragma once
#include "action.h"
class LoadGridAction :
	public Action
{
	string source ;
public:
	LoadGridAction(ApplicationManager* App);
	void ReadActionParameters() ;
	void Execute() ;
	~LoadGridAction(void);
};

