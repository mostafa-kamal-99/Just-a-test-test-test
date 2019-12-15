#pragma once

#include "Card.h"


class CardFive :	public Card
{
	int last_roll;

public:
	CardFive(const CellPosition & pos); // A Constructor takes card position
	CardFive();
	
	virtual void ReadCardParameters(Grid*pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	                                                 
	void Save(ofstream& OutFile);
	void Load(ifstream& Infile, Grid* pGrid);

	virtual ~CardFive(); // A Virtual Destructor
};

