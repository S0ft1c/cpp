#include<iostream> 
using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");     

	cout << "Вложенность конструкций (циклов)" << NEW_LINE;

	//тут мы рассматриваем вариант когда итераторы разные

	i = 1;
	for (; i < 5; i++)
	{
		cout << "Сработал 1 цикл for, итерация № " << i << NEW_LINE;

		for (int j = 0; j < 5; j++)
		{
			cout << TAB << "Сработал 2 цикл for, итерация № " << j << NEW_LINE;

		}
	}

	int width, heigth;

	cout << "Введите длину и ширину" << NEW_LINE;
	cin >> width >> heigth;
	for (i = 0; i < heigth; i++)
	{

		for (int j = 0; j < width; j++)
		{
			cout << "*";
		}
		cout << NEW_LINE;

	}
}
