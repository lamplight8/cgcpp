
//main.cpp
#include "main.h"
#include "pyramidFrame.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    pyramidFrame *dl = new pyramidFrame{ wxT("绘制金字塔") };
    dl->Show(true);
    return true;
}

/*
#include <iostream>
#include <string>
#include <cassert>
#include <cmath>

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <wx/notebook.h>
#include <wx/treectrl.h>

class GL_Window : public wxGLCanvas
{
public:

    GL_Window(wxWindow* parent,
        wxWindowID id,
        const int* attribList)
        : wxGLCanvas(parent, id, attribList)
        {
         
            m_glRC = new wxGLContext(this);
            SetCurrent(*m_glRC);
        }

    virtual ~GL_Window()
    {
    }

    void draw()
    {
      
        SetCurrent(*m_glRC);
     
        glClearColor(m_ClearColor.Red(), m_ClearColor.Green(), m_ClearColor.Blue(), m_ClearColor.Alpha());
        glClear(GL_COLOR_BUFFER_BIT);
       

        SwapBuffers();
    }

    void OnIdle(wxIdleEvent& event) {
        draw();
        event.RequestMore();
    }

    void OnSize(wxSizeEvent& event)
    {
      
    }

public:
    void setClearColor(const wxColor& color)
    {
        m_ClearColor = color;
    }
private:
    wxColor m_ClearColor;
  
    wxGLContext* m_glRC;
    DECLARE_EVENT_TABLE()
};

class MyApp : public wxApp
{
    virtual bool OnInit();
};


bool MyApp::OnInit()
{
    wxFrame* frame = new wxFrame((wxFrame*)NULL, -1,
        _("Hello GL World"), wxPoint(50, 50), wxSize(450, 340));

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  
    int gl_attrib[20] =
    { WX_GL_RGBA, WX_GL_MIN_RED, 1, WX_GL_MIN_GREEN, 1,
    WX_GL_MIN_BLUE, 1, WX_GL_DEPTH_SIZE, 1,
    WX_GL_DOUBLEBUFFER,
    0 };

    wxPanel* pane1 = new wxPanel(frame, wxID_ANY);
    wxPanel* pane2 = new wxPanel(frame, wxID_ANY);
   
  
   
    sizer->Add(pane1, 1, wxEXPAND | wxALL);
    sizer->Add(pane2, 1, wxEXPAND | wxALL);

    GL_Window* MyGLCanvas1 = new GL_Window(pane1, wxID_ANY, gl_attrib);
    wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);
    sizer1->Add(MyGLCanvas1,1,  wxEXPAND | wxALL);
    MyGLCanvas1->setClearColor(*wxBLUE);
    pane1->SetSizer(sizer1);

    GL_Window* MyGLCanvas2 = new GL_Window(pane2, wxID_ANY, gl_attrib);
    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    sizer2->Add(MyGLCanvas2, 1, wxEXPAND | wxALL);
    MyGLCanvas2->setClearColor(*wxRED);
    pane2->SetSizer(sizer2);

  
    frame->SetSizer(sizer);
    frame->SetSize(1024, 800);
    frame->Show(true);
    return true;
}

BEGIN_EVENT_TABLE(GL_Window, wxGLCanvas)
EVT_IDLE(GL_Window::OnIdle)
EVT_SIZE(GL_Window::OnSize)
END_EVENT_TABLE()

int main()
{
    MyApp* app = new MyApp;
    wxApp::SetInstance(app);

    wxEntry();
}

#include <wx/wx.h>
#include <wx/glcanvas.h>

class MyGLCanvas : public wxGLCanvas
{
public:
    MyGLCanvas(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxGLCanvasName, const int* attribList = 0, const wxPalette& palette = wxNullPalette);
    ~MyGLCanvas();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);

private:
    DECLARE_EVENT_TABLE()
};

class MyGLCanvas : public wxGLCanvas
{
public:
    MyGLCanvas(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxGLCanvasName, const int* attribList = 0, const wxPalette& palette = wxNullPalette);
    ~MyGLCanvas();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);

private:
    DECLARE_EVENT_TABLE()
};

MyGLCanvas::MyGLCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name, const int* attribList, const wxPalette& palette)
:wxGLCanvas(parent, id, pos, size, style, name, attribList, palette)//这里显示wxGLCanvas错误
{
    Connect(wxEVT_PAINT, wxPaintEventHandler(MyGLCanvas::OnPaint));
    Connect(wxEVT_SIZE, wxSizeEventHandler(MyGLCanvas::OnSize));
}

MyGLCanvas::~MyGLCanvas()
{
}

void MyGLCanvas::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    // Initialize OpenGL rendering context
    wxGLContext* context = GetContext();
    context->SetCurrent(*this);

    // Clear the color buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw your scene here

    // Swap the front and back buffers
    SwapBuffers();
}

void MyGLCanvas::OnSize(wxSizeEvent& event)
{
    // Set the viewport and projection matrix for OpenGL rendering
    wxGLContext* context = GetContext();
    context->SetCurrent(*this);

    int w, h;
    GetClientSize(&w, &h);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

BEGIN_EVENT_TABLE(MyGLCanvas, wxGLCanvas)
    EVT_PAINT(MyGLCanvas::OnPaint)
    EVT_SIZE(MyGLCanvas::OnSize)
END_EVENT_TABLE()

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

bool MyApp::OnInit()
{
    wxFrame* frame = new wxFrame(NULL, wxID_ANY, wxT("OpenGL Example"), wxDefaultPosition, wxSize(640, 480));
    MyGLCanvas* canvas = new MyGLCanvas(frame);

    frame->Show(true);

    return true;
}

wxIMPLEMENT_APP(MyApp);
*/
