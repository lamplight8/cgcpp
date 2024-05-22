#include <wx/glcanvas.h>

class TestGLContext : public wxGLContext
{
public:
    TestGLContext(wxGLCanvas *canvas);
    void DrawRotatedCube(float xangle, float yangle);
private:
    GLuint m_textures[6];
};

class MyApp : public wxApp
{
public:
    MyApp() { m_glContext = NULL; }
    TestGLContext& GetContext(wxGLCanvas *canvas);
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE;
private:
    TestGLContext *m_glContext;
};

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    void OnClose(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

class TestGLCanvas : public wxGLCanvas
{
public:
    TestGLCanvas(wxWindow *parent, int *attribList = NULL);
private:
    void OnPaint(wxPaintEvent& event);
    void Spin(float xSpin, float ySpin);
    void OnKeyDown(wxKeyEvent& event);
    void OnSpinTimer(wxTimerEvent& WXUNUSED(event));

    // angles of rotation around x- and y- axis
    float m_xangle,
          m_yangle;
    wxTimer m_spinTimer;

    wxDECLARE_EVENT_TABLE();
};

enum
{
    NEW_STEREO_WINDOW = wxID_HIGHEST + 1
};

