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

void printList(student* head) {
    student* curr = head;
    while (curr) {
        cout << curr->no << " " << curr->name << " " << curr->score << endl;
        curr = curr->next;
    }
}


bool isContinue()
{
    std::cout << "是否继续?(y/n): \n";
    char tmp;
    std::cin >> tmp;
    if (tmp == 'Y' || tmp == 'y')
    {
        return true;
    }
    return false;
}

bool searchbyID(student* head, student*& curr, int query) {

    curr = head;
    bool found = false;

    while (curr != NULL) {
        if (curr->no == query) {
            found = true;
            break;
        }
        curr = curr->next;
    }

    return found;
}

student* sort(student* head) {
    if (!head || !head->next) return head;

    bool swapped;
    student* last_unsorted = nullptr;

    do {
        swapped = false;
        student* curr = head;

        while (curr->next != last_unsorted) {
            if (curr->score < curr->next->score) {
                std::swap(curr->no, curr->next->no);
                std::swap(curr->score, curr->next->score);
                std::swap(curr->name, curr->next->name);
                swapped = true;
            }
            else if (curr->score == curr->next->score) {
                if (curr->no > curr->next->no) {
                    std::swap(curr->no, curr->next->no);
                    std::swap(curr->score, curr->next->score);
                    std::swap(curr->name, curr->next->name);
                }
            }
            curr = curr->next;
        }
        last_unsorted = curr;

    } while (swapped);

    return head;
}

int main()
{
    /* 在这里读取文件 */
    FILE* fp = fopen("student.txt", "r");
    if (fp == NULL) {
        cout << "Error opening file!" << endl;
        exit(EXIT_FAILURE);
    }

    student* head = NULL;
    read(fp, head);
    // 当你读取完成
    student* curr = head;
    while (1)
    {
        /* 执行添加 */
        int new_no;
        std::cin >> new_no;

        bool found = searchbyID(head, curr, new_no);

        if (found) {
            cout << "已存在" << endl;
        }
        else if (!found) {
			char new_name[20];
			int new_score;
			cin >> new_name >> new_score;
			student* newStudent = (student*)malloc(sizeof(student));
            if (newStudent == NULL) {
				cout << "Memory allocation failed!" << endl;
				student* temp = NULL;
                while (head != NULL) {
                    temp = head;
                    head = head->next;
                    free(temp);
                }
            }
            else {
                newStudent->no = new_no;
                newStudent->score = new_score;
                for (int i = 0; i < 20; i++) {
                    newStudent->name[i] = new_name[i];
                }
                newStudent->next = head;
                head = newStudent;
            }
        }

        if (!isContinue())
        {
            break; // 当接收到不需要继续，则退出循环
        }
    }
    /* 退出前排序并打印现有名单 */
	sort(head); 
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
