#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class PriceList
{
private:
	string ServiceName, line;
	float ServicePrice;
	unsigned int RecordNum;
public:
	void ShowPrices();
};

class ClientRecord
{
private:
	string ClFirstName, ClSecondName, SerName, CBrand, CModel;
	float SerPrice;
	unsigned int year, month, day, hour, minute;
public:
	ClientRecord(string ClFN, string ClSN, string CB, string CM, string SN, unsigned int yy, unsigned int mm, unsigned int dd, unsigned int hh, unsigned int mint, float SP);
	~ClientRecord();
	string getClientFirstName();
	string getClientSecondName();
	string getCarBrand();
	string getCarModel();
	string getServiceName();
	unsigned int getYear();
	unsigned int getMonth();
	unsigned int getDay();
	unsigned int getHour();
	unsigned int getMinute();
	float getServicePrice();
};

class TimeTable
{
private:
	string ClFirstName, ClSecondName, SerName, CBrand, CModel;
	float SerPrice;
	unsigned int year, month, day, hour, minute;
public:
	list <ClientRecord*> ptrClientRecord;
	list <ClientRecord*>::iterator iter,iter2;
	void ShowTimeTable();
	void InsertClient(ClientRecord*);
	void SaveFile();
	void LoadFile();
};

class AddClientScreen
{
private:
	//ClientRecord* ptrClientRecord;
	TimeTable* ptrTimeTable;
	PriceList* ptrPriceList;
	string ClFirstName, ClSecondName, SerName, CBrand, CModel, line;
	unsigned int SerNum, year, month, day, hour, minute;
	float SerPrice;
public:
	AddClientScreen(TimeTable* ptrTT) : ptrTimeTable(ptrTT)
	{
		/*  */
	}
	void setClient();
};

class Expenses
{
public:
	string Product;
	unsigned int year, month, day;
	float Cost;
	Expenses(string P, unsigned int y, unsigned int m, unsigned int d, float ct) :
		Product(P), year(y), month(m), day(d), Cost(ct)
	{
		/* */
	}
};

class ExpensesTable
{
private:
	string Product;
	unsigned int year, month, day;
	float Cost;
public:
	vector<Expenses*> vecptrExpenses;
	vector<Expenses*>::iterator iter;
	void insertExpenses(Expenses*);
	void ShowExpensesTable();
	void LoadExpenses();
	void SaveExpenses();
};

class AddExpensesScreen
{
private:
	ExpensesTable* ptrExpensesTable;
	string Product;
	unsigned int year, month, day;
	float Cost;
public:
	AddExpensesScreen(ExpensesTable*);
	void setExpenses();
};

class EditClientScreen
{
private:
	TimeTable* ptrTimeTable;
	string ClFirstName, ClSecondName, SerName, CBrand, CModel, line;
	unsigned int SerNum, year, month, day, hour, minute;
	float SerPrice;
public:
	EditClientScreen(TimeTable* ptrTT) :ptrTimeTable(ptrTT)
	{

	}
	void EditInfo(unsigned int YY, unsigned int MM, unsigned int DD, unsigned int hh, unsigned int mm);
};

class DeleteClientScreen
{
private:
	TimeTable* ptrTimeTable;
	unsigned int year, month, day, hour, minute;
public:
	DeleteClientScreen(TimeTable* ptrTT) :ptrTimeTable(ptrTT)
	{

	}
	void DeleteClient(unsigned int YY, unsigned int MM, unsigned int DD, unsigned int hh, unsigned int mm);

};

class EditDeleteScreen
{
private:
	TimeTable* ptrTimeTable;
	EditClientScreen* ptrEditClientScreen;
	DeleteClientScreen* ptrDeleteClientScreen;
	unsigned int year, month, day, hour, minute, choice;
public:
	EditDeleteScreen(TimeTable* ptrTT) :ptrTimeTable(ptrTT)
	{

	}
	~EditDeleteScreen();
	void getRecordDate();
};

class Report
{
private:
	unsigned int year1, month1, day1, year2, month2, day2;
	float Revenue, Expenses, Profit;
	TimeTable* ptrTimeTable;
	ExpensesTable* ptrExpensesTable;
public:
	Report(TimeTable* ptrTT, ExpensesTable* ptrET): ptrTimeTable(ptrTT), ptrExpensesTable(ptrET)
	{

	}
	void ShowReport();
}; 

class UserInterface
{
private:
	PriceList* ptrPriceList;
	AddClientScreen* ptrAddClientScreen;
	EditDeleteScreen* ptrEditDeleteScreen;
	TimeTable* ptrTimeTable;
	ExpensesTable* ptrExpensesTable;
	AddExpensesScreen* ptrAddExpensesScreen;
	Report* ptrReport; 
	char choice;
public:
	UserInterface();
	~UserInterface();
	void Menu();
};