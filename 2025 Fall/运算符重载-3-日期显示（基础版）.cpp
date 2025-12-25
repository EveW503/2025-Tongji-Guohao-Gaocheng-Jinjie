#include <iostream>
using namespace std;

class Date
{
private:
	int year, month, day;

public:
	Date(int y, int m, int d);
	Date(int days); // 从公元元年（0001年）1月1日开始的天数，仅考虑公元元年之后的日期

	// 注意输出格式，格式为"yyyy-mm-dd"，如"2000-01-01"，位数不足的要补0
	/****************** TODO ******************/
	friend ostream& operator<<(ostream& os, const Date& d);
	friend int operator-(const Date& d1, const Date& d2);
	explicit operator int() const;

	/**************** TODO-END ****************/
};

/****************** TODO ******************/
Date::Date(int y, int m, int d)
{
    year = y;
    month = m;
    day = d;
}

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

int operator-(const Date& d1, const Date& d2)
{
    return int(d1) - int(d2);
}

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


/**************** TODO-END ****************/

int main()
{
	// 测试构造函数
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

	// 测试类型转换运算符重载
	cout << "d1转换为天数为：" << endl;
	cout << int(d1) << endl;
	cout << "d2转换为天数为：" << endl;
	cout << int(d2) << endl;

	// 测试减法运算符重载
	cout << "d1和d2相差天数为：" << endl;
	cout << d1 - d2 << endl;

	return 0;
}