//pyramid.cpp
#include "pyramid.h"

enum
{
    SpinTimer = wxID_HIGHEST + 1
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame* mf = new MyFrame(wxT("立方体"));
    mf->Show();
    return true;
}

MyFrame::MyFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title)
{
    new TestGLCanvas(this);

    SetIcon(wxICON(sample));

    SetClientSize(Width, Height);
}

// ----------------------------------------------------------------------------
// TestGLCanvas
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(TestGLCanvas, wxGLCanvas)
    EVT_PAINT(TestGLCanvas::OnPaint)
    EVT_KEY_DOWN(TestGLCanvas::OnKeyDown)
    EVT_TIMER(SpinTimer, TestGLCanvas::OnSpinTimer)
wxEND_EVENT_TABLE()

TestGLCanvas::TestGLCanvas(wxWindow *parent)
: wxGLCanvas(parent, wxID_ANY, NULL,
    wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE),
    m_xangle(45), m_yangle(30), m_spinTimer(this, SpinTimer)
{

}

void TestGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    // This is required even though dc is not used otherwise.
    wxPaintDC dc(this);
    const wxSize ClientSize = GetClientSize() * GetContentScaleFactor();

    myGLContext* glc = new myGLContext(this);
    glViewport(0, 0, ClientSize.x, ClientSize.y);
    glc->DrawPyramid(m_xangle, m_yangle);
    SwapBuffers();
}

void TestGLCanvas::Spin(float xSpin, float ySpin)
{
    m_xangle += xSpin;
    m_yangle += ySpin;

    Refresh(false);
}

void TestGLCanvas::OnKeyDown(wxKeyEvent& event)
{
    float angle = 5.0;

    switch ( event.GetKeyCode() )
    {
        case WXK_RIGHT:
            Spin( 0.0, -angle );
            break;

        case WXK_LEFT:
            Spin( 0.0, angle );
            break;

        case WXK_DOWN:
            Spin( -angle, 0.0 );
            break;

        case WXK_UP:
            Spin( angle, 0.0 );
            break;

        case WXK_SPACE:
            if ( m_spinTimer.IsRunning() )
                m_spinTimer.Stop();
            else
                m_spinTimer.Start( 25 );
            break;

        default:
            event.Skip();
            return;
    }
}

void TestGLCanvas::OnSpinTimer(wxTimerEvent& WXUNUSED(event))
{
    Spin(0.0, 4.0);
}

myGLContext::myGLContext(wxGLCanvas *canvas)
: wxGLContext(canvas)
{
    SetCurrent(*canvas);
}

void myGLContext::DrawPyramid(float xangle, float yangle)
{
    glClearColor(0.5, 0.5, 0.5, 0.0);//设置背景色
    glClearDepth(1.0f);//初始化深度
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);//开启深度测试
    glShadeModel(GL_SMOOTH);//平滑阴影模式

    glMatrixMode(GL_PROJECTION);//选择投影矩阵
    glLoadIdentity();
    
    GLfloat fov = 60;//眼睛上下睁开的角度
    GLfloat zNear = 0.1;//前裁剪面
    GLfloat zFar = 100.0;//后裁剪面
    GLfloat rFov = fov * PI / 180.0;
    glFrustum( -zNear * tanf( rFov / 2.0 ) * GLfloat(Width)/Height,
              zNear * tanf( rFov / 2.0 ) * GLfloat(Width)/Height,
              -zNear * tanf( rFov / 2.0 ),
              zNear * tanf( rFov / 2.0 ),
              zNear, zFar );
    glMatrixMode(GL_MODELVIEW);//选择模式矩阵
    glLoadIdentity();//重置模式矩阵
    //设置光照(定义一个位于左上方的白色定位光源)
    GLfloat lmodel_ambient[] = { 1.0f,1.0f,1.0f,1.0f };//定义环境光
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);//设置环境光
    GLfloat light0_ambient[] = { 1.0,1.0,1.0,1.0 };//定义光源环境光
    GLfloat light0_diffuse[] = { 1.0,1.0,1.0,1.0 };//定义光源散射光
    GLfloat light0_specular[] = { 1.0,1.0,1.0,1.0 };//定义光源反射光
    GLfloat light0_position[] = { 15.0,15.0,15.0,10.0 };//定义光源位置
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);//设置光源环境光
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);//设置光源散射光
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);//设置光源反射光
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);//设置光源位置
    glEnable(GL_LIGHT0);//启用光源
    glEnable(GL_LIGHTING);//启用光照效果

    //定义黄铜材质
    GLfloat brass_ambient[] = { 0.329412f,0.223529f,0.027451f,1.0f };//定义材质环境光
    GLfloat brass_diffuse[] = { 0.780392f,0.568627f,0.113725f,1.0f };//定义材质散射光
    GLfloat brass_specular[] = { 0.992157f,0.941176f,0.807843f,1.0f };//定义材质反射光
    GLfloat brass_sinines[] = { 100.0f };//定义材质镜面反射强度
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, brass_ambient);//设置材质环境光
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brass_diffuse);//设置材质散射光
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, brass_specular);//设置材质反射光
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, brass_sinines);//设置材质镜面反射强度
    //设置坐标系统
    glTranslatef(0.0f, -0.1f, -2.0f);//将坐标系统下移0.1，后移2.0
    glRotatef(xangle, 1.0, 0.0, 0.0);//将坐标系统绕x轴逆时针旋转45度
    glRotatef(yangle, 0.0, -1.0, 0.0);//将坐标系统绕y轴顺时针旋转30度

    //绘制金字塔
    GLfloat pyramid[][3] = {
        { 0.0,1.0,0.0 },
        { 0.5,0.0,0.5 },
        { -0.5,0.0,0.5 },
        { -0.5,0.0,-0.5 },
        { 0.5,0.0,-0.5 }
    };
    glBegin(GL_TRIANGLE_FAN);//使用扇形三角形模式
    glNormal3f(0.0, 0.447214f, 0.894427f);//前平面法向量
    glVertex3fv(pyramid[0]);//前平面
    glVertex3fv(pyramid[1]);
    glVertex3fv(pyramid[2]);
    glNormal3f(-0.894427f, 0.447214f, 0.0);//左平面法向量
    glVertex3fv(pyramid[3]);//左平面
    glNormal3f(0.0, 0.447214f, -0.894427f);//后平面法向量
    glVertex3fv(pyramid[4]);//后平面
    glNormal3f(0.894427f, 0.447214f, 0.0);//右平面法向量
    glVertex3fv(pyramid[1]);//右平面
    glEnd();//结束绘制

    //定义塑料材质
    GLfloat plastic_ambient[] = { 0.0f,0.0f,0.00f,1.0f };//定义材质环境光
    GLfloat plastic_diffuse[] = { 0.7f,0.85f,0.7f,1.0f };//定义材质散射光
    GLfloat plastic_specular[] = { 0.75f,0.75f,0.75f,1.0f };//定义材质反射光
    GLfloat plastic_sinines[] = { 10.0f };//定义材质镜面反射强度
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, plastic_ambient);//设置材质环境光
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, plastic_diffuse);//设置材质散射光
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, plastic_specular);//设置材质反射光
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, plastic_sinines);//设置材质镜面反射强度
//定义纹理图案(类似于国际象棋的黑白棋盘)
#define textureWidth  64//定义纹理图案宽度
#define textureHeight 64//定义纹理图案高度
    GLubyte texture[textureWidth][textureHeight][3];//定义纹理图案数组，3分量
    GLubyte c;
    for (int i = 0; i<textureWidth; i++)//生成纹理图案数组
    {
        for (int j = 0; j<textureHeight; j++)
        {
            c = (((i & 8) == 0) ^ ((j & 8) == 0)) * 255;
            texture[i][j][0] = c;
            texture[i][j][1] = c;
            texture[i][j][2] = c;
        }
    }

    glTexImage2D(//定义纹理
        GL_TEXTURE_2D,//二维纹理
        0,//纹理级别，单重纹理
        3,//3分量模式，包含R、G、B信息
        textureWidth,//纹理图案宽度
        textureHeight,//纹理图案高度
        0,//纹理边界宽度
        GL_RGB,//纹理图案数据种类
        GL_UNSIGNED_BYTE,//纹理图案数据存储类型
        &texture[0][0][0]//纹理图案数据起始地址
        );

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//设置纹理在s方向上重复
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//设置纹理在t方向上重复
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//设置纹理放大方式
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//设置纹理缩小方式
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//设置调节映射方式
    glEnable(GL_TEXTURE_2D);//启用纹理映射
    GLfloat texpoints[2][2][2] =//定义纹理坐标(s,t)
        {
            { { 0.0,0.0 },{ 1.0,0.0 } },
            { { 0.0,1.0 },{ 1.0,1.0 } }
        };
    glMap2f(//定义纹理坐标求值器
        GL_MAP2_TEXTURE_COORD_2,//求值器生成值种类，选用纹理坐标
        0, 1,	//u的取值范围
        2,//u的跨度 = u方向上两个值之间的间隔 = texpoints数组第一个维度
        2,	//u的阶数 = texpoints数组第二个维度
        0, 1,	//v的取值范围
        4,	//v的跨度 = v方向上两个值之间的间隔 = texpoints数组第一个维度*第二个纬度
        2,	//v的阶数 = texpoints数组第三个维度
        &texpoints[0][0][0]		//控制点矩阵的指针
        );
    glEnable(GL_MAP2_TEXTURE_COORD_2);//激活纹理坐标求值器

    //定义曲面控制点
#define ustride 3//u的跨度
#define uorder 6//u的阶数
#define vstride (ustride * uorder)//v的跨度
#define vorder 5//v的阶数
    GLdouble points[vorder][uorder][ustride] =//定义顶点坐标(x,y,z)
        {
            {
                {-2.00f,0.4f,-1.00f },
                { -1.20f,0.3f,-1.00f },
                { -0.40f,0.4f,-1.00f },
                { 0.40f,-0.3f,-1.00f },
                { 1.20f,0.0f,-1.00f },
                { 2.00f,0.5f,-1.00f }
            },
            {
                { -2.00f,0.1f,-0.60f },
                { -1.20f,0.0f,-0.60f },
                { -0.40f,0.5f,-0.60f },
                { 0.40f,0.0f,-0.60f },
                { 1.20f,0.0f,-0.60f },
                { 2.00f,0.0f,-0.60f }
            },
            {
                { -2.00f,0.3f,-0.20f },
                { -1.20f,0.3f,-0.20f },
                { -0.40f,0.0f,-0.20f },
                { 0.40f,0.0f,-0.20f },
                { 1.20f,0.0f,-0.20f },
                { 2.00f,0.5f,-0.20f }
            },
            {
                { -2.00f,0.1f,0.50f },
                { -1.20f,0.2f,0.20f },
                { -0.40f,0.0f,0.50f },
                { 0.40f,0.0f,0.20f },
                { 1.20f,0.6f,0.60f },
                { 2.00f,0.0f,0.40f }
            },
            {
                { -2.00f,-0.5f,1.00f },
                { -1.20f,0.6f,1.00f },
                { -0.40f,0.0f,1.00f },
                { 0.40f,0.0f,1.00f },
                { 1.20f,0.1f,1.00f },
                { 2.00f,0.5f,1.00f }
            }
        };

    glMap2d(//定义顶点坐标求值器
        GL_MAP2_VERTEX_3,
        0, 1, ustride, uorder,
        0, 1, vstride, vorder,
        &points[0][0][0]
        );
    glEnable(GL_MAP2_VERTEX_3);//激活顶点坐标求值器

    //绘制曲面
    glPushMatrix();//将当前模视矩阵压栈，防止当前变换影响原有的变换模式
    glLoadIdentity();//重置模视矩阵
    glTranslatef(0.0f, -0.1f, -2.2f);//将坐标系统下移0.1，后移2.2
    glRotatef(45, 1.0, 0.0, 0.0);//将坐标系统绕x轴逆时针旋转45度

    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);//定义二维均布网格
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);//生成二维多边形网格

    glDisable(GL_TEXTURE_2D);//禁用纹理映射
    glPopMatrix();//将模视矩阵出栈
    glFlush();
}
