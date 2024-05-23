//interaction.cpp
#include "interaction.h"

interactionFrame::interactionFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title)
{
    SetClientSize(Width, Height);

    //创建菜单
    menubar = new wxMenuBar;
    show = new wxMenu;
    show->Append(ID_COORDINATE, wxT("&显示坐标"));
    show->Append(ID_RUBBER, wxT("&橡皮筋"));
    show->Append(ID_TRANSLATE, wxT("&移动"));
    show->Append(ID_SCALE, wxT("&缩放"));
    show->Append(ID_ROTATE, wxT("&旋转"));
    show->Append(ID_GRAVITY, wxT("&引力场"));
    show->Append(ID_DIRECTION, wxT("&定向"));
    show->Append(ID_GRID, wxT("&网格"));
    show->Append(ID_RULER, wxT("&标尺"));
    show->Append(ID_GUIDE, wxT("&引导线"));
    
    menubar->Append(show, wxT("&演示"));
    SetMenuBar(menubar);

    Connect(ID_COORDINATE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(interactionFrame::OnCoordinate));
    Connect(ID_RUBBER, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(interactionFrame::OnRubber));
    Connect(ID_TRANSLATE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(interactionFrame::OnTranslate));
    Connect(ID_SCALE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(interactionFrame::OnScale));
    Connect(ID_ROTATE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(interactionFrame::OnRotate));
    Connect(ID_GRAVITY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(interactionFrame::OnGravity));
    Connect(ID_DIRECTION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(interactionFrame::OnDirection));
    Connect(ID_GRID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(interactionFrame::OnGrid));
    Connect(ID_RULER, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(interactionFrame::OnRuler));
    Connect(ID_GUIDE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(interactionFrame::OnGuide));

    //创建工具栏
    wxImage::AddHandler(new wxPNGHandler);
    wxBitmap coordinate(wxT("..\\bmp\\show.png"), wxBITMAP_TYPE_PNG);
    wxBitmap rubber(wxT("..\\bmp\\rubberband.png"), wxBITMAP_TYPE_PNG);
    wxBitmap translate(wxT("..\\bmp\\translate.png"), wxBITMAP_TYPE_PNG);
    wxBitmap scale(wxT("..\\bmp\\scale.png"), wxBITMAP_TYPE_PNG);
    wxBitmap rotate(wxT("..\\bmp\\rotate.png"), wxBITMAP_TYPE_PNG);
    wxBitmap gravity(wxT("..\\bmp\\gravity.png"), wxBITMAP_TYPE_PNG);
    wxBitmap direction(wxT("..\\bmp\\directional.png"), wxBITMAP_TYPE_PNG);
    wxBitmap grid(wxT("..\\bmp\\grid.png"), wxBITMAP_TYPE_PNG);
    wxBitmap ruler(wxT("..\\bmp\\ruler.png"), wxBITMAP_TYPE_PNG);
    wxBitmap guide(wxT("..\\bmp\\guide.png"), wxBITMAP_TYPE_PNG);

    wxToolBar *toolbar = CreateToolBar();
    toolbar->AddTool(ID_COORDINATE, wxT("显示坐标"), coordinate);
    toolbar->AddTool(ID_RUBBER, wxT("橡皮筋"), rubber);
    toolbar->AddTool(ID_TRANSLATE, wxT("移动"), translate);
    toolbar->AddTool(ID_SCALE, wxT("缩放"), scale);
    toolbar->AddTool(ID_ROTATE, wxT("旋转"), rotate);
    toolbar->AddTool(ID_GRAVITY, wxT("引力场"), gravity);
    toolbar->AddTool(ID_DIRECTION, wxT("定向"), direction);
    toolbar->AddTool(ID_GRID, wxT("网格"), grid);
    toolbar->AddTool(ID_RULER, wxT("标尺"), ruler);
    toolbar->AddTool(ID_GUIDE, wxT("引导线"), guide);
    toolbar->Realize();

    Connect(ID_COORDINATE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(interactionFrame::OnCoordinate));
    Connect(ID_RUBBER, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(interactionFrame::OnRubber));
    Connect(ID_TRANSLATE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(interactionFrame::OnTranslate));
    Connect(ID_SCALE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(interactionFrame::OnScale));
    Connect(ID_ROTATE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(interactionFrame::OnRotate));
    Connect(ID_GRAVITY, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(interactionFrame::OnGravity));
    Connect(ID_DIRECTION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(interactionFrame::OnDirection));
    Connect(ID_GRID, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(interactionFrame::OnGrid));
    Connect(ID_RULER, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(interactionFrame::OnRuler));
    Connect(ID_GUIDE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(interactionFrame::OnGuide));

    Centre();

}

void interactionFrame::OnCoordinate(wxCommandEvent& event)
{
    // true is to force the frame to close
    //Close(true);
}

void interactionFrame::OnRubber(wxCommandEvent& event)
{

}

void interactionFrame::OnTranslate(wxCommandEvent& event)
{

}

void interactionFrame::OnScale(wxCommandEvent& event)
{

}

void interactionFrame::OnRotate(wxCommandEvent& event)
{

}

void interactionFrame::OnGravity(wxCommandEvent& event)
{

}

void interactionFrame::OnDirection(wxCommandEvent& event)
{

}

void interactionFrame::OnGrid(wxCommandEvent& event)
{

}

void interactionFrame::OnRuler(wxCommandEvent& event)
{

}

void interactionFrame::OnGuide(wxCommandEvent& event)
{

}