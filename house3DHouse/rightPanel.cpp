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

    //gc->Translate(52, 102);
    
    // 创建一个 wxFont 对象
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial"); 
    gc->SetFont(font, wxColor(255,0, 0));
    gc->DrawText("x:", 10, 10);

    // 设置画笔  
    wxPen pen(wxColor(255, 0, 0), 1); // 蓝色，2像素宽  
    gc->SetPen(pen);

    gc->StrokeLine(11, 11, 200, 200);

    //gc->Translate(52, 102);

    //o3d_project->ShowLayout(gc);
    
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
    
    // 创建一个 wxFont 对象
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial"); 
    gc->SetFont(font, wxColor(255,0, 0));
    //gc->DrawText("x:", 10, 10);

    // 设置画笔  
    wxPen pen(wxColor(255, 0, 0), 1); // 蓝色，2像素宽  
    gc->SetPen(pen);

    //cout<<o3d_layout->nProjectionType<<endl;
    //cout<<o3d_layout->VRP[0]<<", "<<o3d_layout->VRP[1]<<", "<<o3d_layout->VRP[2]<<endl;
    //cout<<o3d_layout->PRP[0]<<", "<<o3d_layout->PRP[1]<<", "<<o3d_layout->PRP[2]<<endl;
    //cout<<o3d_layout->Theta<<", "<<o3d_layout->Phi<<", "<<o3d_layout->Delta<<endl;
    //cout<<o3d_layout->CW[0]<<", "<<o3d_layout->CW[1]<<endl;

    gc->Translate(52, 102);
    o3d_layout->ShowLayout(gc);

    // 释放图形上下文  
    delete gc;
}
