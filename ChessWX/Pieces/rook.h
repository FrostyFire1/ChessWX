#pragma once
#include "piece.h"
class rook : piece{
public:
	rook();
	~rook();
public:
	wxString getDisplayText() override;
};

