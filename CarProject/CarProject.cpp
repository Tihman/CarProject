#include <stdio.h>
#include <iostream>
#include <fstream>
#include "CarRepair.h"

using namespace std;

UserInterface::UserInterface()
{
	ptrTimeTable = new TimeTable;
	ptrExpensesTable = new ExpensesTable;
	//ptrEditDeleteScreen = new EditDeleteScreen;

}
UserInterface::~UserInterface()
{

}
void UserInterface::Menu()
{
	cout << "Добро пожаловать" << endl;
	while (true)
	{
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
			ptrAddClientScreen = new AddClientScreen(ptrTimeTable);
			ptrAddClientScreen->setClient();
			delete ptrAddClientScreen;
			system("pause");
			break;
		}
		case '2':
		{
			cout << "Расписание" << endl;
			cout << "НомерЗаписи\tИмяКлиента\tУслуга\tСтоимостьУслуги\tВремяЗаписи" << endl;
			ptrTimeTable->ShowTimeTable();
			system("pause");
			break;
		}
		case '3':
		{
			cout << "Редактирование расписания" << endl;
			ptrEditDeleteScreen = new EditDeleteScreen(ptrTimeTable);
			ptrTimeTable->ShowTimeTable();
			ptrEditDeleteScreen->getRecordDate();
			delete ptrEditDeleteScreen;
			break;
		}
		case '4':
		{
			cout << "Прайс-лист" << endl;
			PriceList a;
			a.ShowPrices();
			system("pause");
			break;
		}
		case '5':
		{
			cout << "Ввод расходов" << endl;
			ptrAddExpensesScreen = new AddExpensesScreen(ptrExpensesTable);
			ptrAddExpensesScreen->setExpenses();
			delete ptrAddExpensesScreen;
			system("pause");
			break;
		}
		case '6':
		{
			cout << "Таблица расходов" << endl;
			ptrExpensesTable->ShowExpensesTable();
			system("pause");
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
		system("cls");
	}
} 

void AddClientScreen::setClient()
{
	cout << "Введите Имя и Фамилию клиента:" << endl;
	cin >> ClFirstName;
	cin >> ClSecondName;
	cout << "Введите марку и модель машины:" << endl;
	cin >> CBrand;
	cin >> CModel;
	PriceList a;
	a.ShowPrices();
	cout << "Введите Номер услуги: " << endl;
	cin >> SerNum;
	//ifstream in (".\\PriceList.txt"); //for .exe
	ifstream in ("../PriceList.txt");
	
	if (in.is_open())
	{
		while (getline(in, line))
		{
			if (line.find(to_string(SerNum)) != string::npos) {
				SerName = line.substr(3, 13);
				SerPrice= stof(line.substr(16, 4));
			}
		}
	}
	in.close();

	cout << "Введите дату выполнения услуги(YYYY MM DD hh mm):" << endl;
	cin >> year;
	cin >> month;
	cin >> day;
	cin >> hour;
	cin >> minute;
	
	//debug
	/*
	cout << ClFirstName << endl;
	cout << ClSecondName << endl;
	cout << CBrand << endl;
	cout << CModel << endl;
	cout << SerNum << endl;  
	cout << SerName << endl; 
	cout << SerPrice << endl;
	cout << year << month << day << hour << minute << endl;
	*/
	
	ClientRecord* ptrClientRecord = new ClientRecord(ClFirstName, ClSecondName, CBrand, CModel, SerName, year, month, day, hour, minute, SerPrice);
	ptrTimeTable->InsertClient(ptrClientRecord);
	

}
void PriceList::ShowPrices()
{
	//ifstream in (".\\PriceList.txt"); //for .exe
	ifstream in ("../PriceList.txt");
	if (in.is_open())
	{
		while (getline(in, ServiceName))
		{
			cout << ServiceName << endl;
		}
	}
	in.close();     // закрываем файл
}

ClientRecord::ClientRecord(string ClFN, string ClSN, string CB, string CM, string SN,
	unsigned int yy, unsigned int mm, unsigned int dd, unsigned int hh, unsigned int mint, float SP) : //конструктор
	ClFirstName(ClFN), ClSecondName(ClSN), CBrand(CB), CModel(CM), SerName(SN), year(yy), month(mm),
	day(dd), hour(hh), minute(mint), SerPrice(SP)
{

}

ClientRecord::~ClientRecord() //деструктор
{

}

string ClientRecord::getClientFirstName()
{
	return ClFirstName;
}

string ClientRecord::getClientSecondName()
{
	return ClSecondName;
}

string ClientRecord::getCarBrand()
{
	return CBrand;
}

string ClientRecord::getCarModel()
{
	return CModel;
}

string ClientRecord::getServiceName()
{
	return SerName;
}

unsigned int ClientRecord::getYear()
{
	return year;
}

unsigned int ClientRecord::getMonth()
{
	return month;
}

unsigned int ClientRecord::getDay()
{
	return day;
}

unsigned int ClientRecord::getHour()
{
	return hour;
}

unsigned int ClientRecord::getMinute()
{
	return minute;
}

float ClientRecord::getServicePrice()
{
	return SerPrice;
}

void TimeTable::ShowTimeTable()
{
	//cout << "\nApt#\tИмя жильца\n-------------------\n";
	if (ptrClientRecord.empty()) // если список жильцов пуст
		cout << "Нет жильцов\n" << endl; // выводим запись, что он пуст)
	else
	{
		iter = ptrClientRecord.begin();
		while (iter != ptrClientRecord.end()) // распечатываем всех жильцов
		{
			cout << (*iter)->getClientFirstName() << " " << (*iter)->getClientSecondName() << " | | " << (*iter)->getCarBrand() << " " << (*iter)->getCarModel() << " | | "
				<< (*iter)->getServiceName() << " | | " << (*iter)->getYear() << "-" << (*iter)->getMonth() << "-" << (*iter)->getDay() << " " << (*iter)->getHour() << ":"
				<< (*iter)->getMinute() << " | | " << (*iter)->getServicePrice() << endl;
			*iter++;
		}
	}
}

void TimeTable::InsertClient(ClientRecord* ptrCR)
{
	ptrClientRecord.push_back(ptrCR);
}

void ExpensesTable::insertExpenses(Expenses* ptrExp)
{
	vecptrExpenses.push_back(ptrExp);
}

void ExpensesTable::ShowExpensesTable()
{
	//cout << "\nДата\tПолучатель\tСумма\tКатегория\n" << "----------------------------------------\n" << endl;
	if (vecptrExpenses.size() == 0) 
		cout << "Расходов нет\n" << endl;
	else
	{
		iter = vecptrExpenses.begin();
		while (iter != vecptrExpenses.end())
		{ 
			cout << (*iter)->Product << " | | " << (*iter)->year << "-" << (*iter)->month << "-" << (*iter)->day << " | | " << (*iter)->Cost << endl;
			iter++;
		}
		cout << endl;
	}
}

AddExpensesScreen::AddExpensesScreen(ExpensesTable* ExpTab) : ptrExpensesTable(ExpTab)
{
	/*пусто*/
}

void AddExpensesScreen::setExpenses()
{
	cout << "Введите что израсходовали: ";
	cin >> Product;
	cout << "Введите дату расхода(YYYY MM DD): ";
	cin >> year;
	cin >> month;
	cin >> day;
	cout << "Введите стоимость расхода: ";
	cin >> Cost;
	Expenses* ptrExpenses = new Expenses(Product, year, month, day, Cost);
	ptrExpensesTable->insertExpenses(ptrExpenses);
}

EditDeleteScreen::~EditDeleteScreen()
{

}



void DeleteClientScreen::DeleteClient(unsigned int YY, unsigned int MM, unsigned int DD, unsigned int hh, unsigned int mm, TimeTable* ptrTimeTable)
{
	if (ptrTimeTable->ptrClientRecord.empty()) // если список жильцов пуст
		cout << "Нет записей" << endl; // выводим запись, что он пуст)
	else
	{
		ptrTimeTable->iter = ptrTimeTable->ptrClientRecord.begin();
		while (ptrTimeTable->iter != ptrTimeTable->ptrClientRecord.end())
		{
			if (YY == (*ptrTimeTable->iter)->getYear() && MM == (*ptrTimeTable->iter)->getMonth() && DD == (*ptrTimeTable->iter)->getDay() && hh == (*ptrTimeTable->iter)->getHour() && mm == (*ptrTimeTable->iter)->getMinute())
			{
				//деструктор
				delete *ptrTimeTable->iter;
				ptrTimeTable->iter = ptrTimeTable->ptrClientRecord.erase(ptrTimeTable->iter);
				cout << "Запись успешно удалена" << endl;
			}
			else
			{
				*ptrTimeTable->iter++;
			}
		}
	}
}

void EditDeleteScreen::getRecordDate()
{
	//ptrTimeTable->ShowTimeTable();
	cout << "Введите дату записи, которую хотите редактировать(YYYY MM DD hh mm):" << endl;
	cin >> year;
	cin >> month;
	cin >> day;
	cin >> hour;
	cin >> minute;
	cout << "Изменить - 1\nУдалить - 2\nВыбор:" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		//ptrEditClientScreen = new EditClientScreen();
		//ptrEditClientScreen->EditInfo();
		//delete ptrEditClientScreen;
		cout << "1" << endl;
	}
	case 2:
	{
		ptrDeleteClientScreen = new DeleteClientScreen();
		ptrDeleteClientScreen->DeleteClient(year, month, day, hour, minute, ptrTimeTable);
		delete ptrDeleteClientScreen;
		system("Pause");
		break;
	}
	default:
		cout << "3" << endl;
		break;
	}
}

