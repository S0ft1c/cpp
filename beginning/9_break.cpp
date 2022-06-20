#include<iostream> 
using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");     

	cout << "Ключевое слово break" << NEW_LINE;


	//ключевое слово break надо для того чтобы прерывать работу цикла (любого)

	cout << "Цикл начался!" << NEW_LINE;

	for (i = 0; i < 10; i++)
	{
		cout << "Переменная i равна " << i << NEW_LINE;
		if (i == 5)
		{
			break;
		}
	}

	cout << "Конец цикла" << NEW_LINE;

	i = 0;
	while (true)
	{
		i++;
		cout << "Переменная i равна " << i << NEW_LINE;

		if (i == 5)
		{
			break;
		}
	}
}
