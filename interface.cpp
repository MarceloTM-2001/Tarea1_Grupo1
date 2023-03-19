#include <wx/wxprec.h>
#include <wx/bmpbuttn.h>
#include <cmath>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "exprtk.hpp"

#include <iostream>
#include "funtras.cpp"

using namespace std;

//Márgenes utilizados para la colocación de los widgets
#define ENTRYMARGIN 40
#define UENTRYSPACE 25 
#define OFFSETSPACE 7
#define OFFSETENTRY 75



class MyApp : public wxApp
{
public:
    virtual bool OnInit();
    wxSize windowSize = wxSize(350, 665);
};

class MyAbout : public wxFrame{
public:
    MyAbout(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxStaticText* message;

private:

};

MyAbout::MyAbout(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    message = new wxStaticText(this, wxID_ANY, wxT(
        "Esta         calculadora         pemite\n"
        "encontrar    valores    aproximados\n"
        "a    funciones    no    tan    sencillas\n"
        "de    calcular.\n\n"
        "Para    su    correcto    uso\n"
        "debe    ingresar    un    valor    en\n"
        "la    entrada    x    cuando    la    función\n\n"
        "Cuando    la    función    cuente\n"
        "con    entrada    y,    también\n"
        "se    le    solicitará    ingresar\n"
        "un    valor\n\n"
        "El    resultado    se    puede    ver\n"
        "en    la    casilla    de    Answer\n\n"
        "Geovanny    García\n"
        "Diana    Mejías\n"
        "Valesska    Blanco\n"
        "Marcelo    Truque"

    ), wxPoint(ENTRYMARGIN+20,UENTRYSPACE+OFFSETSPACE+20));
    message->SetWindowStyle(wxALIGN_CENTER_VERTICAL);
}

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxBoxSizer* m_mainSizer;
    
    //Declaración de los widgets principales
    wxButton* clearButton;
    wxButton* helpButton;

    wxStaticText* yFuncLabel;
    wxStaticText* xFuncLabel;
    wxStaticText* ansFuncLabel;
    
    wxTextCtrl* yFuncEntry;
    wxTextCtrl* xFuncEntry;
    wxTextCtrl* ansFuncEntry;

    //Etiquetas para los botones
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
    void OnChar(wxKeyEvent& event);
    cpp_dec_float_50 eval (wxString text);

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
    //Etiquetas de la interfaz
    xFuncLabel = new wxStaticText(this, wxID_ANY, wxT("x ="), wxPoint(ENTRYMARGIN,UENTRYSPACE+OFFSETSPACE));
    yFuncLabel = new wxStaticText(this, wxID_ANY, wxT("y ="), wxPoint(ENTRYMARGIN,UENTRYSPACE*3+OFFSETSPACE));
    ansFuncLabel = new wxStaticText(this, wxID_ANY, wxT("Answer ="), wxPoint(ENTRYMARGIN,UENTRYSPACE*5+OFFSETSPACE));

    //Definición de botones help y clear
    clearButton = new wxButton(this, 100, wxT("Clear"), wxPoint(ENTRYMARGIN+2.5*OFFSETENTRY, UENTRYSPACE+15), wxSize(75, 35));
    Connect(100, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnButtonClicked));
    helpButton = new wxButton(this, 101, wxT("Help!"), wxPoint(ENTRYMARGIN+2.5*OFFSETENTRY, UENTRYSPACE*5-15), wxSize(75, 35));
    Connect(101, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnButtonClicked));

    //Espacios de entradas y salida
    xFuncEntry = new wxTextCtrl(this, wxID_ANY, wxT(""),
                               wxPoint(ENTRYMARGIN+OFFSETENTRY, UENTRYSPACE), wxDefaultSize,
                               wxTE_PROCESS_ENTER);

    yFuncEntry = new wxTextCtrl(this, wxID_ANY, wxT(""),
                               wxPoint(ENTRYMARGIN+OFFSETENTRY, UENTRYSPACE*3), wxDefaultSize,
                               wxTE_PROCESS_ENTER);

    ansFuncEntry = new wxTextCtrl(this, wxID_ANY, wxT(""),
                               wxPoint(ENTRYMARGIN+OFFSETENTRY, UENTRYSPACE*5), wxDefaultSize,
                               wxTE_PROCESS_ENTER);

    //Link con eventos
    xFuncEntry->Bind(wxEVT_CHAR, &MyFrame::OnChar, this);
    yFuncEntry->Bind(wxEVT_CHAR, &MyFrame::OnChar, this);
    ansFuncEntry->SetEditable(false);
    
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(m_mainSizer);

    //Grid para los botones
    wxGridSizer* buttonSizer = new wxGridSizer(7, 3, 10, 10);

    int i = 1;
    int j = 1;

    //Creación de los botones para las funciones
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
    //Lógica de selección de función, manejo de errores y validaciones
    errorflag = false;
    this->ansFuncEntry->Clear();
    cpp_dec_float_50 ans;
    
    if (event.GetId()!=53 && event.GetId()!=63 && event.GetId()!=72 && event.GetId()!=100 && event.GetId()!=101){
        if (this->xFuncEntry->IsEmpty() == false)
        {
            cpp_dec_float_50 num = eval(this->xFuncEntry->GetValue());
            int numint = static_cast<int>(floor(num));

            if (event.GetId()==11){
                ans = sinh_t(num);
            } else if (event.GetId()==12) {
                ans = cosh_t(num);
            } else if (event.GetId()==13) {
                ans = tanh_t(num);
            } else if (event.GetId()==21) {
                ans = asin_t(num);
            } else if (event.GetId()==22) {
                ans = acos_t(num);
            } else if (event.GetId()==23) {
                ans = atan_t(num);
            } else if (event.GetId()==31) {
                ans = sec_t(num);
            } else if (event.GetId()==32) {
                ans = csc_t(num);
            } else if (event.GetId()==33) {
                ans = cot_t(num);
            } else if (event.GetId()==41) {
                ans = sin_t(num);
            } else if (event.GetId()==42) {
                ans = cos_t(num);
            } else if (event.GetId()==43) {
                ans = tan_t(num);
            } else if (event.GetId()==51) {
                ans = ln_t(num);
            } else if (event.GetId()==52) {
                ans = log10_t(num);
            } else if (event.GetId()==61) {
                ans = divi_t(num);
            } else if (event.GetId()==62) {
                ans = sqrt_t(num);
            } else if (event.GetId()==71) {
                ans = exp_t(num);
            } else if (event.GetId()==73) {
                ans = factorial_t(numint);
            }

            std::stringstream ss;
            ss << std::setprecision(50) << ans;
            wxString x_str = wxString::FromUTF8(ss.str());

            if (errorflag == false && ans == ans){
                this->ansFuncEntry->WriteText(x_str);
            } else if (ans != ans) {
                this->ansFuncEntry->WriteText("Sintax Error");
            } else {
                this->ansFuncEntry->WriteText("Indefinido");
            }
            
        } else {
            wxMessageBox("Debe ingresar un valor para x");
        }
    } else if (event.GetId()==100 || event.GetId()==101){
        if (event.GetId()==100){
            this->ansFuncEntry->Clear();
            this->xFuncEntry->Clear();
            this->yFuncEntry->Clear();
        } else if (event.GetId()==101) {
            MyAbout *myMessage = new MyAbout( "About", wxPoint(50, 50), wxSize(350, 500));
            myMessage->Show(true);
            myMessage->SetMinSize(wxSize(350, 500));
            myMessage->SetMaxSize(wxSize(350, 500));

        }
    
    } else {
        if (this->xFuncEntry->IsEmpty() == false && this->yFuncEntry->IsEmpty() == false)
        {
            cpp_dec_float_50 num = eval(this->xFuncEntry->GetValue());
            cpp_dec_float_50 num1 = eval(this->yFuncEntry->GetValue());

            if (event.GetId()==53) {
                ans = log_t(num, num1);
            } else if (event.GetId()==63) {
                ans = root_t(num, num1);
            } else if (event.GetId()==72) {
                ans = power_t(num, num1);
            }

            std::stringstream ss;
            ss << std::setprecision(50) << ans;
            wxString x_str = wxString::FromUTF8(ss.str());

            if (errorflag == false && ans == ans){
                this->ansFuncEntry->WriteText(x_str);
            } else if (ans != ans) {
                this->ansFuncEntry->WriteText("Sintax Error");
            } else {
                this->ansFuncEntry->WriteText("Indefinido");
            }

        } else {
            wxMessageBox("Debe ingresar un valor para x, y");
        }    
    }
}

void MyFrame::OnChar(wxKeyEvent& event)
{
    // Obtiene el código de la tecla presionada
    int keycode = event.GetKeyCode();

    // Verificacion de tipo de caracter
    if (keycode >= '0' && keycode <= '9' || 
        keycode == '.' || 
        keycode == '*' || keycode == '/' ||
        keycode == '+' || keycode == '-' || 
        keycode == 'p' || keycode == 'i' ||
        keycode == 'e' || keycode == ')' ||  
        keycode == '(' ||
        keycode == wxKeyCode::WXK_LEFT || 
        keycode == wxKeyCode::WXK_RIGHT || 
        keycode == wxKeyCode::WXK_BACK || 
        keycode == wxKeyCode::WXK_DELETE)
    {
        // Acepta la tecla
        event.Skip();
    }
    else
    {
        // Descarta la tecla
        return;
    }
}

cpp_dec_float_50 MyFrame::eval(wxString text)
{

    // Replace pi and e with their values
    text.Replace("pi", wxString::Format("%.50g", pi_t));
    text.Replace("e", wxString::Format("%.50g", e_t));
    
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    expression_t expression;
    parser_t parser;

    parser.compile(text.ToStdString(), expression);

    try {
        cpp_dec_float_50 result = expression.value();
        return result;
    } catch (const std::exception& e) {
        errorflag = true;
        wxMessageBox("Error de Sintaxis");
        return 0;
    }
}