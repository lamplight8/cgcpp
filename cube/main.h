#include "testGLContext.h"
#include "myFrame.h"

class MyApp : public wxApp
{
public:
    MyApp();

    TestGLContext& GetContext(wxGLCanvas *canvas, bool useStereo);

    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE;

private:
    TestGLContext *m_glContext;
    TestGLContext *m_glStereoContext;
};