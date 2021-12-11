#include <iostream>
#include <fstream>
#include "CarRepair.h"

using namespace std;

void getaLine(string& inStr) // получение строки текста
{
	char temp[21];
	cin.get(temp, 20, '\n');
	cin.ignore(20, '\n'); //число пропускаемых символов и символ разделения
	inStr = temp;
}

UserInterface::UserInterface()
{

}
UserInterface::~UserInterface()
{

}
void UserInterface::Menu()
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
			AddClientScreen b;
			b.setClient();
			break;
		}
		case '2':
		{
			cout << "Расписание" << endl;
			cout << "НомерЗаписи\tИмяКлиента\tУслуга\tСтоимостьУслуги\tВремяЗаписи" << endl;
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
			PriceList a;
			a.ShowPrices();
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

void AddClientScreen::setClient()
{
	cout << "Введите Имя клиента: " << endl;
	cin >> ClName;
	//getaLine(ClName);
	cout << "Введите Информацию о машине: " << endl;
	cin >> CInfo;
	// cin.getline(CInfo, 50);
	//cin.ignore(numeric_limits<streamsize>::max(),' ');
	//cin>> 
	//getaLine(CInfo);
	PriceList a;
	a.ShowPrices();
	cout << "Введите Номер услуги: " << endl;
	cin >> RecNum;
	ifstream in("P:\\TP\\TeamProject\\Car\\CarProject\\PriceList.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			if (line.find(to_string(RecNum)) != string::npos) {
				SerName = line.substr(3, 13);
				SerPrice= line.substr(16, 4);
			}
		}
	}
	in.close();



	cout << ClName << endl;
	cout << CInfo << endl;
	cout << RecNum << endl;  
	cout << SerName << endl; 
	cout << SerPrice << endl;;

}
void PriceList::ShowPrices()
{
	/*fstream F;
	F.open("C:\\CarProject\\PriceList.txt");
	if (F)
	{
		while (!F.eof())
		{
			F >> ServiceName;
			cout << ServiceName << endl;
		}
		F.close();
	} */
	ifstream in("P:\\TP\\TeamProject\\Car\\CarProject\\PriceList.txt"); 
	if (in.is_open())
	{
		while (getline(in, ServiceName))
		{
			cout << ServiceName << endl;
		}
	}
	in.close();     // закрываем файл

	//cout << "End of program" << endl;
}

ClientRecord::ClientRecord(string CName, string SName, string CarInfo, string DateTime, float SPrice, unsigned int RNum) :
	ClientName(CName), ServiceName(SName), CarInfo(CarInfo), DateTime(DateTime), ServicePrice(SPrice), RecordNum(RNum)
{

}//конструктор

ClientRecord::~ClientRecord()
{

}//деструктор

string ClientRecord::getClientName()
{
	return ClientName;
}

string ClientRecord::getClientCarInfo()
{
	return CarInfo;
}

string ClientRecord::getServiceName()
{
	return ServiceName;
}

string ClientRecord::getDateTime()
{
	return DateTime;
}

float ClientRecord::getServicePrice()
{
	return ServicePrice;
}

void TimeTable::ShowTimeTable()
{
	cout << "НомерЗаписи\tИмяКлиента\tУслуга\tСтоимостьУслуги\tВремяЗаписи" << endl;
}