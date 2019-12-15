#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h"

#include "Card.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardFive.h"
#include "CardSix.h" 
#include "CardSeven.h"
#include "CardNine.h"


#include "Player.h"
#include <fstream> 
Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
//		if(pNewObject->is_valid()){
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done 
	//	}
	//	else return false ;
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed
		delete CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{

			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			Ladder* x = CellList[i][j]->HasLadder() ;
			if(x) return x  ;
			
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{

	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

void Grid::SaveAll(ofstream& saveFile , ObjectType Obj ){
	switch(Obj){
		case LADDER :
		{
			int num_ladders = 0 ;
			for(int i = 0 ; i<NumHorizontalCells ; ++i){
				for(int j = 0 ; j<NumVerticalCells ; ++j){
					if(CellList[j][i]->HasLadder()) {
						++num_ladders; 
					}
				}
			}
			saveFile<<num_ladders<<'\n' ;
			for(int i = 0 ; i<NumHorizontalCells ; ++i){
				for(int j = 0 ; j<NumVerticalCells ; ++j){
					if(CellList[j][i]->HasLadder()) {
						CellList[j][i]->HasLadder()->Save(saveFile) ;
					}
				}
			}
		}
			break ;

		case SNAKE :
		{
			int num_snakes = 0 ;
			for(int i = 0 ; i<NumHorizontalCells ; ++i){
				for(int j = 0 ; j<NumVerticalCells ; ++j){
					if(CellList[j][i]->HasSnake()) {
						++num_snakes; 
					}
				}
			}
			saveFile<<num_snakes<<'\n' ;
			for(int i = 0 ; i<NumHorizontalCells ; ++i){
				for(int j = 0 ; j<NumVerticalCells ; ++j){
					if(CellList[j][i]->HasSnake()) {
						CellList[j][i]->HasSnake()->Save(saveFile) ;
					}
				}
			}
		}
			break ;

		case CARD :
		{
			int num_cards = 0 ;
			for(int i = 0 ; i<NumHorizontalCells ; ++i){
				for(int j = 0 ; j<NumVerticalCells ; ++j){
					if(CellList[j][i]->HasCard()) {
						++num_cards; 
					}
				}
			}
			saveFile<<num_cards<<'\n' ;
			for(int i = 0 ; i<NumHorizontalCells ; ++i){
				for(int j = 0 ; j<NumVerticalCells ; ++j){
					if(CellList[j][i]->HasCard()) {
						CellList[j][i]->HasCard()->Save(saveFile) ;
					}
				}
			}
		}
			break ;
	}
}
void Grid::LoadAll(ifstream& loadFile , ObjectType Obj ){
	switch (Obj) {
	case LADDER:
	{	int num_ladders = 0;
		loadFile >> num_ladders;
		for (int i = 0; i < num_ladders; ++i) {
			Ladder* NewLadder = new Ladder();
			NewLadder->Load(loadFile , this);
		}
	}
	break;

	case SNAKE:
	{
		int num_snakes = 0;
		loadFile >> num_snakes;
		for (int i = 0; i < num_snakes; ++i) {
			Snake* NewSnake = new Snake();
			NewSnake->Load(loadFile, this);
		}
		
	}


	case CARD:
	{	
		int num_cards = 0;
		loadFile >> num_cards ;
		for (int i = 0; i < num_cards; ++i) {
			int card_type;
			loadFile >> card_type;
			Card* NewCard = createSpecificCard(card_type) ;
			NewCard->Load(loadFile, this);
		}
	}
	break;


	}
}


Card* Grid::createSpecificCard(int x) {
	switch (x) {
	case 1:		return new CardOne();
				break;
	case 2:		return new CardTwo();
				break;
	/*case 3 :	return new CardThree();
				break;
	case 4 :	return new CardFour();
				break;*/
	case 5 :	return new CardFive();
				break;
	case 6 :	return new CardSix();
				break;
	case 7 :	return new CardSeven();
				break;
	//case 8 :
	//		break;
	case 9:		return new CardNine();
				break;
	/*case 10:
				break;
	case 11:
				break;
	case 12:
				break;
	case 13:
				break;
	case 14:
				break;/**/

	defualt:	return NULL;
				break;
	}
}

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}