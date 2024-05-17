//pyramidCavans.h
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
//#define wxUSE_GLCANVAS 1

class pyramidGLCanvas : public wxGLCanvas
{
public:
    pyramidGLCanvas(wxWindow* parent);
    ~pyramidGLCanvas();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
private:
    DECLARE_EVENT_TABLE()    
};

