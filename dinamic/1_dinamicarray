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

	cout << "динамический массив" << endl;
	//почему он так называется, во первых такой массив находится в динамической памяти, во вторых задать количество элементов массиву мы можем 
	//по ходу действия, заранее не зная сколько элементов будет! В отличие от статич. массива где мы должны были задать значение так еще и оно
	//должно было быть константой
	int longer = 0;


	cout << "Enter array size!" << endl;
	cin >> longer;

	int* arr_new = new int[longer];

	for (int i = 0; i < longer; i++)
	{
		arr_new[i] = rand() % 10; //данный цикл вводит данные в массив



	}
	for (int i = 0; i < longer; i++)
	{
		cout << arr_new[i] << "\t"; //с разыменованием

		cout << arr_new + i << endl; //без него (тупо адреса)



	}
	delete[] arr_new;
}
