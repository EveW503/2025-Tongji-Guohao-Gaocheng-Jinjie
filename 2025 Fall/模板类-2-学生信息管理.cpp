#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Student
{
public:
    Student(int id, const string &name) : id(id), name(name) {}

    int getId() const
    {
        return id;
    }
    string getName() const
    {
        return name;
    }

private:
    int id;
    string name;
};

class StudentManagementSystem
{
public:
    void addStudent(unique_ptr<Student> stu)
    {
        /****************** TODO ******************/
        // 添加学生
        Students.push_back(std::move(stu));
        /**************** TODO-END ****************/
    }

    void findAndPrintStudent(int id)
    {
        Student *stu = nullptr;
        /****************** TODO ******************/
        // 查找学生编号为id的学生
        for (const auto &s : Students)
        {
            if (s->getId() == id)
            {
                // get() 返回原生指针，仅用于访问，不改变所有权
                stu = s.get();
                break;
            }
        }
        /**************** TODO-END ****************/
        if (stu != nullptr)
        {
            cout << "学生编号: " << stu->getId() << "，姓名: " << stu->getName() << endl;
        }
        else
        {
            cout << "未找到该学生" << endl;
        }
    }

private:
    vector<unique_ptr<Student>> Students;
};

int main()
{
    StudentManagementSystem stus;

    int id;
    string name;
    cout << "请依次输入学生编号和姓名：" << endl;
    while (true)
    {
        cin >> id;
        if (id == -1)
        {
            break;
        }

        cin.ignore(); // 忽略前面输入编号后的空格
        getline(cin, name);
        /****************** TODO ******************/
        // 调用addStudent函数添加学生
        stus.addStudent(make_unique<Student>(id, name));
        /**************** TODO-END ****************/
    }

    cout << "请输入要查找的学生编号: " << endl;
    cin >> id;
    stus.findAndPrintStudent(id);

    return 0;
}