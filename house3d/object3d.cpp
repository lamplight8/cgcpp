//object3d.cpp

#include "object3d.h"

object3d::object3d(int t, 
        double x, double y, double z,
        double u, double v, double n,
        double th, double ph, double dl,
        double cw, double cv
)
{
    int i, j;

    //初始化投影参数
    nProjectionType = t;
    VRP[0] = x;
    VRP[1] = y;
    VRP[2] = z;
    PRP[0] = u;
    PRP[1] = v;
    PRP[2] = n;
    Theta = th;
    Phi = ph;
    Delta = dl;
    CW[0] = cw;
    CW[1] = cv;

    //////////////////////////////////////////////////////////////////
    //初始化房屋数据
    wcHouse[0][0] = 20.0; wcHouse[0][1] = 0.0; wcHouse[0][2] = 0.0;
    wcHouse[1][0] = 20.0; wcHouse[1][1] = 0.0; wcHouse[1][2] = 8.0;
    wcHouse[2][0] = 20.0; wcHouse[2][1] = 6.0; wcHouse[2][2] = 8.0;
    wcHouse[3][0] = 20.0; wcHouse[3][1] = 9.0; wcHouse[3][2] = 4.0;
    wcHouse[4][0] = 20.0; wcHouse[4][1] = 6.0; wcHouse[4][2] = 0.0;
    wcHouse[5][0] = 28.0; wcHouse[5][1] = 4.0; wcHouse[5][2] = 8.0;
    wcHouse[6][0] = 28.0; wcHouse[6][1] = 0.0; wcHouse[6][2] = 8.0;
    for (i = 7; i<14; i++)
    {
        wcHouse[i][0] = wcHouse[i - 7][0] + 20;
        wcHouse[i][1] = wcHouse[i - 7][1];
        wcHouse[i][2] = wcHouse[i - 7][2];
        //wcHouse[i][3] = 1.0;
    }
    wcHouse[12][0] = wcHouse[5][0] + 4;
    wcHouse[13][0] = wcHouse[6][0] + 4;

    //调整房屋大小
    int nScale = 5; //缩放比例
    for (i = 0; i<14; i++)
    {
        wcHouse[i][0] = nScale * wcHouse[i][0];
        wcHouse[i][1] = nScale * wcHouse[i][1];
        wcHouse[i][2] = nScale * wcHouse[i][2];
    }

    //初始化世界坐标系
    for (i = 0; i<4; i++)
        for (int j = 0; j<3; j++)
            lwcWC[i][j] = 0.0;

    lwcWC[0][0] = 300;
    lwcWC[1][1] = 100;
    lwcWC[2][2] = 100;

    //初始化视图参考坐标系
    for (i = 0; i<4; i++)
        for (j = 0; j<3; j++)
            lwcVRC[i][j] = 0.0;

    lwcVRC[0][0] = 30;
    lwcVRC[1][1] = 30;
    lwcVRC[2][2] = 30;
    lPRP[0] = 3000.0;
    lPRP[1] = 1000.0;
    lPRP[2] = 6000.0;
}

void object3d::setProjectionType(int n)
{
    nProjectionType = n;
}

void object3d::setVRP(double vrp0, double vrp1, double vrp2)
{
    VRP[0] = vrp0;
    VRP[1] = vrp1;
    VRP[2] = vrp2;
}

void object3d::setAngle(double th, double ph, double dt)
{
    Theta = th;
    Phi = ph;
    Delta = dt;
}

void object3d::setPRP(double prp0, double prp1, double prp2)
{
    PRP[0] = prp0;
    PRP[1] = prp1;
    PRP[2] = prp2;
}

void object3d::setCW(double cw0, double cw1)
{
    CW[0] = cw0;
    CW[1] = cw1;
}

//显示布局图，供layoutWidget调用
void object3d::ShowLayout(wxPaintDC* pdc)
{
    int i, j;
    //计算投影参考点的世界坐标
    for (i = 0; i<2; i++)
        for (j = 0; j<3; j++)
        {
            lwcPRP[i][j] = VRP[j] + PRP[j];
            lwcPRP[i][j] = VRP[j] + PRP[j];
        }
    lwcPRP[1][1] = 0.0;
    //////////////////////////////////////////////////////////////////////////////////
    //三维变换
    GenerateMatricTransform(VRP[0], VRP[1], VRP[2], Theta, Phi, Delta, MT);
    //生成三维变换矩阵
    Transform(lwcVRC, lvcVRC, 4, MT); //视图参考坐标系
    Transform(lwcPRP, lvcPRP, 2, MT); //投影参考点
        //////////////////////////////////////////////////////////////////////////////////
        //投影变换
    GenerateMatricProject(lPRP, MP, 0);//生成布局图所用的投影矩阵
    Project(wcHouse, scHouse, 14); //房屋
    Project(lwcWC, lscWC, 4); //世界坐标系
    Project(lvcVRC, lscVRC, 4); //视图参考坐标系
    Project(lvcPRP, lscPRP, 2); //投影参考点
        //////////////////////////////////////////////////////////////////////////////////
        //屏幕变换
    ToScreen(scHouse, 14); //房屋
    ToScreen(lscWC, 4); //世界坐标系
    ToScreen(lscVRC, 4); //视图参考坐标系
    ToScreen(lscPRP, 2); //投影参考点
        //////////////////////////////////////////////////////////////////////////////////
        //显示图形
    DrawHouse(pdc);//画房屋
        //画世界坐标系
    for (i = 0; i<3; i++)
        pdc->DrawLine(wxPoint(lscWC[3][0], lscWC[3][1]), wxPoint(lscWC[i][0], lscWC[i][1]));

    pdc->DrawText("x", wxPoint(lscWC[1][0], lscWC[1][1]));
    pdc->DrawText("y", wxPoint(lscWC[1][0], lscWC[1][1]));
    pdc->DrawText("z", wxPoint(lscWC[2][0], lscWC[2][1]));

    //画视图参考坐标系
    pdc->SetPen(wxPen( wxT("#ff0000")));
    for (i = 0; i<3; i++)
        pdc->DrawLine(wxPoint(lscVRC[i][0], lscVRC[i][1]), wxPoint(lscVRC[3][0], lscVRC[3][1]));
    pdc->DrawText("u", lscVRC[0][0], lscVRC[0][1]);
    pdc->DrawText("v", lscVRC[1][0], lscVRC[1][1]);
    pdc->DrawText("n", lscVRC[2][0], lscVRC[2][1]);

    //画投影参考点
    pdc->SetPen(wxPen( wxT("#0000ff")));
    pdc->DrawEllipse(lscPRP[0][0] - 3, lscPRP[0][1] - 3, 6, 6);
    pdc->DrawLine(wxPoint(lscPRP[0][0], lscPRP[0][1]), wxPoint(lscPRP[1][0], lscPRP[1][1]));
    pdc->DrawText("PRP", lscPRP[0][0], lscPRP[0][1]);
}


//显示投影图，供projectionWidget调用
void object3d::ShowProjection(wxPaintDC* pdc)
{
    //三维变换
    GenerateMatricTransform(-VRP[0], -VRP[1], -VRP[2], -Theta, -Phi, -Delta, MT);
    Transform(wcHouse, vcHouse, 14, MT);
    //投影变换
    GenerateMatricProject(PRP, MP, nProjectionType);
    Project(vcHouse, scHouse, 14);
    //屏幕变换
    ToScreen(scHouse, 14);
    //显示图形
    DrawHouse(pdc);
}

//三维变换
void object3d::Transform(double MS[][3], double MO[][3], int nRow, double MT[4][4])
{
    int i, j;
    for (i = 0; i<nRow; i++)
        for (j = 0; j<3; j++)
            MO[i][j] = MT[j][0] * MS[i][0] + MT[j][1] * MS[i][1] +MT[j][2] * MS[i][2] + MT[j][3] * 1.0;
}


//投影变换
void object3d::Project(double MS[][3], int MO[][2], int nRow)
{
    int i;
    double xObs, yObs, wObs;
    for (i = 0; i<nRow; i++)
    {
        xObs = MS[i][0] * MP[0][0] + MS[i][2] * MP[0][2];
        yObs = MS[i][1] * MP[1][1] + MS[i][2] * MP[1][2];
        wObs = MS[i][2] * MP[3][2] + 1.0;
        MO[i][0] = (int)(xObs / wObs);
        MO[i][1] = (int)(yObs / wObs);
    }
}


// 屏幕变换
void object3d::ToScreen(int MS[][2], int nRow)
{
    int i;
    for (i = 0; i<nRow; i++)
        MS[i][1] = -MS[i][1];
}


// 矩阵乘法
void object3d::MatricMultiply(double M1[4][4], double M2[4][4], double M3[4][4])
{
    for (int i = 0; i<4; i++)
        for (int j = 0; j<4; j++)
            M3[i][j] = M1[i][0] * M2[0][j] + M1[i][1] * M2[1][j] + M1[i][2] * M2[2][j] + M1[i][3] * M2[3][j];
}


// 构造三维变换矩阵
void object3d::GenerateMatricTransform(double dx, double dy, double dz, double theta, double phi, double delta, double MT[4][4])
{
    //将角度转换成弧度
    double _theta = theta*PI / 180;
    double _phi = phi*PI / 180;
    double _delta = delta*PI / 180;
    double T[4][4], Rz[4][4], Ry[4][4], Rx[4][4], temp[4][4];
    //初始化矩阵
    int i, j;
    for (i = 0; i<4; i++)
        for (j = 0; j<4; j++)
        {
            T[i][j] = 0.0;
            Ry[i][j] = 0.0;
            Rx[i][j] = 0.0;
            Rz[i][j] = 0.0;
            temp[i][j] = 0.0;
            MT[i][j] = 0.0;
        }
    //平移变换
    T[0][0] = 1.0;
    T[0][3] = dx;
    T[1][1] = 1.0;
    T[1][3] = dy;
    T[2][2] = 1.0;
    T[2][3] = dz;
    T[3][3] = 1.0;
    //绕z轴旋转
    Rz[0][0] = cos(_theta);
    Rz[0][1] = -sin(_theta);
    Rz[1][0] = sin(_theta);
    Rz[1][1] = cos(_theta);
    Rz[2][2] = 1.0;
    Rz[3][3] = 1.0;
    //绕y轴旋转
    Ry[0][0] = cos(_phi);
    Ry[0][2] = sin(_phi);
    Ry[1][1] = 1.0;
    Ry[2][0] = -sin(_phi);
    Ry[2][2] = cos(_phi);
    Ry[3][3] = 1.0;
    //绕x轴旋转
    Rx[0][0] = 1.0;
    Rx[1][1] = cos(_delta);
    Rx[1][2] = -sin(_delta);
    Rx[2][1] = sin(_delta);
    Rx[2][2] = cos(_delta);
    Rx[3][3] = 1.0;
    //生成三维变换矩阵
    //MT = Rx * Ry * Rz * T
    MatricMultiply(T, Rz, MT);
    MatricMultiply(MT, Ry, temp);
    MatricMultiply(temp, Rx, MT);
}

//投影矩阵
void object3d::GenerateMatricProject(double PRP[3], double MP[4][4], int nType)
{
    //透视投影
    if (nType == 0)
    {
        MP[0][0] = 1.0;
        MP[0][1] = 0.0;
        MP[0][2] = -PRP[0] / PRP[2];
        MP[0][3] = 0.0;
        MP[1][0] = 0.0;
        MP[1][1] = 1.0;
        MP[1][2] = -PRP[1] / PRP[2];
        MP[1][3] = 0.0;
        MP[2][0] = 0.0;
        MP[2][1] = 0.0;
        MP[2][2] = 0.0;
        MP[2][3] = 0.0;
        MP[3][0] = 0.0;
        MP[3][1] = 0.0;
        MP[3][2] = -1.0 / PRP[2];
        MP[3][3] = 1.0;
    }
    //平行投影
    else if (nType == 1)
    {
        MP[0][0] = 1.0;
        MP[0][1] = 0.0;
        MP[0][2] = -(PRP[0] - CW[0]) / PRP[2];
        MP[0][3] = 0.0;
        MP[1][0] = 0.0;
        MP[1][1] = 1.0;
        MP[1][2] = -(PRP[1] - CW[1]) / PRP[2];
        MP[1][3] = 0.0;
        MP[2][0] = 0.0;
        MP[2][1] = 0.0;
        MP[2][2] = 0.0;
        MP[2][3] = 0.0;
        MP[3][0] = 0.0;
        MP[3][1] = 0.0;
        MP[3][2] = 0.0;
        MP[3][3] = 1.0;
    }
}

//绘制房子
void object3d::DrawHouse(wxPaintDC* pdc)
{
    int i;
    int dx = 52;
    int dy = 102;
    //画左侧墙壁
    for (i = 0; i<5; i++)
        pdc->DrawLine(wxPoint(scHouse[i][0]+dx, scHouse[i][1]+dy), wxPoint(scHouse[(i + 1) % 5][0]+dx, scHouse[(i + 1) % 5][1]+dy));
    //画右侧墙壁
    for (i = 7; i<11; i++)
        pdc->DrawLine(wxPoint(scHouse[i][0]+dx, scHouse[i][1]+dy), wxPoint(scHouse[i + 1][0]+dx, scHouse[i + 1][1]+dy));
    pdc->DrawLine(wxPoint(scHouse[i][0]+dx, scHouse[i][1]+dy), wxPoint(scHouse[7][0]+dx, scHouse[7][1]+dy));
    //画横梁
    for (i = 0; i<6; i++)
        pdc->DrawLine(wxPoint(scHouse[i][0]+dx, scHouse[i][1]+dy), wxPoint(scHouse[i + 7][0]+dx, scHouse[i + 7][1]+dy));
    //画门
    pdc->DrawLine(wxPoint(scHouse[5][0]+dx, scHouse[5][1]+dy), wxPoint(scHouse[6][0]+dx, scHouse[6][1]+dy));
    pdc->DrawLine(wxPoint(scHouse[12][0]+dx, scHouse[12][1]+dy), wxPoint(scHouse[13][0]+dx, scHouse[13][1]+dy));
}
