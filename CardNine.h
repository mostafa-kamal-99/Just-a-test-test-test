#pragma once

#include "Card.h"



class CardNine :	public Card
{
	
	int specific_cell;
public:
	CardNine (const CellPosition & pos); // A Constructor takes card position
	CardNine();

	virtual void ReadCardParameters(Grid * pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	
	void Save(ofstream& OutFile);                      // It is a virtual function (implementation depends on Card Type)
	void Load(ifstream& Infile, Grid* pGrid);
	virtual ~CardNine (); // A Virtual Destructor
};

