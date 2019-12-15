#include "CardSeven.h"

CardSeven ::CardSeven (const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (7 here)
}
CardSeven::CardSeven() {
	cardNumber = 7;
}
CardSeven ::~CardSeven (void)
{
}

void CardSeven::ReadCardParameters(Grid*pGrid)
{
}
void CardSeven ::Apply(Grid* pGrid, Player* pPlayer)
{
		
	 Card::Apply(pGrid,pPlayer) ;
	//int playernum= pGrid->get_currPlayerNumber();
	 // let the player be number 0 and after the dice is rolled it is 1
	 pGrid->AdvanceCurrentPlayer(); // now it is 2
	 pGrid->AdvanceCurrentPlayer(); // now it is 3
	 pGrid->AdvanceCurrentPlayer(); //now it returned to 0
	   
	 
}
void CardSeven::Save(ofstream& OutFile) {
	Card::Save(OutFile);
	OutFile << '\n';
}

void CardSeven::Load(ifstream& Infile, Grid* pGrid) {
	Card::Load(Infile, pGrid);

	pGrid->RemoveObjectFromCell(position);
	pGrid->AddObjectToCell(this);
}