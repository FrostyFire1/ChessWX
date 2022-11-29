#pragma once
#include <string>
#include "wx/wx.h"
enum COLOR {
	WHITE,
	BLACK
};
class piece {
public:
	piece();
	~piece();
public:
	virtual wxString getDisplayText(); //virtual methods can be overriden, great for "downcasting"
	wxString displayTextWhite, displayTextBlack;
	COLOR color;
};