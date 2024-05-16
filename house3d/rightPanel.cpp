//rightPanel.cpp

#include "rightPanel.h"
#include <wx/dcgraph.h>
#include <iostream>
using namespace std;

rightProjPanel::rightProjPanel(wxSplitterWindow * parent)
: wxPanel(parent, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE)
{
    o3d_project = new object3d();
    this->Connect(wxEVT_PAINT, wxPaintEventHandler(rightProjPanel::OnPaint));
}

void rightProjPanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    // 获取图形上下文  
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    gc->Translate(52, 112);
    o3d_project->ShowProjection(gc);
    
    // 释放图形上下文  
    delete gc;
}

rightLaytPanel::rightLaytPanel(wxSplitterWindow * parent)
: wxPanel(parent, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE)
{
    o3d_layout = new object3d();
    this->Connect(wxEVT_PAINT, wxPaintEventHandler(rightLaytPanel::OnPaint));
}

void rightLaytPanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    // 获取图形上下文  
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    
    gc->Translate(52, 112);
    o3d_layout->ShowLayout(gc);

    // 释放图形上下文  
    delete gc;

}
