//Panels.cpp
#include "panels.h"
#include <iostream>
using namespace std;

ctrlPanel::ctrlPanel(wxSplitterWindow *parent)
: wxPanel(parent, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE)
{
    //设置投影控件
    const wxString* itemP= new wxString[2]{wxT("平行投影"), wxT("透视投影")};
    wxRadioBox* radioBox = new wxRadioBox(this, wxID_ANY, wxT("投影类型"), wxPoint(10, 10), wxSize(200, 50), 0, itemP, 2);
    radio1 = new wxRadioButton(radioBox, wxID_ANY, itemP[0], wxPoint(10, 20), wxDefaultSize, 0);
    radio2 = new wxRadioButton(radioBox, wxID_ANY, itemP[1], wxPoint(120, 20), wxDefaultSize, 0);
    radio1->SetValue(true);

    //设置视图参考点控件
    wxStaticBox* boxVRP = new wxStaticBox(this, wxID_ANY, wxT("视点VRP坐标"), wxPoint(10, 70), wxSize(200, 110));
    wxStaticText* vrpLabelX = new wxStaticText(boxVRP, wxID_ANY, wxT("x: "), wxPoint(10, 20));
    vrpTextX = new wxTextCtrl(boxVRP, wxID_ANY, wxT("0"), wxPoint(30, 20));
    wxStaticText* vrpLabelY = new wxStaticText(boxVRP, wxID_ANY, wxT("y: "), wxPoint(10, 50));
    vrpTextY = new wxTextCtrl(boxVRP, wxID_ANY, wxT("0"), wxPoint(30, 50));
    wxStaticText* vrpLabelZ = new wxStaticText(boxVRP, wxID_ANY, wxT("z: "), wxPoint(10, 80));
    vrpTextZ = new wxTextCtrl(boxVRP, wxID_ANY, wxT("0"), wxPoint(30, 80));
    
    //设置投影参考点控件
    wxStaticBox* boxPRP = new wxStaticBox(this, wxID_ANY, wxT("投影点PRP坐标"), wxPoint(10, 190), wxSize(200, 110));
    wxStaticText* prpLableU = new wxStaticText(boxPRP, wxID_ANY, wxT("u: "), wxPoint(10, 20));
    prpTextU = new wxTextCtrl(boxPRP, wxID_ANY, wxT("250"), wxPoint(30, 20));
    wxStaticText* prpLableV = new wxStaticText(boxPRP, wxID_ANY, wxT("v: "), wxPoint(10, 50));
    prpTextV = new wxTextCtrl(boxPRP, wxID_ANY, wxT("100"), wxPoint(30, 50));
    wxStaticText* prpLableN = new wxStaticText(boxPRP, wxID_ANY, wxT("n: "), wxPoint(10, 80));
    prpTextN = new wxTextCtrl(boxPRP, wxID_ANY, wxT("250"), wxPoint(30, 80));

    //设置偏转角度控件
    wxStaticBox* boxAngle = new wxStaticBox(this, wxID_ANY, wxT("偏转角"), wxPoint(10, 310), wxSize(200, 110));
    wxStaticText* lableTheta = new wxStaticText(boxAngle, wxID_ANY, wxT("theta: "), wxPoint(10, 20));
    textTheta = new wxTextCtrl(boxAngle, wxID_ANY, wxT("0"), wxPoint(50, 20));
    wxStaticText* labelPhi = new wxStaticText(boxAngle, wxID_ANY, wxT("phi: "), wxPoint(10, 50));
    textPhi = new wxTextCtrl(boxAngle, wxID_ANY, wxT("0"), wxPoint(50, 50));
    wxStaticText* lableDelta = new wxStaticText(boxAngle, wxID_ANY, wxT("delta: "), wxPoint(10, 80));
    textDelta = new wxTextCtrl(boxAngle, wxID_ANY, wxT("0"), wxPoint(50, 80));

    //设置窗口中心控件
    wxStaticBox* winCenter = new wxStaticBox(this, wxID_ANY, wxT("窗口中心CW"), wxPoint(10, 430), wxSize(200, 80));
    wxStaticText* lableCU = new wxStaticText(winCenter, wxID_ANY, wxT("cu: "), wxPoint(10, 20));
    textCU = new wxTextCtrl(winCenter, wxID_ANY, wxT("0"), wxPoint(30, 20));
    wxStaticText* labelCV = new wxStaticText(winCenter, wxID_ANY, wxT("cv: "), wxPoint(10, 50));
    textCV = new wxTextCtrl(winCenter, wxID_ANY, wxT("0"), wxPoint(30, 50));

    //设置按钮控件
    wxButton *butOk = new wxButton{ this, ID_APPLE, wxT("Apple"), wxPoint(20, 520) };
    wxButton *butRestore = new wxButton{ this, ID_RESTORE, wxT("Retore"), wxPoint(120, 520) };

    //读取面板参数
    //vrpx = radio1.GetValue()->GetValue().plCtrl->vrpTextX;

    vrpTextX->GetValue().ToInt(&vrpx);
    vrpTextY->GetValue().ToInt(&vrpy);
    vrpTextZ->GetValue().ToInt(&vrpz);

    prpTextU->GetValue().ToInt(&prpu);
    prpTextV->GetValue().ToInt(&prpv);
    prpTextN->GetValue().ToInt(&prpn);

    textTheta->GetValue().ToInt(&theta);
    textPhi->GetValue().ToInt(&phi);
    textDelta->GetValue().ToInt(&delta);

    textCU->GetValue().ToInt(&cu);
    textCV->GetValue().ToInt(&cv);

    this->Connect(ID_APPLE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ctrlPanel::OnApple));
    this->Connect(ID_RESTORE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ctrlPanel::OnRestore));
    this->Connect(wxEVT_PAINT, wxPaintEventHandler(ctrlPanel::OnPaint));
}

void ctrlPanel::OnApple(wxCommandEvent& event)
{
    isParallel = radio1->GetValue();
    
    vrpTextX->GetValue().ToInt(&vrpx);
    vrpTextY->GetValue().ToInt(&vrpy);
    vrpTextZ->GetValue().ToInt(&vrpz);

    prpTextU->GetValue().ToInt(&prpu);
    prpTextV->GetValue().ToInt(&prpv);
    prpTextN->GetValue().ToInt(&prpn);

    textTheta->GetValue().ToInt(&theta);
    textPhi->GetValue().ToInt(&phi);
    textDelta->GetValue().ToInt(&delta);

    textCU->GetValue().ToInt(&cu);
    textCV->GetValue().ToInt(&cv);

    Refresh();
}

void ctrlPanel::OnRestore(wxCommandEvent& event)
{
    radio1->SetValue(true);
    vrpTextX->SetValue(wxT("0"));
    vrpTextY->SetValue(wxT("0"));
    vrpTextZ->SetValue(wxT("0"));
    prpTextU->SetValue(wxT("250"));
    prpTextV->SetValue(wxT("150"));
    prpTextN->SetValue(wxT("250"));
    textTheta->SetValue(wxT("0"));
    textPhi->SetValue(wxT("0"));
    textDelta->SetValue(wxT("0"));
    textCU->SetValue(wxT("0"));
    textCV->SetValue(wxT("0"));

    isParallel = radio1->GetValue();
        
    vrpTextX->GetValue().ToInt(&vrpx);
    vrpTextY->GetValue().ToInt(&vrpy);
    vrpTextZ->GetValue().ToInt(&vrpz);

    prpTextU->GetValue().ToInt(&prpu);
    prpTextV->GetValue().ToInt(&prpv);
    prpTextN->GetValue().ToInt(&prpn);

    textTheta->GetValue().ToInt(&theta);
    textPhi->GetValue().ToInt(&phi);
    textDelta->GetValue().ToInt(&delta);

    textCU->GetValue().ToInt(&cu);
    textCV->GetValue().ToInt(&cv);

    Refresh();
}


projPanel::projPanel(wxSplitterWindow * parent)
: wxPanel(parent, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE)
{
    ctrlPanel *p = (ctrlPanel *) parent->GetParent();
 
    int t;
    double vx = static_cast<double>(p->vrpx);
    double vy = static_cast<double>(p->vrpy);
    double vz = static_cast<double>(p->vrpz);

    double pu = static_cast<double>(p->prpu);
    double pv = static_cast<double>(p->prpv);
    double pn = static_cast<double>(p->prpn);

    double th = static_cast<double>(p->theta);
    double ph = static_cast<double>(p->phi);
    double dl = static_cast<double>(p->delta);

    double u = static_cast<double>(p->cu);
    double v = static_cast<double>(p->cv);

    if(p->isParallel)
        t = 1;
    else
        t = 0;
    o3d_project = new object3d(t, vx, vy, vz, pu, pv, pn, th, ph, dl, u, v);

    this->Connect(wxEVT_PAINT, wxPaintEventHandler(projPanel::OnPaint));
}

laytPanel::laytPanel(wxSplitterWindow * parent)
: wxPanel(parent, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE)
{
    ctrlPanel *p = parent->GetParent();
 
    int t;
    double vx = static_cast<double>(p->vrpx);
    double vy = static_cast<double>(p->vrpy);
    double vz = static_cast<double>(p->vrpz);

    double pu = static_cast<double>(p->prpu);
    double pv = static_cast<double>(p->prpv);
    double pn = static_cast<double>(p->prpn);

    double th = static_cast<double>(p->theta);
    double ph = static_cast<double>(p->phi);
    double dl = static_cast<double>(p->delta);

    double u = static_cast<double>(p->cu);
    double v = static_cast<double>(p->cv);

    if(p->isParallel)
        t = 1;
    else
        t = 0;

    cout<<t<<endl;
    cout<<pu<<endl;

    o3d_layout = new object3d(t, vx, vy, vz, pu, pv, pn, th, ph, dl, u, v);

    this->Connect(wxEVT_PAINT, wxPaintEventHandler(laytPanel::OnPaint));
}

void projPanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    
    o3d_project->ShowProjection(&dc);
}


void laytPanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    o3d_layout->ShowLayout(&dc);
}