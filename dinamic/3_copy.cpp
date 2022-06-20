#include<iostream>
#include<string>
#include<ctime>
#include<math.h>


//#define DEBUG честно говоря вспомнил об этом только сейчас и вообще забыл что это блть
//знаю только одно - это нах*й не нужно


//define позволяет нам заменять какую либо часть на букавки, что нам удобнее, например 
#define PI 3.14 //вместо того чтобы вечно писать 3.14 мы будем писать PI и будем понимать что мы имеем число пи
#define MATH_TIMES(x, y) ((x)*(y))

void FillOneArr(int* const arr_new, const int longer)
{
	for (int i = 0; i < longer; i++)
	{
		arr_new[i] = rand() % 10;
	}

}

void ShowOneArr(const int* const arr_new, const int longer)
{
	for (int i = 0; i < longer; i++)
	{
		cout << arr_new[i] << "\t";
	}
}

using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	cout << "как скопировать динамический массив в плюсах" << endl;
	//итак навернху есть две функции, FillOneArr и ShowOneArr, по названию догадался что они делают
	//const там стоят для безопастности, и это реально полезно!


}
