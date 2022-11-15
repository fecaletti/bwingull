//Universidade Estadual do Rio Grande do Sul
//Trabalho final da disciplina de Programação Orientada a Objetos
//Grupo 4 - Estudantes:
//André Hartwig
//Fernando Augusto Caletti de Barros
//Leonardo
//Vanderson
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/listbox.h>

#include <stdio.h>
#include <vector>

#include "src/lib/rota/rota.h"
#include "src/frames/rota-form-frame/rota-form-frame.cpp"

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
        void BrowseBtnCallback(wxCommandEvent& event);
        void PushToRouteList();

        DECLARE_EVENT_TABLE()

    private:
        void OnHello(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnCloseFormWindow(wxCloseEvent& event);
        
        wxTextCtrl *LogTxtCtrl;
        wxListBox *RouteListBox;
        wxButton *AddBtn;
        wxButton *RemoveBtn;
        wxButton *UpdateBtn;
        wxButton *OpenInBrowserBtn;

        vector<Rota*>* Rotas;
        int IdAtualRotas = 1;

        RotaFormFrame* rotaForm;
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
    EVT_BUTTON ( ID_OPEN_IN_BROWSER_BTN, MyFrame::BrowseBtnCallback ) // Tell the OS to run test method onclick btn 190
END_EVENT_TABLE() // The button is pressed


MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Gerenciador de Rotas UERGS - POO 2022/2", wxDefaultPosition, wxSize(500, 500))
{
    this->Rotas = new vector<Rota*>();

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

    RouteListBox = new wxListBox(this, ID_ROUTE_LIST_BOX, wxPoint(250, 10), wxSize(240, 200));

        LogTxtCtrl = new wxTextCtrl(this, ID_LOG_TEXT_CONTROLLER,
      wxT(""), wxPoint(250, 220), wxSize(240, 200),
      wxTE_MULTILINE | wxTE_RICH | wxTE_READONLY, wxDefaultValidator, wxTextCtrlNameStr);
    
    AddBtn = new wxButton(this, ID_ADD_BTN, wxT("ADD"), wxPoint(30, 40), wxDefaultSize, 0);
    UpdateBtn = new wxButton(this, ID_UPDATE_BTN, wxT("UPDATE"), wxPoint(30, 70), wxDefaultSize, 0);
    RemoveBtn = new wxButton(this, ID_REMOVE_BTN, wxT("REMOVE"), wxPoint(30, 100), wxDefaultSize, 0);
    OpenInBrowserBtn = new wxButton(this, ID_OPEN_IN_BROWSER_BTN, wxT("BROWSE"), wxPoint(30, 130), wxDefaultSize, 0);
}

void MyFrame :: AddBtnCallback(wxCommandEvent& event)
{
    ostringstream strBuff;
    strBuff << "\nAdicionando rota - id: " << this->IdAtualRotas;
    this->LogTxtCtrl->AppendText(strBuff.str());
    this->Rotas->push_back(new Rota(this->IdAtualRotas++));
    PushToRouteList();
}

void MyFrame :: RemoveBtnCallback(wxCommandEvent& event)
{
    wxArrayInt selectedIndexes;
    int numberOfSelections = this->RouteListBox->GetSelections(selectedIndexes);
    for (int i = 0; i < numberOfSelections; i++)
    {
        ostringstream strBuff;
        strBuff << "\nRemovendo rota " << this->Rotas->at(selectedIndexes[i])->GetId();
        this->LogTxtCtrl->AppendText(strBuff.str());
        this->Rotas->erase(this->Rotas->begin() + (int)selectedIndexes[i]);
    }
    this->PushToRouteList();
}

bool tonclose(bool flag, int data)
{
    cout << "teste binding external -- " << flag << " - " << data << endl;
    return true;
}

void MyFrame :: BrowseBtnCallback(wxCommandEvent& event)
{
    this->Rotas->push_back(new Rota(this->IdAtualRotas++));
    this->rotaForm = new RotaFormFrame(this->Rotas->at(this->Rotas->size() - 1), &tonclose);
    this->rotaForm->Show();

    //Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnCloseFormWindow, this);
}

void MyFrame :: OnCloseFormWindow(wxCloseEvent& event)
{
    cout << "Closed route form!!" << endl;
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
    wxString* stringData = new wxString[this->Rotas->size()];
    for (int i = 0; i < this->Rotas->size(); i++)
    {
        stringData[i] = this->Rotas->at(i)->toString();
    }
    
    this->RouteListBox->Clear();

    if(this->Rotas->size() > 0)
        this->RouteListBox->InsertItems(this->Rotas->size(), stringData, 0);
}
