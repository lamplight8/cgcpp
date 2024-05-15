//rightProjPanel.h
#include <wx/wx.h>
#include <wx/splitter.h>

class rightProjPanel: public wxPanel
{
public:
    rightProjPanel(wxSplitterWindow *parent);
    void OnPaint(wxPaintEvent& event);
};