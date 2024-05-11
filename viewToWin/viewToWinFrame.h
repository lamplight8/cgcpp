//viewToWinFrame.h
#include <wx/wx.h>

const int WinWidth { 800 };
const int WinHeight { 600 };

class viewToWinFrame : public wxFrame
{
public:
    viewToWinFrame(const wxString& title);
    void OnMouseLeftDown(wxMouseEvent& event);
    void OnMouseLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);

    void translate(wxRect& rect, wxPoint p);
    void clip();
    void drawRect(wxPaintDC* pdc, wxRect rect, wxColor clr);
private:

    wxPoint wldOrg;//世界坐标系原点
    wxPoint scrOrg;//屏幕坐标系原点
    wxRect wldRect;//世界坐标系矩形区域
    wxRect scrRect;//屏幕坐标系矩形区域
    wxRect winRect;//窗口
    wxRect viewRect;//视口
    wxVector<wxRect> wldFigs;//世界坐标系中图形
    wxVector<wxRect> scrFigs;//屏幕坐标系中图形
    bool isInWindow;//鼠标是否在窗口内标志
    bool isInView;//鼠标是否在视口内标志
    wxPoint oldPos;//鼠标按下位置

};
