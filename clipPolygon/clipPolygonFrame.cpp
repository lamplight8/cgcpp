//clipLineFrame.cpp
#include "clipPolygonFrame.h"

clipPolygonFrame::clipPolygonFrame(const wxString& title)
: wxFrame{ NULL, -1, title, wxDefaultPosition, wxSize(WinWidth, WinHeight) }
{
    wxStaticText* textLabes = new wxStaticText{ this, -1, wxT("") };
    wxPanel *setPanel = new wxPanel{ this, -1, wxPoint(580, 5), wxSize(400, 320) };

    int col1{10};
    int col2{80};
    int col3{210};
    int col4{280};

    wxStaticText* tex = new wxStaticText{ setPanel, -1, wxT("left x: "), wxPoint(col1, 10) };
    tcx = new wxTextCtrl{ setPanel, -1, wxT("140"), wxPoint(col2, 10) };
    wxStaticText* tey = new wxStaticText{ setPanel, -1, wxT("bottom y: "), wxPoint(col3, 10) };
    tcy = new wxTextCtrl{ setPanel, -1, wxT("60"), wxPoint(col4, 10) };

    wxStaticText* tew = new wxStaticText{ setPanel, -1, wxT("width: "), wxPoint(col1, 40) };
    tcw = new wxTextCtrl{ setPanel, -1, wxT("80"), wxPoint(col2, 40) };
    wxStaticText* teh = new wxStaticText{ setPanel, -1, wxT("hight: "), wxPoint(col3, 40) };
    tch = new wxTextCtrl{ setPanel, -1, wxT("80"), wxPoint(col4, 40) };

    wxStaticText* ten = new wxStaticText{ setPanel, -1, wxT("vertics: "), wxPoint(col1, 70) };
    tcn = new wxTextCtrl{ setPanel, -1, wxT("4"), wxPoint(col2, 70) };

    wxStaticText* tex0 = new wxStaticText{ setPanel, -1, wxT("vertex x0: "), wxPoint(col1, 100) };
    tcx0 = new wxTextCtrl{ setPanel, -1, wxT("100"), wxPoint(col2, 100) };
    wxStaticText* tey0 = new wxStaticText{ setPanel, -1, wxT("vertex y0: "), wxPoint(col3, 100) };
    tcy0 = new wxTextCtrl{ setPanel, -1, wxT("100"), wxPoint(col4, 100) };

    wxStaticText* tex1 = new wxStaticText{ setPanel, -1, wxT("vertex x1: "), wxPoint(col1, 130) };
    tcx1 = new wxTextCtrl{ setPanel, -1, wxT("260"), wxPoint(col2, 130) };
    wxStaticText* tey1 = new wxStaticText{ setPanel, -1, wxT("vertex y1: "), wxPoint(col3, 130) };
    tcy1 = new wxTextCtrl{ setPanel, -1, wxT("50"), wxPoint(col4, 130) };

    wxStaticText* tex2 = new wxStaticText{ setPanel, -1, wxT("vertex x2: "), wxPoint(col1, 160) };
    tcx2 = new wxTextCtrl{ setPanel, -1, wxT("180"), wxPoint(col2, 160) };
    wxStaticText* tey2 = new wxStaticText{ setPanel, -1, wxT("vertex y2: "), wxPoint(col3, 160) };
    tcy2 = new wxTextCtrl{ setPanel, -1, wxT("100"), wxPoint(col4, 160) };

    wxStaticText* tex3 = new wxStaticText{ setPanel, -1, wxT("vertex x3: "), wxPoint(col1, 190) };
    tcx3 = new wxTextCtrl{ setPanel, -1, wxT("260"), wxPoint(col2, 190) };
    wxStaticText* tey3 = new wxStaticText{ setPanel, -1, wxT("vertex y3: "), wxPoint(col3, 190) };
    tcy3 = new wxTextCtrl{ setPanel, -1, wxT("150"), wxPoint(col4, 190) };

    wxStaticText* tex4 = new wxStaticText{ setPanel, -1, wxT("vertex x4: "), wxPoint(col1, 220) };
    tcx4 = new wxTextCtrl{ setPanel, -1, wxT("00"), wxPoint(col2, 220) };
    wxStaticText* tey4 = new wxStaticText{ setPanel, -1, wxT("vertex y4: "), wxPoint(col3, 220) };
    tcy4 = new wxTextCtrl{ setPanel, -1, wxT("00"), wxPoint(col4, 220) };

    wxStaticText* tex5 = new wxStaticText{ setPanel, -1, wxT("vertex x5: "), wxPoint(col1, 250) };
    tcx5 = new wxTextCtrl{ setPanel, -1, wxT("00"), wxPoint(col2, 250) };
    wxStaticText* tey5 = new wxStaticText{ setPanel, -1, wxT("vertex y5: "), wxPoint(col3, 250) };
    tcy5 = new wxTextCtrl{ setPanel, -1, wxT("00"), wxPoint(col4, 250) };

    wxButton *butOk = new wxButton{ setPanel, ID_OK, wxT("Ok"), wxPoint(40, 280) };
    wxButton *butOldCOLOR = new wxButton{ setPanel, ID_OLDCOLOR, wxT("OldColor"), wxPoint(160, 280) };
    wxButton *butNewCOLOR = new wxButton{ setPanel, ID_NEWCOLOR, wxT("NewColor"), wxPoint(280, 280) };

    tcx->GetValue().ToInt(&rt.x);
    tcy->GetValue().ToInt(&rt.y);
    tcw->GetValue().ToInt(&rt.width);
    tch->GetValue().ToInt(&rt.height);

    tcn->GetValue().ToInt(&n);
    
    wxPoint p[6];
    tcx0->GetValue().ToInt(&p[0].x);
    tcy0->GetValue().ToInt(&p[0].y);
    tcx1->GetValue().ToInt(&p[1].x);
    tcy1->GetValue().ToInt(&p[1].y);
    tcx2->GetValue().ToInt(&p[2].x);
    tcy2->GetValue().ToInt(&p[2].y);
    tcx3->GetValue().ToInt(&p[3].x);
    tcy3->GetValue().ToInt(&p[3].y);
    tcx4->GetValue().ToInt(&p[4].x);
    tcy4->GetValue().ToInt(&p[4].y);
    tcx5->GetValue().ToInt(&p[5].x);
    tcy5->GetValue().ToInt(&p[5].y);

    ptv = new wxPoint[n];
    for(int i=0; i<n; i++)
        ptv[i] = p[i];

    oldColor = wxT("#0d0060");//白色
    newColor = wxT("#ff0000");//红色

    this->Connect(ID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(clipPolygonFrame::OnOk));
    this->Connect(ID_OLDCOLOR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(clipPolygonFrame::OnOldColor));
    this->Connect(ID_NEWCOLOR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(clipPolygonFrame::OnNewColor));
    this->Connect(wxEVT_PAINT, wxPaintEventHandler(clipPolygonFrame::OnPaint));
    Centre();
}

void clipPolygonFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc{ this };

    dc.SetPen(wxPen(oldColor));

    int left = rt.x;
    int bottom = rt.y;
    int right = rt.x+rt.width;
    int top = rt.y+rt.height;
    dc.DrawLine(wxPoint(left, bottom), wxPoint(right, bottom));
    dc.DrawLine(wxPoint(right, bottom), wxPoint(right, top));
    dc.DrawLine(wxPoint(right, top), wxPoint(left, top));
    dc.DrawLine(wxPoint(left, top), wxPoint(left, bottom));

    dc.DrawPolygon(n, ptv);

    polygon poly(ptv, n);
    polygon poly1 = poly.polyClip(poly, rt);
    int k = poly1.size();
    wxPoint *pt = new wxPoint[k];
    for(int i=0; i<k; i++)
    {
        pt[i] = poly1.getPoint(i);
    }
    dc.SetBrush(wxBrush(newColor));
    dc.DrawPolygon(k, pt);
}

void clipPolygonFrame::OnOk(wxCommandEvent& event)
{
    tcx->GetValue().ToInt(&rt.x);
    tcy->GetValue().ToInt(&rt.y);
    tcw->GetValue().ToInt(&rt.width);
    tch->GetValue().ToInt(&rt.height);

    wxPoint p[6];
    tcx0->GetValue().ToInt(&p[0].x);
    tcy0->GetValue().ToInt(&p[0].y);
    tcx1->GetValue().ToInt(&p[1].x);
    tcy1->GetValue().ToInt(&p[1].y);
    tcx2->GetValue().ToInt(&p[2].x);
    tcy2->GetValue().ToInt(&p[2].y);
    tcx3->GetValue().ToInt(&p[3].x);
    tcy3->GetValue().ToInt(&p[3].y);
    tcx4->GetValue().ToInt(&p[4].x);
    tcy4->GetValue().ToInt(&p[4].y);
    tcx5->GetValue().ToInt(&p[5].x);
    tcy5->GetValue().ToInt(&p[5].y);

    delete []ptv;
    ptv = new wxPoint[n];
    for(int i=0; i<n; i++)
        ptv[i] = p[i];
    Refresh();
}

void clipPolygonFrame::OnOldColor(wxCommandEvent& event)
{
    wxColourDialog dlg;
    dlg.GetColourData().SetChooseFull(true);
    if(dlg.ShowModal()==wxID_OK)
        oldColor = dlg.GetColourData().GetColour();
    Refresh();
}

void clipPolygonFrame::OnNewColor(wxCommandEvent& event)
{
    wxColourDialog dlg;
    dlg.GetColourData().SetChooseFull(true);
    if(dlg.ShowModal()==wxID_OK)
        newColor = dlg.GetColourData().GetColour();
    Refresh();
}
