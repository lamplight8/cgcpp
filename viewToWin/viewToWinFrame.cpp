//viewToWinFrame.cpp
#include "viewToWinFrame.h"
#include <wx/spinctrl.h>
#include<iostream>
using namespace std;

viewToWinFrame::viewToWinFrame(const wxString& title)
: wxFrame{ NULL, -1, title, wxDefaultPosition, wxSize(WinWidth, WinHeight) }
{
    wxStaticText* textLab1 = new wxStaticText{ this, -1, wxT("窗口宽度: "), wxPoint(60, 20) };
    wxSpinCtrl* spinCtrl1 = new wxSpinCtrl(this, -1, wxT("0"), wxPoint(120,20), wxDefaultSize, 16384L, 0, 500);
    wxStaticText* textLab2 = new wxStaticText{ this, -1, wxT("窗口高度: "), wxPoint(220, 20) };
    wxSpinCtrl* spinCtrl2 = new wxSpinCtrl(this, -1, wxT("0"), wxPoint(280,20), wxDefaultSize, 16384L, 0, 500);
    wxStaticText* textLab3 = new wxStaticText{ this, -1, wxT("视口宽度: "), wxPoint(380, 20) };
    wxSpinCtrl* spinCtrl3 = new wxSpinCtrl(this, -1, wxT("0"), wxPoint(440,20), wxDefaultSize, 16384L, 0, 500);
    wxStaticText* textLab4 = new wxStaticText{ this, -1, wxT("视口高度: "), wxPoint(540, 20) };
    wxSpinCtrl* spinCtrl4 = new wxSpinCtrl(this, -1, wxT("0"), wxPoint(600,20), wxDefaultSize, 16384L, 0, 500);

    isInWindow = false;
    isInView = false;

    int width = this->GetSize().GetWidth();
    int height = this->GetSize().GetHeight();

    wldOrg = wxPoint(50, 120); //记录世界坐标系原点
    scrOrg = wxPoint(width/2+50, 120);//记录屏幕坐标系原点

    wldRect = wxRect(0, 0, width*3/8, height*5/8);
    scrRect = wldRect;

    translate(wldRect, wldOrg);
    translate(scrRect, scrOrg);

    winRect = wxRect(wldRect.width*1/8,
                    wldRect.width*7/32,
                    wldRect.width*6/8,
                    wldRect.width*18/32);//窗口矩形
    viewRect = winRect;//视口矩形

    translate(winRect, wldOrg);
    translate(viewRect, scrOrg);

    //初始化世界坐标系中的图形
    wldFigs.push_back(wxRect(wldRect.width/20,
                         wldRect.height*3/10,
                         wldRect.width*17/20,
                         wldRect.height*4/15));
    wldFigs.push_back(wxRect(wldRect.width*11/26,
                         wldRect.height*25/70,
                         wldRect.width*5/13,
                         wldRect.height*27/70));
    wldFigs.push_back(wxRect(wldRect.width/10,
                         wldRect.height*2/3,
                         wldRect.width*17/30,
                         wldRect.height*7/30));
    wldFigs.push_back(wxRect(wldRect.width*3/10,
                         wldRect.height*1/10,
                         wldRect.width*9/20,
                         wldRect.height*11/40));
    int i;
    for(i=0; i<wldFigs.size(); i++)
        translate(wldFigs[i], wldOrg);
    //初始化屏幕坐标系中的图形
    scrFigs.resize(4);

    spinCtrl1->SetValue(winRect.width);
    spinCtrl2->SetValue(winRect.height);
    spinCtrl3->SetValue(viewRect.width);
    spinCtrl4->SetValue(viewRect.height);

    Bind(wxEVT_LEFT_DOWN, viewToWinFrame::OnMouseLeftDown, this);
    Bind(wxEVT_MOTION, viewToWinFrame::OnMouseMove, this);
    Bind(wxEVT_LEFT_UP, viewToWinFrame::OnMouseLeftUp, this);

    spinCtrl1->Bind(wxEVT_SPINCTRL, viewToWinFrame::OnSpin1, this);
    spinCtrl2->Bind(wxEVT_SPINCTRL, viewToWinFrame::OnSpin2, this);
    spinCtrl3->Bind(wxEVT_SPINCTRL, viewToWinFrame::OnSpin3, this);
    spinCtrl4->Bind(wxEVT_SPINCTRL, viewToWinFrame::OnSpin4, this);

    this->Connect(wxEVT_PAINT, wxPaintEventHandler(viewToWinFrame::OnPaint));

    Centre();
}

void viewToWinFrame::OnMouseLeftDown(wxMouseEvent& event)
{
    wxCursor csr;
    if(event.LeftDown())
    {
        SetCursor(wxCURSOR_HAND);
        oldPos.x = event.GetX();
        oldPos.y = event.GetY();
        if(winRect.Contains(oldPos))
            isInWindow=true;
        else
            isInWindow=false;

        if(viewRect.Contains(oldPos))
            isInView=true;
        else
            isInView=false;
    }

    Refresh();
}

void viewToWinFrame::OnMouseLeftUp(wxMouseEvent& event)
{
    SetCursor(wxNullCursor);
    isInWindow=false;
    isInView=false;
    Refresh();
}

void viewToWinFrame::OnMouseMove(wxMouseEvent& event)
{
    wxPoint newPos;
    newPos.x = event.GetX();
    newPos.y = event.GetY();

    if(isInWindow)
        translate(winRect, wxPoint(newPos.x-oldPos.x, newPos.y-oldPos.y));
    if(isInView)
        translate(viewRect, wxPoint(newPos.x-oldPos.x, newPos.y-oldPos.y));
    oldPos = newPos;

    Refresh();
}

void viewToWinFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    clip();//对窗口中的图形进行裁剪，并变换到视口中去
           //生成视口中的图形数据
           //wldFigs -> scrFigs
    
    //显示标题
    double x,y,w,h;
    x = this->GetSize().GetWidth()/2-50.0;
    y = 80.0;
    w = 100.0;
    h = 20;
    dc.SetTextForeground("#ff0000");
    dc.DrawText(wxT("窗口到视口的变换"), x, y);

    //处理世界坐标系
    x = wldRect.x+wldRect.width/2-20.0;
    y = wldRect.y+10.0;
    w = 40.0;
    dc.SetTextForeground("#0000ff");
    dc.DrawText(wxT("窗口"), wxPoint(x, y));

    x = wldRect.x+wldRect.width/2-30.0;
    y = wldRect.y+wldRect.height-30.0;
    w = 60.0;
    dc.SetTextForeground("#00ff00");
    dc.DrawText(wxT("世界坐标系"), x, y);

    //处理屏幕坐标系
    x = scrRect.x+scrRect.width/2-20.0;
    y = scrRect.y+10.0;
    w = 40.0;
    dc.SetTextForeground("#0000ff");
    dc.DrawText(wxT("视口"), x, y);

    x = scrRect.x+scrRect.width/2-30.0;
    y = scrRect.y+scrRect.height-30.0;
    w = 60.0;
    dc.SetTextForeground("#00ff00");
    dc.DrawText(wxT("屏幕坐标系"), x, y);

    //绘制世界坐标系图形
    drawRect(&dc, wldRect, "#00ff00");
    drawRect(&dc, wldFigs[0], "#000000");
    drawRect(&dc, wldFigs[1], "#000000");
    drawRect(&dc, wldFigs[2], "#000000");
    drawRect(&dc, wldFigs[3], "#000000");
    drawRect(&dc, winRect, "#0000ff");

    //绘制屏幕坐标系图形
    drawRect(&dc, scrRect, "#00ff00");
    drawRect(&dc, scrFigs[0], "#000000");
    drawRect(&dc, scrFigs[1], "#000000");
    drawRect(&dc, scrFigs[2], "#000000");
    drawRect(&dc, scrFigs[3], "#000000");
    drawRect(&dc, viewRect, "#0000ff");

}

void viewToWinFrame::translate(wxRect& rect, wxPoint p)
{
    rect.x += p.x;
    rect.y += p.y;
}

void viewToWinFrame::clip()
{
    wxRect wr;
    double sx = static_cast<double>(viewRect.width)/winRect.width;
    double sy = static_cast<double>(viewRect.height)/winRect.height;
    int dx = viewRect.x-winRect.x;
    int dy = viewRect.y-winRect.y;
    int xMin;
    int yMin;
    int uMin;
    int vMin;
    wxRect rt;
    for(int i=0; i<wldFigs.size(); i++)
    {
        rt = wldFigs[i];
        wr = rt.Intersect(winRect);
        //当前矩形与窗口求交运算，得到裁剪后的矩形
        xMin = wr.x-winRect.x;
        //当前矩形左上角相对于窗口左上角x坐标
        yMin = wr.y-winRect.y;
        //当前矩形左上角相对于窗口左上角y坐标
        uMin = sx*xMin;//当前矩形左上角相对于视口左上角x坐标
        vMin = sy*yMin;//当前矩形左上角相对于视口左上角y坐标

        translate(wr,wxPoint(-xMin, -yMin));
        wr.SetWidth(sx*wr.width);
        wr.SetHeight(sy*wr.height);//沿y方向的放缩变换
        translate(wr, wxPoint(dx,dy));//平道至视口左上角
        translate(wr, wxPoint(uMin, vMin));//平移至视口对应位置
        scrFigs[i] = wr;
    }
}

void viewToWinFrame::drawRect(wxPaintDC* pdc, wxRect rect, wxColor clr)
{
    pdc->SetPen(wxPen(clr));
    int x0 = rect.x;
    int y0 = rect.y;
    int x1 = rect.x + rect.width;
    int y1 = rect.y + rect.height;

    pdc->DrawLine(wxPoint(x0, y0), wxPoint(x0, y1));
    pdc->DrawLine(wxPoint(x0, y1), wxPoint(x1, y1));
    pdc->DrawLine(wxPoint(x1, y1), wxPoint(x1, y0));
    pdc->DrawLine(wxPoint(x1, y0), wxPoint(x0, y0));
}

void viewToWinFrame::OnSpin1(wxSpinEvent& event)
{
    winRect.width = event.GetValue();
    Refresh();
}

void viewToWinFrame::OnSpin2(wxSpinEvent& event)
{
    winRect.height = event.GetValue();
    Refresh();
}

void viewToWinFrame::OnSpin3(wxSpinEvent& event)
{
    viewRect.width = event.GetValue();
    Refresh();
}

void viewToWinFrame::OnSpin4(wxSpinEvent& event)
{
    viewRect.height = event.GetValue();
    Refresh();
}

