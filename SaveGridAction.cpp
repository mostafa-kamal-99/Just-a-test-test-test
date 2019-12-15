#include "SaveGridAction.h"
#include "Grid.h"
#include <fstream>

SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp)
{
}
void SaveGridAction::ReadActionParameters(){
	pManager->GetGrid()->PrintErrorMessage("Saving the current grid , please left-click and enter the name of the saved grid..(eg: grid_name.txt)") ;
	destination = pManager->GetGrid()->GetInput()->GetSrting(pManager->GetGrid()->GetOutput()) ;
}
void SaveGridAction::Execute() {
	ReadActionParameters() ;
	ofstream outfile(destination) ;
	bool was_successful = outfile.is_open() ;
	if(!was_successful){
		pManager->GetGrid()->PrintErrorMessage("Sorry! , Can't find or open the file you specified..click to continue") ;
		int x,y ;
		(pManager->GetGrid()->GetInput())->GetPointClicked(x,y) ; 
		return ;
	}

	pManager->GetGrid()->SaveAll(outfile,LADDER) ;

	pManager->GetGrid()->SaveAll(outfile,SNAKE) ;

	pManager->GetGrid()->SaveAll(outfile,CARD) ;

	pManager->GetGrid()->PrintErrorMessage("Grid Saved Successfully !! click to continue..") ;
	int x,y ;
	(pManager->GetGrid()->GetInput())->GetPointClicked(x,y) ; 


}

SaveGridAction::~SaveGridAction(void)
{
}

