//pyramidCavans.cpp
#include "pyramidCavans.h"

pyramidGLCanvas::pyramidGLCanvas(wxWindow* parent)
:wxGLCanvas(parent, wxID_ANY, 0, wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas"))
{
    Connect(wxEVT_PAINT, wxPaintEventHandler(pyramidGLCanvas::OnPaint));
    Connect(wxEVT_SIZE, wxSizeEventHandler(pyramidGLCanvas::OnSize));
}

pyramidGLCanvas::~pyramidGLCanvas()
{

}

void pyramidGLCanvas::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    // Initialize OpenGL rendering context
    //wxGLContext* context = GetContext();
    //context->SetCurrent(*this);

    // Clear the color buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw your scene here

    // Swap the front and back buffers
    SwapBuffers();
}

void pyramidGLCanvas::OnSize(wxSizeEvent& event)
{
    // Set the viewport and projection matrix for OpenGL rendering
    //wxGLContext* context = GetContext();
    //context->SetCurrent(*this);

    int w, h;
    GetClientSize(&w, &h);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

