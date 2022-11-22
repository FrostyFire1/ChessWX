#pragma once
#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, onButtonClicked)
    EVT_PAINT(paintEvent)
    EVT_SIZE(OnSize)
wxEND_EVENT_TABLE()



cMain::cMain() : wxFrame(nullptr, wxID_ANY, "SzAGHy", wxPoint(30,30), wxSize(1280,720)){
	wxInitAllImageHandlers();
    initVariables();


}

cMain::~cMain(){

}

void cMain::onButtonClicked(wxCommandEvent& evt){
    //windowSizer->Layout();
   
    evt.Skip();
}

// void cMain::paintBackground(wxEraseEvent& Event) {
//	wxDC* DC = Event.GetDC();
//	DC->DrawBitmap(backgroundImage, 0, 0, false);
//}



void cMain::paintEvent(wxPaintEvent& evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}

void cMain::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

void cMain::render(wxDC& dc)
{
    int neww, newh;
    dc.GetSize(&neww, &newh);

    if (neww != w || newh != h)
    {
        resized = wxBitmap(backgroundImg.Scale(neww, newh /*, wxIMAGE_QUALITY_HIGH*/));
        w = neww;
        h = newh;
        dc.DrawBitmap(resized, 0, 0, false);
    }
    else {
        dc.DrawBitmap(resized, 0, 0, false);
    }
}

void cMain::OnSize(wxSizeEvent& event) {
    Refresh();
    //skip the event.
    event.Skip();
}

void cMain::initVariables() {
    windowSizer = new wxBoxSizer(wxHORIZONTAL);
    menuSizer = new wxBoxSizer(wxVERTICAL);
    newGameButton = new wxButton(this, 10001, "Nowa gra", wxDefaultPosition, wxSize(150, 60));
    newGameButton->SetBackgroundColour(wxColour(100, 200, 100));
    atomicChessButton = new wxButton(this, 10002, "Atomic Chess", wxDefaultPosition, wxSize(150, 60));
    atomicChessButton->SetBackgroundColour(wxColour(100, 100, 200));

    menuSizer->Add(0, 0, 5);
    menuSizer->Add(newGameButton, 2, wxDEFAULT, 10);
    menuSizer->Add(atomicChessButton, 2, wxDEFAULT, 10);
    menuSizer->Add(0, 0, 5);

    gameSizer = new wxBoxSizer(wxVERTICAL);
    chessBoard = new wxGridSizer(8, 8, 0, 0);
    wxButton** boardButtons = new wxButton * [8 * 8];
    for (int x = 0; x < 8; x++) {

        for (int y = 0; y < 8; y++) {
            boardButtons[y * 8 + x] = new wxButton(this, 20000 + (y * 8 + x), "",wxDefaultPosition, wxSize(50, 50));
            chessBoard->Add(boardButtons[y * 8 + x], 1, wxEXPAND | wxALL);
        }
    }

    gameSizer->Add(0, 0, 2);
    gameSizer->Add(chessBoard, 1, wxSHAPED, 0);

    windowSizer->Add(menuSizer, 1, wxDEFAULT);
    windowSizer->Add(gameSizer, 2, wxDEFAULT);
    this->SetSizer(windowSizer);
    backgroundImg.LoadFile("img/background.png", wxBITMAP_TYPE_PNG);
}