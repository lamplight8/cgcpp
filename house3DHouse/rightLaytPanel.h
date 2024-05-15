//leftLaytPanel.h
#include <wx/wx.h>
#include <wx/splitter.h>

class rightLaytPanel: public wxPanel
{
public:
    rightLaytPanel(wxSplitterWindow *parent);
    void OnPaint(wxPaintEvent& event);
};