#include <iostream>
using namespace std;

void itobs(int num, char* buffer) {
    /* 将整数转换为二进制并存入 buffer 字符串 */
    /* 例：1964 的二进制是：00000000 00000000 00000111 10101100 */
	unsigned int test_num = 1 << 31;
	for (int i = 0; i < 36; i++) {
		if (i == 8 || i == 17 || i == 26) {
			buffer[i] = ' ';
		}
		else if (num & test_num) {
			buffer[i] = '1';
			test_num >>= 1;
		}
		else {
			buffer[i] = '0';
			test_num >>= 1;
		}
	}
	buffer[35] = '\0'; 
}

int main() {
    int num;
    char buffer[36];
	cout << "输入一些整数： ";
    while (cin >> num) {
		itobs(num, buffer);
		cout << num << " 的二进制是：" << buffer << endl;
    }
	cout << "------程序结束------" << endl;
	return 0;
}