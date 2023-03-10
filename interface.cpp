#include <wx/wxprec.h>
#include <wx/bmpbuttn.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

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

private:
    
    void OnClick(wxCommandEvent& event);

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

    for (int i = 0; i < 21; i++)
    {
        wxString buttonText = wxString::Format(wxT("Button %d"), i + 1);
        wxButton* button = new wxButton(this, wxID_ANY, buttonText, wxDefaultPosition, wxSize(100, 50));
        buttonSizer->Add(button, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL);
    }

   m_mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP, 200);;

    Layout();
}

void MyFrame::OnClick(wxCommandEvent& event)
{
    
}