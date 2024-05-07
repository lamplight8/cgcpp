//clipPolygonFrame.h
#include "clipPolygon.h"
#include <wx/colordlg.h>

const int WinWidth { 1000 };
const int WinHeight { 750 };

class clipPolygonFrame : public wxFrame
{
public:
    clipPolygonFrame(const wxString& title);
    void OnOk(wxCommandEvent& event);
    void OnOldColor(wxCommandEvent& event);
    void OnNewColor(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
private:
    wxTextCtrl *tcx;
    wxTextCtrl *tcy;
    wxTextCtrl *tcw;
    wxTextCtrl *tch;
    wxTextCtrl *tcn;
    wxTextCtrl *tcx0;
    wxTextCtrl *tcy0;
    wxTextCtrl *tcx1;
    wxTextCtrl *tcy1;
    wxTextCtrl *tcx2;
    wxTextCtrl *tcy2;
    wxTextCtrl *tcx3;
    wxTextCtrl *tcy3;
    wxTextCtrl *tcx4;
    wxTextCtrl *tcy4;
    wxTextCtrl *tcx5;
    wxTextCtrl *tcy5;

private:
    wxColor oldColor, newColor;
    rect rt;
    int n;
    wxPoint* ptv;
};

const int ID_OK { 101 };
const int ID_OLDCOLOR { 102 };
const int ID_NEWCOLOR { 103 };

