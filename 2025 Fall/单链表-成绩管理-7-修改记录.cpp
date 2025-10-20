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

bool searchbyID(student* head, student* &curr, int query) {

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
        /* 执行查询与删除 */
        int query;
        std::cin >> query;

		bool found = searchbyID(head, curr, query);

        if (!found) {
            cout << "不存在" << endl;
		}
		else if(found){
            int new_score;
			std::cin >> new_score;
			curr->score = new_score;
		}

        if (!isContinue())
        {
            break; // 当接收到不需要继续，则退出循环
        }
    }
    printList(head);
    /* 退出前打印现有名单 */

    student* current = head;
    while (current != NULL) {
        student* temp = current;
        current = current->next;
        free(temp);
    }

    fclose(fp);
    return 0;
}