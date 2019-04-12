#include <iostream>
#include <cmath>

# ifdef DEBUG
int globtest = 0;
# endif

class Point;

/*
 * 包含自定义的浮点数方法
 */
namespace flt
{
    // flt方法最小精度
    const double eps = 1e-6;

    /*
     * 符号函数
     * @in_x: 输入的值
     * 当x<-1e-6时, 返回-1。
     * 当x>1e-6时, 返回1。
     * 否则返回0。
     */
    inline int sgn (double const &in_x)
    {
        if (std::fabs(in_x) < eps) {
			return 0;
		}
        if (in_x < 0) {
			return -1;
		}
        return 1;
    }
}

/*
 * 点类
 *
 * 重载了构造函数，析构函数等
 * 包含一个友元函数dist和public函数dist，均返回两点间的距离
 */
class Point
{
private:
    // lfx: 横坐标, lfy: 纵坐标
    double lfx, lfy;

	friend std::ostream &operator<< (std::ostream& ous, Point const &right_Point);
    friend std::istream &operator>> (std::istream& ins, Point &left_Point);

public:

    /*
     * 默认构造函数
     *
     * 默认构造为(0, 0)
     */
    Point ()
    {
        lfx = 0;
        lfy = 0;
        # ifdef DEBUG
        std::cout << "Point(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        globtest++;
        # endif
    }

    /*
     * 拷贝构造函数
     * @right_Point: 传入拷贝对象
     */
    Point (Point const &right_Point)
    {
        lfx = right_Point.lfx;
        lfy = right_Point.lfy;
        # ifdef DEBUG
        std::cout << "Point(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        globtest++;
        # endif
    }

    /*
     * 拷贝构造函数
     * @right_Point: 传入拷贝对象的地址
     */
    Point (Point const *right_Point)
    {
        lfx = right_Point->lfx;
        lfy = right_Point->lfy;
        # ifdef DEBUG
        std::cout << "Point(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        globtest++;
        # endif
    }

    /*
     * 构造函数
     * @inx: 横坐标
     * @iny: 纵坐标
     */
    Point (double const &inx, double const &iny)
    {
        lfx = inx;
        lfy = iny;
        # ifdef DEBUG
        std::cout << "Point(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        globtest++;
        # endif
    }

    /*
     * 析构函数
     *
     * 什么都不做
     */
    ~Point () {
        # ifdef DEBUG
        std::cout << "Point(" << reinterpret_cast<unsigned long long>(this) << ") destructed" << std::endl;
        globtest--;
        # endif
    }

    const Point operator++ () const
    {
        return Point(lfx + 1, lfy + 1);
    }

    const Point operator++ (int) const
    {
        return Point(lfx + 1, lfy + 1);
    }

    const Point operator-- () const
    {
        return Point(lfx - 1, lfy - 1);
    }

    const Point operator-- (int) const
    {
        return Point(lfx - 1, lfy - 1);
    }

    /*
     * 距离函数
     * @right_pt: 传入一个右点
     *
     * 返回与右点的距离
     */
    inline double dist (Point const &right_pt=Point()) const
    {
        return std::sqrt(
            (lfx - right_pt.lfx) * (lfx - right_pt.lfx) +
            (lfy - right_pt.lfy) * (lfy - right_pt.lfy)
        );
    }

    /*
     * 距离函数(双参数友元化)
     * @left_pt: 传入一个左点
     * @right_pt: 传入一个右点
     *
     * 返回左点与右点的距离
     */
    friend double dist (Point const &left_pt, Point const &right_pt);

};

inline double dist (Point const &left_pt, Point const &right_pt=Point())
{
    return std::sqrt(
        (left_pt.lfx - right_pt.lfx) * (left_pt.lfx - right_pt.lfx) +
        (left_pt.lfy - right_pt.lfy) * (left_pt.lfy - right_pt.lfy)
    );
}

std::ostream &operator<< (std::ostream &ous, Point const &right_Point)
{
    ous << right_Point.lfx << " " << right_Point.lfy;
    return ous;
}
std::istream &operator>> (std::istream &ins, Point &left_Point)
{
    ins >> left_Point.lfx >> left_Point.lfy;
    if(!ins)
    {
        left_Point = Point();
    }
    return ins;
}

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    Point pt;

    cout << "Initialize: (" << pt << ")" << endl;
    cout << "Please Input a Point(double,double)?" << endl;
    cin >> pt;
    cout << "Inputed: (" << pt << ")" << endl;
    cout << "Point++" << endl;

    cout << "Please Input a Point(double,double)?" << endl;
    cin >> pt;
    cout << "(" << pt++ << ")" << endl;
    cout << "++Point" << endl;
    cout << "(" << ++pt << ")" << endl;
    cout << "Point--" << endl;
    cout << "(" << pt-- << ")" << endl;
    cout << "--Point" << endl;
    cout << "(" << --pt << ")" << endl;

}
