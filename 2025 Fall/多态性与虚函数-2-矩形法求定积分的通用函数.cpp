#include <iostream>
#include <cmath>


using namespace std;


/**********************************************
*
*    TO-DO:
*        请补全该区域的代码。
*
***********************************************/
class integral {
private:
    double delta_x;
protected:
    double shang_xian;
    double xia_xian;
public:
    integral() :delta_x(0),shang_xian(0),xia_xian(0){};
    virtual ~integral() {};

    double getNum()
    {
        delta_x = (shang_xian - xia_xian)/10000.0;
        return delta_x;
    }

    virtual double value(){
        return 0;
    };

    friend istream& operator>>(istream& in, integral& obj)
    {
        in >> obj.xia_xian >> obj.shang_xian;
        return in;
    }
};

class integral_sin : public integral {
private:
protected:
public:
    integral_sin(){};
    double value() override
    {
        double x = getNum();
        double result = 0;
        for (int j = 0; j <= 10000; j++)
        {
            result += sin(xia_xian + x * j) * x;
        }
        return result;
    }

};

class integral_cos : public integral {
private:
protected:
public:
    integral_cos() {};
    double value() override
    {
        double x = getNum();
        double result = 0;
        for (int j = 0; j <= 10000; j++)
        {
            result += cos(xia_xian + x * j) * x;
        }
        return result;
    }

};

class integral_exp : public integral {
private:
protected:
public:
    integral_exp() {};
    double value() override
    {
        double x = getNum();
        double result = 0;
        for (int j = 0; j <= 10000; j++)
        {
            result += exp(xia_xian + x * j) * x;
        }
        return result;
    }

};


/**********************************************
*
*    TO-DO END
*
***********************************************/


int main()
{
    integral_sin s1;
    integral_cos s2;
    integral_exp s3;
    integral* p;


    cout << "请输入上下限：";
    cin >> s1;
    p = &s1;
    cout << "∫sinxdx的计算结果为：" << (p->value()) << endl;


    cout << "请输入上下限：";
    cin >> s2;
    p = &s2;
    cout << "∫cosxdx的计算结果为：" << (p->value()) << endl;


    cout << "请输入上下限：";
    cin >> s3;
    p = &s3;
    cout << "∫expxdx的计算结果为：" << (p->value()) << endl;


    return 0;
}