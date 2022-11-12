// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/listbox.h>

#include <stdio.h>
#include <vector.h>

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
        void TestMethod(wxCommandEvent& event);
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
};

enum
{
    ID_Hello = 1
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

BEGIN_EVENT_TABLE ( MyFrame, wxFrame )
    EVT_BUTTON ( 189, MyFrame::TestMethod ) // Tell the OS to run test method onclick btn 189
END_EVENT_TABLE() // The button is pressed


MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World ---- T", wxDefaultPosition, wxSize(500, 500))
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



    routeListBox = new wxListBox(this, 154, wxPoint(250, 10), wxSize(240, 200));

        logTxtCtrl = new wxTextCtrl(this, 152,
      wxT("Hi!"), wxPoint(250, 220), wxSize(240, 200),
      wxTE_MULTILINE | wxTE_RICH | wxTE_READONLY, wxDefaultValidator, wxTextCtrlNameStr);
    
    addBtn = new wxButton(this, 189, wxT("ADD"), wxPoint(30, 40), wxDefaultSize, 0);
    updateBtn = new wxButton(this, 190, wxT("UPDATE"), wxPoint(30, 70), wxDefaultSize, 0);
    removeBtn = new wxButton(this, 191, wxT("REMOVE"), wxPoint(30, 100), wxDefaultSize, 0);
    openInBrowserBtn = new wxButton(this, 192, wxT("BROWSE"), wxPoint(30, 130), wxDefaultSize, 0);
    //WE CAN CREATE A CONTAINER LIKE wxBoxSizer and add radio buttons with style=wxRB_GROUP to it

    // Layout();
    // wxSize size = GetSize();
    // this->SetMinSize(wxSize(500, 500));
    // Layout();
}

void MyFrame :: TestMethod(wxCommandEvent& event)
{
//     cout << "TESTOU!" << endl;
    this->logTxtCtrl->AppendText("\nteste");
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