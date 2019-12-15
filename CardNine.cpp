#include "CardNine.h"

CardNine::CardNine (const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 9; // set the inherited cardNumber data member with the card number (9 here)
}
CardNine::CardNine() {
	cardNumber = 9;
}
CardNine ::~CardNine (void)
{

}

void CardNine::ReadCardParameters(Grid * pGrid)
{
	
	
	
	Output * pOut = (pGrid)->GetOutput();
	Input * pIn = (pGrid)->GetInput();
	
	pOut->PrintMessage("New CardNine: Enter a cell number ...");
	specific_cell= pIn->GetInteger(pOut);
	

	pOut->ClearStatusBar() ;
}
void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
		
	 Card::Apply(pGrid,pPlayer) ;
	 int currcell=( pPlayer->GetCell())->GetCellPosition().GetCellNum();
	 int distance = specific_cell-currcell;
	 pPlayer->Move(pGrid,distance);
	   
	 
}

void CardNine::Save(ofstream& OutFile) {
	Card::Save(OutFile);
	OutFile << " " << specific_cell << '\n';
}
void CardNine::Load(ifstream& Infile, Grid* pGrid) {
	Card::Load(Infile, pGrid);
	Infile >> specific_cell ;

	pGrid->RemoveObjectFromCell(position);
	pGrid->AddObjectToCell(this);
}
