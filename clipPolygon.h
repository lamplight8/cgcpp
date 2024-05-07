//clipPolygon.h
#include <wx/wx.h>

class rect
{
public:
    wxPoint leftBottom;
    wxPoint rightTop;
};

class polygon
{
private:
    wxVector<wxPoint> vertics;
public:
    polygon();
    polygon(wxVector<wxPoint>& vts);
    polygon(wxPoint* p, int k);
    ~polygon();

    int size();
    polygon polyClip(polygon poly1, rect &rect1);
    polygon edgeClip(polygon poly1, wxPoint p0, wxPoint p1);
    bool isInsideEdge(wxPoint p, wxPoint p0, wxPoint p1);
    wxPoint intersect(wxPoint s, wxPoint p, wxPoint p0, wxPoint p1);
};
