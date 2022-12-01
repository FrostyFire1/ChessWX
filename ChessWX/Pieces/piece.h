#pragma once
#include <string>
#include "wx/wx.h"
#include "../util.h"
enum COLOR {
	WHITE,
	BLACK,
	UNKNOWN,
};
class piece {
public:
	piece(COLOR color);
	~piece();
public:
	virtual wxString getDisplayText(); //virtual methods can be overriden, great for "downcasting"
	virtual std::vector<int[2]> generateMoves(piece**, int, int);
	int arrIndex(int, int, int);
	wxString displayTextWhite, displayTextBlack;
	COLOR color;
};