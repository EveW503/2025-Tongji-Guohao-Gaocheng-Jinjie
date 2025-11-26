#include <iostream>

class StudentInfo {
private:
	int id;
	int score;
	int count;
public:
	StudentInfo() {};
	StudentInfo(int i, int s,int c) : id(i), score(s), count(c) {};

	void displayInfo() {
		std::cout << "第" << count << "个学生的学号是 : " << id << ", 成绩为 " << score << std::endl;
	}
};

int main() {
	const int SIZE = 5;
	StudentInfo Students[SIZE];

	for (int i = 0; i < 5; i++) {
		int id, score;
		std::cin >> id >> score;
		Students[i] = StudentInfo(id, score,i);
	}

	StudentInfo* ptr = Students;
	ptr[0].displayInfo();
	ptr[2].displayInfo();
	ptr[4].displayInfo();

	return 0;
}