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

	std::cout << "Hello World!" << 10 << 'c' << std::endl; // endl, 줄바꿈을 뜻함
	//std는 이름(변수나 함수 등) 공간을 만들어주는 함수, 출력데이터를 분리하기 위해 '<<'를 쓴다
	//std를 없애는 방법은 "using namespace std;"라고 위에 입력하면된다

	cout << "Hello Man!" << endl;
}