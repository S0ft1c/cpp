#include<iostream> 
using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");     //ф-я отвечающая за вывод русских символов в консоль
	
	cout << "№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№" << NEW_LINE;
	cout << "Операторы" << NEW_LINE;

	//ОПЕРАТОРЫ  БЫВАЮТ 3 ТИПОВ:
	//Унарные
	//Бинарные
	//Тернарные

	//ЭТО УНАРНЫЙ ОПЕРАТОР
	// он один единственный = присвоение противоположного числа
	//по другому просто минус
	int a = 5;
	cout << a << NEW_LINE;
	a = -a;     //унарный оператор
	cout << a << NEW_LINE;



	//ЭТО БИНАРНЫЙ ОПЕРАТОР
	//один из примеров это математические вычисления
	//также это могут быть вычисления равенства, неравенства, больше, меньше и т.д.
	int b1 = 5, b2 = 2, b3;
	b3 = b1 + b2;    //бинарный оператор
	cout << b3 << NEW_LINE;

	//а про тернарный вы пока знать не будете
}
