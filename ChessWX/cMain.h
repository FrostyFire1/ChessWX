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
	enum WINDOW_STATE {
		MAIN_MENU,
		NEW_GAME
	};
	enum MOVE_STATE {
		WAITING_FOR_SELECTION,
		SELECTED,
		MAKE_MOVE,
	};
	WINDOW_STATE windowState;
	MOVE_STATE moveState = WAITING_FOR_SELECTION;
	board::Coords startPos,finalPos;

	wxBoxSizer* windowSizer = nullptr;
	wxBoxSizer* menuSizer = nullptr;
	wxButton* newGameButton = nullptr;
	wxButton* atomicChessButton = nullptr;

	wxBoxSizer* gameSizer = nullptr;
	wxGridSizer* chessBoard = nullptr;
	wxButton** boardButtons;
	wxStaticText* playerText;

	wxImage backgroundImg;
	wxBitmap resized;
	int h = -1;
	int w = -1;

	board* gameBoard = nullptr;
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
	void movePiece(board::Coords, board::Coords);
	void highlightValidMoves(std::vector<std::array<int, 2>>);
	wxDECLARE_EVENT_TABLE();
};

