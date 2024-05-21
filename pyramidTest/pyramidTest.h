//pyramidTest.h
#include "myGLCanvas.h"

const int Width { 800 };
const int Height { 600 };

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

private:
    MyGLCanvas*  m_mycanvas;
};
