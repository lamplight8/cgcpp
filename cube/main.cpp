#include "main.h"

wxIMPLEMENT_APP(MyApp);

MyApp::MyApp() 
{ 
    m_glContext = NULL; 
    m_glStereoContext = NULL; 
}

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    new MyFrame();

    return true;
}

int MyApp::OnExit()
{
    delete m_glContext;
    delete m_glStereoContext;

    return wxApp::OnExit();
}

TestGLContext& MyApp::GetContext(wxGLCanvas *canvas, bool useStereo)
{
    TestGLContext *glContext;
    if ( useStereo )
    {
        if ( !m_glStereoContext )
        {
            // Create the OpenGL context for the first stereo window which needs it:
            // subsequently created windows will all share the same context.
            m_glStereoContext = new TestGLContext(canvas);
        }
        glContext = m_glStereoContext;
    }
    else
    {
        if ( !m_glContext )
        {
            // Create the OpenGL context for the first mono window which needs it:
            // subsequently created windows will all share the same context.
            m_glContext = new TestGLContext(canvas);
        }
        glContext = m_glContext;
    }

    glContext->SetCurrent(*canvas);

    return *glContext;
}