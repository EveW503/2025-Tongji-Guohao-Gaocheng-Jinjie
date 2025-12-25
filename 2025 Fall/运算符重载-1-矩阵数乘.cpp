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
    friend ostream& operator<<(ostream& ios, const Matrix& m);
    friend istream& operator>>(istream& ios, Matrix& m);
    /**************** TODO-END ****************/
};

/****************** TODO ******************/
Matrix::Matrix(int r, int c)
{
    row = r;
    col = c;
    data = new int*[row];
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
    return m*a;
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
    // 创建矩阵对象
    Matrix M(r, c);
    // 输入矩阵的元素
    cout << "请输入矩阵M的元素：" << endl;
    cin >> M;
    // 输入数乘的数
    int k;
    cout << "请输入数乘的数k：" << endl;
    cin >> k;

    /********** 测试矩阵左 / 右乘一个数 **********/
    Matrix M1 = M * k;
    cout << "M1 = M * " << k << "：" << endl;
    cout << M1 << endl;
    Matrix M2 = k * M;
    cout << "M2 = " << k << " * M：" << endl;
    cout << M2 << endl;

    /************* 测试矩阵复合乘法 *************/
    Matrix M3 = M * k * k;
    cout << "M3 = M * " << k << " * " << k << "：" << endl;
    cout << M3 << endl;
    Matrix M4 = k * M * k;
    cout << "M4 = " << k << " * M * " << k << "：" << endl;
    cout << M4 << endl;
    Matrix M5 = k * (k * M);
    cout << "M5 = " << k << " * " << k << " * M：" << endl;
    cout << M5 << endl;

    return 0;
}