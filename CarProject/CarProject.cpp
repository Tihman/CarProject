#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "CarRepair.h"

using namespace std;

UserInterface::UserInterface()
{
	ptrTimeTable = new TimeTable;
	ptrExpensesTable = new ExpensesTable;
	ptrTimeTable->LoadFile();
	ptrExpensesTable->LoadExpenses();

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
		system("cls");
		switch (choice)
		{
		case '1':
		{
			cout << "Добавление записи" << endl;
			ptrAddClientScreen = new AddClientScreen(ptrTimeTable);
			ptrAddClientScreen->setClient();
			delete ptrAddClientScreen;
			system("pause");
			break;
		}
		case '2':
		{
			char ch;
			cout << "Расписание" << endl;
			cout << "ИмяКлиента" << "| |"<< "ФамилияКлиента" << "| |"<< "МаркаМашины" << "| |" <<"МодельМашины" << "| |" << "НазваниеУслуги"  << "| |" << left << setw(20) << "ВремяЗаписи" << "| |" << "СтоимостьУслуги" << endl;
			ptrTimeTable->ShowTimeTable();
			cout << "Хотите сохранить данные? (y/n)" << endl;
			cin >> ch;
			if (ch == 'y')
			{
				ptrTimeTable->SaveFile();
			}
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
			cout << "НомерУслуги" << "| |" << left << setw(20) << "НазваниеУслуги" << "| |" << "СтоимостьУслуги" << endl;
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
			char ch;
			cout << "Таблица расходов" << endl;
			cout << left << setw(10) << "Расход" << "| | " << "ДатаРасхода" << "| | " << "СуммаРасхода" << endl;
			ptrExpensesTable->ShowExpensesTable();
			cout << "Хотите сохранить данные? (y/n)" << endl;
			cin >> ch;
			if (ch == 'y')
			{
				ptrExpensesTable->SaveExpenses();
			}
			system("pause");
			break;
		}
		case '7':
		{
			cout << "Отчет за период" << endl;
			ptrReport = new Report(ptrTimeTable, ptrExpensesTable);
			ptrReport->ShowReport();
			delete ptrReport;
			system("Pause");
			break;
		}
		case '8':
		{
			char ch;
			cout << "До свидания" << endl;
			cout << "Хотите сохранить данные? (y/n)" << endl;
			cin >> ch;
			if (ch == 'y')
			{
				ptrTimeTable->SaveFile();
				ptrExpensesTable->SaveExpenses();
			}
			return;
			break;
		}
		default:
		{
			cout << "Нет такого пункта" << endl;
			system("pause");
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
	
	PriceList PList;
	PList.ShowPrices();
	cout << "Введите Номер услуги: " << endl;
	cin >> SerNum;
	//ifstream in (".\\PriceList.txt"); //for .exe
	ifstream in ("../PriceList.txt");
	
	if (in.is_open())
	{
		while (getline(in, line))
		{

			if (line.find(to_string(SerNum)) != string::npos)
			{
				string s1[3];
				int j = 0;
				for (int i = 0; i <= 2; i++)
				{
					while (line[j] != ';')
					{
						s1[i] = s1[i] + line[j];
						j++;
					}
					j++;
				}
				SerName = s1[1];
				SerPrice = stof(s1[2]);
			}
		}
	}
	in.close();

	cout << "Введите дату выполнения услуги(YYYY MM DD hh mm):" << endl;
	bool search = true;
	bool write;
	while (search)
	{
		cin >> year;
		cin >> month;
		cin >> day;
		cin >> hour;
		cin >> minute;
		write = true;
		if (ptrTimeTable->ptrClientRecord.empty())
			//запись даты, так как нет записей
			search = false;
		else
		{
			ptrTimeTable->iter = ptrTimeTable->ptrClientRecord.begin();
			while (ptrTimeTable->iter != ptrTimeTable->ptrClientRecord.end() && write)
			{
				if (year == (*ptrTimeTable->iter)->getYear() && month == (*ptrTimeTable->iter)->getMonth() && day == (*ptrTimeTable->iter)->getDay() && hour == (*ptrTimeTable->iter)->getHour() && minute == (*ptrTimeTable->iter)->getMinute())
				{
					cout << "Запись на эту дату уже существует." << endl;
					write = false;
				}
				*ptrTimeTable->iter++;
			}
			if (write)
			{
				//запись даты, так как нет совпадений
				search = false;
			}
		}
	}
		
	ClientRecord* ptrClientRecord = new ClientRecord(ClFirstName, ClSecondName, CBrand, CModel, SerName, year, month, day, hour, minute, SerPrice);
	ptrTimeTable->InsertClient(ptrClientRecord);	
}

void PriceList::ShowPrices()
{
	//ifstream in (".\\PriceList.txt"); //for .exe
	ifstream in ("../PriceList.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			string s1[3];
			int j = 0;
			for (int i = 0; i <= 2; i++)
			{
				while (line[j] != ';')
				{
					s1[i] = s1[i] + line[j];
					j++;
				}
				j++;
			}
			RecordNum = atoi(s1[0].c_str());
			ServiceName = s1[1];
			ServicePrice = stof(s1[2]);
			cout << left << setw(10) << RecordNum << " | | " << setw(18) << ServiceName << " | | " << ServicePrice << endl;
		}
		
	}
	in.close();     
}

ClientRecord::ClientRecord(string ClFN, string ClSN, string CB, string CM, string SN,
	unsigned int yy, unsigned int mm, unsigned int dd, unsigned int hh, unsigned int mint, float SP) : //конструктор
	ClFirstName(ClFN), ClSecondName(ClSN), CBrand(CB), CModel(CM), SerName(SN), year(yy), month(mm),
	day(dd), hour(hh), minute(mint), SerPrice(SP)
{

}

ClientRecord::~ClientRecord() 
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
	if (ptrClientRecord.empty()) 
		cout << "Нет записей\n" << endl; 
	else
	{
		iter = ptrClientRecord.begin();
		while (iter != prev(ptrClientRecord.end()))
		{
			iter2 = next(iter);
			while (iter2 != ptrClientRecord.end())
			{
				if ((*iter)->getYear() >= (*iter2)->getYear())
				{
					swap(*iter, *iter2);
				}
				*iter2++;
			}
			*iter++;
		}
		iter = ptrClientRecord.begin();
		while (iter != prev(ptrClientRecord.end()))
		{
			iter2 = next(iter);
			while (iter2 != ptrClientRecord.end())
			{
				if ((*iter)->getMonth() >= (*iter2)->getMonth() && (*iter)->getYear() == (*iter2)->getYear())
				{
					swap(*iter, *iter2);
				}
				*iter2++;
			}
			*iter++;
		}
		iter = ptrClientRecord.begin();
		while (iter != prev(ptrClientRecord.end()))
		{
			iter2 = next(iter);
			while (iter2 != ptrClientRecord.end())
			{
				if ((*iter)->getDay() >= (*iter2)->getDay() && (*iter)->getMonth() == (*iter2)->getMonth() && (*iter)->getYear() == (*iter2)->getYear())
				{
					swap(*iter, *iter2);
				}
				*iter2++;
			}
			*iter++;
		}
		iter = ptrClientRecord.begin();
		while (iter != prev(ptrClientRecord.end()))
		{
			iter2 = next(iter);
			while (iter2 != ptrClientRecord.end())
			{
				if ((*iter)->getHour() >= (*iter2)->getHour() && (*iter)->getDay() == (*iter2)->getDay() && (*iter)->getMonth() == (*iter2)->getMonth() && (*iter)->getYear() == (*iter2)->getYear())
				{
					swap(*iter, *iter2);
				}
				*iter2++;
			}
			*iter++;
		}
		iter = ptrClientRecord.begin();
		while (iter != prev(ptrClientRecord.end()))
		{
			iter2 = next(iter);
			while (iter2 != ptrClientRecord.end())
			{
				if ((*iter)->getMinute() >= (*iter2)->getMinute() && (*iter)->getHour() == (*iter2)->getHour() && (*iter)->getDay() == (*iter2)->getDay() && (*iter)->getMonth() == (*iter2)->getMonth() && (*iter)->getYear() == (*iter2)->getYear())
				{
					swap(*iter, *iter2);
				}
				*iter2++;
			}
			*iter++;
		}
		iter = ptrClientRecord.begin();
		while (iter != ptrClientRecord.end()) 
		{
			cout << left << setw(10) << (*iter)->getClientFirstName() << "| |" << setw(14) << (*iter)->getClientSecondName() << "| |" << setw(11) << (*iter)->getCarBrand() << "| |" <<  setw(12) <<(*iter)->getCarModel() << "| |" <<  setw(14) << (*iter)->getServiceName() << "| |";
			cout << left <<  setw(1) <<(*iter)->getYear() << "-";
			if ((*iter)->getMonth()<10)
			{
				cout << left << "0" << setw(1) << (*iter)->getMonth() << "-";
			}
			else
			{
				cout << left << setw(1) <<  (*iter)->getMonth() <<"-";
			}
			if ((*iter)->getDay() < 10)
			{
				cout << left << "0" << setw(1) << (*iter)->getDay() <<" ";
			}
			else
			{
				cout << left << setw(1) << (*iter)->getDay() <<" ";
			}
			if ((*iter)->getHour() < 10)
			{
				cout << left << "0" << setw(1) << (*iter)->getHour() <<":";
			}
			else
			{
				cout << left << setw(1) << (*iter)->getHour() << ":";
			}
			if ((*iter)->getMinute() < 10)
			{
				cout << left << "0" << setw(5) << (*iter)->getMinute() << "| |";
			}
			else
			{
				cout << left << setw(6) <<  (*iter)->getMinute() << "| |";
			}
			cout << left << (*iter)->getServicePrice() << endl;
			*iter++;
		}
	}
}
void TimeTable::SaveFile()
{
	ofstream out; 
	// (".\\PriceList.txt"); //for .exe
	out.open("../TimeTable.txt"); 
	if (out.is_open())
	{
		if (ptrClientRecord.empty()) 
			cout << "Нет записей\n" << endl; 
		else
		{
			iter = ptrClientRecord.begin();
			while (iter != ptrClientRecord.end()) 
			{
				out << (*iter)->getClientFirstName() << ";" << (*iter)->getClientSecondName() << ";" << (*iter)->getCarBrand() << ";" << (*iter)->getCarModel() << ";"
					<< (*iter)->getServiceName() << ";" << (*iter)->getYear() << ";" << (*iter)->getMonth() << ";" << (*iter)->getDay() << ";" << (*iter)->getHour() << ";"
					<< (*iter)->getMinute() << ";" << (*iter)->getServicePrice() << ";" << endl;
				*iter++;
			}
		}
	}

}

void TimeTable::LoadFile()
{
	string line;
	// (".\\PriceList.txt"); //for .exe
	ifstream in("../TimeTable.txt"); 
	if (in.is_open())
	{
		while (getline(in, line))
		{
			string s1[11];
			int j = 0;
			for (int i = 0; i <= 10; i++)
			{
				while (line[j] != ';')
				{
					s1[i] = s1[i] + line[j];
					j++;
				}
				j++;
			}
			ClFirstName = s1[0];
			ClSecondName = s1[1];
			CBrand = s1[2];
			CModel = s1[3];
			SerName = s1[4];
			year = atoi(s1[5].c_str());
			month = atoi(s1[6].c_str());
			day = atoi(s1[7].c_str());
			hour = atoi(s1[8].c_str());
			minute = atoi(s1[9].c_str());
			SerPrice = stof(s1[10]);
			ClientRecord* ptrClientRecord = new ClientRecord(ClFirstName, ClSecondName, CBrand, CModel, SerName, year, month, day, hour, minute, SerPrice);
			InsertClient(ptrClientRecord);
		}
	}
	in.close();     
}

void ExpensesTable::LoadExpenses()
{
	string line;
	// (".\\PriceList.txt"); //for .exe
	ifstream in("../ExpensesTable.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			string s1[5];
			int j = 0;
			for (int i = 0; i <= 4; i++)
			{
				while (line[j] != ';')
				{
					s1[i] = s1[i] + line[j];
					j++;
				}
				j++;
			}
			Product = s1[0];
			year = atoi(s1[1].c_str());
			month = atoi(s1[2].c_str());
			day = atoi(s1[3].c_str());
			Cost = stof(s1[4]);
			Expenses* ptrExpenses = new Expenses(Product, year, month, day, Cost);
			insertExpenses(ptrExpenses);
		}
	}
	in.close();
}

void ExpensesTable::SaveExpenses()
{
	ofstream out;
	// (".\\PriceList.txt"); //for .exe
	out.open("../ExpensesTable.txt");
	if (out.is_open())
	{
		if (vecptrExpenses.empty())
			cout << "Нет расходов\n" << endl;
		else
		{
			iter = vecptrExpenses.begin();
			while (iter != vecptrExpenses.end())
			{
				out << (*iter)->Product << ";" << (*iter)->year << ";" << (*iter)->month << ";" << (*iter)->day << ";"<< (*iter)->Cost << ";" << endl;
				*iter++;
			}
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
	if (vecptrExpenses.size() == 0) 
		cout << "Расходов нет\n" << endl;
	else
	{
		iter = vecptrExpenses.begin();
		while (iter != vecptrExpenses.end())
		{ 
			cout << left << setw(9) << (*iter)->Product << " | | " << (*iter)->year << "-" << (*iter)->month << "-" << (*iter)->day << " | | " << (*iter)->Cost << endl;
			iter++;
		}
		cout << endl;
	}
}

AddExpensesScreen::AddExpensesScreen(ExpensesTable* ExpTab) : ptrExpensesTable(ExpTab)
{

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

void EditClientScreen::EditInfo(unsigned int YY, unsigned int MM, unsigned int DD, unsigned int hh, unsigned int mm)
{
	bool search = true;
	int choice;
	if (ptrTimeTable->ptrClientRecord.empty()) 
		cout << "Нет записей" << endl; 
	else
	{
		ptrTimeTable->iter = ptrTimeTable->ptrClientRecord.begin();
		while (search == true && ptrTimeTable->iter != ptrTimeTable->ptrClientRecord.end())
		{
			if (YY == (*ptrTimeTable->iter)->getYear() && MM == (*ptrTimeTable->iter)->getMonth() && DD == (*ptrTimeTable->iter)->getDay() && hh == (*ptrTimeTable->iter)->getHour() && mm == (*ptrTimeTable->iter)->getMinute())
			{
				search = false;
			}
			else
			{
				*ptrTimeTable->iter++;
			}
		}
		ClFirstName = (*ptrTimeTable->iter)->getClientFirstName();
		ClSecondName = (*ptrTimeTable->iter)->getClientSecondName();
		CBrand = (*ptrTimeTable->iter)->getCarBrand();
		CModel = (*ptrTimeTable->iter)->getCarModel();
		SerName = (*ptrTimeTable->iter)->getServiceName();
		year = (*ptrTimeTable->iter)->getYear();
		month = (*ptrTimeTable->iter)->getMonth();
		day = (*ptrTimeTable->iter)->getDay();
		hour = (*ptrTimeTable->iter)->getHour();
		minute = (*ptrTimeTable->iter)->getMinute();
		SerPrice = (*ptrTimeTable->iter)->getServicePrice();
		delete* ptrTimeTable->iter;
		ptrTimeTable->iter = ptrTimeTable->ptrClientRecord.erase(ptrTimeTable->iter);
		while (true)
		{
			cout << "Выберите данные для изменения:" << endl;
			cout << "1. Имя:" << ClFirstName << endl;
			cout << "2. Фамилия:" << ClSecondName << endl;
			cout << "3. Марка машины:" << CBrand << endl;
			cout << "4. Модель машины:" << CModel << endl;
			cout << "5. Услуга:" << SerName << endl;
			cout << "6. Дата исполнения услуги:" << year << "-" << month << "-" << day << " " << hour << ":" << minute << endl;
			cout << "7. Сохранить и выйти" << endl;
			cout << "Введите цифру нужного пункта:" << endl;
			cin >> choice;
			system("cls");
			switch (choice)
			{
			case 1:
			{
				cout << "Введите Имя:" << endl;
				cin >> ClFirstName;
				break;
			}
			case 2:
			{
				cout << "Введите Фамилию:" << endl;
				cin >> ClSecondName;
				break;
			}
			case 3:
			{
				cout << "Введите марку машины:" << endl;
				cin >> CBrand;
				break;
			}
			case 4:
			{
				cout << "Введите модель машины:" << endl;
				cin >> CModel;
				break;
			}
			case 5:
			{
				PriceList PList;
				PList.ShowPrices();
				cout << "Введите Номер услуги: " << endl;
				cin >> SerNum;
				//ifstream in (".\\PriceList.txt"); //for .exe
				ifstream in("../PriceList.txt");

				if (in.is_open())
				{
					while (getline(in, line))
					{
						if (line.find(to_string(SerNum)) != string::npos) {
							SerName = line.substr(3, 13);
							SerPrice = stof(line.substr(16, 4));
						}
					}
				}
				in.close();
				break;
			}
			case 6:
			{
				cout << "Введите дату выполнения услуги(YYYY MM DD hh mm):" << endl;
				bool search = true;
				bool write;
				while (search)
				{
					cin >> YY;
					cin >> MM;
					cin >> DD;
					cin >> hh;
					cin >> mm;
					write = true;
					if (ptrTimeTable->ptrClientRecord.empty())
						//запись даты, так как нет записей
						search = false;
					else
					{
						ptrTimeTable->iter = ptrTimeTable->ptrClientRecord.begin();
						while (ptrTimeTable->iter != ptrTimeTable->ptrClientRecord.end() && write)
						{
							if (YY == (*ptrTimeTable->iter)->getYear() && MM == (*ptrTimeTable->iter)->getMonth() && DD == (*ptrTimeTable->iter)->getDay() && hh == (*ptrTimeTable->iter)->getHour() && mm == (*ptrTimeTable->iter)->getMinute())
							{
								cout << "Запись на эту дату уже существует." << endl;
								write = false;
							}
							*ptrTimeTable->iter++;
						}
						if (write)
						{
							//запись даты, так как нет совпадений
							search = false;
						}
					}
				}
				break;
			}
			case 7:
			{
				ClientRecord* ptrClientRecord = new ClientRecord(ClFirstName, ClSecondName, CBrand, CModel, SerName, year, month, day, hour, minute, SerPrice);
				ptrTimeTable->InsertClient(ptrClientRecord);
				cout << "Данные успешно изменены" << endl;
				return;
				break;
			}
			default:
			{
				cout << "Нет такого пункта" << endl;
				system("pause");
				break;
			}
			}
			system("cls");
		}
	}
}

void DeleteClientScreen::DeleteClient(unsigned int YY, unsigned int MM, unsigned int DD, unsigned int hh, unsigned int mm)
{
	char conf;
	if (ptrTimeTable->ptrClientRecord.empty()) 
		cout << "Нет записей" << endl;
	else
	{
		ptrTimeTable->iter = ptrTimeTable->ptrClientRecord.begin();
		while (ptrTimeTable->iter != ptrTimeTable->ptrClientRecord.end())
		{
			if (YY == (*ptrTimeTable->iter)->getYear() && MM == (*ptrTimeTable->iter)->getMonth() && DD == (*ptrTimeTable->iter)->getDay() && hh == (*ptrTimeTable->iter)->getHour() && mm == (*ptrTimeTable->iter)->getMinute())
			{
				cout << "Уверены ли вы в удалении данной записи?(y/n)" << endl;
				cin >> conf;
				if (conf=='y')
				{
					delete* ptrTimeTable->iter;
					ptrTimeTable->iter = ptrTimeTable->ptrClientRecord.erase(ptrTimeTable->iter);
					cout << "Запись успешно удалена" << endl;
				}
			}
			*ptrTimeTable->iter++;
		}
	}
}

void EditDeleteScreen::getRecordDate()
{
	cout << "Введите дату записи, которую хотите редактировать(YYYY MM DD hh mm):" << endl;
	cin >> year;
	cin >> month;
	cin >> day;
	cin >> hour;
	cin >> minute;
	cout << "Изменить - 1\nУдалить - 2\nВыбор:" << endl;
	cin >> choice;
	system("cls");
	switch (choice)
	{
	case 1:
	{
		
		ptrEditClientScreen = new EditClientScreen(ptrTimeTable);
		ptrEditClientScreen->EditInfo(year, month, day, hour, minute);
		delete ptrEditClientScreen;
		system("Pause");
		break;
	}
	case 2:
	{
		ptrDeleteClientScreen = new DeleteClientScreen(ptrTimeTable);
		ptrDeleteClientScreen->DeleteClient(year, month, day, hour, minute);
		delete ptrDeleteClientScreen;
		system("Pause");
		break;
	}
	default:
		cout << "Нет такого пункта" << endl;
		system("pause");
		break;
	}
}

void Report::ShowReport()
{
	cout << "Введите начальную дату (YYYY MM DD): " << endl;
	cin >> year1;
	cin >> month1;
	cin >> day1;
	cout << "Введите конечную дату (YYYY MM DD): " << endl;
	cin >> year2;
	cin >> month2;
	cin >> day2;

    Revenue = 0;

		ptrTimeTable->iter = ptrTimeTable->ptrClientRecord.begin();
		while (ptrTimeTable->iter != ptrTimeTable->ptrClientRecord.end())
		{
			if (year1 == (*ptrTimeTable->iter)->getYear())
			{
				if (month1 == (*ptrTimeTable->iter)->getMonth())
				{
					if (day1 <= (*ptrTimeTable->iter)->getDay())
					{
						Revenue += (*ptrTimeTable->iter)->getServicePrice();
					}
				}
				else if (month1 < (*ptrTimeTable->iter)->getMonth())
				{
					Revenue += (*ptrTimeTable->iter)->getServicePrice();
				}
			}
			else if (year1 < (*ptrTimeTable->iter)->getYear() && year2 >(*ptrTimeTable->iter)->getYear())
			{
				Revenue += (*ptrTimeTable->iter)->getServicePrice();
			}
			else if (year2 == (*ptrTimeTable->iter)->getYear())
			{
				if (month2 == (*ptrTimeTable->iter)->getMonth())
				{
					if (day2 >= (*ptrTimeTable->iter)->getDay())
					{
						Revenue += (*ptrTimeTable->iter)->getServicePrice();
					}
				}
				else if (month2 > (*ptrTimeTable->iter)->getMonth())
				{
					Revenue += (*ptrTimeTable->iter)->getServicePrice();
				}
			}
			*ptrTimeTable->iter++;
		}

	Expenses = 0;

		ptrExpensesTable->iter = ptrExpensesTable->vecptrExpenses.begin();
		while (ptrExpensesTable->iter != ptrExpensesTable->vecptrExpenses.end())
		{
			if (year1 == (*ptrExpensesTable->iter)->year)
			{
				if (month1 == (*ptrExpensesTable->iter)->month)
				{
					if (day1 <= (*ptrExpensesTable->iter)->day)
					{
						Expenses += (*ptrExpensesTable->iter)->Cost;
					}
				}
				else if (month1 < (*ptrExpensesTable->iter)->month)
				{
					Expenses += (*ptrExpensesTable->iter)->Cost;
				}
			}
			else if (year1 < (*ptrExpensesTable->iter)->year && year2 >(*ptrExpensesTable->iter)->year)
			{
				Expenses += (*ptrExpensesTable->iter)->Cost;
			}
			else if (year2 == (*ptrExpensesTable->iter)->year)
			{
				if (month2 == (*ptrExpensesTable->iter)->month)
				{
					if (day2 >= (*ptrExpensesTable->iter)->day)
					{
						Expenses += (*ptrExpensesTable->iter)->Cost;
					}
				}
				else if (month2 > (*ptrExpensesTable->iter)->month)
				{
					Expenses += (*ptrExpensesTable->iter)->Cost;
				}
			}
			*ptrExpensesTable->iter++;
		}

	Profit = Revenue - Expenses;

	cout << "Доходы за указанный период: " << Revenue << endl;
	cout << "Расходы за указанный период: " << Expenses << endl;
	cout << "Выручка за указанный период: " << Profit << endl;
}