#include<iostream> 
using namespace std;

void foo1();

void main()
{
	setlocale(LC_ALL, "Rus");     

	cout << "Прототип функции" << NEW_LINE;

	foo1();//внизу, под ф-ей main лежит ф-ия foo1, наверху оставлен прототип функции foo1, чтоюы коспилятор не ругался
}

void foo1()
{
	cout << "Я вызвавась" << endl;
}
int global = 1;//глобальная переменная
