//ctrlPanel.h
#include <wx/wx.h>
#include <wx/splitter.h>
#include "proInfo.h"

class ctrlPanel : public wxPanel
{
public:
    ProInfo projObj;

public:
    ctrlPanel(wxSplitterWindow *parent, ProInfo& pObj);

};
