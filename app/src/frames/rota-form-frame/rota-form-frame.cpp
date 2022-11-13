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
#include <wx/stattext.h>

#include <stdio.h>
#include <vector>

#include "../../lib/rota/rota.h"

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
        void OnHello(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        
        wxTextCtrl *LogTxtCtrl;
        wxListBox *PontosListBox;

        wxButton *SalvarBtn;
        wxButton *CancelarBtn;
        wxButton *AdicionaPontoBtn;
        wxButton *RemovePontoBtn;

        wxTextCtrl *RotaDescTxt;
        wxTextCtrl *XCoordTxt;
        wxTextCtrl *YCoordTxt;

        Rota* NovaRota;
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
    ID_RF_PONTO_Y_TXT = 30,
    ID_RF_ROTA_DESC_LBL = 31,
    ID_RF_PONTO_LBL = 32
};

BEGIN_EVENT_TABLE ( RotaFormFrame, wxFrame )
    EVT_BUTTON ( ID_RF_ADD_PONTO_BTN, RotaFormFrame::AdicionaPontoBtnCallback ) // Tell the OS to run test method onclick btn 189
    EVT_BUTTON ( ID_RF_REMOVE_PONTO_BTN, RotaFormFrame::RemovePontoBtnCallback ) // Tell the OS to run test method onclick btn 190
    EVT_BUTTON ( ID_RF_SALVAR_BTN, RotaFormFrame::SalvarBtnCallback ) // Tell the OS to run test method onclick btn 190
    EVT_BUTTON ( ID_RF_CANCELAR_BTN, RotaFormFrame::CancelarBtnCallback ) // Tell the OS to run test method onclick btn 190
END_EVENT_TABLE() // The button is pressed


RotaFormFrame::RotaFormFrame(Rota* novaRota)
    : wxFrame(nullptr, wxID_ANY, "Cadastro de nova rota", wxDefaultPosition, wxSize(500, 500))
{
    this->NovaRota = novaRota;

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

    PontosListBox = new wxListBox(this, ID_RF_PONTOS_LIST_BOX, wxPoint(250, 10), wxSize(240, 200));

    LogTxtCtrl = new wxTextCtrl(this, ID_RF_LOG_TEXT_CONTROLLER,
      wxT(""), wxPoint(250, 220), wxSize(240, 200),
      wxTE_MULTILINE | wxTE_RICH | wxTE_READONLY, wxDefaultValidator, wxTextCtrlNameStr);


    wxStaticText* novoPontoLbl = new wxStaticText(this, ID_RF_PONTO_LBL, wxString("Adicionar ponto"), wxPoint(10, 155));
    AdicionaPontoBtn = new wxButton(this, ID_RF_ADD_PONTO_BTN, wxT("Adicionar Ponto"), wxPoint(10, 210), wxDefaultSize, 0);
    RemovePontoBtn = new wxButton(this, ID_RF_REMOVE_PONTO_BTN, wxT("Remover Ponto"), wxPoint(10, 240), wxDefaultSize, 0);
    SalvarBtn = new wxButton(this, ID_RF_SALVAR_BTN, wxT("Salvar"), wxPoint(10, 400), wxDefaultSize, 0);
    CancelarBtn = new wxButton(this, ID_RF_CANCELAR_BTN, wxT("Cancelar"), wxPoint(110, 400), wxDefaultSize, 0);

    wxStaticText* descRotaLbl = new wxStaticText(this, ID_RF_ROTA_DESC_LBL, wxString("Descrição da rota"), wxPoint(10, 15));
    RotaDescTxt = new wxTextCtrl(this, ID_RF_ROTA_DESC_TXT, wxT("Descrição"), wxPoint(10, 40), wxSize(180, 25));
    XCoordTxt = new wxTextCtrl(this, ID_RF_PONTO_X_TXT, wxT("X"), wxPoint(10, 180), wxSize(60, 25));
    YCoordTxt = new wxTextCtrl(this, ID_RF_PONTO_Y_TXT, wxT("Y"), wxPoint(80, 180), wxSize(60, 25));
}

void RotaFormFrame :: AdicionaPontoBtnCallback(wxCommandEvent& event)
{
    // ostringstream strBuff;
    // strBuff << "\nAdicionando ponto - id: " << this->IdAtualPonto;
    // this->LogTxtCtrl->AppendText(strBuff.str());
    // this->Rotas->push_back(new Rota(this->IdAtualRotas++));
    // PushToRouteList();
}

void RotaFormFrame :: RemovePontoBtnCallback(wxCommandEvent& event)
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

void RotaFormFrame :: SalvarBtnCallback(wxCommandEvent& event)
{

}

void RotaFormFrame :: CancelarBtnCallback(wxCommandEvent& event)
{

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

void RotaFormFrame :: ImprimirListaPontos()
{
    wxString* stringData = new wxString[this->NovaRota->Pontos->size()];
    for (int i = 0; i < this->NovaRota->Pontos->size(); i++)
    {
        stringData[i] = this->NovaRota->Pontos->at(i)->toString();
    }
    
    this->PontosListBox->Clear();

    if(this->NovaRota->Pontos->size() > 0)
        this->PontosListBox->InsertItems(this->NovaRota->Pontos->size(), stringData, 0);
}