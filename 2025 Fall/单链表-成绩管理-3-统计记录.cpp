#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdlib.h>
using namespace std;

struct student {
    int no;                // 学号
    char name[20];         // 姓名
    int score;             // 成绩
    struct student* next;  // 下一结点
    /*! 不允许修改上述结构 !*/
};

void read(FILE *fp, student* &head) {
    int student_num;
    student* p = NULL, * q = NULL;

    if (fscanf(fp, "%d", &student_num) != 1) {
        cout << "Error reading student number from file!" << endl;
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < student_num; i++) {
        p = (student*)malloc(sizeof(student));
        if (p == NULL) {
            cout << "Memory allocation failed!" << endl;
            fclose(fp);
            exit(EXIT_FAILURE);
        }

        if (i == 0) {
            if (fscanf(fp, "%d %s %d", &p->no, &p->name, &p->score) != 3) {
                cout << "Error reading student information from file!" << endl;
                fclose(fp);
                exit(EXIT_FAILURE);
            }
            head = p;
            q = p;
        }
        else {
            if (fscanf(fp, "%d %s %d", &p->no, p->name, &p->score) != 3) {
                cout << "Error reading student information from file!" << endl;
                fclose(fp);
                exit(EXIT_FAILURE);
            }
            q->next = p;
            q = p;
        }
        p->next = NULL;
    }
}

int main() {
	int student_u = 0, student_liang = 0, student_zhong = 0, student_jige = 0, student_bujige = 0;
    FILE* fp;

    fp = fopen("student.txt", "r");
    if (fp == NULL) {
        cout << "Error opening file!" << endl;
        exit(EXIT_FAILURE);
    }

    student* head = NULL;

    read(fp, head);

	while (head != NULL) {
		if (head->score >= 90) {
			student_u++;
		}
		else if (head->score >= 80) {
			student_liang++;
		}
		else if (head->score >= 70) {
			student_zhong++;
		}
		else if (head->score >= 60) {
			student_jige++;
		}
		else {
			student_bujige++;
		}

		head = head->next;
	}

	cout << "统计信息如下：优: " << student_u << "人 良: " << student_liang << "人 中: " << student_zhong << "人 及格: " << student_jige << "人 不及格: " << student_bujige << "人" << endl;

    fclose(fp);
	return 0;
}