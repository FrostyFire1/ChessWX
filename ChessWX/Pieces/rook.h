#pragma once
#include "piece.h"
class rook : piece{
public:
	rook(COLOR color);
	~rook();
public:
	wxString getDisplayText() override;
};

