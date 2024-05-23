//pyramid.cpp
#include "pyramid.h"
#include <iostream>
using namespace std;

#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    MyFrame* frame = new MyFrame{ wxT("绘制金字塔") };

    if ( ! frame->OGLAvailable() )
        return false;

    frame->Show(true);

    return true;
}

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(Width, Height))
{
    SetIcon(wxICON(sample));

    // The canvas
    m_mycanvas = NULL;
    wxGLAttributes vAttrs;//OpenGL渲染上下文属性
    vAttrs.PlatformDefaults().Defaults().EndList();//返回系统默认的属性列表
    bool accepted = wxGLCanvas::IsDisplaySupported(vAttrs);

    if ( accepted )
        m_mycanvas = new MyGLCanvas(this, vAttrs);

    SetMinSize(wxSize(250, 200));
}

bool MyFrame::OGLAvailable()
{
    if ( ! m_mycanvas )
        return false;

    return m_mycanvas->OglCtxAvailable();
}

// 全局函数，用于图像、文字和像素之间的转换
// NOTE: The returned pointer must be deleted somewhere in the app.
unsigned char* MyImgToArray(const wxImage& img, const wxColour& cTrans, unsigned char cAlpha)
{
    int w = img.GetWidth();
    int h = img.GetHeight();
    int siz = w * h;
    unsigned char *resArr = new unsigned char [siz * 4];
    unsigned char *res = resArr;
    unsigned char *sdata = img.GetData();
    unsigned char *alpha = NULL;
    if ( img.HasAlpha() )
        alpha = img.GetAlpha();
    // Pixel by pixel
    for ( int i = 0; i < siz; i++ )
    {   //copy the colour
        res[0] = sdata[0] ;
        res[1] = sdata[1] ;
        res[2] = sdata[2] ;
        if ( alpha != NULL )
        {   //copy alpha
            res[3] = alpha[i] ;
        }
        else
        {   // Colour cTrans gets cAlpha transparency
            if ( res[0] == cTrans.Red() && res[1] == cTrans.Green() && res[2] == cTrans.Blue() )
                res[3] = cAlpha;
            else
                res[3] = 255 ;
        }
        sdata += 3 ;
        res += 4 ;
    }

    return resArr;
}

// NOTE: The returned pointer must be deleted somewhere in the app.
unsigned char* MyTextToPixels(const wxString& sText,     // The string
                              const wxFont& sFont,       // Font to use
                              const wxColour& sForeColo, // Foreground colour
                              const wxColour& sBackColo, // Background colour
                              unsigned char cAlpha,      // Background transparency
                              int* width, int* height)   // Image sizes
{
    if ( sText.IsEmpty() )
        return NULL;

    // The dc where we temporally draw
    wxMemoryDC mdc;

    mdc.SetFont(sFont);

    // Measure
    mdc.GetMultiLineTextExtent(sText, width, height);

    // Now we know dimensions, let's draw into a memory dc
    wxBitmap bmp(*width, *height, 24);
    mdc.SelectObject(bmp);
    // If we have multiline string, perhaps not all of the bmp is used
    wxBrush brush(sBackColo);
    mdc.SetBackground(brush);
    mdc.Clear(); // Make sure all of bmp is cleared
    // Colours
    mdc.SetBackgroundMode(wxPENSTYLE_SOLID);
    mdc.SetTextBackground(sBackColo);
    mdc.SetTextForeground(sForeColo);
    // We draw the string and get it as an image.
    // NOTE: OpenGL axis are bottom to up. Be aware when setting the texture coords.
    mdc.DrawText(sText, 0, 0);
    mdc.SelectObject(wxNullBitmap); // bmp must be detached from wxMemoryDC

    // Bytes from the image. Background pixels become transparent with the
    // cAlpha transparency value.
    unsigned char *res = MyImgToArray(bmp.ConvertToImage(), sBackColo, cAlpha);

    return res;
}

wxBEGIN_EVENT_TABLE(MyGLCanvas, wxGLCanvas)
    EVT_PAINT(MyGLCanvas::OnPaint)
    EVT_SIZE(MyGLCanvas::OnSize)
    EVT_MOUSE_EVENTS(MyGLCanvas::OnMouse)
wxEND_EVENT_TABLE()

//We create a wxGLContext in this constructor.
//We do OGL initialization at OnSize().
MyGLCanvas::MyGLCanvas(MyFrame* parent, const wxGLAttributes& canvasAttrs)
: wxGLCanvas(parent, canvasAttrs)
{
    m_parent = parent;

    m_oglManager = NULL;
    m_winHeight = 0; // We have not been sized yet

    // Explicitly create a new rendering context instance for this canvas.
    wxGLContextAttrs ctxAttrs;
    ctxAttrs.PlatformDefaults().CoreProfile().OGLVersion(3, 2).EndList();
    m_oglContext = new wxGLContext(this, NULL, &ctxAttrs);
}

MyGLCanvas::~MyGLCanvas()
{
    if ( m_oglContext )
        SetCurrent(*m_oglContext);

    if ( m_oglManager )
    {
        delete m_oglManager;
        m_oglManager = NULL;
    }

    if ( m_oglContext )
    {
        delete m_oglContext;
        m_oglContext = NULL;
    }
}

bool MyGLCanvas::oglInit()
{
    if ( !m_oglContext )
        return false;

    // The current context must be set before we get OGL pointers
    SetCurrent(*m_oglContext);

    // Initialize our OGL pointers
    if ( !myOGLManager::Init() )
    {
        wxMessageBox("Error: Some OpenGL pointer to function failed.",
            "OpenGL initialization error", wxOK | wxICON_INFORMATION, this);
        return false;
    }

    // Create our OGL manager, pass our OGL error handler
    m_oglManager = new myOGLManager();

    // Load some data into GPU
    m_oglManager->SetShadersAndTriangles();

    // This string will be placed on a face of the pyramid
    int swi = 0, shi = 0; //Image sizes
    wxString stg("wxWidgets");
    // Set the font. Use a big pointsize so as to smoothing edges.
    wxFont font(wxFontInfo(48).Family(wxFONTFAMILY_MODERN));
    if ( !font.IsOk() )
        font = *wxSWISS_FONT;
    wxColour bgrdColo(*wxBLACK);
    wxColour foreColo(160, 0, 200); // Dark purple
    // Build an array with the pixels. Background fully transparent
    unsigned char* sPixels = MyTextToPixels(stg, font, foreColo, bgrdColo, 0,
                                            &swi, &shi);
    // Send it to GPU
    m_oglManager->SetStringOnPyr(sPixels, swi, shi);
    delete[] sPixels; // That memory was allocated at MyTextToPixels

    return true;
}

void MyGLCanvas::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
    // This is a dummy, to avoid an endless succession of paint messages.
    // OnPaint handlers must always create a wxPaintDC.
    wxPaintDC dc(this);

    // Avoid painting when we have not yet a size
    if ( m_winHeight < 1 || !m_oglManager )
        return;

    // This should not be needed, while we have only one canvas
    SetCurrent(*m_oglContext);

    // Do the magic
    m_oglManager->Render();

    SwapBuffers();
}

//Note:
// You may wonder why OpenGL initialization was not done at wxGLCanvas ctor.
// The reason is due to GTK+/X11 working asynchronously, we can't call
// SetCurrent() before the window is shown on screen (GTK+ doc's say that the
// window must be realized first).
// In wxGTK, window creation and sizing requires several size-events. At least
// one of them happens after GTK+ has notified the realization. We use this
// circumstance and do initialization then.

void MyGLCanvas::OnSize(wxSizeEvent& event)
{
    event.Skip();

    // If this window is not fully initialized, dismiss this event
    if ( !IsShownOnScreen() )
        return;

    if ( !m_oglManager )
    {
        //Now we have a context, retrieve pointers to OGL functions
        if ( !oglInit() )
            return;
        //Some GPUs need an additional forced paint event
        PostSizeEvent();
    }

    // This is normally only necessary if there is more than one wxGLCanvas
    // or more than one wxGLContext in the application.
    SetCurrent(*m_oglContext);

    // It's up to the application code to update the OpenGL viewport settings.
    const wxSize size = event.GetSize() * GetContentScaleFactor();
    m_winHeight = size.y;
    m_oglManager->SetViewport(0, 0, size.x, m_winHeight);

    // Generate paint event without erasing the background.
    Refresh(false);
}

void MyGLCanvas::OnMouse(wxMouseEvent& event)
{
    event.Skip();

    // GL 0 Y-coordinate is at bottom of the window
    int oglwinY = m_winHeight - event.GetY();

    if ( event.LeftIsDown() )
    {
        if ( ! event.Dragging() )
        {
            // Store positions
            m_oglManager->OnMouseButDown(event.GetX(), oglwinY);
        }
        else
        {
            // Rotation
            m_oglManager->OnMouseRotDragging( event.GetX(), oglwinY );

            // Generate paint event without erasing the background.
            Refresh(false);
        }
    }
}

