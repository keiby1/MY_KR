#include "stdafx.h"
#include "iostream"
#include <string>
using namespace std;
/**
*  Номер четки - 86
*  Тип списка - Двусвязный кольцевой список
*  Метод сортировки - Отбор
*/


struct Item {			//структура двусвязного кольцевого списка
	int type;			//тип
	long int address;	//данные
	string desc;		//описание
	int arrAdr[10];		//адреса
	Item *next, *prev;  //указатели
};

void addInfo(Item *d) {	//ввод информации
	cout << "Введите адрес: ";
	cin >> d->address;
	cout << "Введите тип устройства: ";
	cin >> d->type;
	cout << "Введите описание: ";
	cin >> d->desc;
	cout << "Введите адрес соседнего устройства: " << endl;
	int t;
	int i;
	for (i = 0; i < 10; i++) {
		cout << "адрес[" << i << "] = ";
		cin >> t;
		if (t != -1)
			d->arrAdr[i] = t;
		else break;
	}
	cout << endl;
	for (i; i < 10; i++) {
		d->arrAdr[i] = -1;
	}
}

void initialize(Item *d) {	//инициализация
	addInfo(d);
	d->next = d;
	d->prev = d;
}

void addNode(Item *d) {	//добавление в конец списка
	Item *head = d;
	while (d->next != head)
		d = d->next;
	Item *s = new Item;
	addInfo(s);
	s->next = d->next;
	s->prev = d;
	d->next = s;
	s->next->prev = s;
}

string GetType(int i) { //преобразование типа
	switch (i)
	{
	case 1:
		return "ЭВМ";
	case 2:
		return "кабель";
	case 3:
		return "концентратор (хаб, hub)";
	case 4:
		return "коммутатор (свитч, switch)";
	case 5:
		return "сервер";
	case 6: 
		return "сетевой принтер";
	case 7:
		return "маршрутизатор (router)";
	case 8:
		return "внешняя сеть";
	}
	return "";
}

void outInfo(Item *d) {	//вывод на экран значения поля структуры
	cout << "Адрес: " <<  d->address << endl 
		<< "Тип: " << GetType(d->type) << endl
		<< "Описание: " << d->desc << endl
		<< "Соседние адреса: " << endl;
	for (int i = 0; i < 10; i++) {
		if (d->arrAdr[i] == -1)
			break;
		cout << d->arrAdr[i] << " ";
	}
	cout << endl;
}

void outItems(Item *d) {	//проход по всему списку для вывода информации на экран
	Item *head = d;
	bool first = true;
	while (d != head || first == true) {
		outInfo(d);
		cout << endl;
		first = false;
		d = d->next;
	}
	cout << endl;
}

void delItem(Item *d) { //удаление звена
	Item *t = d->next;
	d->next = d->next->next;
	delete t;
}

Item* RemoveItem(Item *d) {//удаление
	long int c;
	Item *head;
	bool f = false;
	cout << "Введите адрес удаляемого элемента: ";
	cin >> c;
	if (d->address == c) {
		head = d->next;
		d->prev->next = head;
		head->prev = d->prev;
		delete d;
		cout << "Удаление прошло успешно" << endl;
	}
	else {
		head = d;
		while (d->next != head) {
			if (d->next->address == c) {
				delItem(d);
				f = true;
				break;
			}
			d = d->next;
		}
		if (f == true)
			cout << "Удаление прошло успешно." << endl;
		else
			cout << "Искомый элемент не найден" << endl;
		cout << "\n";
	}
	return head;
}

void SWAP(Item *id, Item *min) { //обмен элементов
	
	Item *t = new Item;
	t->address = id->next->address;
	t->desc = id->next->desc;
	for (int i = 0; i < 10; i++)
		t->arrAdr[i] = id->next->arrAdr[i];
	t->type = id->next->type;

	id->next->address = min->address;
	id->next->desc = min->desc;
	id->next->type = min->type;
	for (int i = 0; i < 10; i++)
		id->next->arrAdr[i] = min->arrAdr[i];

	min->address = t->address;
	min->desc = t->desc;
	min->type = t->type;
	for (int i = 0; i < 10; i++)
		min->arrAdr[i] = t->arrAdr[i];

	/*
	t->next = i->next;
	t->prev = i->prev;

	i->next = min->next;
	i->prev = min->prev;

	min->next = t->next;
	min->prev = t->prev;*/
}

void Sort(Item *d) {		//сортировка
	Item *head = d;
	Item *i = head;
	Item *j = head;

	do {
		Item *min = i;
		do {
			if (j->address < min->address) {
				min = j;
			}
			j = j->next;
		} while (j != head);

		SWAP(i, min);

		j = head;
		i = i->next;
	} while (i != head);
	cout << "Готово!" << endl << endl;
}

void Insert(Item *d, Item *p) { //вставка элемента
	Item *t = new Item;
	t->address = p->address;
	for(int i =0;i < 10; i++)
		t->arrAdr[i] = p->arrAdr[i];
	t->desc = p->desc;
	t->type = p->type;
	t->next = d->next;
	t->prev = d;
	d->next->prev = p;
	d->next = p;
}

/* Пузырьковая сортировка с удалением и дополнением
void Sort(Item *d)
{
	Item *head = d;
	Item *j = head, *i = head;
	do {
		do {
			if (i->address < j->address && i != head && j != head) {
				cout << i->address << " vs " << j->address << endl;
				Insert(i, j);
				delItem(j);
			}
			j = j->next;
		} while (j != head);
		j = head;
		i = i->next;
	} while (i != head);
}
*/

void search(Item *d) {			//поиск в списке
	long int data;
	cout << "Введите адрес: ";
	cin >> data;

	bool finded = false;
	Item *head = d;
	bool first = true;
	while (d != head || first == true) {
		if (d->address == data)
		{
			cout << "Найдено: " << endl;
			outInfo(d);
			cout << endl;
			finded = true;
			break;
		}
		first = false;
		d = d->next;
	}
	if (finded == false)
		cout << "Ничего не найдено!\n" << endl;

}

void menu() {		//меню
	Item *d = new Item;
	initialize(d);

	bool fl = true;
	int key;

	while (fl) {
		cout << "1-Просмотреть элементы" << endl;
		cout << "2-Вставка элемента" << endl;
		cout << "3-Удалить элемет" << endl;
		cout << "4-Поиск элемента" << endl;
		cout << "5-Сортировка элементов" << endl;
		cout << "6-Выход" << endl;
		cout << "\n>>";
		cin >> key;
		switch (key) {
		case 1:
			outItems(d);						//Просмотреть содержимое списка.
			break;
		case 2:
			addNode(d);				//добавление узла в конец
			break;
		case 3:
			d = RemoveItem(d);						//Удалить звено из середины списка, используя операцию поиска данных в списке.
			break;
		case 4:
			search(d);						//поиск узла
			break;
		case 5:
			Sort(d);						//сортировка
			break;
		case 6:								//выход из приложения
			fl = false;
			break;
		}
	}
}

int main()			//начало
{
	setlocale(LC_ALL, "");
	menu();
	system("pause");
	return 0;
}
