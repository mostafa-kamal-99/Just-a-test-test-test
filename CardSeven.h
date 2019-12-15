#pragma once

#include "Card.h"



class CardSeven :	public Card
{
	
public:
	CardSeven (const CellPosition & pos); // A Constructor takes card position
	CardSeven();

	virtual void ReadCardParameters(Grid*pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer); 

	void Save(ofstream& OutFile);
	void Load(ifstream& Infile, Grid* pGrid);

	virtual ~CardSeven (); // A Virtual Destructor
};

