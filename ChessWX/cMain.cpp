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
    playerText = new wxStaticText(this, wxID_ANY, wxT("Current player: White"), wxPoint(0,0), wxSize(400, 60));
    wxFont font = GetFont();
    font.SetPointSize(25);

    for (int x = 0; x < 8; x++) {

        for (int y = 0; y < 8; y++) {
             
            boardButtons[arrIndex(x,y,8)] = new wxButton(this, 20000 + (arrIndex(x,y,8)), "", wxDefaultPosition, wxSize(50, 50), wxNO_BORDER);
            boardButtons[arrIndex(x,y,8)]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::boardSelect, this); //bind cMain::boardSelect to button
            boardButtons[arrIndex(x,y,8)]->SetFont(font);

            if ((y + x) % 2) boardButtons[arrIndex(x,y,8)]->SetBackgroundColour(wxColor(158, 83, 14)); //Alternate the bg color
            else boardButtons[arrIndex(x,y,8)]->SetBackgroundColour(wxColor(191, 132, 78));

            chessBoard->Add(boardButtons[arrIndex(x,y,8)], 1, wxEXPAND | wxALL);
        }
    }
    renderBoard();
    playerText->SetBackgroundColour(wxColour(255, 255, 255));
    playerText->SetFont(font);
    gameSizer->Add(playerText, 1, wxALIGN_RIGHT, 0);
    gameSizer->Add(0, 0, 3); //Add spacing
    gameSizer->Add(chessBoard, 2, wxSHAPED, 0);
}

void cMain::boardSelect(wxCommandEvent& evt) {
    int trueId = evt.GetId() - 20000;
    int x = trueId % 8;
    int y = trueId / 8;
    handleSelection(x,y);
    evt.Skip();
}

void cMain::handleSelection(int x, int y) {
    piece* selectedPiece = gameBoard->boardState[arrIndex(x, y, 8)];
    //current player is represented by the COLOR enum. comparing it to the selected piece's color verifies that this is the player's piece
    if (moveState == WAITING_FOR_SELECTION && curPlayer == selectedPiece->color) { //Player selected a valid piece
        startPos.x = x;
        startPos.y = y;
        moveState = SELECTED;

    }

    else if (moveState == SELECTED) { //One of the pieces is already selected
        finalPos.x = x;
        finalPos.y = y;
        if (!(gameBoard->moveIsValid(startPos, finalPos))) { //Check if move is legal
            moveState = WAITING_FOR_SELECTION; //Move is illegal - let the player select their move again
            return;
        }

        movePiece(startPos, finalPos);
        moveState = WAITING_FOR_SELECTION;
        //Switch players
        if (curPlayer == WHITE) {
            curPlayer = BLACK; 
            playerText->SetLabelText("Current player: Black");
        }
        else {
            curPlayer = WHITE;
            playerText->SetLabelText("Current player: White");
        }
    }
}

void cMain::movePiece(board::Coords startPos, board::Coords finalPos) {
    gameBoard->move(startPos, finalPos);
    renderBoard();
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

