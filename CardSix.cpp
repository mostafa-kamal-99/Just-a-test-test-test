#include "CardSix.h"

CardSix::CardSix(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (6 here)
}
CardSix::CardSix() {
	cardNumber = 6;
}
CardSix::~CardSix(void)
{
}
void CardSix::ReadCardParameters(Grid*pGrid)
{
}
void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer) ;
	//////////////////////////////
	last_roll= pPlayer->GetJustRolledDiceNum ();
	//last_roll=0-last_roll;
	pPlayer->Move (pGrid,-last_roll);
}
void CardSix::Save(ofstream& OutFile) {
	Card::Save(OutFile);
	OutFile << '\n';
}

void CardSix::Load(ifstream& Infile, Grid* pGrid) {
	Card::Load(Infile, pGrid);

	pGrid->RemoveObjectFromCell(position);
	pGrid->AddObjectToCell(this);
}