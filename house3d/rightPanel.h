//rightPanel.h

#include <wx/wx.h>
#include <wx/splitter.h>
#include "object3d.h"

class rightProjPanel: public wxPanel
{
public:
    rightProjPanel(wxSplitterWindow *parent);
    void OnPaint(wxPaintEvent& event);

public:
    object3d* o3d_project;
};

class rightLaytPanel: public wxPanel
{
public:
    rightLaytPanel(wxSplitterWindow *parent);
    void OnPaint(wxPaintEvent& event);

public:
    object3d* o3d_layout;
};
