//main.cpp
#include "main.h"
#include "viewToWinFrame.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    viewToWinFrame *dl = new viewToWinFrame{ wxT("视窗变换") };
    dl->Show(true);
    return true;
}
