//main.cpp
#include "main.h"
#include "house3dFrame.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    house3dFrame *dl = new house3dFrame{ wxT("绘制3D房屋") };
    dl->Show(true);
    return true;
}
