// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/listbox.h>

#include <stdio.h>
#include <vector>

#include "src/rota/rota.h"

using namespace std;



class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
};

class MyFrame : public wxFrame
{
    public:
        MyFrame();
        void AddBtnCallback(wxCommandEvent& event);
        void RemoveBtnCallback(wxCommandEvent& event);
        void PushToRouteList();
        DECLARE_EVENT_TABLE()

    private:
        void OnHello(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        
        wxTextCtrl *logTxtCtrl;
        wxListBox *routeListBox;
        wxButton *addBtn;
        wxButton *removeBtn;
        wxButton *updateBtn;
        wxButton *openInBrowserBtn;

        vector<Rota*>* rotas;
        int idAtualRotas = 1;
};

enum
{
    ID_Hello = 1,
    ID_ADD_BTN = 2,
    ID_REMOVE_BTN = 3,
    ID_UPDATE_BTN = 4,
    ID_OPEN_IN_BROWSER_BTN = 5,
    ID_LOG_TEXT_CONTROLLER = 6,
    ID_ROUTE_LIST_BOX = 7
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

BEGIN_EVENT_TABLE ( MyFrame, wxFrame )
    EVT_BUTTON ( ID_ADD_BTN, MyFrame::AddBtnCallback ) // Tell the OS to run test method onclick btn 189
    EVT_BUTTON ( ID_REMOVE_BTN, MyFrame::RemoveBtnCallback ) // Tell the OS to run test method onclick btn 190
END_EVENT_TABLE() // The button is pressed


MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Gerenciador de Rotas UERGS - POO 2022/2", wxDefaultPosition, wxSize(500, 500))
{
    this->rotas = new vector<Rota*>();

    wxMenu *menuFile = new wxMenu();
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    routeListBox = new wxListBox(this, ID_ROUTE_LIST_BOX, wxPoint(250, 10), wxSize(240, 200));

        logTxtCtrl = new wxTextCtrl(this, ID_LOG_TEXT_CONTROLLER,
      wxT(""), wxPoint(250, 220), wxSize(240, 200),
      wxTE_MULTILINE | wxTE_RICH | wxTE_READONLY, wxDefaultValidator, wxTextCtrlNameStr);
    
    addBtn = new wxButton(this, ID_ADD_BTN, wxT("ADD"), wxPoint(30, 40), wxDefaultSize, 0);
    updateBtn = new wxButton(this, ID_UPDATE_BTN, wxT("UPDATE"), wxPoint(30, 70), wxDefaultSize, 0);
    removeBtn = new wxButton(this, ID_REMOVE_BTN, wxT("REMOVE"), wxPoint(30, 100), wxDefaultSize, 0);
    openInBrowserBtn = new wxButton(this, ID_OPEN_IN_BROWSER_BTN, wxT("BROWSE"), wxPoint(30, 130), wxDefaultSize, 0);
}

void MyFrame :: AddBtnCallback(wxCommandEvent& event)
{
    ostringstream strBuff;
    strBuff << "\nAdicionando rota - id: " << this->idAtualRotas;
    this->logTxtCtrl->AppendText(strBuff.str());
    this->rotas->push_back(new Rota(this->idAtualRotas++));
    PushToRouteList();
}

void MyFrame :: RemoveBtnCallback(wxCommandEvent& event)
{
    wxArrayInt selectedIndexes;
    int numberOfSelections = this->routeListBox->GetSelections(selectedIndexes);
    for (int i = 0; i < numberOfSelections; i++)
    {
        ostringstream strBuff;
        strBuff << "\nRemovendo rota " << this->rotas->at(selectedIndexes[i])->GetId();
        this->logTxtCtrl->AppendText(strBuff.str());
        this->rotas->erase(this->rotas->begin() + (int)selectedIndexes[i]);
    }
    this->PushToRouteList();
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}
 
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets - teste!");
}

void MyFrame :: PushToRouteList()
{
    wxString* stringData = new wxString[this->rotas->size()];
    for (int i = 0; i < this->rotas->size(); i++)
    {
        stringData[i] = this->rotas->at(i)->toString();
    }
    
    this->routeListBox->Clear();

    if(this->rotas->size() > 0)
        this->routeListBox->InsertItems(this->rotas->size(), stringData, 0);
}