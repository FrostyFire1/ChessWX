#pragma once
#include "Pieces/piece.h"
#include "Pieces/pawn.h"
#include "Pieces/rook.h"
#include "Pieces/knight.h"
#include "Pieces/bishop.h"
#include "Pieces/queen.h"
#include "Pieces/king.h"
class board {

public:
	board();
	~board();

public:
	int pos1 = -1, pos2 = -1, width, height;
	piece** boardState;
	
	void initEmpty();
	void initBoard();
	void initPawns();
	void initMaterial(COLOR color);
	void move(int, int);
	int arrIndex(int, int);
};