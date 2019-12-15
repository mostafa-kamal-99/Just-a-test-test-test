#include "LoadGridAction.h"
#include "Grid.h"
#include <fstream>
#include <iostream>

LoadGridAction::LoadGridAction(ApplicationManager* App) : Action(App)
{
}

void LoadGridAction::ReadActionParameters() {
	 pManager->GetGrid()->PrintErrorMessage("Loading a grid now , left-click and enter the name of the grid..(eg: grid_name.txt)") ;
	 source  =  pManager->GetGrid()->GetInput()->GetSrting(pManager->GetGrid()->GetOutput())  ;
}


void LoadGridAction::Execute(){
	ReadActionParameters() ;
	ifstream infile(source) ;
	bool was_successful = infile.is_open() ;
	Grid* pGrid = pManager->GetGrid();
	if(!was_successful){
		pGrid->PrintErrorMessage("Sorry! , Can't find or open the file you specified..click to continue") ;
		int x,y ;
		pGrid->GetInput()->GetPointClicked(x,y) ;
		return ;
	}

	pGrid->LoadAll(infile,LADDER) ;
	pGrid->LoadAll(infile,SNAKE) ;
	pGrid->LoadAll(infile,CARD) ;

	infile.close() ;

	pGrid->UpdateInterface();
	pGrid->PrintErrorMessage("Grid Loaded Successfully !! click to continue..") ;
	int x,y ;
	pGrid->GetInput()->GetPointClicked(x,y) ;
}

LoadGridAction::~LoadGridAction(void)
{
}
