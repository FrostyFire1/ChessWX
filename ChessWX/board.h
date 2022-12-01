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
	struct Coords {
		int x;
		int y;
	};
	int pos1 = -1, pos2 = -1, width, height;
	piece** boardState;
	piece* lastMoved;
	void initEmpty();
	void initBoard();
	void initPawns();
	void initMaterial(COLOR color);
	void move(Coords, Coords);
	void checkEnPassant(piece*, Coords);
	bool moveIsValid(Coords, Coords);
	std::vector<std::array<int, 2>> validMoves(Coords, Coords);
	int arrIndex(Coords);
};