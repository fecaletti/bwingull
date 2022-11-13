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
#include <wx/textentry.h>

#include <stdio.h>
#include <vector>

#include "../../lib/rota/rota.h"
#include "../../lib/text-controller-logger/text-controller-logger.h"

using namespace std;

class RotaFormFrame : public wxFrame
{
    public:
        RotaFormFrame(Rota* novaRota);
        void AdicionaPontoBtnCallback(wxCommandEvent& event);
        void RemovePontoBtnCallback(wxCommandEvent& event);
        void SalvarBtnCallback(wxCommandEvent& event);
        void CancelarBtnCallback(wxCommandEvent& event);
        void ImprimirListaPontos();
        DECLARE_EVENT_TABLE()

    private:
        TextControllerLogger* Logger;
        void OnHello(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        
        wxTextCtrl *LogTxtCtrl;
        wxListBox *PontosListBox;

        wxButton *SalvarBtn;
        wxButton *CancelarBtn;
        wxButton *AdicionaPontoBtn;
        wxButton *RemovePontoBtn;

        wxTextEntry *rotaDescTxt;
        wxTextEntry *xCoordTxt;
        wxTextEntry *yCoordTxt;

        Rota* novaRota;
        int IdAtualPonto = 0;
};

enum
{
    ID_RF_Hello = 21,
    ID_RF_ADD_PONTO_BTN = 22,
    ID_RF_REMOVE_PONTO_BTN = 23,
    ID_RF_SALVAR_BTN = 24,
    ID_RF_CANCELAR_BTN = 25,
    ID_RF_LOG_TEXT_CONTROLLER = 26,
    ID_RF_PONTOS_LIST_BOX = 27,
    ID_RF_ROTA_DESC_TXT = 28,
    ID_RF_PONTO_X_TXT = 29,
    ID_RF_PONTO_Y_TXT = 30
};

BEGIN_EVENT_TABLE ( RotaFormFrame, wxFrame )
    EVT_BUTTON ( ID_RF_ADD_BTN, RotaFormFrame::AddBtnCallback ) // Tell the OS to run test method onclick btn 189
    EVT_BUTTON ( ID_RF_REMOVE_BTN, RotaFormFrame::RemoveBtnCallback ) // Tell the OS to run test method onclick btn 190
END_EVENT_TABLE() // The button is pressed


RotaFormFrame::RotaFormFrame(Rota* novaRota)
    : wxFrame(nullptr, wxID_ANY, "Cadastro de nova rota", wxDefaultPosition, wxSize(500, 500))
{
    this->novaRota = novaRota;

    wxMenu *menuFile = new wxMenu();
    menuFile->Append(ID_RF_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
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

    Bind(wxEVT_MENU, &RotaFormFrame::OnHello, this, ID_RF_Hello);
    Bind(wxEVT_MENU, &RotaFormFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &RotaFormFrame::OnExit, this, wxID_EXIT);

    RouteListBox = new wxListBox(this, ID_RF_ROUTE_LIST_BOX, wxPoint(250, 10), wxSize(240, 200));

        LogTxtCtrl = new wxTextCtrl(this, ID_RF_LOG_TEXT_CONTROLLER,
      wxT("nova rota sendo cadastrada!"), wxPoint(250, 220), wxSize(240, 200),
      wxTE_MULTILINE | wxTE_RICH | wxTE_READONLY, wxDefaultValidator, wxTextCtrlNameStr);

    Logger = new TextControllerLogger(LogTxtCtrl);
}

void RotaFormFrame :: AddBtnCallback(wxCommandEvent& event)
{
    // ostringstream strBuff;
    // strBuff << "\nAdicionando ponto - id: " << this->IdAtualPonto;
    // this->LogTxtCtrl->AppendText(strBuff.str());
    // this->Rotas->push_back(new Rota(this->IdAtualRotas++));
    // PushToRouteList();
    this->Logger << "ISSO EH UM LOG DE TESTE";
}

void RotaFormFrame :: RemoveBtnCallback(wxCommandEvent& event)
{
    // wxArrayInt selectedIndexes;
    // int numberOfSelections = this->RouteListBox->GetSelections(selectedIndexes);
    // for (int i = 0; i < numberOfSelections; i++)
    // {
    //     ostringstream strBuff;
    //     strBuff << "\nRemovendo rota " << this->Rotas->at(selectedIndexes[i])->GetId();
    //     this->LogTxtCtrl->AppendText(strBuff.str());
    //     this->Rotas->erase(this->Rotas->begin() + (int)selectedIndexes[i]);
    // }
    // this->PushToRouteList();
}

void RotaFormFrame :: OnExit(wxCommandEvent& event)
{
    Close(true);
}

void RotaFormFrame :: OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}
 
void RotaFormFrame :: OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets - teste!");
}

void RotaFormFrame :: PushToRouteList()
{
    // wxString* stringData = new wxString[this->Rotas->size()];
    // for (int i = 0; i < this->Rotas->size(); i++)
    // {
    //     stringData[i] = this->Rotas->at(i)->toString();
    // }
    
    // this->RouteListBox->Clear();

    // if(this->Rotas->size() > 0)
    //     this->RouteListBox->InsertItems(this->Rotas->size(), stringData, 0);
}

void RotaFormFrame :: Log(ostringstream stream)
{
    // this->LogTxtCtrl->AppendText(stream.str());
}