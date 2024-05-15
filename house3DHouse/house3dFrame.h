//house3dFrame.h
#include "rightProjPanel.h"
#include "rightLaytPanel.h"

const int Width { 800 };
const int Height { 600 };

class house3dFrame: public wxFrame
{
public:
    house3dFrame(const wxString& title);
    void OnApple(wxCommandEvent& event);
    void OnRestore(wxCommandEvent& event);

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
    int vrpx, vrpy, vrpz;
    int prpu, prpv, prpn;
    int theta, phi, delta;
    int cu, cv;
};

const int ID_APPLE { 101 };
const int ID_RESTORE { 102 };
