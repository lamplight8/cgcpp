//house3dFrame.cpp

#include "house3dFrame.h"
//#include <wx/statbox.h>


house3dFrame::house3dFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(Width, Height))
{
    //设置控制面板、投影面板、布局面板
    wxSplitterWindow *spl1 = new wxSplitterWindow(this, -1, wxDefaultPosition, wxSize(Width, Height));
    wxSplitterWindow *spl2 = new wxSplitterWindow(spl1, -1, wxDefaultPosition, wxSize(550, 550));
    plCtrl = new ctrlPanel(spl1);
    plPorj = new projPanel(spl2);
    plLayt = new laytPanel(spl2);
    spl1->SplitVertically(plCtrl, spl2);
    spl2->SplitHorizontally(plPorj, plLayt);

    Center();
}
