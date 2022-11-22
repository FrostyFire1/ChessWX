#pragma once
#include "wx/wx.h"
#include "wx/bitmap.h"
#include "wx/event.h"
#include "wxImagePanel.h"

class cMain : public wxFrame{
typedef wxEvtHandler Inherited;
public:
	cMain();
	~cMain();

public:
	enum GAME_STATE {
		MAIN_MENU,
		NEW_GAME
	};
	
	wxBoxSizer* windowSizer = nullptr;
	wxButton* newGameButton = nullptr;
	wxButton* atomicChessButton = nullptr;
	wxPanel* buttonWrapper = nullptr;
	GAME_STATE gameState;

	wxImage backgroundImg;
	wxBitmap resized;
	int h = -1;
	int w = -1;

	void onButtonClicked(wxCommandEvent& evt);
	void paintEvent(wxPaintEvent& evt);
	void paintNow();
	void render(wxDC& dc);
	void OnSize(wxSizeEvent& evt);
	void initVariables();

	wxDECLARE_EVENT_TABLE();
};

