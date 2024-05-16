//house3dFrame.h
#include "rightPanel.h"

const int Width { 800 };
const int Height { 600 };

class house3dFrame: public wxFrame
{
public:
    house3dFrame(const wxString& title);
    void OnApple(wxCommandEvent& event);
    void OnRestore(wxCommandEvent& event);

public:
    rightLaytPanel* rp1;
    rightProjPanel* rp2;

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

    int projType;
    double vrpx, vrpy, vrpz;
    double prpu, prpv, prpn;
    double theta, phi, delta;
    double cu, cv;
};

const int ID_APPLE { 101 };
const int ID_RESTORE { 102 };
