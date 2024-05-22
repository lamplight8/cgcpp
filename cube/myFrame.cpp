#include "myFrame.h"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_NEW, MyFrame::OnNewWindow)
    EVT_MENU(NEW_STEREO_WINDOW, MyFrame::OnNewStereoWindow)
    EVT_MENU(wxID_CLOSE, MyFrame::OnClose)
wxEND_EVENT_TABLE()

MyFrame::MyFrame( bool stereoWindow )
: wxFrame(NULL, wxID_ANY, "wxWidgets OpenGL Cube Sample")
{
    int stereoAttribList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_STEREO, 0 };

    new TestGLCanvas(this, stereoWindow ? stereoAttribList : NULL);

    SetIcon(wxICON(sample));

    // Make a menubar
    wxMenu *menu = new wxMenu;
    menu->Append(wxID_NEW);
    menu->Append(NEW_STEREO_WINDOW, "New Stereo Window");
    menu->AppendSeparator();
    menu->Append(wxID_CLOSE);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menu, "&Cube");

    SetMenuBar(menuBar);

    CreateStatusBar();

    SetClientSize(400, 400);
    Show();

    // test IsDisplaySupported() function:
    static const int attribs[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, 0 };
    wxLogStatus("Double-buffered display %s supported",
                wxGLCanvas::IsDisplaySupported(attribs) ? "is" : "not");

    if ( stereoWindow )
    {
        const wxString vendor = glGetwxString(GL_VENDOR).Lower();
        const wxString renderer = glGetwxString(GL_RENDERER).Lower();
        if ( vendor.find("nvidia") != wxString::npos &&
                renderer.find("quadro") == wxString::npos )
            ShowFullScreen(true);
    }
}

void MyFrame::OnClose(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnNewWindow( wxCommandEvent& WXUNUSED(event) )
{
    new MyFrame();
}

void MyFrame::OnNewStereoWindow( wxCommandEvent& WXUNUSED(event) )
{
    new MyFrame(true);
}