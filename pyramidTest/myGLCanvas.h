//myGLCanvas.h
#include <wx/wx.h>
#include <wx/glcanvas.h>

class MyGLCanvas : public wxGLCanvas
{
public:
    MyGLCanvas(wxWindow* parent, const wxGLAttributes& canvasAttrs);
    ~MyGLCanvas();
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);

private:
    // Members
    wxWindow*      m_parent;
    wxGLContext*  m_oglContext;

    wxDECLARE_EVENT_TABLE();
};