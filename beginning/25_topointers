#include<iostream> 
using namespace std;

void Swap(int* pa, int* pb)
{
	int temp = *pa;
	*pa = *pb;
	*pb = temp;


}
void ukazka(int* pa)
{
	(*pa)++;

}

void main()
{
	setlocale(LC_ALL, "Rus");     

	cout << "передача аргументов по указателю" << NEW_LINE;
	a = 0;
	cout << a << NEW_LINE;
	ukazka(&a); //вот используемая функция
	cout << a << NEW_LINE; //магия указателей позволяет нам разрушить правила фигурныъ скобок!

	b = 0;
	int c = 0;
	int v = 0;

	ukazka2(&b, &c, &v);

	cout << b << TAB << c << TAB << v << NEW_LINE; //вообще все то что ты сейчас узнал нужно КАЖДОМУ программисту, так что да

	int first;
	int second;
	cin >> first;
	cin >> second;


	Swap(&first, &second);

	cout << first << TAB << second << NEW_LINE;
}
