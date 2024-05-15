//house3dFrame.h

#include "panels.h"

const int Width { 800 };
const int Height { 600 };

class house3dFrame: public wxFrame
{
private:
    ctrlPanel* plCtrl;
    projPanel* plPorj;
    laytPanel* plLayt;

public:
    house3dFrame(const wxString& title);
};
