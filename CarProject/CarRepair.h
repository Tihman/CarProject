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
	unsigned int RecordNum, year, month, day, hour, minute;
public:
	ClientRecord(unsigned int RN, string ClFN, string ClSN, string CB, string CM, string SN, unsigned int yy, unsigned int mm, unsigned int dd, unsigned int hh, unsigned int mint, float SP);
	~ClientRecord();
	unsigned int getRecordNum();
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
	list <ClientRecord*> ptrClientRecord;
	list <ClientRecord*>::iterator iter;
public:
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
	Expenses(string P, unsigned int y, unsigned int m, unsigned int d, float cost) :
		Product(P), year(y), month(m), day(d)
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

class UserInterface
{
private:
	PriceList* ptrPriceList;
	AddClientScreen* ptrAddClientScreen;
	TimeTable* ptrTimeTable;
	//EditDeleteScreen ptrEditDeleteScreen;
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
class EditDeleteScreen
{
private:
	TimeTable* ptrTimeTable;
	EditClientScreen* ptrEditClientScreen;
	DeleteClientScreen* ptrDeleteClientScreen;
	unsigned int RecordNum;
public:
	unsigned int getRecordNum();
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
	ClientRecord* ptrClientRecord;
public:
	void DeleteClient();
};
*/

/*





class Report
{
private:
	string DateTime;
	float Revenue, Expenses, Profit;
public:
	void ShowReport();
}; */