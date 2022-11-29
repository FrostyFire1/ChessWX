#pragma once
#include "piece.h"
class knight : piece
{
public:
	knight(COLOR color);
	~knight();
public:
	wxString getDisplayText() override;
};

