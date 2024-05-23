//pyramid.h
#include <wx/wx.h>
#include "oglstuff.h"
#include <wx/glcanvas.h>

const int Width { 800 };
const int Height { 600 };

class MyApp: public wxApp
{
public:
    MyApp(){}
    bool OnInit() wxOVERRIDE;
};

class MyGLCanvas;

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    bool OGLAvailable();

private:
    wxString     m_OGLString;
    MyGLCanvas*  m_mycanvas;
};

class MyGLCanvas : public wxGLCanvas
{
public:
    MyGLCanvas(MyFrame* parent, const wxGLAttributes& canvasAttrs);
    ~MyGLCanvas();

    //Used just to know if we must end now because OGL 3.2 isn't available
    bool OglCtxAvailable()
        {return m_oglContext != NULL;}

    //Init the OpenGL stuff
    bool oglInit();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnMouse(wxMouseEvent& event);

private:
    // Members
    MyFrame*      m_parent;
    wxGLContext*  m_oglContext;
    myOGLManager* m_oglManager;
    int           m_winHeight; // We use this var to know if we have been sized

    wxDECLARE_EVENT_TABLE();
};

