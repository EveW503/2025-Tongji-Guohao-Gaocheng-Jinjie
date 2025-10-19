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

int main() {
    int student_num;

    FILE* fp;
    fp = fopen("student.txt", "r");
    if (fp == NULL) {
        cout << "Error opening file!" << endl;
        exit(EXIT_FAILURE);
    }

    if (fscanf(fp, "%d", &student_num) != 1) {
        cout << "Error reading student number from file!" << endl;
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    cout << "所有的学生信息如下：" << endl;

    student* head = NULL, * p = NULL, * q = NULL;
    for (int i = 0; i < student_num; i++) {
        p = (student*)malloc(sizeof(student));

        if (p == NULL) {
            cout << "Memory allocation failed!" << endl;
            if (head != NULL) {
                student* current = head;
                while (current != NULL) {
                    student* temp = current;
                    current = current->next;
                    free(temp);
                }
            }
            fclose(fp);
            exit(EXIT_FAILURE);
        }

        p->next = NULL;

        if (i == 0) {
            if (fscanf(fp, "%d %s %d", &p->no, &p->name, &p->score) != 3) {
                cout << "Error reading student information from file!" << endl;
                free(p);
                fclose(fp);
                exit(EXIT_FAILURE);
            }
            head = p;
            q = p;
        }
        else {
            if (fscanf(fp, "%d %s %d", &p->no, p->name, &p->score) != 3) {
                cout << "Error reading student information from file!" << endl;
                student* temp = NULL;
                while (head != NULL) {
                    temp = head;
                    head = head->next;
                    free(temp);
                }
                fclose(fp);
                exit(EXIT_FAILURE);
            }
            q->next = p;
            q = p;
        }

        cout << "学号：" << p->no << " 姓名：" << p->name << " 成绩：" << p->score << endl;
    }

    student* current = head;
    while (current != NULL) {
        student* temp = current;
        current = current->next;
        free(temp);
    }

    fclose(fp);
    return 0;
