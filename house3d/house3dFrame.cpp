//house3dFrame.cpp
#include "house3dFrame.h"
#include <iostream>
using namespace std;

house3dFrame::house3dFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(Width, Height))
{
    //设置控制面板、投影面板、布局面板
    wxSplitterWindow *spl = new wxSplitterWindow(this, -1, wxDefaultPosition, wxSize(Width, Height));//总的可裂变窗口
    wxSplitterWindow *splRight = new wxSplitterWindow(spl, -1, wxDefaultPosition, wxSize(550, Height));//右面可裂变窗口

    wxPanel* ctrlPanel = new wxPanel(spl, wxID_ANY, wxDefaultPosition, wxDefaultSize);//产生左边控制面板
    rp1 = new rightLaytPanel(splRight);//产生右面布局视图面板
    rp2 = new rightProjPanel(splRight);//产生右面投影视图面板

    spl->SplitVertically(ctrlPanel, splRight);
    splRight->SplitHorizontally(rp1, rp2);

    //设置投影控件
    const wxString* itemP= new wxString[2]{wxT("平行投影"), wxT("透视投影")};
    wxRadioBox* radioBox = new wxRadioBox(ctrlPanel, wxID_ANY, wxT("投影类型"), wxPoint(10, 10), wxSize(200, 50), 0, itemP, 2);
    radio1 = new wxRadioButton(radioBox, wxID_ANY, itemP[0], wxPoint(10, 20), wxDefaultSize, 0);
    radio2 = new wxRadioButton(radioBox, wxID_ANY, itemP[1], wxPoint(120, 20), wxDefaultSize, 0);
    radio1->SetValue(true);

    //设置视图参考点控件
    wxStaticBox* boxVRP = new wxStaticBox(ctrlPanel, wxID_ANY, wxT("视点VRP坐标"), wxPoint(10, 70), wxSize(200, 110));
    wxStaticText* vrpLabelX = new wxStaticText(boxVRP, wxID_ANY, wxT("x: "), wxPoint(10, 20));
    vrpTextX = new wxTextCtrl(boxVRP, wxID_ANY, wxT("0"), wxPoint(30, 20));
    wxStaticText* vrpLabelY = new wxStaticText(boxVRP, wxID_ANY, wxT("y: "), wxPoint(10, 50));
    vrpTextY = new wxTextCtrl(boxVRP, wxID_ANY, wxT("0"), wxPoint(30, 50));
    wxStaticText* vrpLabelZ = new wxStaticText(boxVRP, wxID_ANY, wxT("z: "), wxPoint(10, 80));
    vrpTextZ = new wxTextCtrl(boxVRP, wxID_ANY, wxT("0"), wxPoint(30, 80));
    
    //设置投影参考点控件
    wxStaticBox* boxPRP = new wxStaticBox(ctrlPanel, wxID_ANY, wxT("投影点PRP坐标"), wxPoint(10, 190), wxSize(200, 110));
    wxStaticText* prpLableU = new wxStaticText(boxPRP, wxID_ANY, wxT("u: "), wxPoint(10, 20));
    prpTextU = new wxTextCtrl(boxPRP, wxID_ANY, wxT("250"), wxPoint(30, 20));
    wxStaticText* prpLableV = new wxStaticText(boxPRP, wxID_ANY, wxT("v: "), wxPoint(10, 50));
    prpTextV = new wxTextCtrl(boxPRP, wxID_ANY, wxT("100"), wxPoint(30, 50));
    wxStaticText* prpLableN = new wxStaticText(boxPRP, wxID_ANY, wxT("n: "), wxPoint(10, 80));
    prpTextN = new wxTextCtrl(boxPRP, wxID_ANY, wxT("250"), wxPoint(30, 80));

    //设置偏转角度控件
    wxStaticBox* boxAngle = new wxStaticBox(ctrlPanel, wxID_ANY, wxT("偏转角"), wxPoint(10, 310), wxSize(200, 110));
    wxStaticText* lableTheta = new wxStaticText(boxAngle, wxID_ANY, wxT("theta: "), wxPoint(10, 20));
    textTheta = new wxTextCtrl(boxAngle, wxID_ANY, wxT("0"), wxPoint(50, 20));
    wxStaticText* labelPhi = new wxStaticText(boxAngle, wxID_ANY, wxT("phi: "), wxPoint(10, 50));
    textPhi = new wxTextCtrl(boxAngle, wxID_ANY, wxT("0"), wxPoint(50, 50));
    wxStaticText* lableDelta = new wxStaticText(boxAngle, wxID_ANY, wxT("delta: "), wxPoint(10, 80));
    textDelta = new wxTextCtrl(boxAngle, wxID_ANY, wxT("0"), wxPoint(50, 80));

    //设置窗口中心控件
    wxStaticBox* winCenter = new wxStaticBox(ctrlPanel, wxID_ANY, wxT("窗口中心CW"), wxPoint(10, 430), wxSize(200, 80));
    wxStaticText* lableCU = new wxStaticText(winCenter, wxID_ANY, wxT("cu: "), wxPoint(10, 20));
    textCU = new wxTextCtrl(winCenter, wxID_ANY, wxT("0"), wxPoint(30, 20));
    wxStaticText* labelCV = new wxStaticText(winCenter, wxID_ANY, wxT("cv: "), wxPoint(10, 50));
    textCV = new wxTextCtrl(winCenter, wxID_ANY, wxT("0"), wxPoint(30, 50));

    //设置按钮控件
    wxButton *butOk = new wxButton{ ctrlPanel, ID_APPLE, wxT("Apple"), wxPoint(20, 520) };
    wxButton *butRestore = new wxButton{ ctrlPanel, ID_RESTORE, wxT("Retore"), wxPoint(120, 520) };

    Connect(ID_APPLE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(house3dFrame::OnApple));
    Connect(ID_RESTORE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(house3dFrame::OnRestore));

    //读取初始面板参数
    if(radio1->GetValue())
        projType = 1;

    vrpTextX->GetValue().ToDouble(&vrpx);
    vrpTextY->GetValue().ToDouble(&vrpy);
    vrpTextZ->GetValue().ToDouble(&vrpz);

    prpTextU->GetValue().ToDouble(&prpu);
    prpTextV->GetValue().ToDouble(&prpv);
    prpTextN->GetValue().ToDouble(&prpn);

    textTheta->GetValue().ToDouble(&theta);
    textPhi->GetValue().ToDouble(&phi);
    textDelta->GetValue().ToDouble(&delta);

    textCU->GetValue().ToDouble(&cu);
    textCV->GetValue().ToDouble(&cv);

    rp1->o3d_layout->setParameter(
        projType,
        vrpx, vrpy, vrpz,
        prpu, prpv, prpn,
        theta, phi, delta,
        cu, cv
    );
    rp2->o3d_project->setParameter(
        projType,
        vrpx, vrpy, vrpz,
        prpu, prpv, prpn,
        theta, phi, delta,
        cu, cv
    );

    Center();
}

//刷新面板参数
void house3dFrame::OnApple(wxCommandEvent& event)
{
    if(radio1->GetValue())
        projType = 1;
    
    vrpTextX->GetValue().ToDouble(&vrpx);
    vrpTextY->GetValue().ToDouble(&vrpy);
    vrpTextZ->GetValue().ToDouble(&vrpz);

    prpTextU->GetValue().ToDouble(&prpu);
    prpTextV->GetValue().ToDouble(&prpv);
    prpTextN->GetValue().ToDouble(&prpn);

    textTheta->GetValue().ToDouble(&theta);
    textPhi->GetValue().ToDouble(&phi);
    textDelta->GetValue().ToDouble(&delta);

    textCU->GetValue().ToDouble(&cu);
    textCV->GetValue().ToDouble(&cv);

    rp1->o3d_layout->setParameter(
        projType,
        vrpx, vrpy, vrpz,
        prpu, prpv, prpn,
        theta, phi, delta,
        cu, cv
    );
    rp2->o3d_project->setParameter(
        projType,
        vrpx, vrpy, vrpz,
        prpu, prpv, prpn,
        theta, phi, delta,
        cu, cv
    );

    this->Refresh();
    rp1->Refresh();
    rp2->Refresh();
}

//复位面板参数
void house3dFrame::OnRestore(wxCommandEvent& event)
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

    if(radio1->GetValue())
        projType = 1;
        
    vrpTextX->GetValue().ToDouble(&vrpx);
    vrpTextY->GetValue().ToDouble(&vrpy);
    vrpTextZ->GetValue().ToDouble(&vrpz);

    prpTextU->GetValue().ToDouble(&prpu);
    prpTextV->GetValue().ToDouble(&prpv);
    prpTextN->GetValue().ToDouble(&prpn);

    textTheta->GetValue().ToDouble(&theta);
    textPhi->GetValue().ToDouble(&phi);
    textDelta->GetValue().ToDouble(&delta);

    textCU->GetValue().ToDouble(&cu);
    textCV->GetValue().ToDouble(&cv);

    rp1->o3d_layout->setParameter(
        projType,
        vrpx, vrpy, vrpz,
        prpu, prpv, prpn,
        theta, phi, delta,
        cu, cv
    );
    rp2->o3d_project->setParameter(
        projType,
        vrpx, vrpy, vrpz,
        prpu, prpv, prpn,
        theta, phi, delta,
        cu, cv
    );

    this->Refresh();
    rp1->Refresh();
    rp2->Refresh();
}