#include "InputDiceValue.h"

#include "Grid.h"
#include "Player.h"


InputDiceValue::InputDiceValue(ApplicationManager *pApp): Action(pApp)
{

}

void InputDiceValue::ReadActionParameters() 
{

}

void InputDiceValue::Execute()
{

	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Enter your Dice Number: ");
	int diceNumber=pIn->GetInteger(pOut);

	if(diceNumber<=0 || diceNumber>6)
	{	
		pGrid->PrintErrorMessage("Invalid Dice Value ! , click to continue..") ;
		int x , y; 
		pIn->GetPointClicked(x,y) ;
		return ;
	}
	///TODO: Make the needed validations on the read parameters
	pGrid->GetCurrentPlayer();

	pGrid->GetCurrentPlayer()->Move(pGrid,diceNumber);

	pGrid->AdvanceCurrentPlayer();


	// Clear messages
	pOut->ClearStatusBar();

}

InputDiceValue::~InputDiceValue(void)
{
}
