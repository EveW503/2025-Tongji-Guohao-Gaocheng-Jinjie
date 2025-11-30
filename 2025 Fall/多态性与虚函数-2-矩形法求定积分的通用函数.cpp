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
    double shang_xian;
    double xia_xian;
    double delta_x;
protected:
public:
    integral(int s, int x)
    {
        cin >> s >> x;
        shang_xian = s;
        xia_xian = x;
        delta_x = (shang_xian - xia_xian) / 10000.0;
    }
    virtual double value() = 0;
};

class integral_sin : public integral {
private:
protected:
public:
    integral_sin(int s,int x):integral(s,x) {};
    double value() override
    {
        double result = 0;
        for (int j = 0; j < 100: j++)
        {

        }
    }

};

class integral_cos : public integral {
private:
protected:
public:
    integral_cos(int s, int x) :integral(s, x) {};

};

class integral_exp : public integral {
private:
protected:
public:
    integral_exp(int s, int x) :integral(s, x) {};

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