#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


class SemesterGrad {
private:
   int ch_score;
   int math_score;
   int eng_score;
   double avg_score;
public:
   SemesterGrad() : ch_score(0), math_score(0), eng_score(0), avg_score(0.0) {}
   SemesterGrad(int ch, int math, int eng) : ch_score(ch), math_score(math), eng_score(eng) {
       avg_score = (ch_score + math_score + eng_score) / 3.0;
   }

   void displayScores(int semester) {

	   std::cout << "==学期" << semester<<  " == " << std::endl;
       std::cout << "语文成绩: " << ch_score << std::endl;
	   std::cout << "数学成绩: " << math_score << std::endl;
	   std::cout << "英语成绩: " << eng_score << std::endl;
	   std::cout << "平均成绩: " << avg_score << std::endl;
   }
};

class Student {
private:
   char name[100];
   int id;
   SemesterGrad sem_grad[4];
public:
   Student(const char* student_name, int id_input, int grade[4][3]) : id(id_input) {
       strcpy(name, student_name);

       for (int i = 0; i < 4; i++) {
           sem_grad[i] = SemesterGrad(grade[i][0], grade[i][1], grade[i][2]);
       }
   }

   void displayInfo() {

      std::cout << "==学生信息==" << std::endl;
      std::cout << "学生姓名: " << name << ", 学号: " << id << std::endl;
      std::cout << "==学期成绩==" << std::endl;
      for (int i = 0; i < 4; i++) {
          sem_grad[i].displayScores(i + 1); 
      }
   }
};

int main() {
   int grades[4][3] = { 0 };
   int id_input = 0;
   char student_name[100];
   std::cout << "请输入学生姓名和学号: ";
   std::cin >> student_name >> id_input; 

   for (int i = 0; i < 4; i++) {
       std::cout << "请输入第" << (i + 1) << "学期的语文、数学、英语成绩: ";
       std::cin >> grades[i][0] >> grades[i][1] >> grades[i][2];
   }

   Student Sophia(student_name, id_input, grades);
   Sophia.displayInfo();

   return 0;
}