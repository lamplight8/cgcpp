#include "testGLContext.h"

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
    bool m_useStereo,
         m_stereoWarningAlreadyDisplayed;

    wxDECLARE_EVENT_TABLE();
};