#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>

struct student {
    int no;                // 学号
    char name[20];         // 姓名
    int score;             // 成绩
    struct student* next;  // 下一结点
    /*! 不允许修改上述结构 !*/
};

void read(student*& head) {
    int student_num;
    student* p = NULL, * q = NULL;

    /* 在这里读取文件 */
    FILE* fp = fopen("student.txt", "r");
    if (fp == NULL) {
        std::cout << "Error opening file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (fscanf(fp, "%d", &student_num) != 1) {
        std::cout << "Error reading student number from file!" << std::endl;
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < student_num; i++) {
        p = (student*)malloc(sizeof(student));
        if (p == NULL) {
            std::cout << "Memory allocation failed!" << std::endl;
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
                std::cout << "Error reading student information from file!" << std::endl;
                free(p);
                fclose(fp);
                exit(EXIT_FAILURE);
            }
            head = p;
            q = p;
        }
        else {
            if (fscanf(fp, "%d %s %d", &p->no, p->name, &p->score) != 3) {
                std::cout << "Error reading student information from file!" << std::endl;
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
	fclose(fp);
}

void quit(student* head) {
	student* current = head;
	while (current != NULL) {
		student* temp = current;
		current = current->next;
		free(temp);
	}
}

bool isContinue()
{
    std::cout << "是否继续？(y/n): \n";
    char tmp;
    std::cin >> tmp;
    if (tmp == 'Y' || tmp == 'y')
    {
        return true;
    }
    return false;
}

void menu()
{
    int i;
    std::cout << std::endl;
    for (i = 0; i < 57; i++)
    {
        std::cout << '*';
    }
    std::cout << std::endl;
    std::cout << "*\t1 显示记录\t2 统计记录\t3 排序记录\t*\n";
    std::cout << "*\t4 查找记录\t5 删除记录\t6 修改记录\t*\n";
    std::cout << "*\t7 添加记录\t0 退出系统\t\t\t*\n";
    for (i = 0; i < 57; i++)
    {
        std::cout << '*';
    }
}

void disp(student* head) {
    student* curr = head;
    while (curr) {
        std::cout << curr->no << " " << curr->name << " " << curr->score << std::endl;
        curr = curr->next;
    }
}

void count(student* head) {
    int student_u = 0, student_liang = 0, student_zhong = 0, student_jige = 0, student_bujige = 0;
	student* curr = head;
    while (curr != NULL) {
        if (curr->score >= 90) {
            student_u++;
        }
        else if (curr->score >= 80) {
            student_liang++;
        }
        else if (curr->score >= 70) {
            student_zhong++;
        }
        else if (curr->score >= 60) {
            student_jige++;
        }
        else {
            student_bujige++;
        }

        curr = curr->next;
    }

    std::cout << "统计信息如下：优: " << student_u << "人 良: " << student_liang << "人 中: " << student_zhong << "人 及格: " << student_jige << "人 不及格: " << student_bujige << "人" << std::endl;
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
                char temp_name[20];
                strcpy(temp_name, curr->name);
                strcpy(curr->name, curr->next->name);
                strcpy(curr->next->name, temp_name);
                swapped = true;
            }
            else if (curr->score == curr->next->score) {
                if (curr->no > curr->next->no) {
                    std::swap(curr->no, curr->next->no);
                    std::swap(curr->score, curr->next->score);
                    char temp_name[20];
                    strcpy(temp_name, curr->name);
                    strcpy(curr->name, curr->next->name);
                    strcpy(curr->next->name, temp_name);
                }
            }
            curr = curr->next;
        }
        last_unsorted = curr;

    } while (swapped);

    return head;
}   

void searchbyID(student* head) {
    while (1)
    {
        // 程序查询循环
        int query;
        std::cin >> query;
        /* 执行查询 */
        student* curr = head;
        bool found = false;

        while (curr) {
            if (curr->no == query) {
                std::cout << curr->no << " " << curr->name << " " << curr->score << std::endl;
                found = true;
                break;
            }
            curr = curr->next;
        }

        if (!found) {
            std::cout << "不存在" << std::endl;
        }

        if (!isContinue())
        {
            break; // 当接收到不需要继续，则退出循环
        }
    }
}

void delbyID(student* &head) {
    student* curr = head;
    while (1)
    {
        /* 执行查询与删除 */
        int query;
        std::cin >> query;

        bool found = false;

        if (head != NULL && head->no == query) {
            student* temp = head;
            head = head->next;
            free(temp);
            found = true;
        }
        else {
            // 处理其他节点
            student* curr = head;
            while (curr != NULL && curr->next != NULL) {
                if (curr->next->no == query) {
                    student* temp = curr->next;
                    curr->next = curr->next->next;
                    free(temp);
                    found = true;
                    break;
                }
                curr = curr->next;
            }
        }


        if (!found) {
            std::cout << "不存在" << std::endl;
        }

        if (!isContinue())
        {
            break; // 当接收到不需要继续，则退出循环
        }
    }
}

void modibyID(student* head) {
    while (1)
    {
        /* 执行查询与删除 */
        int query;
        std::cin >> query;

        student* curr = head;
        bool found = false;

        while (curr != NULL) {
            if (curr->no == query) {
                found = true;
                break;
            }
            curr = curr->next;
        }

        if (!found) {
            std::cout << "不存在" << std::endl;
			std::cin.ignore(10000, '\n');
        }
        else if (found) {
            int new_score;
            std::cin >> new_score;
            curr->score = new_score;
        }

        if (!isContinue())
        {
            break; // 当接收到不需要继续，则退出循环
        }
    }
}

void addbyID(student* &head) {
    student* curr = head;
    while (1)
    {
        /* 执行添加 */
        int new_no;
        std::cin >> new_no;

        bool found = false;

        while (curr != NULL) {
            if (curr->no == new_no) {
                found = true;
                break;
            }
            curr = curr->next;
        }

        if (found) {
            std::cout << "已存在" << std::endl;
			std::cin.ignore(10000, '\n'); 
        }
        else if (!found) {
            char new_name[20];
            int new_score;
            std::cin >> new_name >> new_score;
            student* newStudent = (student*)malloc(sizeof(student));
            if (newStudent == NULL) {
                std::cout << "Memory allocation failed!" << std::endl;
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
}


int main()
{
    int choice; // 保证输入的为正整数数字
    char ch;
	student* head = NULL;

    read(head); // 在这里读取文件或作初始化操作，自行设计
    menu();  // 调用菜单显示函数，为防止输出超出限度，请将此项放在循环外部

    while (true) // 注意该循环退出的条件
    {
        std::cout << "选择菜单项(0~7):";
        std::cin >> choice;
        if (choice == 0) // 选择退出
        {
            std::cout << "\n 确定退出吗?(y/n)" << std::endl;
            std::cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                quit(head); // 自行设计
                break;
            }
            else
                continue;
        }
        switch (choice)
        {
        case 1:
            disp(head); // 自行设计
            break;
        case 2:
            count(head); // 自行设计
            break;
        case 3:
            head = sort(head); // 自行设计
            break;
        case 4:
            searchbyID(head); // 自行设计
            break;
        case 5:
            delbyID(head); // 自行设计
            break;
        case 6:
            modibyID(head); // 自行设计
            break;
        case 7:
            addbyID(head); // 自行设计
            break;
        default:
            std::cout << "\n输入错误，请从新输入" << std::endl;
        }
    }
    return 0;
}