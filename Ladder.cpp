#include "Ladder.h"

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{   
	if( endCellPos.VCell() < startCellPos.VCell() ) {
		this->endCellPos = endCellPos ;
	}
	///TODO: Do the needed validation
}

/*bool Ladder::is_valid(){
	return valid ;
}*/

Ladder::Ladder() {
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...") ;
	pGrid->UpdatePlayerCell(pPlayer , endCellPos ) ;

	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

void Ladder::Save(ofstream& file) {
	file<<this->position.GetCellNum()<<"  "<<this->endCellPos.GetCellNum()<<'\n' ;
}
void Ladder::Load(ifstream& file , Grid* pGrid){
	int startCellNum, endCellNum ;
	file >> startCellNum >> endCellNum;
	endCellPos = CellPosition::GetCellPositionFromNum(endCellNum);
	position = CellPosition::GetCellPositionFromNum(startCellNum);

	pGrid->RemoveObjectFromCell(position);
	pGrid->AddObjectToCell(this);
}

Ladder::~Ladder()
{
}
