#include<iostream> 
using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");     

	cout << "сокращенные арифметические действия" << NEW_LINE;
	a = 0;
	cout << a << NEW_LINE;

	a += 20; //сложение
	cout << a << NEW_LINE;

	a -= 10;//вычитание
	cout << a << NEW_LINE;

	a *= 2;//умножение
	cout << a << NEW_LINE;

	a /= 2;//деление
	cout << a << NEW_LINE;
}
