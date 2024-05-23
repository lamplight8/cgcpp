//interaction.cpp
#include "interaction.h"

interactionFrame::interactionFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title)
{
    SetClientSize(Width, Height);

    menubar = new wxMenuBar;
    show = new wxMenu;
    show->Append(ID_COORD, wxT("&显示坐标"));
    menubar->Append(show, wxT("&演示"));
    SetMenuBar(menubar);

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(interactionFrame::OnCoordinate));
    Centre();

}

void interactionFrame::OnCoordinate(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    //Close(true);
}