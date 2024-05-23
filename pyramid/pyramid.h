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
    void DrawPyramid();
};

class TestGLCanvas : public wxGLCanvas
{
public:
    TestGLCanvas(wxWindow *parent);
private:
    void OnPaint(wxPaintEvent& event);

    wxDECLARE_EVENT_TABLE();
};

