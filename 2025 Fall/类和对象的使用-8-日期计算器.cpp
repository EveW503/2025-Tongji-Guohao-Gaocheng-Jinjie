#include <iostream>

class dateToDay
{
public:
    dateToDay(int, int, int);    // 通过传参构建
    // dateToDay();    // 构建时从键盘读入 实现方式二选一
    void setDate(int, int, int); // 设置日期
    // void setDate(); // 从键盘读入设置日期 实现方式二选一
    // 合法性检查应该在构建/设置时完成
    void display();    // 将计算结果输出(即本年内第几天)
private:
    bool checkLeap();  // 该函数用于检查闰年
    bool checkValid(); // 该函数用于检查合法
    int computeDay();  // 该函数用于计算日期
    int year;
    int month;
    int day;
};

dateToDay::dateToDay(int year, int month, int date)
{
	this->year = year;
	this->month = month;
	this->day = date;
	if (!checkValid())
	{
		std::cout << "Illegal" << std::endl;
        exit(0);
	}
}

void dateToDay::setDate(int year, int month, int date)
{
	this->year = year;
	this->month = month;
	this->day = date;
	if (!checkValid())
	{
		std::cout << "Illegal" << std::endl;
		exit(0);
	}
}

bool dateToDay::checkLeap()
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return true;
	else
		return false;
}

bool dateToDay::checkValid()
{
	if (year < 1 || year > 9999)
		return false;
	if (month < 1 || month > 12 || day < 1)
		return false;
	int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (checkLeap())
		days_in_month[1] = 29;
	if (day > days_in_month[month - 1])
		return false;
	return true;
}

int dateToDay::computeDay() 
{
	int total_days = 0;
	int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (checkLeap()) {
		days_in_month[1] = 29;
	}

	for (int i = 0; i < month - 1; ++i) {
		total_days += days_in_month[i];
	}
	total_days += day;

	return total_days;
}

void dateToDay::display()
{
	int day_of_year = computeDay();
	std::cout << year << "-" << month << "-" << day << "是" << year << "年的第" << day_of_year << "天" << std::endl;
}

int main() {
	int year, month, day;
	std::cout << "请输入日期（年 月 日）：" << std::endl;
	std::cin >> year >> month >> day;
	if (std::cin.fail()) {
		std::cout << "Illegal" << std::endl;
		exit(0);
	}

	dateToDay date(year, month, day);
	date.display();

	std::cout << "请输入日期（年 月 日）：" << std::endl;
	std::cin >> year >> month >> day;
	if (std::cin.fail()) {
		std::cout << "Illegal" << std::endl;
		exit(0);
	}

	date.setDate(year, month, day);
	date.display();

	return 0;
}