#pragma once
#include "cMain.h"
#include <iostream>
#include <fstream>
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, onButtonClicked)
    EVT_BUTTON(10002, loadGame)
    EVT_BUTTON(10003, newGameAtomic)
    EVT_BUTTON(10004, saveGame)
    EVT_BUTTON(10005, resetGame)
    EVT_BUTTON(10006, mainMenuClick)
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
    buttonBGRemoved.LoadFile("img/bg.png", wxBITMAP_TYPE_PNG);
}

void cMain::initMenu() {
    menuSizer = new wxBoxSizer(wxVERTICAL);
    newGameButton = new wxButton(this, 10001, "Nowa gra", wxDefaultPosition, wxSize(150, 60));
    newGameButton->SetBackgroundColour(wxColour(100, 200, 100));
    loadGameButton = new wxButton(this, 10002, "Wczytaj gre", wxDefaultPosition, wxSize(150, 60));
    loadGameButton->SetBackgroundColour(wxColour(200, 100, 100));
    atomicChessButton = new wxButton(this, 10003, "Atomic Chess", wxDefaultPosition, wxSize(150, 60));
    atomicChessButton->SetBackgroundColour(wxColour(100, 100, 200));



    menuSizer->Add(0, 0, 5);
    menuSizer->Add(newGameButton, 2, wxDEFAULT, 10);
    menuSizer->Add(loadGameButton, 2, wxDEFAULT, 10);
    menuSizer->Add(atomicChessButton, 2, wxDEFAULT, 10);
    menuSizer->Add(0, 0, 5);
}

void cMain::initGame() {
    gameSizer = new wxBoxSizer(wxVERTICAL);
    gameplaySizer = new wxBoxSizer(wxHORIZONTAL);
    chessBoard = new wxGridSizer(8, 8, 0, 0);
    gameBoard = new board();
    boardButtons = new wxButton * [8 * 8]; //2D array, simulates chess board
    playerText = new wxStaticText(this, wxID_ANY, wxT("Current player: White"), wxPoint(0,0), wxSize(400, 60));

    saveGameButton = new wxButton(this, 10004, wxT("Zapisz gre"), wxDefaultPosition, wxSize(150,60));
    saveGameButton->SetBackgroundColour(wxColor(150, 100, 200));
    resetGameButton = new wxButton(this, 10005, wxT("Zrestartuj gre"), wxDefaultPosition, wxSize(150, 60));
    resetGameButton->SetBackgroundColour(wxColor(100, 200, 150));
    mainMenu = new wxButton(this, 10006, wxT("Wróć do menu"), wxDefaultPosition, wxSize(150, 60));
    mainMenu->SetBackgroundColour(wxColor(200, 150, 100));
    wxFont font = GetFont();
    font.SetPointSize(25);

    for (int x = 0; x < 8; x++) {

        for (int y = 0; y < 8; y++) {
             
            boardButtons[arrIndex(x,y,8)] = new wxButton(this, 20000 + (arrIndex(x,y,8)), "", wxDefaultPosition, wxSize(50, 50));
            boardButtons[arrIndex(x,y,8)]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::boardSelect, this); //bind cMain::boardSelect to button
            boardButtons[arrIndex(x,y,8)]->SetFont(font);

            chessBoard->Add(boardButtons[arrIndex(x,y,8)], 1, wxEXPAND | wxALL);
        }
    }
    renderBoard();
    playerText->SetBackgroundColour(wxColour(255, 255, 255));
    font.SetPointSize(18);
    playerText->SetFont(font);
    gameSizer->Add(0, 0, 1);
    initLegend();
    gameSizer->Add(saveGameButton, 1, wxALIGN_RIGHT, 0);
    gameSizer->Add(resetGameButton, 1, wxALIGN_RIGHT, 0);
    gameSizer->Add(mainMenu, 1, wxALIGN_RIGHT, 0);
    gameSizer->Add(0, 0, 3); //Add spacing

    gameplaySizer->Add(chessBoard, 1, wxSHAPED | wxALIGN_CENTER, 0);
    gameplaySizer->Add(playerText, 1, wxDEFAULT, 0);
    gameSizer->Add(gameplaySizer, 4, wxDEFAULT, 0);
}

void cMain::initLegend() {

    wxString legendText = "";
    legendText += wxT("Politechnika Krakowska/UJ - Pionek\n");
    legendText += wxT("EAiIB - Wieża\n");
    legendText += wxT("Wydział odlewnictwa - Skoczek\n");
    legendText += wxT("WWNiG - Goniec\n");
    legendText += wxT("WIET - Królowa\n");
    legendText += wxT("WIMiIP - Król\n");

    wxStaticText* legend = new wxStaticText(this, wxID_ANY, legendText);
    gameSizer->Add(legend, 1, wxALIGN_RIGHT, 10);
    
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
        std::vector<std::array<int, 2>> validMoves = gameBoard->validMoves(startPos);
        highlightValidMoves(validMoves);
    }

    else if (moveState == SELECTED) { //One of the pieces is already selected
        finalPos.x = x;
        finalPos.y = y;

        if (selectedPiece->color == curPlayer) {
            startPos.x = x;
            startPos.y = y;
            std::vector<std::array<int, 2>> validMoves = gameBoard->validMoves(startPos);
            renderBoard();
            highlightValidMoves(validMoves);
            return;
        }

        if (!(gameBoard->moveIsValid(startPos, finalPos))) { //Check if move is legal
            moveState = WAITING_FOR_SELECTION; //Move is illegal - let the player select their move again
            renderBoard();
            return;
        }

        movePiece(startPos, finalPos);
        moveState = WAITING_FOR_SELECTION;
        //Switch players
        if (curPlayer == WHITE) {
            curPlayer = BLACK;
        }
        else {
            curPlayer = WHITE;
        }
        setPlayerText();

    }
}

void cMain::setPlayerText() {
    std::string text = "";
    COLOR potentialLoser;
    if (curPlayer == WHITE) potentialLoser = BLACK;
    else potentialLoser = WHITE;
    bool isCheck = gameBoard->isCheck(potentialLoser);
    bool isMate = gameBoard->isMate(potentialLoser);
    bool isDraw = gameBoard->isDraw(potentialLoser);
    if (curPlayer == WHITE) {
        text = "Current player: White ";
    }
    else {
        text = "Current player: Black ";
    }
    if (!gameBoard->isAtomic) {
        if (isCheck) {
            text += "CHECK";
            PlaySound(L"audio/check.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
        if (isMate) {
            text = "CHECKMATE!";
            if (potentialLoser == WHITE) text += " White wins!";
            else text += " Black wins!";
        }
        else if (isDraw) {
            text = "STALEMATE!";
        }
    }
    else {
        if (!(gameBoard->hasKing(curPlayer))) {
            text = "GAME OVER!";
            if (curPlayer == WHITE) text += " Black wins!";
            else text += " White wins!";
        }
    }
    if (gameBoard->isAtomic) text += "\nYOU ARE PLAYING ATOMIC CHESS";
    playerText->SetLabelText(text);
}
void cMain::movePiece(board::Coords startPos, board::Coords finalPos) {
    gameBoard->move(startPos, finalPos);
    renderBoard();
}

void cMain::highlightValidMoves(std::vector<std::array<int,2>> validMoves) {
    for (std::array<int, 2> move : validMoves) {
        wxButton* highlightButton = boardButtons[arrIndex(move[0], move[1], 8)];
        highlightButton->SetBackgroundColour(wxColor(222, 25, 11));
    }
}

/*
------------------------------------------------------------------------------------------------------------
                                                BUTTON EVENTS
------------------------------------------------------------------------------------------------------------
*/
void cMain::onButtonClicked(wxCommandEvent& evt){
    //windowSizer->Layout();
    windowSizer->Hide(menuSizer);
    windowSizer->Show(gameSizer);
    windowSizer->Layout();

    evt.Skip();
}


void cMain::saveGame(wxCommandEvent& evt) {
    wxFileDialog saveFileDialog(this, _("Save txt file"), "", "", "txt files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        evt.Skip();
        return;// the user changed idea...
    }

    std::string gameState = gameBoard->getState();
    std::ofstream save;
    save.open(saveFileDialog.GetPath().ToStdString());
    save << gameState;
    if (curPlayer == WHITE) save << "white\n";
    else save << "black\n";
    save << gameBoard->isAtomic;
    save.close();

    evt.Skip();
}

void cMain::loadGame(wxCommandEvent& evt) {
    wxFileDialog openFileDialog(this, _("Open txt file"), "", "", "txt files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        evt.Skip();
        return;     // the user changed idea...
    }
    curPlayer = gameBoard->loadSave(openFileDialog.GetPath().ToStdString());
    setPlayerText();
    windowSizer->Hide(menuSizer);
    windowSizer->Show(gameSizer);
    windowSizer->Layout();
    renderBoard();
    evt.Skip();
}

void cMain::newGameAtomic(wxCommandEvent& evt) {
    gameBoard->isAtomic = true;
    setPlayerText();
    windowSizer->Hide(menuSizer);
    windowSizer->Show(gameSizer);
    windowSizer->Layout();
    evt.Skip();
}

void cMain::resetGame(wxCommandEvent& evt) {
    bool isAtomic = gameBoard->isAtomic;
    gameBoard = new board();
    gameBoard->isAtomic = isAtomic;
    curPlayer = WHITE;
    setPlayerText();
    renderBoard();
}

void cMain::mainMenuClick(wxCommandEvent& evt) {
    gameBoard = new board();
    curPlayer = WHITE;
    setPlayerText();
    renderBoard();
    windowSizer->Hide(gameSizer);
    windowSizer->Show(menuSizer);
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
            piece* curPiece = gameBoard->boardState[arrIndex(x, y, 8)];
            if (curPiece->type != PLACEHOLDER) {
                boardButtons[arrIndex(x, y, 8)]->SetBitmap(curPiece->getPieceImage());
            }
            else boardButtons[arrIndex(x, y, 8)]->SetBitmap(buttonBGRemoved);

            //wxString displayText = gameBoard->boardState[arrIndex(x, y, 8)]->getDisplayText();
            //boardButtons[arrIndex(x, y, 8)]->SetLabel(displayText);
            if ((y + x) % 2) boardButtons[arrIndex(x, y, 8)]->SetBackgroundColour(wxColor(158, 83, 14)); //Alternate the bg color
            else boardButtons[arrIndex(x, y, 8)]->SetBackgroundColour(wxColor(191, 132, 78));
        }
    }

}
void cMain::OnSize(wxSizeEvent& event) {
    Refresh();
    //skip the event.
    event.Skip();
}
