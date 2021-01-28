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
	cout << "이름 입력: ";
	cin >> name;

	string msg = "이름 : " + name + " 입니다.";
	cout << msg << endl;
}