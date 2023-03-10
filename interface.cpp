#include <wx/wxprec.h>
#include <wx/bmpbuttn.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <iostream>

using namespace std;


class MyApp : public wxApp
{
public:
    virtual bool OnInit();
    wxSize windowSize = wxSize(350, 665);
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxBoxSizer* m_mainSizer;
    std::vector<std::string> buttonLabels = {
    "senh(x)",
    "cosh(x)",
    "tanh(x)",
    "asen(x)",
    "acos(x)",
    "atan(x)",
    "sec(x)",
    "csc(x)",
    "cot(x)",
    "sen(x)",
    "cos(x)",
    "tan(x)",
    "ln(x)",
    "log10(x)",
    "logy(x)",
    "1/x",
    "√x",
    "y√x",
    "exp(x)",
    "x^y",
    "x!"
};

private:
    
    void OnButtonClicked(wxCommandEvent& event);

};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Aproximation Calculator", wxPoint(50, 50), windowSize);
    frame->Show(true);
    frame->SetMinSize(windowSize);
    frame->SetMaxSize(windowSize);

    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(m_mainSizer);

    wxGridSizer* buttonSizer = new wxGridSizer(7, 3, 10, 10);

    int i = 1;
    int j = 1;

    for (const auto& label : buttonLabels)
    {
        wxButton* button = new wxButton(this, i*10+j, wxString::FromUTF8(label), wxDefaultPosition, wxSize(100, 50));
        buttonSizer->Add(button, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL);
        Connect(i*10+j, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnButtonClicked));
        if (j == 3)
        {
            i++;
            j=1;
        } else
        {
            j++;
        }  
    }

   m_mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP, 200);;

    Layout();
}

void MyFrame::OnButtonClicked(wxCommandEvent& event)
{
    cout<<event.GetId()<<endl;
}