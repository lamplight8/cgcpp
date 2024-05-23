// interaction.h
#include <wx/wx.h>
#include <wx/menu.h>

const int Width { 800 };
const int Height { 600 };

class interactionFrame : public wxFrame
{
public:
    interactionFrame(const wxString& title);
    void OnCoordinate(wxCommandEvent& event);
    void OnRubber(wxCommandEvent& event);
    void OnTranslate(wxCommandEvent& event);
    void OnScale(wxCommandEvent& event);
    void OnRotate(wxCommandEvent& event);
    void OnGravity(wxCommandEvent& event);
    void OnDirection(wxCommandEvent& event);
    void OnGrid(wxCommandEvent& event);
    void OnRuler(wxCommandEvent& event);
    void OnGuide(wxCommandEvent& event);
private:
    wxMenuBar *menubar;
    wxMenu *show;
};

const int ID_COORDINATE = 1;
const int ID_RUBBER = 2;
const int ID_TRANSLATE = 3;
const int ID_SCALE = 4;
const int ID_ROTATE = 5;
const int ID_GRAVITY = 6;
const int ID_DIRECTION = 7;
const int ID_GRID = 8;
const int ID_RULER = 9;
const int ID_GUIDE = 10;