#include "Snake.h"

Snake::Snake(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	if(endCellPos.VCell() > startCellPos.VCell())
	{
		this->endCellPos = endCellPos;
	}
	//else valid = false ;

	///TODO: Do the needed validation


}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer) 
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a snake. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a snake.Click to continue...");
	// 2- Apply the snake's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer,endCellPos);	
}

/*bool Snake::is_valid(){
	return valid ;
}*/
Snake::Snake() {

}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

void Snake::Save(ofstream& saveFile) {
	saveFile<<this->position.GetCellNum()<<"  "<<this->endCellPos.GetCellNum()<<'\n' ;
}
void Snake::Load(ifstream& loadFile, Grid* pGrid) {
	int startCellNum, endCellNum;
	loadFile >> startCellNum >> endCellNum;
	endCellPos = CellPosition::GetCellPositionFromNum(endCellNum);
	position = CellPosition::GetCellPositionFromNum(startCellNum);

	pGrid->RemoveObjectFromCell(position);
	pGrid->AddObjectToCell(this);
}
Snake::~Snake()
{
}
