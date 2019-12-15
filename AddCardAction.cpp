#include "AddCardAction.h"
#include "Input.h"
#include "Output.h"
///////////////CARDS////////////// 
#include "Card.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
//#include "CardEight.h"
#include "CardNine.h"

AddCardAction::AddCardAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters() //M.W
{	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("please enter a card number");
	int cardNumberin= pIn->GetInteger(pOut);
	if (cardNumberin>0 && cardNumberin<15) cardNumber=cardNumberin;
	else cardNumber=-1;


	// 3- Read the "cardPosition" parameter (its cell position) and set its data member
	pOut->PrintMessage("please choose a cell");

	cardPosition=pIn->GetCellClicked();

	// 4- Make the needed validations on the read parameters
	// done ;
	// 5- Clear status bar
	pOut->ClearStatusBar() ;
}

void AddCardAction::Execute() //M.W
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	this->ReadActionParameters();
	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card * pCard = NULL; // will point to the card object type
	switch (cardNumber) // not completed
	{
	case 1: pCard = new CardOne(cardPosition); 
					break;
	case 2: pCard = new CardTwo(cardPosition); 
					break;
	case 5: pCard = new CardFive(cardPosition); 
					break;	 
	case 6: pCard = new CardSix(cardPosition);
					break;
	case 7: pCard = new CardSeven(cardPosition); 
					break;
	//case 8: pCard = new CardEight(cardPosition); break;
	case 9: pCard = new CardNine(cardPosition);
					break;
		// A- Add the remaining cases
		
	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		Grid* pGrid = pManager->GetGrid();
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();
		// A- We get a pointer to the Grid from the ApplicationManager
		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type

		pCard->ReadCardParameters( pGrid);

		// C- Add the card object to the GameObject of its Cell:

		bool obj_can_be_added = ( pGrid-> AddObjectToCell(pCard) );	

		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		if (obj_can_be_added) {
			pCard->Draw(pOut);
		}// pOut->DrawCell(cardPosition,cardNumber); same but we used Draw for the class responsiplities 
		//30/11->  fe problem eno m4 betb3 L rqm w ana m4 fahm hwa L mafrod ytb3 wl la2
		//1/12-> L error makn4 mnha kan bsbb en fe class L cell feh functions m4 kamla hya L responsible for saving the card number after updating
		else
		{

			( pGrid)->PrintErrorMessage("The cell is already ocupied by another object , please try another one !  press any key to containue");

		}



		// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

	}
}
