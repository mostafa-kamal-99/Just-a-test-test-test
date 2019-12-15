#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;

	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	if(wallet >=0)
		this->wallet = wallet;
	// Make any needed validations
	else
		wallet=0;
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}
//========================================================================//
//                  KAREEM DEFINED THESE SETTERS/GETTERS                  //
//========================================================================//
void Player::SetTurnCount(int rturncount)
{
	if(rturncount < 0)
		turnCount=0;
	turnCount=rturncount;
}
void Player::SetStepCount(int rstepcount)
{
	if(rstepcount<=0)
		stepCount=1;
	else
	stepCount=rstepcount;
}
int Player::GetStepCount() const
{
	return stepCount;
}
void Player::SetJustRolledDiceNum(int rjustRolledDiceNum )
{
	if(rjustRolledDiceNum <= 0 || rjustRolledDiceNum> 6 )
	justRolledDiceNum=0;
	else
	justRolledDiceNum=rjustRolledDiceNum;
}
int Player::GetJustRolledDiceNum() const
{
	return justRolledDiceNum;
}
//=======================================================================//
//*****************00000000000000<<<|*|>>>00000000000000*****************//
//=======================================================================//

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];


	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut->DrawPlayer(pCell->GetCellPosition(),playerNum,playerColor);

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;


	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(),playerNum,cellColor);

}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	turnCount++;

	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	if(turnCount>0 && turnCount%3==0)
	{
		//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
		wallet=wallet+10*diceNumber;
		turnCount=0;
		return;
	}

	// 3- Set the justRolledDiceNum with the passed diceNumber
	justRolledDiceNum=diceNumber;

	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"
	int pos=pCell->GetCellPosition().GetCellNumFromPosition( pCell->GetCellPosition());
	pos=pos+diceNumber;

	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell( this,pCell->GetCellPosition().GetCellPositionFromNum(pos));

	// 6- Apply() the game object of the reached cell (if any)
	if(  dynamic_cast<GameObject*> (pCell->GetGameObject() )   )
		pCell->GetGameObject()->Apply(pGrid,this);

	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	if(stepCount==99)
	{
		pGrid->SetEndGame(true);
	}

}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}