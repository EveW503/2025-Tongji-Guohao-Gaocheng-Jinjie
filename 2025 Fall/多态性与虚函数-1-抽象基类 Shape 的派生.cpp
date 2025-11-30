#include <iostream>
#include <cmath>


using namespace std;


/**********************************************
*
*    TO-DO:
*        请补全该区域的代码。
*
***********************************************/
class Shape {
private:
protected:
public:
    Shape() {};
    virtual double area() = 0;
};

class Circle : public Shape {
private:
    double r;
protected:
public:
    Circle(double r) : r(r) {}
    double area() {
        cout << "圆形的面积是：";
        return 3.1416 * r * r;
    }
};

class Square : public Shape {
private:
    double a;
protected:
public:
    Square(double a) : a(a) {}
    double area() {
        cout << "正方形的面积是：";
        return a * a;
    }
};

class Rectangle : public Shape {
private:
    double w, h;
protected:
public:
    Rectangle(double w, double h) : w(w), h(h) {}
    double area() {
        cout << "矩形的面积是：";
        return w * h;
    }
};

class Trapezoid : public Shape {
private:
    double top, bottom, h;
protected:
public:
    Trapezoid(double top, double bottom, double h) : top(top), bottom(bottom), h(h) {}
    double area() {
        cout << "梯形的面积是：";
        return (top + bottom) * h / 2.0;
    }
};

class Triangle : public Shape {
private:
    double a, b, c;
protected:
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}
    double area() {
        cout << "三角形的面积是：";
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};


/**********************************************
*
*    TO-DO END
*
***********************************************/


int main() {
    Circle    c1(2);
    Square    s1(3);
    Rectangle r1(4, 5);
    Trapezoid t1(6, 7, 8);
    Triangle  t2(3, 4, 5);


    Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };


    for (int i = 0; i < 5; i++) {
        cout << s[i]->area() << endl;
    }
    return 0;
}