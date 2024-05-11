//clipPolygon.cpp
#include "clipPolygon.h"

polygon::polygon()
{
    vertics.clear();
}

polygon::polygon(wxVector<wxPoint>& vts)
:vertics(vts)
{
/*
    wxVector<wxPoint>::iterator iter;
    vertics.clear();
    for(iter=vertics.begin(); iter!=vertics.end(); iter++)
    {
        vertics.push_back(*iter);
    }
*/
}

polygon::polygon(wxPoint* p, int k)
{
    int i;
    vertics.clear();
    for(i=0; i<k; i++)
    {
        vertics.push_back(p[i]);
    }
}

polygon::~polygon()
{
    vertics.clear();
}

int polygon::size()
{
    return vertics.size();
}

wxPoint polygon::getPoint(int k)
{
    return vertics[k];
}

polygon polygon::polyClip(polygon poly1, wxRect &rect1)
{
    int x0, y0, x1, y1;
    polygon py0, py1, py2, py3;
    x0 = rect1.x;
    y0 = rect1.y+rect1.height;
    x1 = rect1.x;
    y1 = rect1.y;
    py0 = edgeClip(poly1, wxPoint(x0,y0), wxPoint(x1,y1));
    //裁剪下边
    x0 = rect1.x+rect1.width;
    y0 = rect1.y+rect1.height;
    x1 = rect1.x;
    y1 = rect1.y+rect1.height;
    py1 = edgeClip(py0, wxPoint(x0,y0), wxPoint(x1,y1));
    //裁剪右边
    x0 = rect1.x+rect1.width;
    y0 = rect1.y;
    x1 = rect1.x+rect1.width;
    y1 = rect1.y+rect1.height;
    py2 = edgeClip(py1, wxPoint(x0,y0), wxPoint(x1,y1));
    //裁剪上边
    x0 = rect1.x;
    y0 = rect1.y;
    x1 = rect1.x+rect1.width;
    y1 = rect1.y;
    py3 = edgeClip(py2, wxPoint(x0,y0), wxPoint(x1,y1));
    return py3;
}

polygon polygon::edgeClip(polygon poly1, wxPoint p0, wxPoint p1)
{
    wxVector<wxPoint> v;
    int i;
    int m = poly1.size();
    wxPoint s, p;
    wxPoint pt;
    s = poly1.vertics[m-1];
    for(i=0; i<m; i++)
    {
        p = poly1.vertics[i];
        if(isInsideEdge(p,p0,p1))//点p在边(p0,p1)的内侧
        {
            if(isInsideEdge(s,p0,p1))//情况1
                v.push_back(p);
            else//情况4
            {
                pt = intersect(s,p,p0,p1);
                v.push_back(pt);
                v.push_back(p);
            }
        }
        else if(isInsideEdge(s,p0,p1)){//情况2
            pt = intersect(s,p,p0,p1);
            v.push_back(pt);
        }//情况3没有输出
        s=p;
    }
    return polygon(v);
}

//判断点p位于矩形边(p0,p1)的内侧还是外侧
bool polygon::isInsideEdge(wxPoint p, wxPoint p0, wxPoint p1)
{
    if(p0.x > p1.x)//裁剪边为窗口的下边
    {
        if(p.y <= p0.y)
            return true;
    }
    else if(p0.x < p1.x)//裁剪边为窗口的上边
    {
        if(p.y >= p0.y)
            return true;
    }
    else if(p0.y < p1.y)//裁减边为窗口的右边
    {
        if(p.x <= p0.x)
            return true;
    }
    else if(p0.y > p1.y )//裁减边为窗口的左边
    {
        if(p.x >= p0.x)
            return true;
    }
    return false;
}

wxPoint polygon::intersect(wxPoint s, wxPoint p, wxPoint p0, wxPoint p1)
{
    double m;
    int x,y;
    if(p0.y == p1.y)//水平裁剪边
    {
        m=(double)(p.x-s.x)/(double)(p.y-s.y);
        x=s.x+(int)((p0.y-s.y)*m);
        y=p0.y;
    }
    else//竖直裁剪边
    {
        m=(double)(p.y-s.y)/(double)(p.x-s.x);
        x = p0.x;
        y=s.y+(int)((p0.x-s.x)*m);
    }
    return wxPoint(x,y);
}