//Universidade Estadual do Rio Grande do Sul
//Trabalho final da disciplina de Programação Orientada a Objetos
//Grupo 4 - Estudantes:
//André Hartwig
//Fernando Augusto Caletti de Barros
//Leonardo
//Vanderson
// #ifndef MAIN_BWINGULL_CPP
// #define MAIN_BWINGULL_CPP

#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/listbox.h>

#include <stdio.h>
#include <vector>

#include "src/lib/rota/rota.h"
#include "src/frames/rota-form-frame/rota-form-frame.cpp"

using namespace std;

#define INTERVALO_ATUALIZACAO_TELA 300 //ms

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
        void UpdateBtnCallback(wxCommandEvent& event);
        void BrowseBtnCallback(wxCommandEvent& event);
        void PushToRouteList();
        void AtualizaTelaEvent(wxTimerEvent& event);
        mutex* ListaRotasMutex;
        vector<Rota*>* Rotas = new vector<Rota*>();
        int IdAtualRotas = 1;
        bool DeveAtualizarTela = false;

        DECLARE_EVENT_TABLE()

    private:
        void OnHello(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnCloseFormWindow(wxCloseEvent& event);
        // void UpdateRouteVisualizationTask();
        
        wxTextCtrl *LogTxtCtrl;
        wxListBox *RouteListBox;
        wxButton *AddBtn;
        wxButton *RemoveBtn;
        wxButton *UpdateBtn;
        wxButton *OpenInBrowserBtn;

        vector<Rota*>* UltimasRotasRenderizadas;

        RotaFormFrame* rotaForm;
        wxTimer AtualizaTelaTimer;
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

// void UpdateRouteVisualizationTask(MyFrame& frameObject);

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
    EVT_BUTTON ( ID_UPDATE_BTN, MyFrame::UpdateBtnCallback ) // Tell the OS to run test method onclick btn 4
    EVT_BUTTON ( ID_OPEN_IN_BROWSER_BTN, MyFrame::BrowseBtnCallback ) // Tell the OS to run test method onclick btn 190
END_EVENT_TABLE() // The button is pressed


void testeFunc()
{

}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Gerenciador de Rotas UERGS - POO 2022/2", wxDefaultPosition, wxSize(500, 500))
{
    //Rotas = new vector<Rota*>();

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

    ListaRotasMutex = new mutex();
    //AtualizaVisualizacaoThread = new thread(UpdateRouteVisualizationTask, ref(*this));
    AtualizaTelaTimer.Bind(wxEVT_TIMER, &MyFrame::AtualizaTelaEvent, this);
    AtualizaTelaTimer.Start(INTERVALO_ATUALIZACAO_TELA);
}

void MyFrame :: AddBtnCallback(wxCommandEvent& event)
{
    // ADICIONA ROTA DIRETAMENTE AO ARRAY
    // AtualizaTelaTimer.Stop();
    // ostringstream strBuff;
    // strBuff << "\nAdicionando rota - id: " << this->IdAtualRotas;
    // this->LogTxtCtrl->AppendText(strBuff.str());
    // Rotas->push_back(new Rota(this->IdAtualRotas++));
    // AtualizaTelaTimer.Start(INTERVALO_ATUALIZACAO_TELA);
    // //PushToRouteList();
    // this->DeveAtualizarTela = true;

    // if(this->rotaForm != nullptr)
    //     delete this->rotaForm;

    this->rotaForm = new RotaFormFrame(this->Rotas, &this->IdAtualRotas, &this->DeveAtualizarTela);
    this->rotaForm->Show();
}

void MyFrame :: AtualizaTelaEvent(wxTimerEvent& event)
{
    if(this->DeveAtualizarTela)
        this->PushToRouteList();
}

void MyFrame :: RemoveBtnCallback(wxCommandEvent& event)
{
    wxArrayInt selectedIndexes;
    int numberOfSelections = this->RouteListBox->GetSelections(selectedIndexes);
    for (int i = 0; i < numberOfSelections; i++)
    {
        ostringstream strBuff;
        strBuff << "\nRemovendo rota " << Rotas->at(selectedIndexes[i])->GetId();
        this->LogTxtCtrl->AppendText(strBuff.str());
        Rotas->erase(Rotas->begin() + (int)selectedIndexes[i]);
    }
    this->DeveAtualizarTela = true;
    //this->PushToRouteList();
}

void MyFrame :: UpdateBtnCallback(wxCommandEvent& event)
{
    // if(this->rotaForm != nullptr)
    //     delete this->rotaForm;

    wxArrayInt selectedIndexes;
    int numberOfSelections = this->RouteListBox->GetSelections(selectedIndexes);
    if(numberOfSelections <= 0)
        return;

    Rota* rotaSelecionada = this->Rotas->at(selectedIndexes[0]);
    
    cout << "Rota encontrada. Iniciando form..." << endl;
    this->rotaForm = new RotaFormFrame(this->Rotas, rotaSelecionada, &this->DeveAtualizarTela);
    this->rotaForm->Show();
}

bool tonclose(bool flag, int data)
{
    cout << "teste binding external -- " << flag << " - " << data << endl;
    return true;
}

void MyFrame :: BrowseBtnCallback(wxCommandEvent& event)
{
    cout << "browse button!" << endl;
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
    wxString* stringData = new wxString[Rotas->size()];

    // if(UltimasRotasRenderizadas == nullptr)
    //     UltimasRotasRenderizadas = new vector<Rota*>();

    // if(UltimasRotasRenderizadas->size() > 0)
    // {
    //     delete UltimasRotasRenderizadas;
    //     UltimasRotasRenderizadas = new vector<Rota*>();
    // }

    for (int i = 0; i < Rotas->size(); i++)
    {
        // UltimasRotasRenderizadas->push_back(Rotas->at(i));
        stringData[i] = Rotas->at(i)->toString();
    }

    // cout << "Finalizado push para list - diff: " << this->DeveAtualizarTela() << endl;
    
    this->RouteListBox->Clear();

    if(Rotas->size() > 0) 
    {
        this->RouteListBox->InsertItems(Rotas->size(), stringData, 0);
    }

    this->DeveAtualizarTela = false;
}

// #endif