#include <iostream>
#include <string>

using namespace std;

void ex03() {

	cout << "EX03" << endl;

	//char str[] = "Hello";
	string str;
	str = "Hello";
	cout << str << endl;

	string name;
	cout << "�̸� �Է�: ";
	cin >> name;

	string msg = "�̸� : " + name + " �Դϴ�.";
	cout << msg << endl;
}