#include<iostream> 
using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");     

	cout << "Массив" << NEW_LINE;

	//Массив - это совокупность переменных, каждая из которых имеет свой индекс(порядковый номер) и свое значение, и вся эта штука 
	//хранится под одним именем

	//индексы в массиве отсчитываются с 0!!!!

	//для того чтобы вызвать элемент по индексу нужно использовать следующую запись --> array[0]
	//для того чтобы объявить массив нужно использовать следующую запись ТИП_ДАННЫХ ИМЯ [кол-во элементов]
	//или ТИП_ДАННЫХ ИМЯ [] = {внести значния в массив через запятую} // *а еще можно даже без равно*
	//ВАЖНО не пиши сколько именно элементов в массиве во 2 способе!

	int arr[4];
	arr[0] = 5;  //1 вариант как внести данные в массив
	arr[0] = 7;
	arr[0] = 898;
	arr[0] = 123;

	cout << arr[0] << NEW_LINE;

	int arr2[] = { 1,5,798,549 };

	cout << arr2[3] << NEW_LINE;

	cout << "Взаимодействие массива с циклами" << NEW_LINE;

	const int SIZE = 10;

	int arr3[SIZE]{};
	//в основном обращаются к элементам массива с помощью цикла for
	for (int i = 0; i < SIZE; i++)
	{
		arr3[i] = i;

	}


	for (int i = 0; i < SIZE; i++)
	{
		cout << arr3[i] << NEW_LINE;

	}
}