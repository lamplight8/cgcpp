// pyramid.h

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <math.h>
const double PI = 3.1415926;

const int Width { 800 };
const int Height { 600 };

class MyApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
};

class myGLContext : public wxGLContext
{
public:
    myGLContext(wxGLCanvas *canvas);
    void DrawPyramid(float xangle, float yangle);
};

class TestGLCanvas : public wxGLCanvas
{
public:
    TestGLCanvas(wxWindow *parent);
private:
    void OnPaint(wxPaintEvent& event);
    void Spin(float xSpin, float ySpin);
    void OnKeyDown(wxKeyEvent& event);
    void OnSpinTimer(wxTimerEvent& WXUNUSED(event));
    
    float m_xangle;
    float m_yangle;
    wxTimer m_spinTimer;
    wxDECLARE_EVENT_TABLE();
};

