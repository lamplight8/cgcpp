//pyramidTest.cpp
#include "pyramidTest.h"

MyFrame::MyFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(Width, Height))
{
    SetIcon(wxICON(sample));

    // The canvas
    m_mycanvas = NULL;
    wxGLAttributes vAttrs;//OpenGL渲染上下文属性
    vAttrs.PlatformDefaults().Defaults().EndList();//返回系统默认的属性列表
    bool accepted = wxGLCanvas::IsDisplaySupported(vAttrs);

    if ( accepted )
        m_mycanvas = new MyGLCanvas(this, vAttrs);

    SetMinSize(wxSize(250, 200));
}