#include<iostream>
#include<string>
#include<ctime>
#include<math.h>


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

void push_back_for_one(int*& arr, int& size, const int value)
{
	int* new_massiv = new int[size + 1];

	for (int i = 0; i < size; i++)
	{
		new_massiv[i] = arr[i];
	}

	new_massiv[size++] = value;

	delete[] arr;

	arr = new_massiv;

}



void pop_back_for_one(int*& arr, int& size)
{
	size--;

	int* new_massiv = new int[size];

	for (int i = 0; i < size; i++)
	{
		new_massiv[i] = arr[i];
	}

	delete[] arr;

	arr = new_massiv;

}



//define позволяет нам заменять какую либо часть на букавки, что нам удобнее, например 
#define PI 3.14 //вместо того чтобы вечно писать 3.14 мы будем писать PI и будем понимать что мы имеем число пи
#define MATH_TIMES(x, y) ((x)*(y))


using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	cout << "изменение размеров и изменение данных массива" << endl;

	//ИЗМЕНЕНИЕ ДАННЫХ В МАССИВЕ
	//любой массив должен находится в памяти непрерывно, следовательно если оперативка решит воткнуть ваш массив впритык между другими данными
	//то просто так добавить что либо, не получится
	//решение есть, для того чтобы добавить в массив что-то, надо создать абсолютно идентичный массив, просто на x элементов больше
	//НО но, чтобы у нас не было утечки памяти удалаяем предыдущий массив, а указатель переписываем на новый

	//УДАЛЕНИЕ ДАННЫХ В МАССИВЕ
	//тут проблема абсолютно та же, не повверите, но даже решение тоже самое просто вместо добавления, удаляем x элементов

	//однако надо понимать, добавление и удаление первого и последнего элемента, немного проще чем удаление или изменение элемента где-то в середине

	int longerr = 5;
	int* massiv = new int[longerr];

	FillOneArr(massiv, longerr);

	ShowOneArr(massiv, longerr);

	push_back_for_one(massiv, longerr, 111);

	cout << endl;

	ShowOneArr(massiv, longerr);

	pop_back_for_one(massiv, longerr);

	cout << endl;

	ShowOneArr(massiv, longerr);

	delete[] massiv;

	cout << endl;
	//вот как-то так, мда, странно согласен, зато работает!
}
