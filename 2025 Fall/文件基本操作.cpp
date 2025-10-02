#include <iostream>
#include <fstream>
using namespace std;

int num[20];
int temp;
int main() {
	ifstream numbers;
	numbers.open("1.txt",ios::in);

	for (int i = 0; i < 10;i++) {
		numbers >> num[i];
	}

	numbers.close();

	for (int i = 10; i < 20; i++) {
		cin >> num[i];
	}

	for (int i = 0; i < 20; i++) {
		for (int j = i + 1; j < 20; j++) {
			if (num[i] > num[j]) {
				temp = num[i];
				num[i] = num[j];
				num[j] = temp;
			}
		}
	}

	for (int i = 0; i < 20; i++) {
		cout << num[i] << endl;
	}

	return 0;
}