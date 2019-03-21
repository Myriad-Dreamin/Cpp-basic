
// # define DEBUG

#include <iostream>
#include <cmath>

# ifdef DEBUG
int globtest = 0;
# endif

/*
 * namespace flt
 *
 * 包含自定义的浮点数方法
 */
namespace flt
{
    // flt方法最小精度
    const double eps = 1e-6;

    /*
     * function sgn
     * 符号函数
     * @x: 输入的值
     * 当x<-1e-6时, 返回-1。
     * 当x>1e-6时, 返回1。
     * 否则返回0。
     */
    inline int sgn (double const &x)
    {
        if (std::fabs(x) < eps)
		{
			return 0;
		}
        if (x < 0)
		{
			return -1;
		}
        return 1;
    }
}

/*
 * class Point
 * 点类
 *
 * 重载了构造函数，析构函数等
 * 包含一个友元函数dist和public函数dist，均返回两点间的距离
 */
class Point
{
private:

    double lfx, lfy;

	friend std::ostream &operator<< (std::ostream& ous, Point const &right_Point);
    friend std::istream &operator>> (std::istream& ins, Point &left_Point);

public:
    Point ()
    {
        lfx = 0;
        lfy = 0;
        # ifdef DEBUG
        std::cout << "Point(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        globtest++;
        # endif
    }
    Point (Point const &right_Point)
    {
        lfx = right_Point.lfx;
        lfy = right_Point.lfy;
        # ifdef DEBUG
        std::cout << "Point(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        globtest++;
        # endif
    }
    Point (Point const *right_Point)
    {
        lfx = right_Point->lfx;
        lfy = right_Point->lfy;
        # ifdef DEBUG
        std::cout << "Point(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        globtest++;
        # endif
    }
    Point (double const &inx, double const &iny)
    {
        lfx = inx;
        lfy = iny;
        # ifdef DEBUG
        std::cout << "Point(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        globtest++;
        # endif
    }
    ~Point () {
        # ifdef DEBUG
        std::cout << "Point(" << reinterpret_cast<unsigned long long>(this) << ") destructed" << std::endl;
        globtest--;
        # endif
    }

    inline double dist (Point const &right_pt) const
    {
        return std::sqrt (
            (lfx - right_pt.lfx) * (lfx - right_pt.lfx) +
            (lfy - right_pt.lfy) * (lfy - right_pt.lfy)
        );
    }

    friend double dist (Point const &, Point const &);

};

inline double dist (Point const &left_pt, Point const &right_pt)
{
    return std::sqrt (
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
        // std::cout << "delete " << "double(" << rad << ")" <<
        //     "(double, double)"<< "(" << *center << ")" << std::endl; 
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