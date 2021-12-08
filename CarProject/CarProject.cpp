#include <iostream>
#include "CarRepair.h"

UserInterface::UserInterface()
{

}
UserInterface::~UserInterface()
{

}
void UserInterface::Menu()
{
	while (true)
	{
		cout << "Добро пожаловать" << endl;
		cout << "1. Добавить запись" << endl;
		cout << "2. Посмотреть расписание" << endl;
		cout << "3. Редактировать расписание" << endl;
		cout << "4. Посмотреть прайс-лист" << endl;
		cout << "5. Ввести расходы" << endl;
		cout << "6. Посмотреть таблицу расходов" << endl;
		cout << "7. Посмотреть отчет за период" << endl;
		cout << "8. Выход" << endl;
		cout << "Введите цифру нужного пункта" << endl;
		cin >> choice;

		switch (choice)
		{
		case '1':
		{
			cout << "добавление записи" << endl;
			break;
		}
		case '2':
		{
			cout << "Расписание" << endl;
			break;
		}
		case '3':
		{
			cout << "Редактирование расписания" << endl;
			break;
		}
		case '4':
		{
			cout << "Прайс-лист" << endl;
			break;
		}
		case '5':
		{
			cout << "Ввод расходов" << endl;
			break;
		}
		case '6':
		{
			cout << "Таблица расходов" << endl;
			break;
		}
		case '7':
		{
			cout << "Отчет за период" << endl;
			break;
		}
		case '8':
		{
			cout << "Пока" << endl;
			return;
			break;
		}
		default:
		{
			cout << "Нет такого пункта" << endl;
			break;
		}
		} 
	} 
} 