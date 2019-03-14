#include <iostream>
#include <cmath>


namespace flt
{
    const double PI = acos(-1.0);
}


class Shape
{
public:
    Shape() {}
    virtual ~Shape() {}

    inline virtual double area()
    {
        std::cout << "the method area not implemented!" << std::endl;
        return 0;
    }
};


class Rectangle: protected Shape
{
private:

    friend std::ostream &operator<< (std::ostream &os, Rectangle const &out_rec);
    friend std::istream &operator>> (std::istream &is, Rectangle const &in_rec);

public:
    double a, b;

    Rectangle () {}
    Rectangle (double const &x, double const &y): a(x), b(y) {}
    ~Rectangle() override {}

    inline double area() override
    {
        return a * b;
    }
};


inline std::ostream &operator<< (std::ostream &out_s, Rectangle const &out_rec)
{
    out_s << out_rec.a << " " << out_rec.b;
    return out_s;
}


class Circle: protected Shape
{
private:

    friend std::ostream &operator<< (std::ostream &os, Circle const &out_cir);
    friend std::istream &operator>> (std::istream &is, Circle &in_cir);

public:
    double r;

    Circle () {}
    Circle (double const &_r): r(_r) {}
    ~Circle() override {}

    inline double area() override
    {
        return flt::PI * r * r;
    }
};


inline std::ostream &operator<< (std::ostream &out_s, Circle const &out_cir)
{
    out_s << out_cir.r;
    return out_s;
}


int main ()
{
    Shape *A = new Shape();

    Rectangle *R = new Rectangle(1, 2);
    Circle *C = new Circle(10);

    A->area();

    std::cout << "R's area = "<< R->area() << std::endl
              << "C's area = "<< C->area() << std::endl;

    delete A;
    delete R;
    delete C;

    return 0;
}