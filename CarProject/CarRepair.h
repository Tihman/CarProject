#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class PriceList
{
private:
	string ServiceName;
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
public:
	list <ClientRecord*> ptrClientRecord;
	list <ClientRecord*>::iterator iter;
	void ShowTimeTable();
	void InsertClient(ClientRecord*);
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
		/* тут пусто */
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
	/*
	string getProduct();
	unsigned int getYear();
	unsigned int getMonth();
	unsigned int getDay();
	unsigned int getHour();
	unsigned int getMinute();
	float getCost();
	*/
};

class ExpensesTable
{
private:
	vector<Expenses*> vecptrExpenses;
	vector<Expenses*>::iterator iter;
public:
	//~ExpensesTable();
	void insertExpenses(Expenses*);
	void ShowExpensesTable();
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
	ClientRecord* ptrClientRecord;
	TimeTable* ptrTimeTable;
public:
	string EditInfo();
	void insertEditedInfo();
};

class DeleteClientScreen
{
private:
	TimeTable* ptrTimeTable;
	unsigned int year, month, day, hour, minute;
public:
	void DeleteClient(unsigned int YY, unsigned int MM, unsigned int DD, unsigned int hh, unsigned int mm, TimeTable* ptrTimeTable);

};

class EditDeleteScreen
{
private:
	TimeTable* ptrTimeTable;
	EditClientScreen* ptrEditClientScreen;
	DeleteClientScreen* ptrDeleteClientScreen;
	unsigned int year, month, day, hour, minute, choice;
public:
	EditDeleteScreen();
	~EditDeleteScreen();
	void getRecordDate(TimeTable* ptrTimeTable);
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
	//Report* ptrReport; 
	char choice;
public:
	UserInterface();
	~UserInterface();
	void Menu();
};

/*





class Report
{
private:
	string DateTime;
	float Revenue, Expenses, Profit;
public:
	void ShowReport();
}; */