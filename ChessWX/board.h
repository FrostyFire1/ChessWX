#pragma once
#include "Pieces/piece.h"
#include "Pieces/pawn.h"
class board {

public:
	board(int width, int height);
	~board();

public:
	int pos1 = -1, pos2 = -1, width, height;
	piece** boardState;
	
	void initEmpty();
	void initBoard();
	void initPawns();
	void initWhite();
	void initBlack();
};