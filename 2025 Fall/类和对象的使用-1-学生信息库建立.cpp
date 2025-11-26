#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Student {
private:
	char name[100];
	int num;
	int ch_score;
	int math_score;
	int eng_score;
	int avg_score;

public:
	Student() {};
	Student(const char* name, int num, int ch_score, int math_score, int eng_score) {
		strcpy(this->name, name);
		this->num = num;
		this->ch_score = ch_score;
		this->math_score = math_score;
		this->eng_score = eng_score;
		calculateAvg();
	}

	void calculateAvg() {
		avg_score = (ch_score + math_score + eng_score) / 3;
	}

	void displayInfo() {
		std::cout << "==学生信息==" << std::endl;
		std::cout << "姓名：" << name << std::endl;
		std::cout << "学号：" << num << std::endl;
		std::cout << "====成绩====" << std::endl;
		std::cout << "语文成绩：" << ch_score << std::endl;
		std::cout << "数学成绩：" << math_score << std::endl;
		std::cout << "英语成绩：" << eng_score << std::endl;
		std::cout << "平均成绩：" << avg_score << std::endl;
	}
};
int main() {
	Student student[5];
	for (int i = 0; i < 5; i++) {
		char name[100] = {" "};
		int num = 0;
		int ch_score = 0;
		int math_score = 0;
		int eng_score = 0;
		std::cout << "请输入学生的姓名、学号、语文成绩、数学成绩、英语成绩：" << std::endl;
		std::cin >>name >> num >> ch_score >> math_score >> eng_score;
		student[i] = Student(name, num, ch_score, math_score, eng_score);
		student[i].displayInfo();
	}
	return 0;
}