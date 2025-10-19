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

void read(FILE* fp, student*& head) {
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
        p->next = NULL;
    }
}

// 优化的冒泡排序
student* optimizedBubbleSort(student* head) {
    if (!head || !head->next) return head;

    bool swapped;
    student* last_unsorted = nullptr;

    do {
        swapped = false;
        student* curr = head;

        while (curr->next != last_unsorted) {
            if (curr->score < curr->next->score) {
				swap(curr->no, curr->next->no);
                swap(curr->score, curr->next->score);
				swap(curr->name, curr->next->name);
                swapped = true;
			}
            else if (curr->score == curr->next->score) {
                if (curr->no > curr->next->no) {
					swap(curr->no, curr->next->no);
					swap(curr->score, curr->next->score);
					swap(curr->name, curr->next->name);
                }
            }
            curr = curr->next;
        }
        last_unsorted = curr;

    } while (swapped);

    return head;
}

void printList(student* head) {
	student* curr = head;
	while (curr) {
		cout << curr->no << " " << curr->name << " " << curr->score << endl;
		curr = curr->next;
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

	student* head = NULL, * temp = NULL, * prev = NULL, *curr = NULL;

    read(fp, head);
    
	optimizedBubbleSort(head);
    
	cout << "Sorted student records:" << endl;
	printList(head);

    student* current = head;
    while (current != NULL) {
        student* temp = current;
        current = current->next;
        free(temp);
    }

    fclose(fp);
    return 0;
}