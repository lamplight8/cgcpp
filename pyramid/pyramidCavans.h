//pyramidCavans.h
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <wx/window.h>
#include <GL/gl.h>
#include <GL/glu.h>

class pyramidGLCanvas : public wxGLCanvas
{
public:
    pyramidGLCanvas(wxWindow* parent);
    ~pyramidGLCanvas();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);

};

