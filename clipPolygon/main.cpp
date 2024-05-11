//main.cpp
#include "main.h"
#include "clipPolygonFrame.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    clipPolygonFrame *dl = new clipPolygonFrame{ wxT("多边形裁剪算法") };
    dl->Show(true);
    return true;
}
