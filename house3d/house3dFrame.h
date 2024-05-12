//house3dFrame.h

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/generic/dirctrlg.h>
#include <wx/dnd.h>
#include <wx/splitter.h>
#include <wx/dirctrl.h>
#include <wx/treectrl.h>
#include <wx/dir.h>

const int Width{800};
const int Height{600};

class house3dFrame: public wxFrame
{
public:
    house3dFrame(const wxString& title);
};
