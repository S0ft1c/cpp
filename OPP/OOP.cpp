#include<iostream>
#include<string>
#include <fstream>
#include <Windows.h>
#include <memory>
#include <vector>

using namespace std;

//мне было очень в падлу все сортировать и делать крксиво так что вот

template<typename T>
class List
{
public:
	List();
	~List();

	//теперь к ф-у, надо доабвить список в конец, ну напишем
	void push_back(T data);

	//нам надо бы знать размер нашего листа, а он тут приватный, геттер
	int GetSize() { return size; }

	//надо бы индексы сделать, а это значит, что время для скобочек, возвращаем ссылку, чтобы пото была возможность эти данные еще и изменять!
	T& operator[](const int index);

	//надо это все как-то очищать, а для этого надо научится удалять первый элемент
	void pop_front();

	//хм, данные стали бесполезны, надо бы их очистить. А поможет нам pop_front!
	void clear();

	//мы умеем добавлять назад, почему бы и не вперед)
	void push_front(T data);

	//а что если нам надо вставить элементы не в начало и не в конец а куда-то в середину? Можно)
	void insert(T data, int index);

	//как насчет удаления любого элемента?
	void removeAt(int index);

	//удалим наконец последний элемент
	void pop_back();
private:
	//так как элемент у нас это КЛАСС, а он у нас напрмую недоступен, он, естественно, тут
	//также, сделаем его шаблонным (логично)
	template<typename T>
	class Node
	{
		//так как наш узел находится в приватке, то можно с инкапсуляцией не парится)
	public: 
		//итак adress у нас должен содержать именно адрес в памяти следующего Nodа, то есть указатель на тип Node  (след элемент)
		Node* pNext;
		T data;
		Node(T data = T(), Node *pNext = nullptr) //дефолт нужен для того, чтобы последний элемент не имел adress, ну и для подстраховки нашей ass
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	//в массивах есть удобные индексы, сделаем такие же!)
	int size;

	//а как найти элементы? нужен первый элемент не так ли? ну го, ааааа как? У нас только один выход - делать жестскую привязку, а оно нам надо? Нет, так что весь наш List - T
	//и голова у нас это указатель, так как надо нам в динамике вссе выделять!!!
	Node<T>*head;
};

template<typename T>
List<T>::List()
{
	//мы создаем список, то есть size = 0, а элементов нет, то есть head = nullptr
	size = 0;
	head = nullptr;
}

template<typename T>
List<T>::~List()
{
	//мы значит тут понасоздавали кучу new, а удалять кто будет? А вот тут будем, причем используя clear)
	clear();
}

template<typename T>
void List<T>::push_back(T data) //добавим данные)
{
	//для начала, а есть ли у нас голова?
	if (head == nullptr) //ну если нет, то делаем)
	{
		head = new Node<T>(data);
	}
	else //мы не безголовые - класс!
	{
		//тут нам потребуется временная переменнная
		Node<T>* current = this->head;
		while (current->pNext != nullptr) //ищем до тех пор пока не найдем Node где adress != nullptr, находим и модно создавать новый Node
		{
			current = current->pNext; //ну и присваиваем adress currentу пока не найдем то, где его нет!)
		}
		current->pNext = new Node<T>(data); //мы создаем новый элемент с нашими данными 
	}
	//самое главное
	size++;
}

template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0; //счетчик
	Node<T>* current = this->head; //опять временный объект	
	while (current != nullptr) //ищем пока наш current не станет nullptr, то есть не станет последним!
	{
		if (counter == index)
		{
			return current->data; //если нашли, то вот
		}
		//если не нашли
		current = current->pNext;
		counter++;
	}

}

template<typename T>
void List<T>::pop_front()
{
	Node<T> *temp = head; //нам надо временный объект, что хранит head, для сохранения так сказать
	head = head->pNext; //делаем второй элемент главным
	//ну теперь, мы сохранили бывший head, поставили новый head, можно с бывшим кончать
	delete temp; //удаляем temp, ведь именно он является указательем на head, то есть удаляем и head

	//самое важное
	size--;
}

template<typename T>
void List<T>::clear()
{
	//тут прикол один, используем конечно же while
	while (size) //не забываем, что для while любое интовое значение не равное 0 считается как True, соответственно пока кол-во элементов у нас не 0, мы будем это делать
	{
		pop_front(); //как быстро, да?
	}
}

template<typename T>
void List<T>::push_front(T data)
{
	//для исполнения в действие нам надо сделать ноду, сказать что теперь она head (а прошлый нет автоматиччески), и адрес бывшего headа добавить
	head = new Node<T>(data, head); //вот так просто: дата добавляет данные, а adress становится адресом бывшего headа, даже если его не было, ему максимально пох
	//самое главное
	size++;
}

template<typename T>
void List<T>::insert(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		Node<T>* previous = this->head; //создаем временую переменную
		for (int i = 0; i < index - 1; ++i) //ищем предшествующий элемент
		{
			previous = previous->pNext;
		}
		
		Node<T>* newNode = new Node<T>(data, previous->pNext); //создаем тот самый новый элемент, при этом в adress передаем adress предыдущего (то есть адрес правого
		//элемента) таким образом, newNode теперь знает, какой элемент идет после него.
		previous->pNext = newNode; //и предыдущему элементу в строку adress пишем адресс нового элемента

		//самое главное
		size++;
	}
}

template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head; //временная переменная, что будет головой
		for (int i = 0; i < index - 1; ++i)//ищем предыдущий удаляемому элемент
		{
			previous = previous->pNext;
		}

		Node<T>* toDelete = previous->pNext; //в указателе сохряняем СВОЙ ЖЕ АДРЕСС, чтобы не потерять его
		previous->pNext = toDelete->pNext; //меняем адрес предыдущего элемента на тот, что указывает на следующий элемент после ужаляемого
		delete toDelete; //удаляем сам удаляемый элемент
		size--; //самое главное
	}
}

template<typename T>
void List<T>::pop_back()
{
	removeAt(size - 1); //хе-хе
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
class SmartPointer
{
public:

	SmartPointer(T *ptr)
	{
		this->ptr = ptr;
	}

	~SmartPointer()
	{
		delete ptr;
	}

	T& operator*()
	{
		return *ptr;
	}

private:

	T* ptr;

};

template<class T>
class Printer_2
{
public:

	void Print(T value)
	{
		cout << value << endl;
	}


private:

};
//а вот его специализация
template<>
class Printer_2<string>
{
public:
	void Print(string value)
	{
		cout << "______" << value << "______" << endl;

	}
};

template<class T1>
class TypeSize
{
public:

	TypeSize(T1 value)
	{
		this->value = value;
	}

	void DataTypeSize()
	{
		cout << sizeof(value) << endl;
	}

protected:

	T1 value;

};

template<class T1> //важно, надо писать либо class либо typename в зависимости от того что написано в основном классе!
class TypeInfo : public TypeSize<T1> //привяжем не жестко скажем так, однако можно и просто жетско int или string поставить, но мы хотим универсальный, передаем обобщенный тип
{
public:
	
	TypeInfo(T1 value) : TypeSize<T1>(value) //вот так надо чтобы запустились оба нудных нам класса (не понял тебе на тему запуска наследуемых классов)
	{
		
	}

	void ShowTypeName()
	{
		cout << "Название типа: " << typeid(this->value).name() << endl; //я думаю ты быстро понял что еще за типеди и какие у него ф-ии
	}

private:

};



class magic_Point
{
public:
	magic_Point()
	{
		x = y = z = 0;
	}

	magic_Point(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	int x, y, z;

};


template<class T>
class MyClass
{
public:

	MyClass(T value)
	{
		this->value = value;
	}

	void DataTypeSize()
	{
		cout << sizeof(value) << endl;
	}

private:

	T value;
	
};



namespace FirstNS
{
	void Simple_Function()
	{
		cout << "FirstNS working" << endl;
	}
}

namespace SecondNS
{
	void Simple_Function()
	{
		cout << "SecondNS working" << endl;
	}
}

namespace ThirdNS
{
	namespace SecondNS
	{
		void Simple_Function()
		{
			cout << "SecondNS working" << endl;
		}
	}
}


class PC
{
public:
	
	enum PCState //тут мы как и класс описываем enum, нам надо состояние, называем PCState
	{
		OFF, //вот так и пишем собственно, получился enum с 3 состояниями. Совет: писать надо с запятыми (иначе просто не робит), ну и заглавнми надо писать, ведь это и есть константы
		ON,
		SLEEP //для того чтобы это все использовать создаем переменную типа PCState в PC
	};

	PCState GetState() { return State; }
	void SetState(PCState State) { this->State = State; }

private:

	//предположим что нам надо контролировать состояние работы компа
	//1 - вкл или выкл? так как всего два состояния, то можно юзать bool. А если он в спящем режиме? То тогда уже int. 0 - выкл, 1 - вкл, 2 - сон
	//а вот теперь представьте что вы другой программист которому дали этот код. Что если вы не знаете об этих магческих числах? Да даже если не про них говорить, все равно,
	//будет много писанины (куча if). Нам оно не надо. И как уже можно догадаться именно enum порешает эти магические числа. См наверх
	PCState State;

};

class myException : public exception
{
	//Даже в изначальном (пустом) виде можно уже бросить этот класс, ведь по сути throw не разбирается что там внутри, главное ,что что-то есть)
public:

	myException(const char *msg, int dataState):exception(msg) //вот этим действие мы это полученное сообщение просто отправим к предку, а он за нас все сделает)
	{
		this->dataState = dataState;
	}

	int GetDataState(){ return dataState; }

private:

	int dataState;

};

void Function_my(int value)
{
	if (value < 0)
	{
		throw exception("Число меньше 0!!!");
	}
	if (value == 0)
	{
		throw myException("Число равно 0!!!", value);
	}

	cout << "Переменная - " << value << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
class Toch
{
public:
	Toch()
	{
		x = y = z = 0;
	}

	Toch(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;

	}

	
	int x;
	int y;
	int z;
};

ostream& operator<<(ostream& os, const Toch& toch)
{
	os << toch.x << " " << toch.y << " " << toch.z;

	return os;
}

istream& operator>>(istream& is, Toch& toch)
{
	is >> toch.x >> toch.y >> toch.z;

	return is;
}

/// //////////////////////////////
class Character
{
public:
	Character()
	{
		cout << "Конструктор Character" << endl;

	}
	int HP;
};

class Orc : public virtual Character
{
public:
	Orc()
	{
		cout << "Контруктор Orc" << endl;
	}
};

class Warrior : public virtual Character
{
public:
	Warrior()
	{
		cout << "Конструктор Warrior" << endl;

	}
};

class OrcWarrior : public Orc, public Warrior
{
public:
	OrcWarrior()
	{
		cout << "Конструктор OrcWarrior" << endl;
	}
};

/// ///////////////////////
class Component
{
public:
	Component(string companyName)
	{
		cout << "конструктор Detail" << endl;
		this->companyName = companyName;
	}
	string companyName;
};

class GPU : public Component
{
public:
	GPU(string companyName) : Component(companyName)
	{
		cout << "конструктор GPU" << endl;

	}
};

class Memory : public Component
{
public:
	Memory(string companyName) : Component(companyName)
	{
		cout << "Конструктор Memory" << endl;
	}
};

class GraticCard : public GPU, public Memory
{
public:
	GraticCard(string GPUcompanyName, string MemorycompanyName) : GPU(GPUcompanyName), Memory(MemorycompanyName)
	{
		cout << "Конструктор Gratрic card" << endl;
	}
};

/// ///////////////////////

class I_bicycle
{
public:
	void virtual TwistTheWheel() = 0;
	
	void virtual KeepTheBalance() = 0;
	
	void virtual Pedal() = 0;
	
};

class Cyclist
{
public:
	void RideOn(I_bicycle& bicycle)
	{
		cout << "Крутим руль" << endl;
		bicycle.TwistTheWheel();
		cout << "Держим равновесие" << endl;
		bicycle.KeepTheBalance();
		cout << "Поехали!" << endl;
		bicycle.Pedal();
	}
};

class SimpleBicycle : public I_bicycle
{
public:
	void TwistTheWheel() override
	{
		cout << "Вызван навык кручения рулем	// Simple Bicycle" << endl;
	}
	void KeepTheBalance() override
	{
		cout << "Вызван навык поддерживания равновесия	// Simple Bicycle" << endl;

	}
	void Pedal() override
	{
		cout << "Вызван навык кручени педалей	// Simple Bicycle" << endl;
	}
};

class Car
{
public:
	Car()
	{
		cout << "Вызов конструктора класса Машина" << endl;
	}

	~Car()
	{
		cout << "Выов деструктора класса Машина" << endl;
	}

	string str = "Поле класса машина";
	void Drive()
	{
		cout << "Я еду!!!!!" << endl;
	}

	void use()
	{
		cout << "Машина поехала" << endl;
	}
};

class Plane
{
public:
	
	Plane()
	{
		cout << "Вызов конструктора класса Самолет" << endl;
	}

	~Plane()
	{
		cout << "Вызов деструктора класса Самолет" << endl;
	}

	string str2 = "Поле класса самолет";
	void Fly()
	{
		cout << "А я лечу!!!" << endl;
	}
	
	void use()
	{
		cout << "Самолет взлетает" << endl;
	}
};

class FlyingCar : public Car, public Plane
{
public:

	FlyingCar()
	{
		cout << "Вызов конструктора класса Летающая Машина" << endl;
	}
	~FlyingCar()
	{
		cout << "Вызов конструкторов класса Летающая Машина" << endl;
	}
};

class Sms
{
public:
	Sms(string sms)
	{
		this->sms = sms;
	}

	virtual string Getsms()
	{
		return sms;
	}
	
private:
	string sms;
};

class SuperSms : public Sms
{
public:
	SuperSms(string sms):Sms(sms)
	{

	}
	string Getsms() override
	{
		return "[" + ::Sms::Getsms() + "]";
	}
};

class Printer
{
public:
	void Print(Sms* SMS)
	{
		cout << SMS->Getsms() << endl;
	}
};



class human_two
{
private:

public:

	void Print()
	{
		cout << name << "\tвозраст - " << age << "\tвес - " << weight << endl;
	}

	//можно так
	/*
	human_two(string name, int age, int weight)
	{
		this->name = name;
		this->age = age;
		this->weight = weight;
	}

	human_two(string name, int age)
	{
		this->name = name;
		this->age = age;
		this->weight = 0;
	}

	human_two(string name)
	{
		this->name = name;
		this->age = 0;
		this->weight = 0;
	}
	*/

	//а можно так
	
	human_two(string name)
	{
		this->name = name;
		this->age = 0;
		this->weight = 0;
	}

	human_two(string name, int age) : human_two(name)
	{
		this->age = age;	
	}

	human_two(string name, int age, int weight) :human_two(name, age)
	{
		
		this->weight = weight;
	}

	//дубляжа нет, да и код все за тебя сделает)

	string name;
	int age;
	int weight;

};

/// оружия //////////////////////////////////////////////////


class Weapon
{
	//вот эта ф-я чисто виртуальна

public:

	virtual void Shoot() = 0;

	void Foo()
	{
		cout << "Негры пашут" << endl;
	}
};

class Gun :public Weapon
{
public:
	 void Shoot() override
	{
		cout << "BANG!!!" << endl;
	}
};

class SubMachinGun : public Gun
{
public:
	//а теперь про override
	//оно необязательно, в принципе можно и без него, просто одна ф-я виртуальная в одном классе, а потом в след. классе пишем эту же ф-ю но изменяем ф-ал
	//это уже будет работать, но для того чтобы точно контролировать сигнатуру метода, и не получить беду на свою и так уже поломанную бошку
	// напиши это слово, 3 сек. а поломок уже будет меньше

	void Shoot() override
	{
		cout << "BANG!!! BANG!!! BANG!!!" << endl;
	}

	//дело вот в чем, если слова не будет, а ты где нибудь накосячил, то при вызове ф-ии может вызваться ф-я БАЗОВОГО класса, что конечно же провал
	//используй слово override, оно важно!!!
};

class Knife : public Weapon
{
public:
	void Shoot() override
	{
		cout << "VJUH!!!" << endl;
	}
};

class Player
{
public:
	void Shoot(Weapon *gun)
	{
		gun->Shoot();
	}
};
/// ////////////////////////////////////////////////////////////

/// виртуальный деструктор
class first
{
public:
	first()
	{
		cout << "выделена динамическая память // класс first" << endl;
	}

	 virtual ~first()
	{
		cout << "динамическая память удалена // класс first" << endl;
	}
};

class second : public first
{
public:
	second()
	{
		cout << "выделена динамическая память // класс second" << endl;
	}

	~second() override
	{
		cout << "динамическая память удалена // класс second" << endl;
	}
};

//чисто виртуальный деструктор

class clear_one
{
public:
	clear_one()
	{
		
	}

	virtual ~clear_one() = 0;
	
};

//внимание сюда

clear_one:: ~clear_one() {};

class clear_two : public clear_one
{
public:
	clear_two()
	{
		
	}

	~clear_two() override
	{

	}
};
// /// //// //////////////////////////////////////////////////////


class A
{
public:
	string msgOne = "Сообщение I";

	

private:
	string msgTwo = "Сообщение II";

protected:
	string msgThree = "Сообщение III";

};
class B : public A
{
public:

	void PrintMsg()
	{
		cout << msgOne << endl;
	}
	void printMSG()
	{
		cout << msgThree << endl;
	}

};

class AA
{
public:
	AA()
	{
		cout << "Вызов конструктора A" << endl;
	}
	
	~AA()
	{
		cout << "ДЕСТРУКТОР А" << endl;

	}
};

class BB : public AA
{
public:
	BB()
	{
		cout << "Вызвался конструктор B" << endl;

	}

	~BB()
	{
		cout << "ДЕСТРУКТОР Б" << endl;
	}
};

class CC : public BB
{
public:
	CC()
	{
		cout << "Вызвался конструктор C" << endl;

	}
	~CC()
	{
		cout << "ДЕСТРУКТОР С" << endl;
	}
};

class Humann
{
public:
	string name;

};

class Student : public Humann
{
public:
	string group;

	void learn()
	{
		cout << "Я пришел на пару" << endl;
	}
};

class ExStudent : public Student
{
public:
	void learn()
	{
		cout << "Надо бы прийти на пары" << endl;
	}
};

class Cap
{
	//кепку мы можем надеть не только на человека. То есть кепка не привязана так жестко к человеку, следовательно может действовать и без него
public:
	string GetColor()
	{
		return color;
	}


private:
	string color = "red";
};

class Man
{
public:
	
	void Think()
	{
		brain.Think(); // тут мы можем наблюдать делигирование, один из паттернов проектирования
	}

	void InspectCap()
	{
		cout << "Моя кепка " + cap.GetColor()  << " цвета." << endl;
	}

private:
	//рассмотрим композицию

	class Brain
	{
	public:
		//заметьте что мозг, существует только при существоввании человека
		void Think()
		{
			cout << "Я думаю!!!" << endl;
		}
	};

	Brain brain;

	//и вот прикол, кепка может испоьзоваться с разными предметами не только с человеком
	Cap cap;
};

class Image 
{
public:

	void GetImageInfo()
	{
		for (int i = 0; i < LENG; i++)
		{
			cout << pixels[i].GetInfo();
			cout << endl;
		}
	}

private:

	class Pixel
	{
	public:

		Pixel(int r, int g, int b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
		}

		string GetInfo()
		{
			return "Pixel: r = " + to_string(r) + "\t" + "g = " + to_string(g) + "\t" + "b = " + to_string(b) + "\t";
		}

	private:

		int r;
		int b;
		int g;

	};

	static const int LENG = 5;

	Pixel pixels[5]
	{
		Pixel(0, 4, 64),
		Pixel(4, 14, 10),
		Pixel(111, 4, 24),
		Pixel(244, 244, 14),
		Pixel(111, 179, 64)
	};

};

class Pixels
{
public:

	Pixels()
	{
		r = g = b = 0;
	}

	Pixels(int r, int g, int b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	string GetInfo()
	{
		return "Pixel: r = " + to_string(r) + "\t" + "g = " + to_string(g) + "\t" + "b = " + to_string(b) + "\t";
	}

private:

	int r;
	int b;
	int g;

};

//эту вещь создает визуалка за тебя, просто наведи курсор на class во время ввода а потом нажми Tab
class Vinosim
{
public:
	Vinosim();
	~Vinosim();

	void Print_message();
	
private:

};


//это и есть вынос, в теории это прототип ф-ии
//работает оно также само, дажде если бы мы взяли и открыли фиг. скобки прямо внутри класса
//можно просто написать что у нас конструктор есть, а потом описать его внизу то все
// но рассмотрим мы на примере метода

Vinosim::Vinosim()
{
}

Vinosim::~Vinosim()
{
}

void Vinosim::Print_message()
{

	cout << "Добро пожаловать в WarZone." << endl;
	
}

//тестовый класс, который нужен для перегрузки оператора индексирования []
class TestClass
{
public:
	TestClass() {}

	int & operator [] (int index)
	{
		return arr[index];
	}
private:
	int arr[5]{ 5,44,78,98,72 };
};

class Copy //пробный класс для проверки копирования
{
	//его ф-я проста - просто выводить адрес создаваемого элемента и выдавать адрес элемента который все)
public:

	int data;

	Copy(int value)
	{
		data = value;
		cout << "Объект " << this <<"\t" << "Вызвали класс-пробник" << endl;

	}

	~Copy()
	{
		cout << "Объект " << this << "\t" << "Вызвался деструктор класса-пробника" << endl;
	}

};

//самый навороченный класс
class Copy_new //пробный класс для проверки копирования
{
	int Size;//переменная нужная для копирования
public:

	int *data;

	Copy_new(int size)
	{
		this->Size = size;
		this->data = new int[size];

		for (int i = 0; i < size; i++)
		{
			data[i] = i;
		}

		cout << "Объект " << this << "\t" << "Вызвали класс-пробник" << endl;

	}
	//да синтаксис одинаковый, меняется параметр
	Copy_new(const Copy_new &other)//то есть константный элемент который копируем, и other который мы передаем по ссылке
	{
		//this->data = other.data; это стандартный конструктор копирования, по виду понятно что работать не будет
		
		this->Size = other.Size;

		this->data = new int [other.Size];

		for(int i = 0;i<other.Size; i++)
		{
			this->data[i] = other.data[i];
		}

		cout << "Объект " << this << "\t" << "Вызвали конструктор копирования класса-пробник" << endl;

	}

	//а какие параметры будем принимать??? а такие же как при копировании
	Copy_new & operator = (const Copy_new& other)
	{
		cout << "Вызвали оператор присваивания = " << this << endl;
		
		this->Size = other.Size;
		
		if (this->data != nullptr)
		{
			delete[] data;
		}

		this->Size = other.Size;

		this->data = new int[other.Size];

		for (int i = 0; i < other.Size; i++)
		{
			this->data[i] = other.data[i];
		}

		return *this;
	}

	~Copy_new()
	{
		cout << "Объект " << this << "\t" << "Вызвался деструктор класса-пробника" << endl;
		delete[] data;
	}

};//

Copy Copy_exp_2()
{
	cout << "Вызвалась ф-ия Foo2" << endl;

	Copy temp(2);

	return temp;
}

class Destruction
{
	
public:

	int data;

	Destruction(int value)
	{
		data = value;
		cout << "Объект "<< data << " Вызвали класс-пробник" << endl;

	}

	~Destruction()//вот он, деструктор, пишется через волну
	{
		cout << "Объект "<< data << "Вызвался деструктор класса-пробника" << endl;
	}

};

void Copy_exp(Copy value)
{
	cout << "Вызвалась ф-ия Foo" << endl;
}

class Point //вот таш класс, пока он без модификаторов
{
private:
	int x;
	int y;
public:

	Point(int valueX, int valueY)//тут как будто в ф-ии мы пишем параметры, они должны совпадать поо типу данных
	{	//вот он конструктор, вручную вызвать его нельзя, он сам это сделает в тот момент когда вы создаете объект класса
		x = valueX;
		y = valueY;
		cout << this << " constructor" << endl;//улыбаемся и машем, см. ключевое слово this

	}

	Point()//конструктор по умолчанию, чтобы ничего не сломалось, однако с одной доработакой, это дефолт значения
	{
		x = 0;
		y = 0;
	}

	bool operator ==(const Point & other)
	{
		return this->x == other.x && this->y == other.y;
	}

	bool operator !=(const Point& other)
	{
		return !(this->x == other.x && this->y == other.y);
	}

	Point operator +(const Point& other)
	{
		Point temp;
		temp.x = this->x + other.x;
		temp.y = this->y + other.y;
		return temp;
	}



	int GetX()
	{
		return x;
	}
	void SetX(int valueX)
	{
		x = valueX;
	}
	int GetY()
	{
		return y;
	}
	void SetY(int valueY)
	{
		y = valueY;
	}
	void Print()
	{
		cout << "X = " << x << "\t\tY = " << y << endl;
	}

	Point &operator ++()
	{
		this->x++;//иронично
		this->y++;

		return *this;
	}

	Point operator ++(int value)
	{
		Point temp(*this);

		this->x++;
		this->y++;

		return temp;
	}

	friend void Change_X(Point& value);
	//хоб и теперь друг, кстати по сути это прототип ф-ии

};

//друж. ф-я по тоношению к Point 
// на горьком опыте осознал, друж. ф-я пишется СТРОГО ПОСЛЕ класса, иначе жалуется
void Change_X(Point& value)
{
	value.x = -1;
}

class Human 
{
public://это модификатор доступа

	int age; //дали возраст
	int weight;

	string name;//дали имя

	void Print()//пишем ф-ию вывода для нашего класса
	{
		cout << "Имя " << name << "\n" << "Вес " << weight << "\n" << "Возраст " << age << endl;

	}

};

//тупо точка
class Tochka
{
private:

	int y;
	int x;

public:
	Tochka()
	{
		x = 0;
		y = 0;
		cout << this << " constructor" << endl;

	}


};

//друж. методы по отношению к классам

class Apple;

class Cat
{
public:
	void Take_Apple(Apple& apple);
	void Eat_Apple(Apple& apple);
};

class Apple
{
	friend Cat;
	//лучше просто так не дружить так сказать, потому что возможна потеря инкапсуляции

public:
	
	static int GetCount()
	{
		return Count;
	}

	Apple(int weight, string color) 
	{
		this->weight = weight;
		this->color = color;
		
		Count++;
		id = Count;
	};
	~Apple() {};

	void GetId()
	{
		cout << "ID = " << id << endl;
	}
	
private:
	int weight;
	string color;
	int id;
	//пока не думать что это такое
	static int Count;

	//friend void Cat::Take_Apple(Apple& apple);
	//все что надо это указать у какого класса дружба то
};


	
int Apple::Count = 0;

class ID
{
public:
	static int ID_editor;
	ID ()
	{
		++ID_editor;
		id = ID_editor;
	}

	int GetId()
	{
		return id;
	}
private:
	int id;

};

int ID::ID_editor = 0;


void Function_1(int value)
{
	//предположим мы хотим, чтобы выводимое число всегда!!! было больше 0
	if (value<0)
	{
		throw value;
	}

	

	cout << "Переменная - " << value << endl;
}

void Function_2(int value)
{
	if (value < 0)
	{
		throw exception("Число меньше нуля!");
	}

	cout << "Переменная - " << value << endl;
}

void Function_3(int value)
{
	if (value < 0)
	{
		throw "Число меньше 0!!!";
	}

	if (value == 0)
	{
		throw exception("Число должно быть СТРОГО больше 0");
	}

	cout << "Переменная - " << value << endl;
}

int main(int argc, char* argv) 
{
	setlocale(LC_ALL, "ru");
	cout << "Вот мы и приступили к ООП, объектно ориентированному программированию" << endl<<endl;
	//для начала разберем 3 главные термина ООП: инкапсуляция, наследование, полиморфизм

	//инкапсуляуия - принцип независимости определенных данных в программировании. То есть какой нибудь програаммист создающий класс объекта
	//может скрыть определенную инф-ию о нем от другого пользователя, без которой он существовать не будет.
	//А вместо этого сделать какой-то внешний инструмент, чтобы пользователь через него работал с объектом.

	//наследование - процесс при котором один объект может наследовать св-ва и особенности какого-то объекта и дополнять их своими
	//тут все просто

	//полиморфизм - возможность объектов вести себя по-разному, в зависимости от ситуации, и каким-то особенным способом на определенное действие
	//которое свойственно только это объекту(классу)

	cout << "что такое класс, что такое объект класса" << endl;
	//класс наверху, нахывается Human
	
	Human de_first;		//видал. теперь de_first объект класса Human
	//то есть по сути, класс это шаблон, а когда мы создаем экземпляр такого класса, мы получаем объект||однако пока с нашим Human мы ничего 
	//не сделаем, так как у класса нету тела, а для того чтобы наполнить тело нашего класса мы можем использовать примитивные типы, но не только их
	//а еще и другие класса в качетсве типов! Запутанно зато клево
	//теперь int age; это часть тела класса, такие части называют полями класса||теперь наш человек не пустышка, и с ним можно работать
	de_first.age = 54;
	de_first.name = "Комаров Иван Иванович";
	de_first.weight = 64;

	cout << de_first.age << endl;
	cout << de_first.name << endl;
	cout << de_first.weight << endl<<endl;

	setlocale(LC_ALL, "ru");
	cout << "Метод класса, ф-я класса" << endl;
	//для справки метод класса и ф-ия по сути тоже самое, абсолютно
	//помните как мы вписывали данные в класс а потом ручками их выводили? так вот сейчас мы напишем ф-ию которая по сути все это сделает за нас
	//для этого надо будет поместить прямо в тело класса

	de_first.Print();//вот так происходит вызов
	//ФАКТ всегда ф-ия будет брять значение именно того объекта который вызвали, чужого она не возьмет

	cout << endl;
	cout << "Модификаторы доступа в ООП" << endl;
	//итак модификаторы доступа о которых мы сейчас поговорим также используются в наследовании, то каким образом, пока не важно
	//так как же модификаторы доступа влияют на класса

	//модификаторы бывают: public, private, protected||эксперимент проводится над классам Point

	//nothing, когда ничего нет, то есть модификатор отстутствует, соответственно нет и возможности хоть что-то делать с классом, он просто есть	
	Point a;//это происходит потому что по умолчанию стоит private||соответственно данные будут открыты только к друж. ф-ям и классам
	//пока не задавай вопросов про скобочки, внизу есть ответ
	//public, все свободно, все легко, доступно всем

	//protected, этф вещь пока на данном этапе не то что ты должен знать, забудь пока про ее существование!
	cout << endl;
	cout << "Геттеры и сеттеры для класса, инкапсуляция" << endl;
	//в ООП принято писать код чтобы данные были отделены от ф-ий
	//например, у Point есть две переменные, и вообще не принято оставлять все это в public, ведь это считай критические данные данного класса!
	//сключения бывают но обычно такие классы маленькие и включены в другие классы
	//дял этого приняято чтобы с полем с которым вы будете взаимодействовать, был геттер и сеттер||это обыкновенные методы класса

	int valueX; //создаем значение дял икса
	cout << "Введите занчение для X" << endl;
	cin >> valueX;
	a.SetX(valueX);//тут мы выполняем ф-ию, чтобы ввести данные в икс
	int result_point_class_x = a.GetX();

	int valueY;
	cout << "Введите занчение для Y" << endl;
	cin >> valueY;
	a.SetY(valueY);
	int result_point_class_y = a.GetY();
	a.Print();//выводим данные

	cout << endl;
	cout << "Конструктор класса" << endl;
	//конструктор класса - это такая сущность которая в основном предназначена для инициализации класса, в какое-либо значение нажное вам
	//что это значит: вот у нас есть класс Point и тут для того чтобы вводить данные в нужное нам значение, надо пользоваться сеттером, что плодит 
	//трудности (а что если переменных не 2 а 1000?). Чтобы такого не было и сущетсвует конструктор класса. Нпример мы не будет заполнять все поля, а
	//выведутся все, даже те что с мусором! Нам это не надо.

	//По сути конструктор класса это ф-я которая НЕ имеет типа возвращаемого значения!

	//увидишь его в классе Point

	//итак конструктор есть всегда, если вы не прописали конструктор, копилятор скрыто от вас сам поставит свой конструктор - конструктор по умолчанию
	/*
		Point ()
		{

		}
	*/
	//это вид конструктора по умолчанию, пусто
	//создав свой конструктор, конструк тор по умолчанию заканчивается. Теперь при создании объекта надо указать первоначальные значения
	//и да там есть перегрузки, потом узнаешь почему там они есть
	Point b(0, 0);
	b.Print();//магия работает, вот такая штука, причем полезная ведь в конструктор можно записать много чего полезного
	//не понял? пройдись отладкой
	//КОНСТРУКТОР КЛАССА ДОЛЖЕН НАХОДИТСЯ В ПАБЛИК СЕКЦИИ, в приватке он не даст ничего создать, пока что

	cout << endl;
	cout << "Перегрузка конструкторов класса" << endl;
	//она очень сильно похожа на перегрузку ф-ий
	//например можно создать несколько конструкторов, и менять поведение и работу класса (немного полиформизма)

	Point defalt_constructor;//один с конструктором по умолчанию (если не понял почему нули, посмори наверх)
	defalt_constructor.Print();
	Point constructor_mod_1(1, 89);//один с модифицированным конструктором
	constructor_mod_1.Print();

	//кол-во созданий таких конструкторов не ограничено, пока оперативка не грохнется

	cout << endl;
	cout << "Деструктор класса" << endl;
	//деструктор - противоположность коснтруктору, он срабатывает при разрушении объекта, также как конструктор, мы не можем вызвать ее вручную
	//но при этом когда объект класса разрушается, он срабатывает и что-то делает
	//обычно разрушение объекта происходит когда он уходит из зоны видимости

	//см. класс Destruction, он наверху

	//если деструктора нет компилятор сам добавит пустой деструктор
	//в отличии от конструкторов, деструктор всегда один, их нельзя сделать много
	//также у деструктора нет параметров, он не может их хранить || согласен странно, поле для них есть а сами параметры он принимать не может

	Destruction Experiment(1);
	Destruction Experimentt(2);//замет как они удаляются, в каком порядке! прикольно да

	cout << endl;
	cout << "ключевое слово this" << endl;
	//эта  вещь очень важна в ООП, кстати мы ей даже уже пользовались, просто мы это не видели, компилятор делал это неявно
	//предположим у нас два объекта: а, b. и у каждого свои методы, у каждого объекта мы можем вызвать через точку метод Print(пусть будет он)
	//но каким образом компилятор знает какой именно объект ему нужен? Ну на деел он просто знает что у объекта a и у объекта b разные адреса
	//в памяти. Когда мы обращаемся к объекту a, компилятор обращается к адресу объекта a и потом к методу Print, и вот как раз таки этот адрес и 
	//содержит слово this. по сути это указатель объекта на самого себя, т.е. это знание объекта где он находится в памяти, использовать его можно
	//только внутри класса, снаружи никак нет

	//реализацию можно увиеть наверху

	Point thiss(1,78);
	thiss.Print();

	cout << endl;
	cout << "Конструктор копирования" << endl;

	//данный конструктор позволяет скопировать обьекты (логично), но какова его важность и применение в программировании 
	//все просто - рассмотрим момент когда мы его удалим (до этого конструктор копирования делался скрытно компилятором)
	//в данный момент все очень легко и просто, реализация вот:

	Copy copy1(3);//вот и все

	Copy_exp(copy1); //а сейчас рубрика эксперименты, что произойдет когда мы введем параметром в ф-ию переменную параметра Dectruction?
	//прально, она скопируется, но как она скопируется? а вот щас и узнаем)

	//а теперь творим поллную дичь, создаем ф-ию, тип возврата данных Copy

	Copy_exp_2();//вот удивительно да, как итог у нас вызывается конструктор, потом вызывается деструктор, а потом еще один деструктор(ОТКУДА, ща)

	//а теперь просто скопируем какой-нибудь объект)

	Copy copy2(copy1);
	//но опять несколько раз вызывается деструктор, почему... ||это серьезная проблема если что

	//теперь отредачим класс Copy, будем сейчас динамически выделять память|| я создал отдельный класс, теперь это Copy_new

	Copy_new a_copy(10);
	Copy_new b_copy(a_copy);

	//тут такой хаос - из-за точнейшего копирования, скопировался и адрес, а следовательно и деструктор пытается удалить два раза  одно и то же,НО
	//НЕ УДАЛЯЕТ ВТОРУЮ ПЕРМЕННУЮ!!! Утечка памяти.

	//напишем тогда правильный конструктор копирования, чтобы не ломалось ничего-> см. вверх

	//ГОТОВО, согласен вещь сложная, но работает!

	cout << endl;
	cout << "Перегрузка оператора присваивания" << endl;
	//оператора присваивания чел!!! ЭТО ПРОСТО =

	Copy_new a_prisvoit(10);
	Copy_new b_prisvoit(2);

	//a_prisvoit = b_prisvoit;		//при данной операции, у нас получится что объект а, будетт думать что он объект б
	//через отладку, можно посмотреть и увидеть что происходит, два объекта с одинаковым адресом
	//как мы знаем это очень плохо (катастрафически плохо)

	//чтобы такого не было надо сделать перегрузку оператора присваивания
	//по сути оператор типа =, <, >, это ф-я, следовательно ее можно перегрузить! 

	//для начала определимся а какой тип данных возвращает =, на первый взгляд что ничего она не возвращает да? НЕТ
	// но пока напишем void)))

	//для перегрузки оператора надо написать слово operator

	//начало есть, а теперь сама логика оператора, как она будет выглядеть

	//логика может быть по сути почти что идентичной с конструктором копирования, но тогда мы думали что объект которому присваивали значение
	//был пустым, а теперь он не пустой, дело в том что в this уже будет выделена часть памяти, следовательно если мы просто сопируем код, то утечка!

	//а значит сначала надо удалить данные и только потом добавлять

	//мы это сделали! НО НЕ ДО КОНЦА

	a_prisvoit = b_prisvoit;

	//а что если переменных 3, и мы их инициализируем примерно так

	//заметьте, из y в t и потом из t в r

	//а что если сделаем так с нашими объектами? А НЕ ПОЛУЧИТСЯ
	//отсутствует оператор = соответствующий этим операндам 
	//а почему, мы же его перегрузили

	//на самом деле этот самый оператор присвоить, возвращает значение!
	//и он должен возвращать ссылку на текущий объект
	//т.е. Copy_new &

	//соответсвенно мы return *this; || возвращаем this при этом разыменовывая

	cout << endl;
	cout << "Перегрузка оператора равенства и неравенства" << endl;

	//это == и != || они очень похожи, реализация у них почти одинаковая

	Point sravnit_a(5, 1);
	Point sravnit_b(9, 4);

	 bool result_ravno = sravnit_a == sravnit_b;
	 cout << result_ravno << endl;//вывелось 0, и правда данные объекты не равны!

	 bool result_neravno = sravnit_a != sravnit_b;
	 cout << result_neravno << endl;//вывелось 1, и опять все нормас!

	 cout << endl;
	 cout << "Перегрузка оператора сложения" << endl;
	 //складывае точки твою мэть

	 Point sum_a(5, 1);
	 Point sum_b(77, 12);

	 Point c = sum_a + sum_b;
	 
	 cout << endl;
	 cout << "Перегрузка инкеремента и декремента" << endl;

	 Point inkrement_post(0, 0);
	 ++inkrement_post;

	 inkrement_post++;


	 cout << endl;
	 cout << "Перегрузка оператора индексирования" << endl;
	 //это []

	 TestClass index_a;

	 cout << "Вот собственно и вывели" << endl;
	 cout << index_a[1] << endl;

	 //данная шняга исопользуется в векторе в библеотеке stl, просто сказал, чтобы ты продолжил учится!

	 //кста заметь, мы передаем значения по ссылке, и именно благодаря этому, мы и можем МЕНЯТЬ значения в объекте

	 cout << index_a[0] << endl;
	 index_a[0] = 100;
	 cout << index_a[0] << endl;

	 cout << endl;
	 cout << "Дружественные ф-ии и классы" << endl;

	 //друж. ф-ей по отношению  к классу называется такая ф-ия, которая не является членом класса, имеет доступ к закрытым полям класса

	 Point friendly(4,89);
	 friendly.Print();

	 //напишем такую шнягу

	 Change_X(friendly);
	 friendly.Print();
	 
	 //еще один факт, через дружественную ф-ю нельзя получить доступ к оператору this!!!

	 //так же стоит знать что одна ф-я может быть друж. по отношению ко многим ф-ям, просто надо прописать в классе

	 cout << endl;
	 cout << "Как вынести реализацию метода из класса" << endl;

	 //для начала, на кой ска это нам надо? 

	 //пока у нас класс маленький, но что если класс сложный, и там куча методов на всю страницу, вы откроете класс а там нипойми что
	 //логично что лучше вынести такую пофигень из класса

	 //или у нас тесно взаимодействуют два класса, и внутри их один ссылается на другой и так далее
	 //но ведь в C++ если класс описать позже другого, он не будет ничего знать о другом классе (для этого и придумали прототипы)


	 //для реализации такой вещи есть два способа - первый легкий, он автоматизирован самой Визуалкой
	 //для того чтобы вынести метод из класса, мы должны оставить саму сигнатуру, а реализацию вниз, собственно как было изначально

	 Vinosim V_a;

	 V_a.Print_message();

	 cout << endl;
	 cout << "Дружественный метод класса" << endl;
	 //это когда один из методов одного класса, дружит с другим классом (ИМЕННО МЕТОД)
	 
	 Apple apple(150, "Red");
	 Cat cat;
	 cat.Take_Apple(apple); 
	 
	 cout << endl;
	 cout << "Дружественные классы " << endl;

	 cat.Eat_Apple(apple);


	 cout << endl;
	 cout << "Ключевое слово static" << endl;
	 //для начала что это примерно
	 //представим класс,  нем есть поля, и есть какае-то одна статич. переменная. Потом создаем 3 объекта класса
	 //Если мы в классе создадим какуе-то перменную и дадим ей модификатор static. Оно будет рабоать по другому.
	 //обычно у каждого элемента будет одна своя переменная (пример color у каждого яблока разный: желтый, красный и т.д.)
	 //то статичная перменная будет общей для всех объектов, т.е если у одного объекта изменить перменную static мод., то она изменится у всех
	 //даже больше, для работы с переменной нам не надо использовать экземпляр класса!
	 //для того чтобы работать с такой перменной, нам надо напрямую обратится к классу.

	 //кста скоро сделаем самый простейший генератор ID. Зачем? Да по приколу)
	 /*
	 
	 apple.Count;//можно так

	 Apple::Count;//а можно так

	 */
	 //итак для работы с такой перменной надо ее инициализировать - делается это вне класса, и даже вне ф-ий

	 Apple apple_2(100, "green");
	 /*
	 cout << apple.Count << endl;
	 cout << apple_2.Count << endl;
	 */
	 //это подтверждает что она одна у всех

	//можно еще делать вот так
	 /*
	 cout << Apple::Count << endl;
	 */
	 //а теперь как делать ID

	//полистай наверх увидишь

	 cout << "Создание ID-ников" << endl;

	 ID dog;
	 ID dog2;
	 cout << dog.GetId() << endl;
	 cout << dog2.GetId() << endl;

	 //#####################################################################################################################################

	 apple.GetId();
	 apple_2.GetId();

	 cout << endl;
	 cout << "Статические методы" << endl;
	 //данная труктура нужна для сохранения работы программы и ее инкапсулирования, мы опустили статик переменную Count в классе Apple в секцию
	 //private
	 //теперь нам надо реализовать геттер для Count так чтобы каждый раз не образаться к объекту, собственно для этого и нужен статик метод

	 //см. наверх
	
	 cout << Apple::GetCount() << endl;

	 //вот и все

	 cout << endl;
	 cout << "Вложенные классы" << endl;
	 //это класс в классе, как сундук в сундуке

	 //так же он может находится в разных частях таких как private, public, protected
	 //опишем класс image

	 Image img;
	 img.GetImageInfo();

	 cout << endl;
	 cout << "Массив объектов класса" << endl;

	 //на саммо деле массив объектов класса, почти ничем не отличается от обыкновенных массивов
	 //исключение: у любого объекта класса могут быть поля и методы
	 //начнем со статич. массива

	 //до
	 const int LENGTH = 5;
	 int arrr[LENGTH];

	 //после
	 Pixels pix_arrr[LENGTH];

	 cout << pix_arrr[0].GetInfo() << endl;
	 pix_arrr[0] = Pixels(148, 82, 28);

	 //заемтьте провернуть такое получилось только при том что я добавил в класс конструктор по умолчанию!!! (перегрузок 2)

	 //а теперь динамический массив

	 Pixels* pixx_arrr = new Pixels[LENGTH];
	 
	 pixx_arrr[0] = Pixels(337, 228, 322);

	 cout << pixx_arrr[0].GetInfo() << endl;

	 delete[]pixx_arrr;

	 cout << endl;
	 cout << "Агрегация и композиция" << endl;
	 //кста мы ими уже пользовались
	 //и агрегация и композиция по сути являются включением одного класса в другой

	 //Агрегация - позволяет исппользовать включенный класс в других местах
	 //Композиция - включенный класс не может существовать без "хозяина"
	 //рассмотрим это на примере класса man

	 Man man;
	 man.Think();
	 //вот тебе и композиция, мозг и нас жестко инкапсулирован в человека (прикольно звучит)

	 //а вот пример агрегации
	 man.InspectCap();

	 cout << endl;
	 cout << "Наследование" << endl;
	 //это механизм при котором какой-либо объект может принять какие-либо свойства из другого объекта, а также при этом добавить что-то свое

	 Student st;
	 st.name; // мы нигде это не описали а оно тут есть, вот так 
	 st.learn();

	 ExStudent ExST;
	 ExST.learn();

	 cout << endl;
	 cout << "Модификаторы доступа при наследовании" << endl;
	 
	 //итак мы знаем что их 3
	 //так же хочу сообщить что поведение между переменными, методами и ф-ями одинаковое
	 //поэтому для удобства посмотрим на примере полей
	 
	 
	 //рассмотрим классы А и Б
	 //Б наследует от А ф-ии

	 B bbb;
	 bbb.PrintMsg();
	 bbb.msgOne;

	 //без проблем получили доступ к 1, а вот ко 2 мы доступ не можем получить, так как там стоит private
	 //то есть 2 сообщение не дает доступ вообще

	 bbb.printMSG();

	 //теперь 3, оно protected, тут мы можем работать с данной переменной только в классе, а обратится к нему через объект, уже нельзя!

	 //public - доступно все и всем
	 //private - закрыто всем, кроме самого первого класса
	 //protected - что-то среднее, через объект обратится нельзя, зато можно работать наследникам

	 //это были модификаторы в самих полях, но есть еще моды при наследовании
	 //чтобы все было просто вот тебе таблица
	 
	 /*
	 
		иден. при насл. \поля	|	public	|	private		|	protected
		public - насл			|	можно	|	нельзя		|	среднее		
		private - насл			|	нельзя	|	нельзя		|	нельзя					
		protected - насл		|	среднее	|	нельзя		|	среднее			
	 
	 можно - использовать можно все
	 нельзя - ничего использовать нельзя
	 среднее - использовать объект или ф-ю которая наследуется можно только в самом классе, через обект или напрямую нельзя

	 небольшая оговорка - при private наследовании все поля меняются на private, таким образом использовать в классе их можно, но не сразу, все инкапсулировано
	 также надо понимать что при private все protected поля блокируются, и их нельзя использовать

	 */

	 cout << endl;
	 cout << "Порядок процесса конструрирования и деструирования при наследовании" << endl;

	 BB bebra;
	 CC cebra;

	 //во прикол правда, думаю тут итак все понятно

	 cout << endl;
	 cout << "Вызов конструктора базового класса из конструктора класса-наследника" << endl;

	 /*
	 сейчас чтобы не перегружать файл ненужным кодом, буду писать тут

	 заметим тчо при вызове класса B вызывается конструктор класса AA, но что будет если в классе AA несколько конструкторов, и нам нужен определенный из них
	 как нам такое осуществить?

	 /////////////////////////////////////////////////////////////////// класс А

	 class A
	 {
	 public:
		A()
		{
			msg = "Пустота";
		}

		void PrintMSG()
		{
			cout << msg << endl;
		}

		A(string msg)
		{
			this->msg = msg;
		}

	private:
		string msg;
	 }

	 ////////////////////////////////////////////////////////////////// класс Б

	 class BB : public AA
	{
	public:
		BB()
		{

		}

	}

	
	 
	 */

	 //собственно
	 //компилятор всегда вызывает коснтруктор по умолчанию класса A, а там у нас просто присваивание

	 //но как указать ему, олуху, что нам надо?

	 //для этого вот что надо сделать в классе BB

	 /*
	 
	 class BB : public AA
	{
	public:
		BB():A("наше новое сообщение")
		{

		}

	}
	 
	 */

	 //не понял?
	 //отладка!

	 //если нет даже просто конструктора по умолчанию, он просто возьмет и начнет на нас орать (компилятор злой)

	 cout << endl;
	 cout << "Ключевое слово virtual и override" << endl;

	 //это важно, это полиморфизм, и да будет интересно, а также нелегко
	 
	 //если что полиморфизм мы уже видели, это указатели на ф-ии, пересмотри если забыл

	 //прикол в том что сейчас мы сделаем так, что классы будут иметь одинаковые ф-ии, но при этом вести себ по разному!!!

	 Gun pistol;
	 pistol.Shoot();

	 SubMachinGun smg;

	 Gun* weapon = &smg;

	 weapon->Shoot(); //вызвался метод смг, так как указатель на ссылку с смг, если изменим

	 Gun *weaponn = &pistol;

	 weaponn->Shoot();

	 //работает такая вещь только из-за virtual и override, то есть при полиморфизме

	 //но бл"ть в чем суть, зачем такое творить?
	 
	 //для этого создадим класс игрока

	 cout << endl;

	 Player ST;
	 ST.Shoot(&smg);

	//работает, как видите, и главное меньше кода - меньше работы
	//но для идиала

	 cout << endl;
	 cout << "Абстракный класс, чисто виртуальная ф-я" << endl;

	 //virtual и override, это очень нам надо
	 //чисто виртуальная ф-я, по сути означает что эта ф-я пустая, в такой ф-ии нет реализации

	 //класс в котором присутствует такая ф-я, называется абстракным, экземпляры таких классов создать нельзя (логично)

	 Knife knife;

	 ST.Shoot(&knife);

	 knife.Foo();
	 
	 //в абстракном классе, можно сделать норм ф-ю, а потом наследники смогут использовать данную ф-ю

	 cout << endl;
	 cout << "Виртуальный деструктор класса" << endl;

	 //объяснять долго и не интересно, в кратце, вирт. деструктор нужен для удаления всей нужной памяти, иначе может произойти утечка памяти

	 first f;
	 second sec;

	 //вот вроде бы все прекрасно, что еще надо для работы?
	 //да много надо, попробуем создать объект базового класса, а в него присвоим объект класса наследника (а такое сделать можно)

	 first *p_sec_dinamic = new second;

	 cout << endl; // на самом деле сейчас все работает, просто изменения уже есть, а прописывать новые классы - геморой

	 delete p_sec_dinamic;
	 
	 //она из самых не постоянных рубрик - найди 1 отличие
	 //где деструтор класса second?
	 //правильно - его нет, вот тебе и утечка памяти

	 //все это потому что деструктор базового класса, не был виртуальным

	 //вот теперь все работает

	 cout << endl;
	 cout << "Чисто виртуальный деструктор" << endl;

	 //очень похоже на чисто виртуальную ф-ию
	 //однако, если создать чисто виртуальный деструктор в классе, то все - теперь это абстрактный класс

	 //прошу обратить внимание на синтаксис

	 //все, больше не надо, меньше тоже

	 cout << endl;
	 cout << "Делегирующие конструкторы" << endl;

	 //это некий синтаксический сахар (еб"ть что этто значит)
	 //синтаксический сахар - некое удобство при написании кода, которое помогло бы быстрее и проще написать какой либо код

	 human_two h("Аристарх");
	 h.Print();

	 cout << endl;
	 cout << "Вызов виртуального метода базового класса в классе наследнике" << endl;
	 //мы можем спокойно вызывать обыкновенные ф-ии в классах наследнике, однако если метод вирт. то есть небольшие оссобенности
	 //в классе Sms и SuperSms и Printer все подробно описано

	 Sms sms("Hi");
	 Printer p;
	 p.Print(&sms);

	 SuperSms smss("Hi");

	 p.Print(&smss);

	 //прошу обратить внимание на синтаксис в переопределенном методе класса SuperSms! Именно благодаря этомк все это работает, иначе, произойдет рекурсия!
	 //причем оч плохая, бесконечная
	 //проверить очень легко, удали этот синтаксис и пробей отладкой

	 cout << endl;
	 cout << "Множественное наследование в C++" << endl;

	 //до этого у нас был один класс предок, а теперь их будет несколько, и наследник(и) получат свойства абсолютно всех этих классов
	 //классы которые используются - Car и Plane

	 Car car;
	 car.Drive();

	 Plane plane;
	 plane.Fly();

	 cout << endl;
	 //как вам такое?!

	 FlyingCar fc;
	 fc.Drive();
	 fc.Fly();

	 //такое наследование также относится и к полям

	 cout << fc.str << endl;
	 cout << fc.str2 << endl;

	 //прикольно, правда?
	 //унаследоват можно от стольки классов сколько надо, только надо ли?)

	 //тут можно и так

	 Car* ptrc = &fc;
	 Plane* ptrp = &fc;

	 cout << endl;
	 cout << "Порядок вызова конструкторов при множественном наследовании" << endl;
	 //в принципе в консоли уже все было видно, так что можно увидеть - то что было наследовано первым, то и вызывается быстрее)\

	 //теперь десрукторы, тут тоже самое)

	 cout << endl;
	 cout << "Одинаковые методы множественного наследования" << endl;

	 //у обоих классов - машина и самолет, есть одинаковый метод use
	 
	 //Ваши ставки?
	 //fc.use();
	 
	 //ошибка, вот какой ответ, компилятор не тупой! И говорит тебе что как бы ф-я то не однозначная!
	 //для того чтобы решить данную пробему надо и использовать приведение типов
	 //заметить надо что надо их обернуть два раза, понял?

	 ((Car)fc).use();
	 ((Plane)fc).use();

	 //кстати также ты мог заметить что вызываются деструкторы, прикольный факт, правда?)

	 cout << endl;
	 cout << "Интерфейс в ООП" << endl;
	 //внимание - ЭТО ВАЖНО
	 //это может быть сложным кстати
	 cout << "Тут много полезного написано, лучше прочитать" << endl;
	 //а также хочу сообщить, НЕ ЧИТАЙТЕ ОПРЕДЕЛЕНИЯ НА ЭТУ ТЕМУ В ИНТЕРНЕТЕ, там такая чуууууууууууууушь

	 //но для начала, на кой это бл"ть надо? Ну и также хочу немного удивить, формально в C++ нет интерфейсов)
	 //Думаю каждый поймет, что если человек научился однажды научился кататься на велике, ему больше не придется учится ктаться на велике. Даже если ему какой
	 //то другой велик поставить, пусть даже другого типа. То есть наш человек освоил интерфейс управления велосипедом

	 //То есть интерфейс - публичные методы с помощью которых вы можете взаимодействовать с какой-либо сущностью

	 //кстати я не зря акцентировал внимание на том что человек может после того как научился какаться на велосипедах разного типа - везде один принцип
	 // 	 ПРИМЕР
	 //можно еще привести пример по серьезней, предположим что мы делаем ПО с базами данных, но мы не знаем какая именно база данных будет
	 //как быть тогда
	 //ну предположим что мы зннаем что каждая база данных будет реализовывать метод Read, мы можем написать метод который будет выводить данные на экран
	 //таким образом, что ему будет абсолютно все похер какая база данных будет, клавное чтобы был метод Read
	 
	 //сначала я вам сказал что в чистом C++ нет ключевого слова интерфейс, однако в С++ есть множественное наследование
	 //а что по сути своей интерфейс - это некая договоренность

	 //то есть предположим что наш человек знает как водить велик - крутить руль, крутить педали, держать равновесие. Тогда он сможет повести и что нибудь другое
	 //что бы это ни было, главное чтобы для того чтобы эта фиговина работала надо просто крутить руль педали и смотреть по сторонам.
	 //такая логика напоминает логику абстрактных классов

	 //и наконец что такое интерфейс
	 //ИНТЕРФЕЙС (в С++) - это асбтрактный класс, в котором АБСОЛЮТНО все методы будут виртуальны, никакой реализации не будет

	 SimpleBicycle SB;

	 Cyclist cyc;
	 cyc.RideOn(SB);

	 //кста когда мы наследуемся от интерфейса, принято говорить "реализовываем интерфейс"

	 //мы моежем создать хоть миллион велосипедов и их подобий, если они реализовывают интерфейс I_bicycle то со всеми объектами будет возможность
	 //взаимодествовать у нашего велосипедиста

	 cout << endl;
	 cout << "Ромбовидное наследование. Виртуальное наследование" << endl;

	 //по сути это одно и тоже, просто называется по-другому

	 GraticCard sd("AMD", "Intel");

	 //Посмотри внимательно! Изза создания всех этих классов и вызывания конструкторов предков получится что наша плата sd содержит 2 части Component
	 //которые одинаковые! Но ты скажешь, и ладно, не волнует. Да, на данном этапе это нас не волнует, даже наоборот. 
	 //ЭТО НЕ БАГ А ФИЧА))))

	 //мы можем каждому предку дать разные названия компаний и все будет прикольно)

	 //но что если...

	 OrcWarrior War;

	 //а как нам теперь посчитать количество хп у нашего воина? Дублировать данные? нет конечно

	 //нам надо чтобы в этой структуре вызовов Character встречался один раз, для этого и нужно ромбовидное наследование

	 //используем там где наследование virtual!

	 //изменилось да?

	 cout << endl;
	 cout << "Работа с файлами" << endl;

	 //нах оно? надо!
	 //собственно работает все благодаря библеотеке, а она в свою очередь благодарая классам : fstream, ifstream, ofstream
	 //основной класс тут fstream - предназначен для чтения и записи файлов
	 //ifstream - для чтения
	 //ofstream - для записи

	 //начнем с ofstream || если мы не пишем полный путь при открытии файла то его сохранят автоматически в папку с проектом

	 //прошу заметить что мы вписываем строку, то есть можно также записывать в переменную типа string и например через cin ввести сам путь!

	 string path = "myFile.txt";
	 string path2 = "myFile2.txt"; //no_matter
	 
	 ofstream fout;
	 fout.open(path); //ф-я open работает интересным образом, если она не находит файл в папке, она его создает. Но как проверить свершилось ли?

	 if (!fout.is_open()) // так проверям открыось ли вообще наше
	 {
		 cout << "Ошибка открытия файла" << endl;
	 }
	 else
	 {
		 
		 fout << "\nЭто наши данные!!!"; //вот так вот вводим данные
	 }
	 
	 fout.close(); //когда ты отработал с каким либо ресурсом, и он перестал тебе быть нужным, заверши работу!

	 //файл появился в папке с проектом, и в них записали строку. Однако можно записать все что угодно.

	 //однако если заменить строку на циферки, то при последующем запуске строка пропадет, куда?

	 //ф-я open изначально при запуске берет и стерает все что было там записано! Если мы не хотим чтобы так было напишите 
	 //fout.open(path, ofstream::app);

	 cout << endl;
	 cout << "Чтение и запись в файле" << endl;
	 //теперь концентрируемся на fstream (универсал)

	 fstream fs;
	 

	 //как мы знаем open перегружен у всех этих операторов, но у fs он будет прегружен оссобенно сильно
	 //2 параметр - ответ на режим работы с файлом, однако их много, их можно комбинировать с помощью побитового ИЛИ.
	 //сейчас дадим ему возможность делать и чтение и запись
	 //in - дает возможность читать
	 //out - дает возможность писать
	 //а написав это все через побитовое ИЛИ (|), мы активировали оба параметра, можно начинать

	 //в эти все параметры идет и знакомый нам app

	 fs.open(path2, fstream::in | fstream::out | fstream::app);
	 
	 Toch toc(112, 4566, 78);

	 cout << toc;

	 

	 if (!fs.is_open())
	 {
		 cout << "Ошибка открытия файла" << endl;
	 }
	 else
	 {
		 /*
		 string file_msg;
		 int menu_value;
		 cout << "Файл открыт!" << endl;
		 
		 cout << "Введите 1 для записи данных в файл:" << endl;
		 cout << "Введите 2 для вывода всех даннных из файла:" << endl;
		 cin >> menu_value;

		 if (menu_value == 1)
		 {
			 file_msg = "";
			 cout << "Введите ваше сообщение!" << endl;
			 SetConsoleCP(1251);
			 cin >> file_msg;
			 fs << file_msg << "\n";
			 SetConsoleCP(866);
		 }

		 if (menu_value == 2)
		 {
			 cout << "Ваши даннные!" << endl;
			 while (!fs.eof())
			 {
				 file_msg = "";
				 fs >> file_msg;
				 cout << file_msg << endl;
			 }
		 }
		 */


		 fs << toc;

 	 }



	 fs.close();

	 cout << endl;
	 cout << "Перегрузка операторов потокового ввода и вывода данных" << endl;
	 //это вот этой штуки << и вот этой штуки >>

	 //будем работать на примере прошлом, так как это удобно, класс Toch имеет поля x y z, просто по сути точка в 3х мерном пространстве

	 cout << endl;
	 cout << "Обработка исключений в C++. try catch" << endl;
	 //что это такое?

	 //по сути обработка исключений - это обработка исключительных ситуаций, то есть каких-либо проблем в работе программы, которые не зависят от программиста!Но программист
	 //предвидел что такая ситуация произойдет у него и сделал обработку ситуаций, то есть реакцию программы на ошибку! (какой умный)

	 string path3 = "meFile3.tx";
	 /*
	 ifstream fin;
	 fin.exceptions(ifstream::badbit | ifstream::failbit);
	 
	 try
	 {
		 cout << "Попытка открыть файл" << endl;

		 fin.open(path3);

		 cout << "Открыто" << endl;
	 }
	 catch (const ifstream::failure& ex)
	 {
		
		 cout << ex.what() << endl;
		 cout << ex.code() << endl;
	 }

	 fin.close();
	 */

	 cout << endl;
	 cout << "Генератор исключений. throw" << endl;

	 //throw как понятно из названия БРОСАЕТ исключение, и собственно нахера нам это? Когда появится надобность бросить исключение?
	 //когда чтот-то идет не так. Представим что мы разрабатываем класс ifstream. Тогда мы проверяем правильно ли введен путь до файла который надо открыть. Неправильно?
	 //бросить
	 //после чего написать какое-либо сообщение почему так произошло

	 //пример будет на ф-ии, однако такое же все работает и с методами класса и ф-ями классов.

	 Function_1(55); // вот так выведется то что надо

	 //Function_1(-55); //а вот так нет, выведет ничего и наорет на нас

	 //а щас будем ловить исключение
	 try
	 {
		 Function_1(-55);
	 }
	 catch (const int ex)
	 {
		 cout << "Мы поймали " << ex << endl; //вот так это все работает.
	 }

	 //вообще передать в throw можно не только число, можно целое сообщение, как строчку. Можно передать все, решать уже тебе.
	 //вообще для полного универсальства можно сделать следующее - поставить во вкид exception тогда одна запись в строке поиска будет всегда работать!

	 try
	 {
		 Function_2(-55);
	 }
	 catch (const exception& ex)
	 {
		 cout << "Мы поймали - " << ex.what() << endl; //таким вот образом, все что мы запишем в срочку в классе exception отобразится в его методе what а еще
	 }
	 //если бросаться будет что-то унаследованное от класса exception то мы поймаем это, вседь ловим то ссылку на объект exception

	 cout << endl;
	 cout << "Несколько блоков catch." << endl;

	 //зачем? все просто, предположим мы не знаем как точно работает та или иная ф-я, какое исключение она выбросит на этот раз? в С++ существует структура которая позволяет
	 //решить данную проблему, а она важна, ведь надо чтобы прога хотя бы не вылетела!

	 try
	 {
		 Function_3(-55);
	 }
	 catch (const exception& ex)
	 {
		 cout << "Блок 2 \t Мы поймали " << ex.what() << endl;
	 }
	 //все что надо сделать это просто продолжить писать новые catchи и все
	 catch (const char * ex)
	 {
		 cout << " Блок 2 \t Мы поймали " << ex << endl;
	 }

	 //я добавил в ф-ию новое условие - число равное 0, тоже выскачет исключение, но наа этот раз бросится exception

	 try
	 {
		 Function_3(0);
	 }
	 catch (const exception& ex)
	 {
		 cout << "Блок 1 \t Мы поймали " << ex.what() << endl;
	 }
	 catch (const char* ex)
	 {
		 cout << " Блок 2 \t Мы поймали " << ex << endl;
	 }

	 //НО, это все бесполезно), ведь есть три точки которые делают все! Все кроме того как это вывести. Да мы сто проц узнаем что там что-то бум, однако не поймем что именно.
	 //а вообще то нам это нужно. Эти три точки ведь по сути ничего точного не принимают, вот и получается такая ситауция. Максимум можно понять что там что-то бум, но мы это и 
	 //так, буз лишней помощи, узнаем! БЕСПОЛЕЗНО

	 try
	 {
		 Function_3(-55);
	 }
	 catch (...)
	 {
		 cout << "Что-то там произошло!!!" << endl;
	 }

	 //и да, эта штука моооожет все таки пригодится в связке когда вообще ничего не подошло, а понять что плохо все таки надо. Тогда советую ставить ее в самый низ, проверка идет 
	 //сверху вниз!


	 cout << endl;
	 cout << "Создание своего собственного блока exception" << endl;
	 //для начала вспомним а зачем оно нам надо.

	 //для этого просто посмотрим какие ограничения есть у базового класса exception, прям базового для всех
	 //он огрничен тем что у ебъекта этого класса есть лишь метод what, то есть то что мы передадим в строку при создании вкида, то мы и увидим, больше ничего
	 //также прошу вспомнить как в прошлый раз мы ловили... по сути тоже exception только другой - класса ifstream. Но это тоже exception
	 //у него есть еще метод code, который содержит намного больше информации чем просто what. Поэтому когда ты будешь разрабатывать свой класс или ф-ю, возможно надо будет 
	 //расписать что именно там не так!)

	 //class myException, см. выше

	 //прошу заметить, что очень важно и необходимо сделать myException наследником базового exception, ведь именно тогда мы будем ловить НАШЕ с помощью одной и той же строчки 
	 try
	 {
		 Function_my(-1);
	 }
	 catch (myException &ex)
	 {
		 cout << "Блок 1 поймали " << ex.what() <<  endl;
		 cout << "Состояние данных " << ex.GetDataState() << endl;
	 }
	 catch (exception& ex)
	 {
		 cout << "Блок 2 мы поймали " << ex.what() << endl;
	 }

	 //первоначально выведет Unknown exception, ведь у базового exception есть конструктор, а мы его не измениля, следовательно по изначальному конструктору выведет неизвестное

	 //такэе прошу заметить что надо быть чрезвычайно осторожным при постановке catch. Просто надо быть внимательным и все

	 cout << endl;
	 cout << "Ключевое слово enum" << endl;
	 //зачем оно надо? ну его используют во всех C подобных языках, значит оно надо) так что вещь полезная
	 //enum - перечисляемый тип, который служит для объявления символических имен, представляющих целочисленные константы // не понятно? мне тоже, но на деле все проще
	 //оно надо именно программисту, чтобы нам было легкче, чтобы мы писали более понятный код. Т.е. в каком то смылсе это синтаксический сахар.
	 //а теперь когда оно надо

	 PC::PCState c_state; //вот так оно и создается
	 c_state = PC::PCState::OFF; //видал // по сути там опять числа, но это для компа, для вас то все более понятно) И да просто наведи на это все мышку и сам все поймешь

	 PC pc;
	 pc.SetState(PC::PCState::ON);

	 if (pc.GetState() == PC::PCState::ON)
	 {
		 cout << "Компутер работает" << endl;
	 }

	 switch (pc.GetState()) //даже тут можно)
	 {
	 case PC::PCState::OFF:
		 cout << "Он не работает" << endl;
		 break;
	 case PC::PCState::ON:
		 cout << "Он работает" << endl;
		 break; 
	 case PC::PCState::SLEEP:
		 cout << "Он вообще спит" << endl;
		 break;
	 }
	 //удобно? удобно
	 //также ты можешь присваивать полям в enumе значения! Целочисленные, для того чтобы не путались значения в классах
	 //а и да, лучше всего описывать enum прямо в классе, ведь, а где еще его будешь использовать? Только делай это в public поле лады?

	 cout << endl;
	 cout << "Пространства имен. namespace" << endl;
	 //да да да, это та штука которая в саааамом верху стоит и ты не знал зачем оно, щас узнаешь
	 //для начала создадим ситаяцию когда оно нам надо

	 //преположим, у нас над проетом работает 2 разраба, они написали одну и ту же ф-ю, и не важно какую
	 //ну как одну и ту же, с одним и тем же названием (кста это моежт быть и класс)
	 //вы же понимаете что у нас оно не заработает. Есть 2 пути - 1, они изменят названия ф-ии, но что если они не знают о таком совпадении? Жопа
	 //2 - наша херь

	 //собственно как оно работает, просто берем и пишем namespace ее название и то что будет в ней) таким образом теперь эти две ф-ии не будут даже знать друг о друге
	 //а теперь как этим делом пользоваться. как можете заметить, нам говорят что такой ф-ии вообще нет. Оно и логично ведь среда разработки ищет ее в глобальном пространстве 
	 //имен (когда мы ничего вообще не указываем оно и есть, принцип схожий с обл. видимости), а ф-я наша не в глобале, а в отдельном пространстве

	 SecondNS::Simple_Function(); //вот так и работаем

	 //прошу также заметить, можно объявить один и тот же namespace где угодно (вне других ф-ии и классов конечно же), и при этом если название совпадает среда разработки как бы
	 //совместит ф-онал двух (или более) кусочков namespace-ов. Т.е. не надо указывать одно и тоже название (чего-бы то ни было) в одном namespace, иинче над тобой надругаются

	 //но есть еще более прикольный прикол. Можно поместить одно пространство в другое! для упрощения понимания объясню
	 //мы ведь по сути создаем пространство имен и так в глобальном, тут тоже самое! Просто для реализации нашего маразма надо сделать так:

	 ThirdNS::SecondNS::Simple_Function(); //матрешка) сравнимо с путем файла на компютере

	 //но ты же помнишь как мы указывали в самом начале using namespace std; да
	 //в пространстве имен std лежат все ф-ии которыми мы с вами пользуемся: cout, cin, abs и тд.
	 //просто все лежит там, и прописав using namespace std; мы как бы сделали по умолчанию использование std. Заметили что ммы не пишем все время std::cout да?
	 //вот это блягодаря этой записи! Мы как бы пользуемся std ничего не прописывая а должны были пользоваться глобальным пространством)

	 //кста работает этот using на все, то есть не надо особо злоупотреблять этим using, а то конфликты и тд. Надеюсь понял

	 cout << endl;
	 cout << "Шаблоны классов" << endl;
	 //звучит как что-то знакомое (шаблонные ф-ии) не не, показалось.
	 //так как в видосе говоится много не понятных вещей, не буду пугать и просто скажу - это нам сильно надо

	 //испольовать шаблонный класс надо когда мы хотим чтобы наш класс работтал с разными типами данных, чтобы не писать много кода. Также такие классы называют обобщенными классами
	 
	 //для того чтобы превратить это все в шаблон, пишем над классом template (шаблон) и <typename T> (говорит что у нас тут обощенные типы данных, T - название этого обощенного),
	 //все (факт - необязатльно писать T, так просто принято)
	 //написали ф-ю по поределинию занимаемой памятти в компе , го

	 int myclass_a = 5; //ах да, сделать так легко и просто шаблонный класс не получится, надо указать после названия класса тот тип даных с которым мы будем работать

	 MyClass <int> int_class(myclass_a); //вот так пишем
	 int_class.DataTypeSize(); //собсттвенно выведет 4, ведь int занимает 4 байта)

	 double myclass_b = 5.65;
	 MyClass <double> double_class(myclass_b);
	 double_class.DataTypeSize(); //а щас будет 8

	 //а теперь немного с классом magic_Point который я быренько написал

	 magic_Point myclass_c;
	 cout << myclass_c.x << endl << endl; //просто чтобы поонял что там внутри
	 MyClass <magic_Point> magic_Point_class(myclass_c); //даже с этим классом он будет работать! Ему вообще зелено
	 magic_Point_class.DataTypeSize(); //выведет 12, ведь 4 на 3 будет 12. изменим int в Point-е на double будет 24 (8*3) и так далее. Работает!

	 //ах и да, в классе этом волшебном можно створить с этим T что хочешь. Даже ф-ю с возращаемым T можно! Было бы желание
	 //можно также через запятую сказать что будет больше typename например T2, и тгда будет реализация для двух типов, класс

	 //есть еще один прекол, помимо слова typename можно как и в ф-ях использовать class, прикол в том что по ф-оналу никакой разницы нет, протос чуть короче)

	 cout << endl;
	 cout << "Наследование шаблонных классов" << endl;
	 //заюзаем по ф-оналу тот де класс MyClass но изменим имя, будет TypeSize
	 //а теперь создадим наследоника - TypeInfo
	 
	 //все оссобенности синтаксиса находятся наверху
	 double info_a = 7.963;
	 TypeInfo <double> info1(info_a); //
	 info1.ShowTypeName();
	 info1.DataTypeSize(); // вот видишь, наследовалось)
	 
	 cout << endl;
	 cout << "Специализация шаблонов класса" << endl;
	 //предположим что в шаблонный класс бросили int, ну и казалось бы рабоатет как работает, а вот нам с этим классом надо как то извратиться. Ща будем это делать

	 Printer_2<string>pr;
	 pr.Print("Hello World!!!");

	 cout << endl;
	 cout << "Разница между структурой и классом" << endl;

	 //что это такое? Струкура почти идентична классу, то есть даже не надо ничего учить, ну почти
	 // 
	 //синтаксис на этапе создания отличается только ключевым словом (struct), все остальное не меняется
	 //теперь в ф-онале, у класса если мы ему явно не скажем какой спецификатор (private, public) будет по умолчанию стоять private, у структуры в точности наоборот! public
	 //2 отличие в том что при наследовании труктуры от другой без указания спецификатор наследования (private, public), будет стоять public, в то время как у класса private

	 //это звучит смешно, но это все отличия! Даже показывать не буду все слишком легко

	 cout << endl;
	 cout << "Умные указатели. Smart pointers" << endl;
	 //для начала вспомним на кой надо обычный указатель

	 int* ptr = new	int(5);//все теперь наше число в куче)
	 delete ptr;//а вот так чтобы не было утечки
	 //я думаю ты помнишь плюсы и минусы такой вещи, + мы все контролируем, - представь что ты забыл удалить

	 //было бы неплохо если бы нам не надо было бы прописывать удаление, да? Вот зачем умные указатели нам и нужны, думаю ты сам поймешь когда оно надо когда не надо
	 //банальный пример - ветвления, предположим что при выполнении какого то условия мы должны удалить память, а теперь представь что таких условий не 2 а 100, плохо

	 //по своей сути смарт поинтер это объектная оболочка для хранений каких-либо типов данных. Это класс.

	 //реализация наверху
	 //но также надо понимать, что память обязательно надо очищать

	 //теперь надо реализовать систему распоковки - перегрузим звуздочку *

	 SmartPointer<int> pointer = new int(5); // вот так создаем переменную, в соответствии с принимаемым значением конструктора
	 cin >> *pointer;
	 cout << "Вот сам указатель : " << *pointer << endl;

	 cout << endl;
	 cout << "auto_ptr | unique_ptr | shared_ptr | Умные указатели" << endl;
	 //щас скажем об этой троице СТАНДАРТНЫХ поинтеров, что ледат в библиотеках С++ - подключим memory

	 //разберем случай
	 SmartPointer<int> ps1 = new int(5); // тут указатель на пятерку
	 SmartPointer<int> ps2 = new int(4);// ps1; // тут указатель содержащий указатель на ту же пятерку в памяти, что будет?
	 
	 // а теперь про удаление классов из области видимости, начнут вызываться деструкторы, предположим, что деструктор ps1 вызвался бестрее, получается он удалит ту самую пятерку
	 //внимание вопрос: на что тогда ссылается ps2. Ни на что. Соответсвенно, когда ps2 начнет удаление всех частей, он попробует удалить то, чего нет!!! Малоприятная ситуация...
	 //но что делать, если вот надо чтобы ps2 указывал на ps1, но та самая "пятерка" не исчезала. тут и приходит эта троица

	 //auto_ptr - устраел, его не испоьзуют сейчас, похож на unique_ptr. Несмотря на истарение, он может использоваться, редко.

	 auto_ptr<int> ap1(new int(5));
	 auto_ptr<int> ap2 = ap1; //что будет теперь)

	 //на смену пришел unique_ptr, юник - уникальный и проблема тут решена РАДИКАЛЬНО

	 unique_ptr<int> up1(new int(5));
	 //unique_ptr<int> up2 = up1; //ну тупо нельзя так делать и все тут, н уровне ошибки
	 //решить данную ситуацию поможет move
	 unique_ptr<int> up2;
	 up2 = move(up1); // было up1 = 5 | up2 = empty
	 //стало up1 = empty | up2 = 5, переместили

	 //похоже на auto_ptr да? даже больше, похоже на наш SmartPointer!!! У юника есть вшитая ф-я get(), что возвращает роу-поинтер ( *p ), ну тупо оболочка
	 //есть еще reset и release, оба затирают значение, но делают по-разному)

	 //reset
	 int* pp = new int(5);
	 unique_ptr<int> up3(pp);
	 up3.reset(); //в отладке он просто затрет значение и поинтер станет пустым, ВСЕ стнанут пустыми, и *pp тоже
	 //release
	 unique_ptr<int> up4(pp);
	 up4.release(); //да, мы удалим значение, но у *pp оно останется! Точечное удаление!

	 //самый топовый и лучший указатель - shared_ptr, шаред - общий и это тоже не зря! В шаред поинтере решена проблема владения раными указателями одной ячейкой памяти

	 shared_ptr<int> hp1(new int(5));
	 shared_ptr<int> hp2(hp1);
	 //отличие просто - рабоать с этой бедной 5 можно и в первом и во втором указателе!! 

	 //все очень просто, эта пятерка удалится только тогда, когда БУДЕТ УНИЧТОЖАТЬСЯ ПОСЛЕДНИЙ ПОИНТЕР, ЧТО ИМЕЛ ДОСТУП К НЕЙ. Весь фокус)

	 //ну и чуть-чуть понимания дианмических массивов и смарт поинтеров
	 int SIZE; //так как у нас тут динамика, можно просто взять и наплевать на кол-во элементов
	 cin >> SIZE;
	 shared_ptr<int[]> arr_ptr(new int [SIZE]); //если мы работаем с МАССИВОМ, то надо ОБЯЗАТЕЛЬНО доабвить []
	 //и да реализация добавления new памяти в поинтер можно прям так, удобно)

	 for (int i = 0; i < SIZE; ++i) //пробежимся)
	 {
		 arr_ptr[i] = rand() % 10; // псевдо случайные числа)
		 cout << arr_ptr[i] << endl; //ну и вывод
	 }

	 cout << endl;
	 cout << "Односвязный список" << endl;
	 //звучит не звучит
	 //итак, суть этой штуки в хранении наших данных, числа, или что-то по-сложнее (объекты классов)
	 //а так как она ДИНАМИЧЕСКАЯ, то она удобна для манипулирования данными
	 //вспомните как можно ДОБАВИТЬ ДАННЫЕ в динаический массив, если вы в принципе вспомните, то понимаете, что нам надо открыть окно, очень уж душно
	 //а теперь представьте, что надо ОЧЕНЬ МНОГО РАЗ делать это. Да мы так перегруз поймаем, а оно нам не надо
	 
	 //итак ячейка у динамического массива это просто ячейка, а вот у односвязного списка это кое-что по-серьезней, а именно КЛАСС, содержащих в себе два поля: adress, data.
	 //внимание вопрос: а нафига нам adress как отдельное поле в элементе? Чтобы знать, где нахожится следующий элемент списка в динамической памяти! То есть это УКАЗАТЕЛЬ НА 
	 //СЛЕДУЮЩИЙ ЭЛЕМЕНТ. Получается, что каждый элемент списка знает, где находится следующий элемент. Ну а data это данные, которые мы засунули в список.
	 //Если же элемент у нас последний, то у него значение adress будет принимать значение NULL.

	 //А теперь по поводу расположения элементов в динамической памяти: массив - это непрерывный поток данных, непрерывный поток памяти, а вот наш список НЕТ, это значит, что 
	 //для того, чтобы хранить данные в односвязном списке, нам НЕ НУЖНА НЕПРЕРЫВНАЯ ПАМЯТЬ. Ведь каждый элемент знает адрес следующего элемента, а массив такое не имеет!!!

	 //Естественно, нам не надо никаких махинаций при добавленнии нового элемнта в список, ведь можно просто адрес в строку последнего элемента написать и все
	 //Таким образом, односвязный список намного удобнее, чем массив в случаях изменения количества элементов

	 //Предположим, что нам надо удалить элемент из середины. В массиве это также душно, даже более душно. А в списке нам просто надо сказать предыдущему элементу, что теперь у 
	 //него другой adress (адресс элемента следующего после того элемента, что мы хотим удалить), а тот самый удаляемый удалить. Все!

	 //Хотим добавить данные в середину. В массиве это ТОЖЕ душно, даже слишкооооооом, а в списке, как вы угадали, легко и просто - тоже небольшая махинация с адресами и все.
	 //Добавить в начало тоже легко, думаю вы поняли)

	 //Список спокойно выигрывает у массива при добавлении и уничтожении элементов, но есть минусы. Как собственно нам индексы элементов находить, их же тут нет...
	 //Ну, у нас есть название первого элемента, мы смотрим на его adress, если он не NULL, то идем на следующий элемент, там проворачиваем то же самое. Не кажется ли вам, что это
	 //МАЛОСТЬ ДОЛГО? Я молчу про получение элемента в середине, ведь тогда нам получается какой-то счетчик нужен, как у массивов? Сложно, долго, неудобно, а лично я ленивый
	 //Конечно, можно решить это говно просто с помощью двусвязного списка, нооооооо не про это
	 //Короче: массив лучше при нахождении данных, список при их изменении, добавлении, удалении и тд.

	 cout << endl;
	 cout << "Реализация односвязного списка)" << endl;
	 //а теперь давайте это все реализуем) хе-хе. Кста код будет СЛОЖНЫМ)
	 //см наверх, там где-то класс List

	 List<int> lst;
	 lst.push_back(5);
	 lst.push_back(55);
	  
	 for (int i = 0; i < lst.GetSize(); ++i)
	 {
		 cout << lst[i] << endl;
	 }
	 cout << "Элементов в списке: " << lst.GetSize() << endl;

	 lst.insert(88, 1);

	 for (int i = 0; i < lst.GetSize(); ++i)
	 {
		 cout << lst[i] << endl;
	 }

	 cout << "Элементов в списке: " << lst.GetSize() << endl;

	 cout << endl;
	 cout << "vector / stl" << endl;

	 //библиотека стандартных шаблонов, она же stl, где находится дахера и еще много, и все это нам надо

	 //итак vector
	 vector<int> myVector; //по своей сути это динамический массив, в отличие от него, нам просто не нужно выполнять какие-либо самостоятельные вызовы, сложные операции и тд
	 myVector.push_back(54); 
	 myVector.push_back(228);
	 myVector.push_back(337);
	 //вот так данные добавляются

	 cout << "Кол-во эл. в векторе: " << myVector.size() << "\nСами элементы: \n";
	 for (int i = 0; i < myVector.size(); i++) //и да, мы не долны где либо хранить данные о кол-ве переменных, это автоматически делается
	 {
		 cout << myVector[i] << " ";
	 }
	 cout << endl;

	 //но есть и еще один способ, кроме []
	 cout << myVector.at(2) << "\n"; //аналогично [], но разница есть, она в реализации
	 //при [] мы не проверяем границы массива, просто идем и будь что будет
	 //at же проверяет, вышли ли мы за границы, не даст нам боратится к чужой области памяти, он умён, настолько что с помощью блока try catch можно спокойно понять в чем дело
	 //но по скорости [] лучше, намного лучше

	 //есть еще clear
	 myVector.clear();
	 cout << "Элементов теперь: " << myVector.size() << "\n"; //очистка всех элементов

	 myVector.push_back(54);
	 myVector.push_back(228);
	 myVector.push_back(337); //вновь забьем 3 элементами

	 // есть еще pop_back, удаляет последний элемент вектора
	 myVector.pop_back();
	 cout << "Теперь элеменов: " << myVector.size() << "\n"; //а не 3

	 //а еще можно забивать вектор через фигурные скобочки (дада), только зачем

	 //но ведь по сути, у нас есть динамический массив, оболочкой для которого являетс вектор... Мы можем работать с внутренним динамическим массивом кстати
	 myVector.capacity(); //капасити, возвращает целочисленную переменную
	 //а значит она ёмкость вектора. А в чем отличие от size?

	 cout << "capacity вектора: " << myVector.capacity() << "\n"; //у нас же 2 элемента, почему тогда выводится 3?
	 // что это такое... а это важно
	 //вернемся в способ добавления элемента в динамический массив - каждый раз когда мы что-то добавляем, мы должны выделять память, переносить элементы, и только потом 
	 // добавлять элемент. Это очень накладная операция и если бы каждый раз при добавлении вектор делал бы это, он работал бы не быстро, поэтому придумыли разрабы одну фичу
	 // если вкратце, при добавлении элемента размер "нового" массива не на 1 больше предыдущего, а на несколько (там зависит от уже кол-ва), поэтому все потом быстро работает
	 //получается size - кол-во забитых чем то ячеек, а capacity - это ВСЯ его ёмкость, сколько вообще ячеек

	 //мы модем сами управлять capacity а не полагаться на машину - reserve

	 myVector.reserve(10); //мы "зарезервивовали" 40 элементов
	 //соотвественно capacity будет 10!

	 cout << "capacity вектора: " << myVector.capacity() << "\n";

	 //но ведь... так много памяти потрачено впустую!!! Надо бы это исправить
	 myVector.shrink_to_fit(); //за вас это сделают!!!
	 cout << "capacity вектора: " << myVector.capacity() << "\n"; //только понимайте, что он прям впритык его урежет

	 /*
		также при создании вектора можно точно указать сколько там элементов
		vector <int> myVector(10);
		это будут реальные элементы, size уыеличится и capacity тоже. Изначально все неизмененные элементы равны 0! Но и это можно исправить
		vector <int> myVector(10,11); теперь изначально все 11
	 */

	 //данная ф-я вернет нам, если у нас элементы в принципе: false значит есть, true значит нет
	 cout << myVector.empty() << "\n";

	 myVector.clear(); //очистим
	 //аналогично измененниям в конструкторе есть еще и resize, точно тоже самое только не в конструкторе
	 myVector.resize(25, 78);

	 cout << "Кол-во эл. в векторе: " << myVector.size() << "\nСами элементы: \n";
	 for (int i = 0; i < myVector.size(); i++) //и да, мы не долны где либо хранить данные о кол-ве переменных, это автоматически делается
	 {
		 cout << myVector[i] << " ";
	 }
	 cout << endl;

	 //есть еще insert, который позволяет вставить элемент в вектор АБСОЛЮТНО куда нам угодно в нем и erase который удаляет ЛЮБОЙ элемент вектора, естесственно на ваш выбор
	 //только работают они НЕ ЧЕРЕЗ индексы, а через ИНТЕРАТОРЫ, так чтоооо... пока не стоит

	 cout << endl;
	 cout << "ключевое слово auto" << "\n";
	 //C++ сторого типизированный ЯП, нам всего надо прописывать int, real, char и тд
	 //auto позволяет не говорить точно компилятору что ему там поступает и разрешает компилятору самому догадаться что это

	 auto au = 10;

	 //а каким образом коомпилятор воообещ понимает что мы там хотим сделать? На основании того, что мы ему туда присвоили! нельзя просто написать "auto a;" над вами надругаются
	 //тогда зачем она? что это за кусок который только ухудшает читабельность кода?

	 //но кое-где оно вам поможет))) В итераторах, чтобы не прописывать большие куски вызова

	 cout << "\nДвусвязный список\n";
	 //если вы забыли или не прочли что такое односвязный список - прочтите!!! ОНО НАДО
	 //напомню только: связный список работает лучше массива если нам часто надо добавлять или удалять элементы, но если про быстроту выдачи элемента массив лучше

	 //вспомним односвязный список, у нас там связь только в одну сторону (адресс только на 1 элемент), потому он и односвязный. Мы не можем там от последнего элемента дойти 
	 //до середины, только он head
	 //отличие у двусвязного списка же в том, что у него абсолютно другое строение

	 //нода двухсвязного списка хранит в с 3! поля - укаазтель на следующий элемент (pNext), указатель на предыдущий (pPrev), данные

	 //суть такая же как у односвязного списка, он также хаотичен и не имеет порядка, но только в две стороны: каждая нода знает о том какая следующая и предыдущая нода
	 //при этом первая нода в pPrev = Nullptr, а последняя нода pNext = Nullptr

	 //помните проблему односвязного списка? чем дальше нода от head тем дольше мы будем ее искать. В двусвязном ЧАСТИЧНО это решено: в нем есть не только head, но и tail!
	 //получается медленне всего двусвязный список работает в середине, но все равно это быстрее чем с односвязным списком.
		

	 cout << "\nstl - контейнер List\n";
	 //list - это реализация двусвязного списка в stl


	cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
	cout << endl;
	return 0;
}

void Cat::Take_Apple(Apple& apple)
{
	cout << "Take_Apple" << "weight = " << apple.weight << "\t" << "color = " << apple.color << endl;

}

void Cat::Eat_Apple(Apple& apple)
{
	cout << "Кошка съела яблоко - " << apple.color << "\t" << apple.weight << endl;
}

