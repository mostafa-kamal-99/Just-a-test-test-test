#include "Card.h"


Card::Card(const CellPosition & pos) : GameObject(pos) // sets the cell position of the GameObject
{
}
Card::Card() {

}

void Card::SetCardNumber(int cnum)
{
	if (cnum>0 && cnum<15) cardNumber = cnum; // validation M.W
	
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{

	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	//pOut->DrawCardNumber (GameObject::position,cardNumber); L function D private bs L t7t B t callha asln f 5las
	pOut->DrawCell(GameObject::position,cardNumber);
}

void Card::ReadCardParameters(Grid * pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer) 
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}

void Card::Save(ofstream& OutFile) {
	OutFile << cardNumber << " " << position.GetCellNum();
}
void Card::Load(ifstream& Infile, Grid* pGrid) {
	int cellNum;
	Infile >> cellNum;
	position = CellPosition::GetCellPositionFromNum(cellNum);
}

Card::~Card()
{
}
