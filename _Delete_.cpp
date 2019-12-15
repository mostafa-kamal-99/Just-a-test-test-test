#include "_Delete_.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"

DeleteObjectAction::DeleteObjectAction(ApplicationManager *pApp):Action(pApp)
{
}
void DeleteObjectAction::ReadActionParameters()
{
	//No parameters for this function
}

void DeleteObjectAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pGrid->PrintErrorMessage("Select game object to delete");
	
	CellPosition pCellpos = pIn->GetCellClicked() ;
	pGrid->RemoveObjectFromCell(pCellpos);
	pGrid->UpdateInterface();


	

}


DeleteObjectAction::~DeleteObjectAction()
{
}
