//rightLaytPanel.cpp
#include "rightLaytPanel.h"

rightLaytPanel::rightLaytPanel(wxSplitterWindow * parent)
: wxPanel(parent, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE)
{

}

void rightLaytPanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    
}