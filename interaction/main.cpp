//main.cpp
#include "main.h"
#include "interaction.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    interactionFrame *menu = new interactionFrame(wxT("Simple Menu"));
    menu->Show(true);

    return true;
}