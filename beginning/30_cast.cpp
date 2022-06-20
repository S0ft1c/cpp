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

	cout << "преобразование типов или приведение типов" << endl;

	//тут мы будем говорить в стиле языка C, именнно так, без плюсов
	//
	double a = 33.3;
	cout << (int)a << endl; //вот эти самые инты в скобочках и есть синтаксис привеедния типов || так как мы привели double к int дробная часть всё

	cout << (bool)a << endl;// приведение к bool (True False), тут все работает просто: если приводимое число равно 0, то выведется False0, если
	//число больше или меньше 0, выведтся True1

	cout << (char)a << endl;//даже так можно, но если разглядывать процесс детально то в данном случае сначала привется к int а потом к char
	//почему вывелся !, узнаешь потом >> смотри таблицу ASCII

	//один из возможных типов такого преобразования является преобразование по типу, точнее по способу осуществления: явное или неявное

	cout << (int)a << endl;//вот делая такую вещь, мы ЯВНО указываем что нам надо преобразование

	//неявное преобразование, это когда мы напрямую не пишем такую штуку, но компилятор это сделал за нас
	//пример: 
	int b = 3.5;
	cout << b << endl;//магия, компилятор сам изменил его! только надо быть очень осторожным, вдруг данные потеряешь
	//то есть присвоить дробное целочисленному мы не можем и компилятор поправляет этот косяк за вас
	b = a; //данная операция сужающая так как тип double может вместить больше, но из-за int он меняяется в меньшую сторону, но может быть наоборот
	//также такое действие можно назвать потерей памяти
	int c = 0;
	double d = c;//это  расширяющеее действие

	//компилятор всегда пытается сохранить данные, он явно не хочет их терять!

	//ASII смотри в отдельном файле
}