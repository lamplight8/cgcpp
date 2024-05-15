//panels.h
#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include "object3d.h"

class ctrlPanel : public wxPanel
{
private:
    wxRadioButton* radio1;
    wxRadioButton* radio2;

    wxTextCtrl* vrpTextX;
    wxTextCtrl* vrpTextY;
    wxTextCtrl* vrpTextZ;
    
    wxTextCtrl* prpTextU;
    wxTextCtrl* prpTextV;
    wxTextCtrl* prpTextN;

    wxTextCtrl* textTheta;
    wxTextCtrl* textPhi;
    wxTextCtrl* textDelta;

    wxTextCtrl* textCU;
    wxTextCtrl* textCV;

public:
    bool isParallel;
    int vrpx, vrpy, vrpz;
    int prpu, prpv, prpn;
    int theta, phi, delta;
    int cu, cv;

public:
    ctrlPanel(wxSplitterWindow *parent);
    void OnApple(wxCommandEvent& event);
    void OnRestore(wxCommandEvent& event);

};
const int ID_APPLE { 101 };
const int ID_RESTORE { 102 };

class projPanel : public wxPanel
{
public:
    projPanel(wxSplitterWindow *parent);
    void OnPaint(wxPaintEvent& event);
public:
    object3d* o3d_project;
};

class laytPanel : public wxPanel
{
public:
    laytPanel(wxSplitterWindow *parent);
    void OnPaint(wxPaintEvent& event);
public:
    object3d* o3d_layout;
};