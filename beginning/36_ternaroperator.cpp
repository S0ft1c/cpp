#include<iostream>
#include<string>
#include<ctime>
#include<math.h>


#define PI 3.14 
#define MATH_TIMES(x, y) ((x)*(y))


using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");     

	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	cout << "условный тернарный оператор" << endl;
	//это тот который может взаимодействовать с тремя аперандами, переменными короч
	//вспомним просто про if else 
	int ter1;
	cout << "введите значение перменной а" << endl;
	cin >> ter1;

	//вот он просто if else
	if (ter1 < 10)
	{
		cout << "а меньше 10" << endl; //видишь как много кода ушло на такое простое задание
	}
	else if (ter1 > 10)
	{
		cout << "а больше 10" << endl;
	}
	else
	{
		cout << "а равно 10" << endl;
	}

	//а вот он особый, по сути повторяет все то что написано до этого, только в одной строке

	ter1 < 10 ? cout << "а меньше 10" << endl : ter1>10 ? cout << "а больше 10" << endl : cout << "а равен 10" << endl; //да, можно сказать что это менее читабельно, но тем не менее это удобно
}
