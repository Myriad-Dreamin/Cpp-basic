#include <iostream>
#include <cmath>

namespace flt
{
    const double eps = 1e-6;
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
    }
    Point (Point const &right_Point)
    {
        lfx = right_Point.lfx;
        lfy = right_Point.lfy;
    }
    Point (Point const *right_Point)
    {
        lfx = right_Point->lfx;
        lfy = right_Point->lfy;
    }
    Point (double const &inx, double const &iny)
    {
        lfx = inx;
        lfy = iny;
    }
    ~Point (){}

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
    }
    Circle (Circle const &right_circle)
    {
        rad = right_circle.rad;
        center = new Point(right_circle.center);
    }
    Circle (double const &radius, Point const &_center)
    {
        rad = radius;
        center = new Point(_center);
    }
    Circle (double const &radius, double const &x, double const &y)
    {
        rad = radius;
        center = new Point(x, y);
    }
    ~Circle ()
    {
        // std::cout << "delete " << "double(" << rad << ")" <<
        //     "(double, double)"<< "(" << *center << ")" << std::endl; 
        delete center;
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
    
    std::cout << (cir1->intersect(*cir2) ? "Intersect" : "Not intersect")<< std::endl;
    
    delete cir1;
    delete cir2;

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