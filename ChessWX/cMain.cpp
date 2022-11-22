#pragma once
#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, onButtonClicked)
	//EVT_ERASE_BACKGROUND(paintBackground)
    EVT_PAINT(paintEvent)
    EVT_SIZE(OnSize)
wxEND_EVENT_TABLE()



cMain::cMain() : wxFrame(nullptr, wxID_ANY, "SzAGHy", wxPoint(30,30), wxSize(1280,720)){
	wxInitAllImageHandlers();
 
	windowSizer = new wxBoxSizer(wxVERTICAL);
    logo = new wxBoxSizer(wxHORIZONTAL);
    button = new wxBoxSizer(wxHORIZONTAL);
    gameBtn = new wxBoxSizer(wxHORIZONTAL);
    wxButton* gameButton = new wxButton(this,wxID_ANY,  "????", wxDefaultPosition, wxDefaultSize);
    m_btn1 = new wxButton(this, 10001, "Nowa gra", wxPoint(0, 100), wxSize(100, 60));
    m_btn1->SetBackgroundColour(wxColour(100, 200, 100));

    button->Add(m_btn1);
	windowSizer->Add(logo, 1, wxEXPAND, 10);
    windowSizer->Add(button, 1, wxEXPAND, 10);
    gameBtn->Add(gameButton, 1, wxEXPAND, 10);
    windowSizer->Add(gameBtn, 1, wxEXPAND, 10);
    windowSizer->Hide(gameBtn);

	this->SetSizer(windowSizer);
    backgroundImg.LoadFile("img/background.png", wxBITMAP_TYPE_PNG);
	backgroundImage.LoadFile("img/background.png", wxBITMAP_TYPE_PNG);

}

cMain::~cMain(){

}

void cMain::onButtonClicked(wxCommandEvent& evt){
	//m_list1->AppendString(m_txt1->GetValue());
	//m_txt1->SetValue("");
	//evt.Skip();
    windowSizer->Show(gameBtn);
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

void cMain::OnSize(wxSizeEvent& event) {
    Refresh();
    //skip the event.
    event.Skip();
}