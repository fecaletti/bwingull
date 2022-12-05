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
#include <fstream>
#include <string>
#include <regex>

#include "src/lib/rota/rota.h"
#include "src/frames/rota-form-frame/rota-form-frame.cpp"
#include "packages/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

#define INTERVALO_ATUALIZACAO_TELA_MS 300

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
        void ExportBtnCallback(wxCommandEvent& event);
        void ImportBtnCallback(wxCommandEvent& event);
        void ApplyFilterBtnCallback(wxCommandEvent& event);
        void ClearFilterBtnCallback(wxCommandEvent& event);
        void PushToRouteList();
        void AtualizaTelaEvent(wxTimerEvent& event);
        mutex* ListaRotasMutex;
        vector<Rota*>* Rotas = new vector<Rota*>();
        vector<Rota*>* RotasEmExibicao = Rotas;
        int IdAtualRotas = 1;
        bool DeveAtualizarTela = false;

        DECLARE_EVENT_TABLE()

    private:
        void Log(string data);
        void OnHello(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnCloseFormWindow(wxCloseEvent& event);
        
        wxTextCtrl *LogTxtCtrl;
        wxTextCtrl *FilterTxtCtrl;
        wxListBox *RouteListBox;
        wxButton *AddBtn;
        wxButton *RemoveBtn;
        wxButton *UpdateBtn;
        wxButton *OpenInBrowserBtn;
        wxButton *ExportJsonBtn;
        wxButton *ImportJsonBtn;
        wxButton *ApplyFilterBtn;
        wxButton *ClearFilterBtn;

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
    ID_ROUTE_LIST_BOX = 7,
    ID_EXPORT_BTN = 8,
    ID_IMPORT_BTN = 9,
    ID_FILTER_TEXT_CONTROLLER = 10,
    ID_APPLY_FILTER_BTN = 11,
    ID_CLEAR_FILTER_BTN = 12
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

BEGIN_EVENT_TABLE ( MyFrame, wxFrame )
    EVT_BUTTON ( ID_ADD_BTN, MyFrame::AddBtnCallback ) 
    EVT_BUTTON ( ID_REMOVE_BTN, MyFrame::RemoveBtnCallback ) 
    EVT_BUTTON ( ID_UPDATE_BTN, MyFrame::UpdateBtnCallback ) 
    EVT_BUTTON ( ID_OPEN_IN_BROWSER_BTN, MyFrame::BrowseBtnCallback ) 
    EVT_BUTTON ( ID_EXPORT_BTN, MyFrame::ExportBtnCallback ) 
    EVT_BUTTON ( ID_IMPORT_BTN, MyFrame::ImportBtnCallback ) 
    EVT_BUTTON ( ID_APPLY_FILTER_BTN, MyFrame::ApplyFilterBtnCallback ) 
    EVT_BUTTON ( ID_CLEAR_FILTER_BTN, MyFrame::ClearFilterBtnCallback )
END_EVENT_TABLE()

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Gerenciador de Rotas UERGS - POO 2022/2", wxDefaultPosition, wxSize(800, 500))
{
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

    RouteListBox = new wxListBox(this, ID_ROUTE_LIST_BOX, wxPoint(250, 10), wxSize(500, 200));

    LogTxtCtrl = new wxTextCtrl(this, ID_LOG_TEXT_CONTROLLER,
      wxT(""), wxPoint(250, 220), wxSize(500, 200),
      wxTE_MULTILINE | wxTE_RICH | wxTE_READONLY, wxDefaultValidator, wxTextCtrlNameStr);

    FilterTxtCtrl = new wxTextCtrl(this, ID_FILTER_TEXT_CONTROLLER,
      wxT("Buscar... (descricao)"), wxPoint(30, 280), wxSize(197, 25),
      wxTE_RICH, wxDefaultValidator, wxTextCtrlNameStr);
    
    AddBtn = new wxButton(this, ID_ADD_BTN, wxT("Adicionar Rota"), wxPoint(30, 40), wxDefaultSize, 0);
    UpdateBtn = new wxButton(this, ID_UPDATE_BTN, wxT("Editar Rota"), wxPoint(30, 70), wxDefaultSize, 0);
    RemoveBtn = new wxButton(this, ID_REMOVE_BTN, wxT("Remover Rota"), wxPoint(30, 100), wxDefaultSize, 0);
    OpenInBrowserBtn = new wxButton(this, ID_OPEN_IN_BROWSER_BTN, wxT("Pesquisar Rota"), wxPoint(30, 130), wxDefaultSize, 0);
    ExportJsonBtn = new wxButton(this, ID_EXPORT_BTN, wxT("Exportar..."), wxPoint(30, 160), wxDefaultSize, 0);
    ImportJsonBtn = new wxButton(this, ID_IMPORT_BTN, wxT("Importar..."), wxPoint(30, 190), wxDefaultSize, 0);
    ApplyFilterBtn = new wxButton(this, ID_APPLY_FILTER_BTN, wxT("Filtrar"), wxPoint(30, 310), wxDefaultSize, 0);
    ClearFilterBtn = new wxButton(this, ID_CLEAR_FILTER_BTN, wxT("Limpar Filtro"), wxPoint(130, 310), wxDefaultSize, 0);

    ListaRotasMutex = new mutex();
    AtualizaTelaTimer.Bind(wxEVT_TIMER, &MyFrame::AtualizaTelaEvent, this);
    AtualizaTelaTimer.Start(INTERVALO_ATUALIZACAO_TELA_MS);
}

void MyFrame::AddBtnCallback(wxCommandEvent& event)
{
    this->rotaForm = new RotaFormFrame(this->Rotas, &this->IdAtualRotas, &this->DeveAtualizarTela);
    this->rotaForm->Show();
}

void MyFrame::AtualizaTelaEvent(wxTimerEvent& event)
{
    if(this->DeveAtualizarTela)
        this->PushToRouteList();
}

void MyFrame::RemoveBtnCallback(wxCommandEvent& event)
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
}

void MyFrame::UpdateBtnCallback(wxCommandEvent& event)
{
    wxArrayInt selectedIndexes;
    int numberOfSelections = this->RouteListBox->GetSelections(selectedIndexes);
    if(numberOfSelections <= 0)
        return;

    Rota* rotaSelecionada = this->Rotas->at(selectedIndexes[0]);
    
    cout << "Rota encontrada. Iniciando form..." << endl;
    this->rotaForm = new RotaFormFrame(this->Rotas, rotaSelecionada, &this->DeveAtualizarTela);
    this->rotaForm->Show();
}

void MyFrame :: ExportBtnCallback(wxCommandEvent& event)
{
    vector<json>* jRotas = new vector<json>();
    for(int i = 0; i < Rotas->size(); i++)
    {
        jRotas->push_back(Rotas->at(i)->ToJson());
    }

    json jBuff = {
        { "Rotas", *jRotas }
    };

    string parsedJson = jBuff.dump();

    ofstream outfile("rotas_bwingull.json");
    outfile << parsedJson << endl;

    ostringstream strBuff;
    strBuff << "\nExportado arquivo JSON!";
    this->LogTxtCtrl->AppendText(strBuff.str());
}

void MyFrame::ImportBtnCallback(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open JSON file"), "", "", "*.json", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    cout << "Received path: " << openFileDialog.GetPath() << endl;
    ifstream inFile(openFileDialog.GetPath());
    json importedData = json::parse(inFile);

    Log("Importando arquivo JSON!");
    Log(importedData.dump());

    vector<json> jRotas = importedData["Rotas"];
    for(int i = 0; i < jRotas.size(); i++)
    {
        Rotas->push_back(Rota::FromJson(jRotas.at(i)));
    }

    Log("Rotas adicionadas a base de dados!");
    DeveAtualizarTela = true;
}

void MyFrame::ApplyFilterBtnCallback(wxCommandEvent& event)
{
    string rawFilter = FilterTxtCtrl->GetLineText(0).ToStdString();
    regex exp(rawFilter);

    vector<Rota*>* rotasFiltradas = new vector<Rota*>();
    Log(rawFilter);

    for (int i = 0; i < Rotas->size(); i++)
    {
        if(regex_search(Rotas->at(i)->GetDescricao(), exp))
        {
            cout << "Found!" << endl;
            rotasFiltradas->push_back(Rotas->at(i));
        }
    }
    RotasEmExibicao = rotasFiltradas;
    DeveAtualizarTela = true;
}

void MyFrame::ClearFilterBtnCallback(wxCommandEvent& event)
{
    if(RotasEmExibicao == Rotas)
        return;

    delete RotasEmExibicao;
    RotasEmExibicao = Rotas;
    DeveAtualizarTela = true;
}

void MyFrame::BrowseBtnCallback(wxCommandEvent& event)
{
    cout << "browse button!" << endl;
    wxArrayInt selectedIndexes;
    int numberOfSelections = this->RouteListBox->GetSelections(selectedIndexes);

    if(numberOfSelections <= 0)
        return;

    Rota* alvo = Rotas->at(selectedIndexes[0]);

    ostringstream comandoBusca;
    comandoBusca << "open -a \"Google Chrome\" \"http://google.com/search?q=" << alvo->GetDescricao() << "\""; 
    system(comandoBusca.str().c_str());
}

void MyFrame::OnCloseFormWindow(wxCloseEvent& event)
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
    wxString* stringData = new wxString[RotasEmExibicao->size()];

    for (int i = 0; i < RotasEmExibicao->size(); i++)
    {
        stringData[i] = RotasEmExibicao->at(i)->ToString();
    }

    this->RouteListBox->Clear();

    if(RotasEmExibicao->size() > 0) 
    {
        this->RouteListBox->InsertItems(RotasEmExibicao->size(), stringData, 0);
    }

    this->DeveAtualizarTela = false;
}

void MyFrame::Log(string data)
{
    ostringstream strBuff;
    strBuff << "\n" << data;
    this->LogTxtCtrl->AppendText(strBuff.str());
}
