#pragma once

#include "Card.h"


class CardSix :	public Card
{
	int last_roll;

public:
	CardSix(const CellPosition & pos); // A Constructor takes card position
	CardSix();
	virtual void ReadCardParameters(Grid*pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	 
	void Save(ofstream& OutFile);
	void Load(ifstream& Infile, Grid* pGrid);
	virtual ~CardSix(); // A Virtual Destructor
};

