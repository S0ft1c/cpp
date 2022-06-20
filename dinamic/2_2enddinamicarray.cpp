#include<iostream>
#include<string>
#include<ctime>
#include<math.h>


//#define DEBUG


//define позволяет нам заменять какую либо часть на букавки, что нам удобнее, например 
#define PI 3.14 //вместо того чтобы вечно писать 3.14 мы будем писать PI и будем понимать что мы имеем число пи
#define MATH_TIMES(x, y) ((x)*(y))


using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	cout << "ДВУМЕРНЫЙ динамический массив" << endl;
	//в плюсах особо нормальной системы по созданию динамического двумерного массива (как и статического кста XD) нет
	//по сути своей это одномерный массив содержащий указатели на другой одномерный массив! да запутанно но зато эффективно

	//это создание нашего двумерного динамического массива

	int rows;
	int cols;
	cout << "Введите количество строчек" << endl;
	cin >> rows;
	cout << "Введите количество колонок" << endl;
	cin >> cols;

	int** arr_two_new = new int* [rows]; //** это нужно, ты как бы вызываешь указатель на указатель типа int. да я знаю

	for (int i = 0; i < rows; i++)
	{
		arr_two_new[i] = new int[cols];


	}
	//только сейчас мы завершили создание нашей чудо-махины
	//сейчасм зададим какие-нибудь значения всем элементам массива
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr_two_new[i][j] = rand() % 20;

		}
	} //сгенерировали
	//теперь выведем значения
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr_two_new[i][j] << "\t";

		}
		cout << endl;
	}


	//все что ниже это то что ОБЯЗАТЕЛЬНО для того чтобы удалить все и не потерять оперативку
	for (int i = 0; i < cols; i++)
	{
		delete[] arr_two_new[i];
	}

	delete[] arr_two_new;
}