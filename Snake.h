#pragma once

#include "Gameobject.h"

class Snake :  public GameObject // inherited from GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the ladder's "Start Cell Position"

	CellPosition endCellPos; // here is the snake's End Cell Position


public:

	Snake(const CellPosition & startCellPos, const CellPosition & endCellPos); // A constructor for initialization
	Snake();

	virtual void Draw(Output* pOut) const; // Draws a ladder from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the ladder by moving player to ladder's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member
	//bool is_valid() ;
	
	void Save(ofstream& saveFile) ;
	void Load(ifstream& loadFile, Grid* pGrid) ;
	virtual ~Snake(); // Virtual destructor
};

