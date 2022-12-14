#pragma once
#include "util.h"
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
	bool isAtomic;

	std::string getState();
	COLOR loadSave(std::string);
	void initEmpty();
	void initBoard();
	void initPawns();
	void initMaterial(COLOR color);
	bool moveIsValid(Coords, Coords);
	bool canCastle(piece*, Coords, Coords);
	void move(Coords, Coords);
	void moveAtomic(Coords, Coords);
	void annihilate(Coords);

	void handlePawn(piece*, Coords, Coords);
	void checkEnPassant(piece*, Coords);
	void castle(piece*, Coords);
	bool isCheck(COLOR);
	bool isMate(COLOR);
	bool isDraw(COLOR);
	bool onlyKingsLeft();
	bool hasKing(COLOR);
	Coords findKing(COLOR);
	std::vector<std::array<int, 2>> validMoves(Coords);

	std::vector<std::array<int, 2>> validMovesAtomic(Coords);
	bool containsOwnKing(std::array<int, 2>, COLOR);
	int arrIndex(Coords);
};