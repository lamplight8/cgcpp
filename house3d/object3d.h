//object3d.h

#include <wx/wx.h>
#include <math.h>
#include <wx/graphics.h>

const double PI = 3.1415926;

class object3d
{
public:
    object3d();

    //重置房屋的投影参数
    void setParameter(
        int t, 
        double x, double y, double z,
        double u, double v, double n,
        double th, double ph, double dl,
        double cw, double cv
    );
    
    // 显示布局图，供CLayoutView调用
    void ShowLayout(wxGraphicsContext* pt);

    // 显示投影图，供CProjectionView调用
    void ShowProjection(wxGraphicsContext* pt);

    // 绘制房子
    void DrawHouse(wxGraphicsContext* pt);

    //三维变换
    void Transform(double MS[][3], double MO[][3], int nRow, double MT[4][4]);

    // 投影变换
    void Project(double MS[][3], int MO[][2], int nRow);

    // 屏幕变换
    void ToScreen(int MS[][2], int nRow);

    // 矩阵乘法
    void MatricMultiply(double M1[4][4], double M2[4][4], double M3[4][4]);

    // 构造三维变换矩阵
    void GenerateMatricTransform(double dx, double dy, double dz, double theta, double phi, double delta, double MT[4][4]);

    // 投影矩阵
    void GenerateMatricProject(double PRP[3], double MP[4][4], int nType);

private:
    int nProjectionType;// 投影类型, 0:透视投影 1:平行投影
    double VRP[3]; //视平面参考点(相对于世界坐标系)
    double Theta; //视图参考坐标系与z轴的偏角
    double Phi; //视图参考坐标系与y轴的偏角
    double Delta; //视图参考坐标系与x轴的偏角
    double PRP[3]; //投影参考点(相对于视图参考坐标系)
    double CW[2]; //窗口中心点(相对于视图参考坐标系)

    double wcHouse[14][3];// 世界坐标系中的房屋坐标，原始数据
    double vcHouse[14][3]; //视图参考坐标系中的房屋坐标
    int scHouse[14][2]; //屏幕坐标系中的房屋坐标

    double lPRP[3]; //布局图所用的投影参考点
    double lwcWC[4][3]; //布局图中的世界坐标系(相对于世界坐标系)
    int lscWC[4][2]; //布局图中的世界坐标系(相对于屏幕坐标系)
    double lwcVRC[4][3]; //布局图中的视图参考坐标系(相对于世界坐标系)
    double lvcVRC[4][3];

    int lscVRC[4][2]; //布局图中的视图参考坐标系(相对于世界坐标系)
    double lwcPRP[2][3]; //布局图中的投影参考点(相对于世界坐标系)
    double lvcPRP[2][3];
    int lscPRP[2][2]; //布局图中的投影参考点(相对于世界坐标系)

    double MT[4][4]; //三维变换矩阵
    double MP[4][4]; //投影变换矩阵
};

