#include<iostream> 
using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");  
	
	cout << "инкременты и декременты" << NEW_LINE;
	//инкремент и декремент
	a = 1;

	a++; //это тот самый инкремент
	cout << a << NEW_LINE;

	a--; //а это тот самый декремент
	cout << a << NEW_LINE;

	//однако эти штуки имеют два способа префиксный и постфиксный
	// а++ ЭТО ПОСТФИКСНЫЙ
	//++а ЭТО ПРЕФИКСНЫЙ
	cout << "Будет 1" << NEW_LINE;
	a = 1;
	cout << a << NEW_LINE;
	cout << a++ << NEW_LINE;
	//тут ты получишь 1 ~~~ ПоЧеМу?
	//потому что у инкремента и декремента приоритет задач ниже чем у всего остального
	cout << "будет 2" << NEW_LINE;
	a = 1;
	cout << a << NEW_LINE;
	cout << ++a << NEW_LINE;

	cout << "цыганские фокусы" << NEW_LINE;
	a = 1;
	int b = ++a * a++;
	cout << b << NEW_LINE; //4
	cout << a << NEW_LINE; //3
}
