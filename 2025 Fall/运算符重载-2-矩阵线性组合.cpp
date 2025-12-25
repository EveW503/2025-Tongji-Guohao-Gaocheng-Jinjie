#include <iostream>
using namespace std;

class Matrix
{
private:
    int** data; // 二维数组指针
    int row, col; // 行数和列数

public:
    Matrix(int r, int c); // 构造函数
    ~Matrix(); // 析构函数

    /****************** TODO ******************/
    friend Matrix operator*(const Matrix& m, const int a);
    friend Matrix operator*(const int a, const Matrix& m);
    friend Matrix operator+(const Matrix& m, const Matrix& n);
    friend ostream& operator<<(ostream& ios, const Matrix& m);
    friend istream& operator>>(istream& ios, Matrix& m);

    /**************** TODO-END ****************/
};

/****************** TODO ******************/
Matrix::Matrix(int r, int c)
{
    row = r;
    col = c;
    data = new int* [row];
    for (int i = 0; i < row; i++)
    {
        data[i] = new int[col];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < row; i++)
    {
        delete[] data[i];
    }
    delete[] data;
    data = nullptr;
}

Matrix operator*(const Matrix& m, const int a)
{
    Matrix result(m.row, m.col);
    for (int i = 0; i < m.row; i++)
    {
        for (int j = 0; j < m.col; j++)
        {
            result.data[i][j] = m.data[i][j] * a;
        }
    }
    return result;
}

Matrix operator*(const int a, const Matrix& m)
{
    return m * a;
}

Matrix operator+(const Matrix& m, const Matrix& n)
{
    Matrix result(m.row, m.col);
    for (int i = 0; i < m.row; i++)
    {
        for (int j = 0; j < m.col; j++)
        {
            result.data[i][j] = m.data[i][j] + n.data[i][j];
        }
    }
    return result;
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.row; i++)
    {
        for (int j = 0; j < m.col; j++)
        {
            os << m.data[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

istream& operator>>(istream& is, Matrix& m)
{
    for (int i = 0; i < m.row; i++)
    {
        for (int j = 0; j < m.col; j++)
        {
            is >> m.data[i][j];
        }
    }
    return is;
}


/**************** TODO-END ****************/

int main()
{
    // 输入矩阵的行数和列数
    int r, c;
    cout << "请输入矩阵的行数和列数：" << endl;
    cin >> r >> c;
    // 创建三个矩阵对象
    Matrix A(r, c), B(r, c), C(r, c);
    // 输入三个矩阵的元素
    cout << "请输入矩阵A的元素：" << endl;
    cin >> A;
    cout << "请输入矩阵B的元素：" << endl;
    cin >> B;
    cout << "请输入矩阵C的元素：" << endl;
    cin >> C;
    // 输入三个矩阵的组合系数
    int ka, kb, kc;
    cout << "请依次输入矩阵A、B、C的组合系数ka，kb，kc：" << endl;
    cin >> ka >> kb >> kc;

    /********** 测试矩阵简单线性组合 **********/
    Matrix D1 = ka * A + kb * B + kc * C;
    cout << "D1 = " << ka << " * A + " << kb << " * B + " << kc << " * C = " << endl;
    cout << D1 << endl;
    Matrix D2 = A * ka + B * kb + C * kc;
    cout << "D2 = A * " << ka << " + B * " << kb << " + C * " << kc << " = " << endl;
    cout << D2 << endl;

    /********** 测试矩阵复杂线性组合 **********/
    Matrix D3 = A * kb * kc + B * ka * kc + C * ka * kb;
    cout << "D3 = A * " << kb << " * " << kc << " + B * " << ka << " * " << kc << " + C * " << ka << " * " << kb << " = " << endl;
    cout << D3 << endl;
    Matrix D4 = ka * (kb * (A + B + C)) * kc;
    cout << "D4 = " << ka << " * (" << kb << " * (A + B + C)) * " << kc << " = " << endl;
    cout << D4 << endl;
    Matrix D5 = ka * (kb * (kc * A) + B) + C;
    cout << "D5 = " << ka << " * (" << kb << " * (" << kc << " * A) + B) + C = " << endl;
    cout << D5 << endl;

    return 0;
}