#include <iostream>
#include <string>

using namespace std;

class UserInterface
{
private:
	/*AddClientScreen* ptrAddClientScreen;
	TimeTable* ptrTimeTable;
	EditDeleteScreen ptrEditDeleteScreen;
	PriceList* ptrPriceList;
	ExpensesTable* ptrExpensesTable;
	AddExpensesScreen* ptrAddExpensesScreen;
	Report* ptrReport; */
	char choice;
public:
	UserInterface();
	~UserInterface();
	void Menu();
};
/*
class ClientRecord
{
private:
	string ClientName, ServiceName, CarInfo, DateTime;
	float ServicePrice;
	unsigned int RecordNum;
public:
	ClientRecord(string CName, string SName, string CarInfo, string DateTime, float SPrice, unsigned int RNum);
	~ClientRecord();
	string getClientName();
	string getClientCarInfo();
	string getServiceName();
	string getDateTime();
	float getServicePrice();
};

class AddClientScreen
{
private:
	ClientRecord* ptrClientRecord;
	PriceList* ptrPriceList;
public:
	void setClient();
	void insertClient();
};

class TimeTable
{
private:
	ClientRecord* ptrClientRecord;
public:
	void ShowTimeTable();
};

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

class PriceList
{
private:
	string ServiceName;
	float ServicePrice;
	unsigned int RecordNum;
public:
	void ShowPrices();
};

class ExpensesTable
{
private:
	Expenses* ptrExpenses;
public:
	void ShowExpensesTable();
};

class Expenses
{
private:
	string Product, DateTime;
	float Cost;
public:
	string getProduct();
	float getCost();
	string getDateTime();
};

class AddExpensesScreen
{
private:
	Expenses* ptrExpenses;
public:
	void setExpenses();
	void insertExpenses();
};
class Report
{
private:
	string DateTime;
	float Revenue, Expenses, Profit;
public:
	void ShowReport();
}; */