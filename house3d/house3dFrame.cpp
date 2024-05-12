//house3dFrame.cpp

#include "house3dFrame.h"

house3dFrame::house3dFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(Width, Height))
{
    wxSplitterWindow *spl1 = new wxSplitterWindow(this, -1, wxDefaultPosition, wxSize(800, 600));
    wxSplitterWindow *spl2 = new wxSplitterWindow(spl1, -1, wxDefaultPosition, wxSize(500, 500));
    wxPanel* panel_1 = new wxPanel(spl1, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE);
    wxPanel* panel_2 = new wxPanel(spl2, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE);
    wxPanel* panel_3 = new wxPanel(spl2, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE);

    spl2->SplitHorizontally(panel_2, panel_3);
    spl1->SplitVertically(panel_1, spl2);

    Center();
}
