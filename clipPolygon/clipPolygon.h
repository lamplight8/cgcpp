//clipPolygon.h
#include <wx/wx.h>

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
    wxPoint getPoint(int k);
    polygon polyClip(polygon poly1, wxRect &rect1);
    polygon edgeClip(polygon poly1, wxPoint p0, wxPoint p1);
    bool isInsideEdge(wxPoint p, wxPoint p0, wxPoint p1);
    wxPoint intersect(wxPoint s, wxPoint p, wxPoint p0, wxPoint p1);
};
