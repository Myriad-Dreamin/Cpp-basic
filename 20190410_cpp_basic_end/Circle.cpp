
# define DEBUG

#include <iostream>
#include <cmath>

# ifdef DEBUG
int globtest = 0;
# endif

class Point;
class Circle;

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


/*
 * class Circle
 * 圆类
 *
 * 重载了构造函数，析构函数等
 * 包含public函数initfs和intersect
 */
class Circle
{
private:

    double rad;
    Point *center;

public:
    Circle ()
    {
        rad = 0;
        center = new Point();
        # ifdef DEBUG
        std::cout << "Circle(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        globtest++;
        # endif
    }
    Circle (Circle const &right_circle)
    {
        rad = right_circle.rad;
        center = new Point(right_circle.center);
        # ifdef DEBUG
        std::cout << "Circle(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        globtest++;
        # endif
    }
    Circle (double const &radius, Point const &_center)
    {
        rad = radius;
        center = new Point(_center);
        # ifdef DEBUG
        std::cout << "Circle(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        globtest++;
        # endif
    }
    Circle (double const &radius, double const &x, double const &y)
    {
        rad = radius;
        center = new Point(x, y);
        # ifdef DEBUG
        std::cout << "Circle(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        globtest++;
        # endif
    }
    ~Circle ()
    {
        delete center;
        # ifdef DEBUG
        std::cout << "Circle(" << reinterpret_cast<unsigned long long>(this) << ") destructed" << std::endl;
        globtest--;
        # endif
    }
    void initfs ()
    {
        using std::cin;
		using std::cout;
		using std::endl;

		cout << "Please input the radius(double):" << endl;
		cin >> rad;

		cout << "Please input the Point(double, double):" << endl;
		cin >> *center;
    }
	inline bool intersect (Circle const &right_circle) const
	{
		double dis = dist(*center, *right_circle.center);
		return (flt::sgn(std::fabs(rad - right_circle.rad) - dis) <= 0) &&
			(flt::sgn(dis - (rad + right_circle.rad)) <= 0);
	}
};

int main ()
{
    Circle *cir1 = new Circle (), *cir2 = new Circle ();

	cir1->initfs ();
	cir2->initfs ();

    std::cout << (cir1->intersect(*cir2) ? "Intersect" : "Not intersect") << std::endl;

    delete cir1;
    delete cir2;
    cir1 = cir2 = nullptr;

    # ifdef DEBUG
    std::cout << globtest << std::endl;
    # endif

    return 0;
}
/*
1 0 0
1 2 0

1 0 0
2 2 0

1 0 0
10 2 0
*/
