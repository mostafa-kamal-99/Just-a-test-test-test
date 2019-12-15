#include "CardFive.h"

CardFive::CardFive(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 5; // set the inherited cardNumber data member with the card number (5 here)
}
CardFive::CardFive() {
	cardNumber = 5;
}
CardFive::~CardFive(void)
{
}
void CardFive::ReadCardParameters(Grid*pGrid)
{
}
void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{



	Card::Apply(pGrid,pPlayer) ;
	//////////////////////////////
	last_roll= pPlayer->GetJustRolledDiceNum ();
	pPlayer->Move (pGrid,last_roll);
}
void CardFive::Save(ofstream& OutFile) {
	Card::Save(OutFile);
	OutFile << '\n';
}

void CardFive::Load(ifstream& Infile, Grid* pGrid) {
	Card::Load(Infile, pGrid);

	pGrid->RemoveObjectFromCell(position);
	pGrid->AddObjectToCell(this);
}