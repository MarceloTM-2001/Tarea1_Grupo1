#include <wx/wxprec.h>
#include <wx/bmpbuttn.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
    wxSize windowSize = wxSize(800, 1000);
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
       
    void OnClick(wxCommandEvent& event);

};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Memory Game", wxPoint(50, 50), windowSize);
    frame->Show(true);
    frame->SetMinSize(windowSize);
    frame->SetMaxSize(windowSize);

    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    //init

}

void MyFrame::OnClick(wxCommandEvent& event)
{
    
}