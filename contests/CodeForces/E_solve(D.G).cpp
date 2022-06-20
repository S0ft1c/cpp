﻿/*
Петя учится в школе и очень любит математику. Уже несколько занятий они с классом проходят арифметические выражения. На последнем уроке учительница написала на доске три положительных целых числа a, b, c. Задание заключалось в том, чтобы расставить между этими числами знаки операций '+' и '*', а также, возможно, скобки. Значение получившегося выражения должно быть как можно больше. Рассмотрим пример: пусть учительница выписала на доску числа 1, 2 и 3. Вот некоторые варианты расстановки знаков и скобок:

1+2*3=7
1*(2+3)=5
1*2*3=6
(1+2)*3=9
Обратите внимание на то, что знаки операций можно вставлять только между a и b, а также между b и c, то есть нельзя менять числа местами. Так, в приведенном примере нельзя получить выражение (1+3)*2.

Легко убедиться, что максимальное значение, которое можно получить, — это 9.

Ваша задача — по заданным a, b и c вывести, какое максимальное значение выражения можно получить.

Входные данные
Во входных данных записаны три целых числа a, b и c, каждое в отдельной строке (1 ≤ a, b, c ≤ 10).

Выходные данные
Выведите максимальное значение выражения, которое можно получить.
*/


#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
	int max = 0, a, m, s, l;
	cin >> m;
	cin >> s;
	cin >> l;

	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 0:
			a = (m + s) * l;
			break;
		case 1:
			a = m * (s + l);
			break;
		case 2:
			a = m * s * l;
			break;
		case 3:
			a = m + s + l;
			break;
		}
		if (a > max)max = a;
	}
	cout << max;
}