#pragma once

#include "Card.h"

// [ CardOne ] Summary:
// Its Apply() Function: increments the value of the passing player’s wallet by a value
// Its Parameters: The Wallet Value to increase --> put it as a "data member" and read it in ReadCardParameters()

class CardTwo :	public Card
{
	// CardTwo Parameters:
	int walletAmount; // the wallet value to increase from the player

public:
	CardTwo(const CellPosition & pos); // A Constructor takes card position
	CardTwo();
	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardTwo which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	                                                  // by incrementing the player's wallet by the walletAmount data member
	void Save(ofstream& OutFile);
	void Load(ifstream& Infile, Grid* pGrid);
	virtual ~CardTwo(); // A Virtual Destructor
};


