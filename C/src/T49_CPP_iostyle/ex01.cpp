#include <iostream>

namespace a
{
	int n;
}

namespace b
{
	int n;
}

using namespace std;

void ex01() {
	a::n = 10;
	b::n = 20;

	cout << "EX01" << endl;

	std::cout << "Hello World!" << 10 << 'c' << std::endl; // endl, �ٹٲ��� ����
	//std�� �̸�(������ �Լ� ��) ������ ������ִ� �Լ�, ��µ����͸� �и��ϱ� ���� '<<'�� ����
	//std�� ���ִ� ����� "using namespace std;"��� ���� �Է��ϸ�ȴ�

	cout << "Hello Man!" << endl;
}