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
private:
    wxMenuBar *menubar;
    wxMenu *show;
};

const int ID_COORD = 1;