#include<iostream>
#include<string>
#include<ctime>
#include<math.h>



#define PI 3.14 
#define MATH_TIMES(x, y) ((x)*(y))


using namespace std;

void main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");     

	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	cout << "параметры ф-ии main argc и argv" << endl;
	//это той самой main в которой мы щас пишем
	//argc - кол-во аргументов, а argv - значения самих аргументов, это массив со строками
	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
	}
	//офигеешь но наша прога выведет путь к нашему exe файлу, от нашей проги, внимание вопрос, ПОЧЕМУ???
	//а потому что такие параметры argc и argv никогда не будут меньше 1, даже если мы ничего нового не передадим в параметры, как видим первый 
	//элемент это путь до нашего exe файла! можешь посмотреть в отладке
	//как нам передеать что-то новое в наш файл? через командную строку Windows
	//для этого надо запустить наш файл не через VS карты памяти или TotalCommander а через командную строку
	//короч таким образом можно менять логику проги, правда зачем оно тебе пока не знаю
}