//house3dFrame.cpp

#include "house3dFrame.h"
//#include <wx/statbox.h>


house3dFrame::house3dFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(Width, Height))
{
    //设置控制面板、投影面板、布局面板
    wxSplitterWindow *spl1 = new wxSplitterWindow(this, -1, wxDefaultPosition, wxSize(Width, Height));
    wxSplitterWindow *spl2 = new wxSplitterWindow(spl1, -1, wxDefaultPosition, wxSize(550, 550));
    wxPanel* panelCtrl = new wxPanel(spl1, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE);
    wxPanel* panelPorj = new wxPanel(spl2, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE);
    wxPanel* panelLayt = new wxPanel(spl2, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxBORDER_DOUBLE);
    spl1->SplitVertically(panelCtrl, spl2);
    spl2->SplitHorizontally(panelPorj, panelLayt);

    //设置投影控件
    const wxString* itemP= new wxString[2]{wxT("平行投影"), wxT("透视投影")};
    wxRadioBox* radioBox = new wxRadioBox(panelCtrl, wxID_ANY, wxT("投影类型"), wxPoint(10, 10), wxSize(200, 50), 0, itemP, 2);
    wxRadioButton* radio1 = new wxRadioButton(radioBox, wxID_ANY, itemP[0], wxPoint(10, 20), wxDefaultSize, 0);
    wxRadioButton* radio2 = new wxRadioButton(radioBox, wxID_ANY, itemP[1], wxPoint(120, 20), wxDefaultSize, 0);

    //设置视图参考点控件
    wxStaticBox* boxVRP = new wxStaticBox(panelCtrl, wxID_ANY, wxT("视点VRP坐标"), wxPoint(10, 70), wxSize(200, 110));
    wxStaticText* vrpLabelX = new wxStaticText(boxVRP, wxID_ANY, wxT("x: "), wxPoint(10, 20));
    wxTextCtrl* vrpTextX = new wxTextCtrl(boxVRP, wxID_ANY, wxT("0"), wxPoint(30, 20));
    wxStaticText* vrpLabelY = new wxStaticText(boxVRP, wxID_ANY, wxT("y: "), wxPoint(10, 50));
    wxTextCtrl* vrpTextY = new wxTextCtrl(boxVRP, wxID_ANY, wxT("0"), wxPoint(30, 50));
    wxStaticText* vrpLabelZ = new wxStaticText(boxVRP, wxID_ANY, wxT("z: "), wxPoint(10, 80));
    wxTextCtrl* vrpTextZ = new wxTextCtrl(boxVRP, wxID_ANY, wxT("0"), wxPoint(30, 80));
    
    //设置投影参考点控件
    wxStaticBox* boxPRP = new wxStaticBox(panelCtrl, wxID_ANY, wxT("投影点PRP坐标"), wxPoint(10, 190), wxSize(200, 110));
    wxStaticText* prpLableU = new wxStaticText(boxPRP, wxID_ANY, wxT("u: "), wxPoint(10, 20));
    wxTextCtrl* prpTextU = new wxTextCtrl(boxPRP, wxID_ANY, wxT("250"), wxPoint(30, 20));
    wxStaticText* prpLableV = new wxStaticText(boxPRP, wxID_ANY, wxT("v: "), wxPoint(10, 50));
    wxTextCtrl* prpTextV = new wxTextCtrl(boxPRP, wxID_ANY, wxT("100"), wxPoint(30, 50));
    wxStaticText* prpLableN = new wxStaticText(boxPRP, wxID_ANY, wxT("n: "), wxPoint(10, 80));
    wxTextCtrl* prpTextN = new wxTextCtrl(boxPRP, wxID_ANY, wxT("250"), wxPoint(30, 80));

    //设置偏转角度控件
    wxStaticBox* boxAngle = new wxStaticBox(panelCtrl, wxID_ANY, wxT("偏转角"), wxPoint(10, 310), wxSize(200, 110));
    wxStaticText* lableTheta = new wxStaticText(boxAngle, wxID_ANY, wxT("theta: "), wxPoint(10, 20));
    wxTextCtrl* textTheta = new wxTextCtrl(boxAngle, wxID_ANY, wxT("0"), wxPoint(50, 20));
    wxStaticText* labelPhi = new wxStaticText(boxAngle, wxID_ANY, wxT("phi: "), wxPoint(10, 50));
    wxTextCtrl* textPhi = new wxTextCtrl(boxAngle, wxID_ANY, wxT("0"), wxPoint(50, 50));
    wxStaticText* lableDelta = new wxStaticText(boxAngle, wxID_ANY, wxT("delta: "), wxPoint(10, 80));
    wxTextCtrl* textDelta = new wxTextCtrl(boxAngle, wxID_ANY, wxT("0"), wxPoint(50, 80));

    //设置窗口中心控件
    wxStaticBox* winCenter = new wxStaticBox(panelCtrl, wxID_ANY, wxT("窗口中心CW"), wxPoint(10, 430), wxSize(200, 80));
    wxStaticText* lableCU = new wxStaticText(winCenter, wxID_ANY, wxT("cu: "), wxPoint(10, 20));
    wxTextCtrl* textCU = new wxTextCtrl(winCenter, wxID_ANY, wxT("0"), wxPoint(30, 20));
    wxStaticText* labelCV = new wxStaticText(winCenter, wxID_ANY, wxT("cv: "), wxPoint(10, 50));
    wxTextCtrl* textCV = new wxTextCtrl(winCenter, wxID_ANY, wxT("0"), wxPoint(30, 50));

    //设置按钮控件
    wxButton *butOk = new wxButton{ panelCtrl, ID_OK, wxT("Ok"), wxPoint(20, 520) };
    wxButton *butRestore = new wxButton{ panelCtrl, ID_RESTORE, wxT("Retore"), wxPoint(120, 520) };
    
    Center();
}
