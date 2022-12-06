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
	bool check;
	piece** boardState;
	piece* lastMoved;
	void initEmpty();
	void initBoard();
	void initPawns();
	void initMaterial(COLOR color);
	bool moveIsValid(Coords, Coords);
	void move(Coords, Coords);

	void handlePawn(piece*, Coords, Coords);
	void checkEnPassant(piece*, Coords);
	void castle(piece*, Coords);
	bool isCheck(COLOR);
	bool isMate(COLOR);
	bool isDraw(COLOR);
	std::vector<std::array<int, 2>> validMoves(Coords);
	int arrIndex(Coords);
};