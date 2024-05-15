//rightLaytPanel.cpp
#include "rightLaytPanel.h"

rightLaytPanel::rightLaytPanel(wxSplitterWindow * parent)
: wxPanel(parent, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE)
{
    this->Connect(wxEVT_PAINT, wxPaintEventHandler(rightLaytPanel::OnPaint));
}

void rightLaytPanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    // 获取图形上下文  
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);  
         
    // 设置画笔和画刷  
    gc->SetPen(wxPen(wxColor(0, 0, 0), 1)); // 黑色画笔，线宽1  
    gc->SetBrush(wxBrush(wxColor(255, 0, 0), wxBRUSHSTYLE_SOLID)); // 红色画刷  
    
    int dx = 52;
    int dy = 102;
    gc->Translate(dx, dy);

    // 绘制矩形  
    gc->DrawRectangle(0, 0, 100, 100); // 左上角坐标(0, 0)，宽度和高度都是100  
      
    // 释放图形上下文  
    delete gc;

}