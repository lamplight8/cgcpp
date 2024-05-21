//main.cpp
#include "main.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    MyFrame* frame = new MyFrame{ wxT("绘制金字塔") };

    frame->Show(true);

    return true;
}
