#pragma once
#include "action.h"
class SaveGridAction :
	public Action
{
	string destination ;
public:
	SaveGridAction(ApplicationManager* papp) ;
	void ReadActionParameters() ;
	void Execute() ;
	~SaveGridAction(void);
};

