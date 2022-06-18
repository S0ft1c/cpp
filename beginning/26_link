#include<iostream> 
using namespace std;

void ssilki(int& a)
{
	a = 2;
}
void ssilki2(int& a, int& b, int& c)
{
	a = 10;
	b = b * 2;
	c = c - 100;
}

void main()
{
	setlocale(LC_ALL, "Rus");     

	cout << "Ссылки" << NEW_LINE;

	//в некотором они схожи, но есть различия, хотя ссылка - это переменная которая хранит в себе адрес с данными

	int exper = 5;
	int* pexper = &exper;

	int& experRef = exper;
	cout << pexper << NEW_LINE;
	cout << experRef << NEW_LINE; //через ссылку мы работаем с данными напрямую, однако все то что использовалось в указателях может use в ссылках
	//ФАКТ ссылка не может не иметь значения в отличие от указателя	, ОДНАКО это свойство не относится к ссылке как параметр функции 

	//ссылка не может иметь значения 0, NULL, nullptr

	cout << "Передача параметров в функцию с помощью ссылки" << NEW_LINE;
	int value = 5;

	ssilki(value);//это функцияя на основе которой все происходит
	cout << "value = " << value << endl; //короч работает так же как и указатели, просто без адреса и операции разыменования

	cout << "возврат нескольки значений функции через ссылки" << NEW_LINE;

	int val = 5;
	int val2 = 4;
	int val3 = 78;

	ssilki2(val, val2, val3);

	cout << "первое значение " << val << endl;
	cout << "второе значение " << val2 << endl;
	cout << "третье значение " << val3 << endl;
}
