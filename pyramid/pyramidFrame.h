//pyramidFrame.h
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <GL/gl.h>
#include <GL/glu.h>

const int Width { 800 };
const int Height { 600 };

class pyramidFrame: public wxFrame
{
public:
    pyramidFrame(const wxString& title);
};

    