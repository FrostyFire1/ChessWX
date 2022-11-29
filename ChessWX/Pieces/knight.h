#pragma once
#include "piece.h"
class knight : piece
{
public:
	knight();
	~knight();
public:
	wxString getDisplayText() override;
};

