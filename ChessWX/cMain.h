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
	wxBoxSizer* gameBtn = nullptr;
	wxSizer* logo = nullptr;
	wxSizer* button = nullptr;
	wxButton* m_btn1 = nullptr;
	wxTextCtrl* m_txt1 = nullptr;
	wxListBox* m_list1 = nullptr;
	wxImage backgroundImg;
	wxBitmap backgroundImage, resized;
	int h = -1;
	int w = -1;
	GAME_STATE gameState;

	void onButtonClicked(wxCommandEvent& evt);
	void paintBackground(wxEraseEvent& evt);
	void paintBackground(wxSizeEvent& evt);
	void paintEvent(wxPaintEvent& evt);
	void paintNow();
	void render(wxDC& dc);
	void OnSize(wxSizeEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

