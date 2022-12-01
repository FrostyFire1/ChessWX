#pragma once
#include "cMain.h"
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, onButtonClicked)
    EVT_PAINT(paintEvent)
    EVT_SIZE(OnSize)
wxEND_EVENT_TABLE()

int arrIndex(int x, int y, int height) {
    return y * height + x;
}

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "SzAGHy", wxPoint(30,30), wxSize(1280,720)){
	wxInitAllImageHandlers();
    initVariables();


}

cMain::~cMain(){
    delete[] boardButtons;
}

void cMain::initVariables() {
    windowSizer = new wxBoxSizer(wxHORIZONTAL);
    initMenu();
    initGame();


    windowSizer->Add(menuSizer, 1, wxDEFAULT);
    windowSizer->Add(gameSizer, 2, wxDEFAULT);
    windowSizer->Hide(gameSizer);
    this->SetSizer(windowSizer);
    backgroundImg.LoadFile("img/background.png", wxBITMAP_TYPE_PNG);
}

void cMain::initMenu() {
    menuSizer = new wxBoxSizer(wxVERTICAL);
    newGameButton = new wxButton(this, 10001, "Nowa gra", wxDefaultPosition, wxSize(150, 60));
    newGameButton->SetBackgroundColour(wxColour(100, 200, 100));
    atomicChessButton = new wxButton(this, 10002, "Atomic Chess", wxDefaultPosition, wxSize(150, 60));
    atomicChessButton->SetBackgroundColour(wxColour(100, 100, 200));

    menuSizer->Add(0, 0, 5);
    menuSizer->Add(newGameButton, 2, wxDEFAULT, 10);
    menuSizer->Add(atomicChessButton, 2, wxDEFAULT, 10);
    menuSizer->Add(0, 0, 5);
}

void cMain::initGame() {
    gameSizer = new wxBoxSizer(wxVERTICAL);
    chessBoard = new wxGridSizer(8, 8, 0, 0);
    gameBoard = new board();
    boardButtons = new wxButton * [8 * 8]; //2D array, simulates chess board

    wxFont font = GetFont();
    font.SetPointSize(25);

    for (int x = 0; x < 8; x++) {

        for (int y = 0; y < 8; y++) {
             
            boardButtons[arrIndex(x,y,8)] = new wxButton(this, 20000 + (arrIndex(x,y,8)), "", wxDefaultPosition, wxSize(50, 50), wxNO_BORDER);
            boardButtons[arrIndex(x,y,8)]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::boardSelect, this); //bind cMain::boardSelect to button
            boardButtons[arrIndex(x,y,8)]->SetFont(font);

            if ((y + x) % 2) boardButtons[arrIndex(x,y,8)]->SetBackgroundColour(wxColor(158, 83, 14));
            else boardButtons[arrIndex(x,y,8)]->SetBackgroundColour(wxColor(191, 132, 78));

            chessBoard->Add(boardButtons[arrIndex(x,y,8)], 1, wxEXPAND | wxALL);
        }
    }
    renderBoard();
    gameSizer->Add(0, 0, 2); //Add spacing
    gameSizer->Add(chessBoard, 1, wxSHAPED, 0);
}

void cMain::boardSelect(wxCommandEvent& evt) {
    int trueId = evt.GetId() - 20000;
    int x = trueId % 8;
    int y = trueId / 8;
    evt.Skip();
}

void cMain::onButtonClicked(wxCommandEvent& evt){
    //windowSizer->Layout();
    windowSizer->Hide(menuSizer);
    windowSizer->Show(gameSizer);
    windowSizer->Layout();

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

void cMain::renderBoard() {
    for (int x = 0; x < gameBoard->width; x++) {
        for (int y = 0; y < gameBoard->height; y++) {
            wxString displayText = gameBoard->boardState[arrIndex(x, y, 8)]->getDisplayText();
            boardButtons[arrIndex(x, y, 8)]->SetLabel(displayText);
        }
    }

}
void cMain::OnSize(wxSizeEvent& event) {
    Refresh();
    //skip the event.
    event.Skip();
}

