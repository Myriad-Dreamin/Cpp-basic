#include <iostream>
#include <cmath>

namespace flt
{
    const double PI = std::acos(-1.0);
}

class Shape
{
    public:
    
    Shape() {}
    virtual ~Shape() {}

    virtual double area()
    {
        return 0;
    }
};

class Rectangle: protected Shape
{
    public:
    double a, b;

    Rectangle () {}
    Rectangle (double const &x, double const &y): a(x), b(y) {}
    ~Rectangle() override {}

    double area() override
    {
        return a * b;
    }
};
class Circle: protected Shape
{
    
    public:
    double r;

    Circle () {}
    Circle (double const &_r): r(_r) {}
    ~Circle() override {}

    double area() override
    {
        return flt::PI * r * r;
    }
};

int main ()
{
    Rectangle *R = new Rectangle(1, 2);
    Circle *C = new Circle(10);

    std::cout << "R's area = "<< R->area() << std::endl
              << "C's area = "<< C->area() << std::endl;
    
    delete R;
    delete C;

    return 0;
}