#include <iostream>
using namespace std; class Date
{
private:
    int year, month, day;

public:
    Date(int y, int m, int d);
    Date(int days); // 从公元元年（0001年）1月1日开始的天数，仅考虑公元元年之后的日期

    // 注意输出格式，格式为"yyyy-mm-dd"，如"2000-01-01"，位数不足的要补0
    /****************** TODO ******************/
    // 类型转换：日期转int
    operator int() const;

    // 输出流重载
    friend ostream& operator<<(ostream& os, const Date& d);

    // 自增自减
    Date& operator++();    // 前置++
    Date operator++(int);  // 后置++
    Date& operator--();    // 前置--
    Date operator--(int);  // 后置--

    // 复合赋值
    Date& operator+=(int days);
    Date& operator-=(int days);

    // 加减运算
    Date operator+(int days) const;
    friend Date operator+(int days, const Date& d);
    Date operator-(int days) const;
    friend Date operator-(int days, const Date& d); // 对应样例中 int - Date 的情况
    int operator-(const Date& other) const;         // Date - Date 求天数差

    // 关系运算符
    // 由于有 Date(int) 构造函数，int 与 Date 比较时会自动隐式转换，
    // 因此只需要定义 Date 与 Date 的比较即可覆盖所有情况。
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    /**************** TODO-END ****************/
};/****************** TODO ******************/
// 构造函数：年月日
Date::Date(int y, int m, int d)
{
    year = y;
    month = m;
    day = d;
}

// 构造函数：天数 -> 日期 (参考你提供的逻辑)
Date::Date(int days)
{
    int y = 1, m = 1;
    while (true)
    {
        int year_days = 365;
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
        {
            year_days = 366;
        }

        if (days > year_days)
        {
            days -= year_days;
            y++;
        }
        else
        {
            break;
        }
    }

    int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    while (true)
    {
        int current_month_days = month_days[m];

        bool isLeap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        if (m == 2 && isLeap)
        {
            current_month_days = 29;
        }

        if (days > current_month_days)
        {
            days -= current_month_days;
            m++;
        }
        else
        {
            break;
        }
    }

    year = y;
    month = m;
    day = days;
}

// 输出重载 (参考你提供的逻辑，不使用 iomanip)
ostream& operator<<(ostream& os, const Date& d)
{
    if (d.year < 1000) os << "0";
    if (d.year < 100) os << "0";
    if (d.year < 10) os << "0";
    os << d.year << "-";

    if (d.month < 10) os << "0";
    os << d.month << "-";

    if (d.day < 10) os << "0";
    os << d.day;

    return os;
}

// 类型转换：日期 -> 天数 (参考你提供的逻辑)
Date::operator int() const
{
    int total_days = 0;

    for (int i = 1; i < year; i++)
    {
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
            total_days += 366;
        else
            total_days += 365;
    }

    int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    for (int i = 1; i < month; i++)
    {
        total_days += month_days[i];
        if (i == 2)
        {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            {
                total_days += 1;
            }
        }
    }

    total_days += day;

    return total_days;
}

// ---------------- 运算符实现 ----------------

// 自增前置
Date& Date::operator++() {
    *this += 1;
    return *this;
}
// 自增后置
Date Date::operator++(int) {
    Date temp = *this;
    *this += 1;
    return temp;
}
// 自减前置
Date& Date::operator--() {
    *this -= 1;
    return *this;
}
// 自减后置
Date Date::operator--(int) {
    Date temp = *this;
    *this -= 1;
    return temp;
}

// 复合赋值 +=
Date& Date::operator+=(int days) {
    // 转换为天数计算，再转回 Date
    int current_days = (int)(*this);
    *this = Date(current_days + days);
    return *this;
}
// 复合赋值 -=
Date& Date::operator-=(int days) {
    int current_days = (int)(*this);
    *this = Date(current_days - days);
    return *this;
}

// Date + int
Date Date::operator+(int days) const {
    return Date((int)(*this) + days);
}
// int + Date (友元)
Date operator+(int days, const Date& d) {
    return d + days;
}

// Date - int
Date Date::operator-(int days) const {
    return Date((int)(*this) - days);
}
// int - Date (根据样例，逻辑为 Date - int)
Date operator-(int days, const Date& d) {
    return d - days;
}

// Date - Date (返回天数差)
int Date::operator-(const Date& other) const {
    return (int)(*this) - (int)(other);
}

// 关系运算符 (转为 int 比较)
bool Date::operator<(const Date& other) const { return (int)(*this) < (int)(other); }
bool Date::operator>(const Date& other) const { return (int)(*this) > (int)(other); }
bool Date::operator<=(const Date& other) const { return (int)(*this) <= (int)(other); }
bool Date::operator>=(const Date& other) const { return (int)(*this) >= (int)(other); }
bool Date::operator==(const Date& other) const { return (int)(*this) == (int)(other); }
bool Date::operator!=(const Date& other) const { return (int)(*this) != (int)(other); }
/**************** TODO-END ****************/int main()
{
    cout << "*********************************" << endl;
    cout << "1. 基础版内容测试" << endl << endl;

    int year, month, day;
    cout << "请输入d1年月日：" << endl;
    cin >> year >> month >> day;
    Date d1(year, month, day);

    int days;
    cout << "请输入d2天数：" << endl;
    cin >> days;
    Date d2(days);

    cout << "d1日期为：" << endl;
    cout << d1 << endl;
    cout << "d2日期为：" << endl;
    cout << d2 << endl;

    cout << "d1转换为天数为：" << endl;
    cout << int(d1) << endl;
    cout << "d2转换为天数为：" << endl;
    cout << int(d2) << endl;

    cout << "d1 - d2 = " << d1 - d2 << endl;
    cout << "*********************************" << endl;
    cout << "2. 自增与自减运算符测试" << endl << endl;

    cout << "d1++ 结果为 " << d1++ << endl;
    cout << "++d1 结果为 " << ++d1 << endl;
    cout << "d1-- 结果为 " << d1-- << endl;
    cout << "--d1 结果为 " << --d1 << endl;

    cout << "*********************************" << endl;
    cout << "3. 复合赋值运算符测试" << endl << endl;

    int gap;
    cout << "请输入加减的天数：" << endl;
    cin >> gap;

    cout << "d1 += " << gap << " 结果为 " << (d1 += gap) << endl;
    cout << "d1 -= " << gap << " 结果为 " << (d1 -= gap) << endl;
    // 注意此时d1将会变为原来的值，因为上面的操作会改变d1的值

    cout << "*********************************" << endl;
    cout << "4. 加法/减法运算符测试" << endl << endl;

    cout << "d1 + " << gap << " = " << d1 + gap << endl;
    cout << gap << " + d1 = " << gap + d1 << endl;

    cout << "d1 - " << gap << " = " << d1 - gap << endl;
    cout << gap << " - d1 = " << gap - d1 << endl;

    cout << "*********************************" << endl;
    cout << "5. 关系运算符测试（1为真，0为假）" << endl << endl;

    cout << "d1 < d2 结果为 " << (d1 < d2) << endl;
    cout << "d1 > d2 结果为 " << (d1 > d2) << endl;
    cout << "d1 <= d2 结果为 " << (d1 <= d2) << endl;
    cout << "d1 >= d2 结果为 " << (d1 >= d2) << endl;
    cout << "d1 == d2 结果为 " << (d1 == d2) << endl;
    cout << "d1 != d2 结果为 " << (d1 != d2) << endl;

    cout << endl;

    cout << "d1 < " << days << " 结果为 " << (d1 < days) << endl;
    cout << "d1 > " << days << " 结果为 " << (d1 > days) << endl;
    cout << "d1 <= " << days << " 结果为 " << (d1 <= days) << endl;
    cout << "d1 >= " << days << " 结果为 " << (d1 >= days) << endl;
    cout << "d1 == " << days << " 结果为 " << (d1 == days) << endl;
    cout << "d1 != " << days << " 结果为 " << (d1 != days) << endl;

    cout << endl;

    cout << days << " > d1 结果为 " << (days > d1) << endl;
    cout << days << " < d1 结果为 " << (days < d1) << endl;
    cout << days << " >= d1 结果为 " << (days >= d1) << endl;
    cout << days << " <= d1 结果为 " << (days <= d1) << endl;
    cout << days << " == d1 结果为 " << (days == d1) << endl;
    cout << days << " != d1 结果为 " << (days != d1) << endl;

    cout << "*********************************" << endl;
    cout << "测试结束" << endl;

    return 0;
}