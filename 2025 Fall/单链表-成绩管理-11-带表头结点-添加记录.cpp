#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
using namespace std;

struct student {
    int no;                // 学号
    char name[20];         // 姓名
    int score;             // 成绩
    struct student* next;  // 下一结点
    /*! 不允许修改上述结构 !*/
};

void read(FILE* fp, student*& real_head) {
    int student_num;
    student* p = NULL, * q = NULL, * head = NULL;

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
    real_head = (student*)malloc(sizeof(student));
    if (real_head == NULL) {
        cout << "Memory allocation failed!" << endl;
        exit(EXIT_FAILURE);
    }
    real_head->next = head;
}

void printList(student* real_head) {

    student* curr = real_head->next;

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

bool searchbyID(student* real_head, int query, student*& curr) {
    bool found = false;
    while (curr) {

        if (curr->next != NULL && curr->next->no == query) {
            found = true;
            break;
        }

        curr = curr->next;
    }

    return found;
}

student* sort(student* head) {
    if (!head || !head->next || !head->next->next) return head;

    bool swapped;
    student* last_unsorted = nullptr;

    do {
        swapped = false;
        student* prev = head;  
        student* curr = head->next;  

        while (curr->next != last_unsorted) {
            student* next_node = curr->next;

            if (curr->score < next_node->score ||
                (curr->score == next_node->score && curr->no > next_node->no)) {

                curr->next = next_node->next;
                next_node->next = curr;
                prev->next = next_node;

                swapped = true;

                curr = next_node;
            }
            prev = curr;
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

    student* real_head = NULL;
    read(fp, real_head);
    // 当你读取完成
    student* curr = real_head;
    while (1)
    {
        /* 执行查询与ADD */
        int new_no;
        std::cout << "请输入要添加的学生学号: \n";
        std::cin >> new_no;

        bool found = false;
        curr = real_head;
        found = searchbyID(real_head, new_no, curr);

        if (!found) {
            char new_name[20];
            int new_score;
            std::cin >> new_name >> new_score;
            student* newStudent = (student*)malloc(sizeof(student));
            if (newStudent == NULL) {
                std::cout << "Memory allocation failed!" << std::endl;
                student* temp = NULL;
                while (real_head != NULL) {
                    temp = real_head;
                    real_head = real_head->next;
                    free(temp);
                }
            }
            else {
                newStudent->no = new_no;
                newStudent->score = new_score;
                for (int i = 0; i < 20; i++) {
                    newStudent->name[i] = new_name[i];
                }
                newStudent->next = real_head->next;
				real_head->next = newStudent;
            }

        }
        else if (found) {
            cout << "已存在" << endl;
        }

        if (!isContinue())
        {
            break; // 当接收到不需要继续，则退出循环
        }
    }
    sort(real_head);
    printList(real_head);
    /* 退出前打印现有名单 */

    student* current = real_head;
    while (current != NULL) {
        student* temp = current;
        current = current->next;
        free(temp);
    }

    fclose(fp);
    return 0;
}