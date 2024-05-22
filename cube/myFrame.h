#include "testGLCanvas.h"

class MyFrame : public wxFrame
{
public:
    MyFrame(bool stereoWindow = false);

private:
    void OnClose(wxCommandEvent& event);
    void OnNewWindow(wxCommandEvent& event);
    void OnNewStereoWindow(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

enum
{
    NEW_STEREO_WINDOW = wxID_HIGHEST + 1
};