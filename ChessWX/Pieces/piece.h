#pragma once
#include <string>
#include "wx/wx.h"
#include "../util.h"
#include <array>
enum COLOR {
	WHITE,
	BLACK,
	UNKNOWN,
};
enum TYPE {
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING,
	PLACEHOLDER,
};
class piece {
public:
	piece(COLOR color);
	~piece();
public:
	virtual wxString getDisplayText(); //virtual methods can be overriden, great for "downcasting"
	virtual std::vector<std::array<int, 2>> generateMoves(piece**, piece*, int, int);
	virtual wxBitmap getPieceImage();
	int arrIndex(int, int, int);
	wxString displayTextWhite, displayTextBlack;
	wxBitmap pieceImageWhite, pieceImageBlack;
	int lastMoveDistance;
	bool hasMoved;
	TYPE type;
	COLOR color;
};