#pragma once
#include "wx/wx.h"
#include "wx/bitmap.h"
#include "wx/event.h"
#include "wxImagePanel.h"
#include "wx/grid.h"
#include "board.h"
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
	GAME_STATE gameState;

	wxBoxSizer* windowSizer = nullptr;
	wxBoxSizer* menuSizer = nullptr;
	wxButton* newGameButton = nullptr;
	wxButton* atomicChessButton = nullptr;

	wxBoxSizer* gameSizer = nullptr;
	wxGridSizer* chessBoard = nullptr;
	wxButton** boardButtons;
	wxImage backgroundImg;
	wxBitmap resized;
	int h = -1;
	int w = -1;

	board* gameBoard = nullptr;
	int desiredMove[2][2] = { {-1,-1},{-1,-1} };
	COLOR curPlayer = WHITE;

	void onButtonClicked(wxCommandEvent& evt);
	void paintEvent(wxPaintEvent& evt);
	void paintNow();
	void render(wxDC& dc);
	void renderBoard();
	void OnSize(wxSizeEvent& evt);
	void initVariables();
	void initMenu();
	void initGame();
	void boardSelect(wxCommandEvent& evt);
	void handleSelection(int, int);
	void movePiece(int[][2]);
	void resetDesiredMove();

	wxDECLARE_EVENT_TABLE();
};

