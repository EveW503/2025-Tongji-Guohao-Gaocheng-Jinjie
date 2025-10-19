#include <fstream>
#include <iostream>
using namespace std;

struct student {
    int no;                // 学号
    char name[20];         // 姓名
    int score;             // 成绩
    struct student* next;  // 下一结点
    /*! 不允许修改上述结构 !*/
};

int main() {
	ifstream studentFile("student.txt");
    if (!studentFile.is_open()) {
		cout << "Error opening file!" << endl;
		exit(EXIT_FAILURE);
    }

    int student_num;
    if (!(studentFile >> student_num)) {
        cout << "读取学生人数失败!" << endl;
        return 1;
    }

    cout << "所有的学生信息如下：" << endl;

    student* head = NULL, * p = NULL, * q = NULL;
    for (int i = 0; i < student_num; i++) {
		p = new(nothrow) student;
        if (p == nullptr) {
            cout << "Memory allocation failed!" << endl;
			if (head != NULL) {
                student* current = head;
                while (current != NULL) {
                    student* temp = current;
                    current = current->next;
                    delete(temp);
                }
			}
			studentFile.close();
            exit(EXIT_FAILURE);
        }

		p->next = NULL;

        if (i == 0) {
            studentFile >> p->no >> p->name >> p->score;
            head = p;
            q = p;
        }
        else {
            studentFile >> p->no >> p->name >> p->score;
            q->next = p;
            q = p;
        }

        cout << "学号：" << p->no << " 姓名：" << p->name << " 成绩：" << p->score << endl;
    }

    student* current = head;
    while (current != NULL) {
        student* temp = current;
        current = current->next;
        delete(temp);
    }

	studentFile.close();
    return 0;
}