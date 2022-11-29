#pragma once
#include "piece.h"
class knight : public piece
{
public:
	knight(COLOR color);
	~knight();
public:
	wxString getDisplayText() override;
};

