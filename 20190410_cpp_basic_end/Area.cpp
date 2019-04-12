
# define DEBUG

#include <iostream>
#include <cmath>
#include <stdexcept>

/*
 * namespace flt
 *
 * 包含自定义的浮点数方法
 */
namespace flt
{
    const double PI = acos(-1.0);
}

/*
 * abstract class Shape
 *
 * 抽象的形状类
 * 包含无参构造方法，析构方法
 *
 * function area()返回形状类的面积
 */
class Shape
{
public:
    Shape ()
    {
        # ifdef DEBUG
        std::cout << "Shape(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        # endif
    }
    virtual ~Shape ()
    {
        # ifdef DEBUG
        std::cout << "Shape(" << reinterpret_cast<unsigned long long>(this) << ") destructed" << std::endl;
        # endif
    }

    virtual double area () = 0;
    //{
    //    std::cout << "Shape area is not implemented" << std::endl;
    //}
};

/*
 * class Rectangle
 *
 * 矩形类
 *
 * 重载了>>，<<，构造和析构函数
 * 包含一个area()方法返回矩形的面积
 */
class Rectangle: public Shape
{
private:

    friend std::ostream &operator<< (std::ostream &os, Rectangle const &out_rec);
    friend std::istream &operator>> (std::istream &is, Rectangle const &in_rec);

public:
    double width, height;

    Rectangle ()
    {
        width = height = 0;
        # ifdef DEBUG
        std::cout << "Rectangle(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        # endif
    }
    Rectangle (double const &x, double const &y): width(x), height(y)
    {
        # ifdef DEBUG
        std::cout << "Rectangle(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        # endif
    }
    virtual ~Rectangle() override
    {
        # ifdef DEBUG
        std::cout << "Rectangle(" << reinterpret_cast<unsigned long long>(this) << ") destructed" << std::endl;
        # endif
    }

    virtual inline double area() override
    {
        return width * height;
    }
};


inline std::istream &operator>> (std::istream &in_s, Rectangle &in_rec)
{
    in_s >> in_rec.width;
    if (!in_s)
        in_rec.width = double(0);
    in_s >> in_rec.height;
    if (!in_s)
        in_rec.height = double(0);
    return in_s;
}

inline std::ostream &operator<< (std::ostream &out_s, Rectangle const &out_rec)
{
    out_s << out_rec.width << " " << out_rec.height;
    return out_s;
}

/*
 * class Square
 *
 * 正方形类
 *
 * 重载了>>，<<，构造和析构函数
 * 包含一个area()方法返回矩形的面积
 */
class Square: public Rectangle
{
private:
    friend std::istream &operator>> (std::istream &is, Square const &in_rec);

public:
    Square (): Rectangle() {}

    Square (double const &x): Rectangle(x,x)
    {
        # ifdef DEBUG
        std::cout << "Square(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        # endif
    }

    virtual ~Square()
    {
        # ifdef DEBUG
        std::cout << "Square(" << reinterpret_cast<unsigned long long>(this) << ") destructed" << std::endl;
        # endif
    }

    virtual inline double area() override
    {
        return width * height;
    }
};

inline std::istream &operator>> (std::istream &in_s, Square &in_rec)
{
    in_s >> in_rec.width;
    if (!in_s)
        in_rec.width = double(0);
    in_rec.height=in_rec.width;
    return in_s;
}

/*
 * class Circle
 *
 * 圆类
 *
 * 重载了>>,<<,构造和析构函数
 * 包含一个area()方法返回圆的面积
 */
class Circle: public Shape
{
private:

    friend std::ostream &operator<< (std::ostream &os, Circle const &out_cir);
    friend std::istream &operator>> (std::istream &is, Circle &in_cir);

public:
    double rad;

    Circle ()
    {
        rad = 0;
        # ifdef DEBUG
        std::cout << "Circle(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        # endif
    }
    Circle (double const &_rad): rad(_rad)
    {
        # ifdef DEBUG
        std::cout << "Circle(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        # endif
    }
    virtual ~Circle() override
    {
        # ifdef DEBUG
        std::cout << "Circle(" << reinterpret_cast<unsigned long long>(this) << ") constructed" << std::endl;
        # endif
    }

    virtual inline double area() override
    {
        return flt::PI * rad * rad;
    }
};

inline std::istream &operator>> (std::istream &in_s, Circle &in_cir)
{
    in_s >> in_cir.rad;
    if (!in_s)
        in_cir.rad = double(0);
    return in_s;
}

inline std::ostream &operator<< (std::ostream &out_s, Circle const &out_cir)
{
    out_s << out_cir.rad;
    return out_s;
}


int main ()
{
    using std::cin;
    using std::cout;
    using std::endl;
    Rectangle *R = new Rectangle();
    Circle *C = new Circle();
    Square *S = new Square();
    Shape *ShapePointer = R;
    cout << "Please input a Rectangle(double, double):" << endl;
    cin >> *R;
    cout << "Please input a Circle(double):" << endl;
    cin >> *C;
    cout << "Please input a Square(double):" << endl;
    cin >> *S;


    cout << "R's area = "<< R->area() << endl
              << "C's area = "<< C->area() << endl
              << "S's area = "<< S->area() << endl
              << "Pointer to R's area = "<< ShapePointer->area() << endl;

    delete R;
    delete C;
    delete S;

    return 0;
}

/*
 1 2 10
 */
