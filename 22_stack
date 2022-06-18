#include<iostream> 
using namespace std;

int recursion(int a)
{
	if (a < 1) { return 0; }

	a--;
	cout << a << endl;

	return recursion(a);
}
int Fact(int n)
{
	if (n == 0) { return 0; }
	if (n == 1) { return 1; }
	return n * Fact(n - 1);
}

void main()
{
	setlocale(LC_ALL, "Rus");     

	cout << "функции и стек" << NEW_LINE;
	//Стек - это как хранилище для цепочки функций(когда одна вызывает другую а та в свою очередь еще другую), переполнять не советую
	//по сути последняя попавшая в стек прога, выполняется первой

	//Рекурсия - вызов функцией саму себя

	recursion(5); // ф-я recursion

	//эксперимент с факториалом
	cout << Fact(5) << NEW_LINE;
}
