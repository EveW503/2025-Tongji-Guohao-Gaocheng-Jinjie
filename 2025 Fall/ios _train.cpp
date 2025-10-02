#include <iostream>
using namespace std;

/* 复读整数，并拒绝错误输入 */
istream& f(istream& in) {
    /* 复读整数，并拒绝错误输入 */
    auto in_state = in.rdstate(); // 保存流入函数的状态
    int num;

    while (true) {
        in >> num;

        if (in.good()) {

            if (in.peek() != ' ' && in.peek() != '\n' && in.peek() != EOF) {
                cout << "Illegal" << endl;
                
                in.clear();
                while (cin.get() != '\n') continue; 
                continue;
            }

            if (num == -1) {
                cout << "------程序结束------" << endl;
                break;
            }

            cout << "你说了:" << num << endl;
        }
        else if (in.eof()) {

            break;

        }
        else if (in.fail()) {

            cout << "Illegal" << endl;

            in.clear();
            while (cin.get() != '\n')
                continue;
        }

    }
    in.setstate(in_state);        // 复位流           
    return in;
}

int main() {
    cout << "请输入一些整数，以-1或Ctrl+Z结束。" << endl;
    f(cin);
    return 0;
