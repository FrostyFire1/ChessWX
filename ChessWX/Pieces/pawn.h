#pragma once
#include "piece.h"
#include <string>
class pawn : public piece{
public:
	pawn();
	~pawn();
public:
	wxString getDisplayText() override;
};