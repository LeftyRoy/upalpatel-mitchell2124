#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct node
{
	int accountNo;
	string name;
	float balance;
	node *next;
};
int HashFun(int accNo);
void insert(node *h[], int x, string y, float z);
void Display(node *h[]);
float const deposit(node *h[], float depAmt, int num);
float const withdraw(node *h[], float withAmt, int num);
string getName(node *h[], int num);
float getBalance(node *h[], int num);
bool search(node *h[], int x);

int HashFun(int accNo)
{
	return accNo % 5;
}

void insert(node *h[], int x, string y, float z)
{
	int i = HashFun(x);
	node *p;
	p = new node;
	p->accountNo = x;
	p->name = y;
	p->balance = z;
	p->next = h[i];
	h[i] = p;
}

void Display(node *h[])
{
	node *p;
	cout << "Account No" << "\t" << "Name" << "\t" << "Balance\n";
	for (int i = 0; i < 5; i++)
	{
		p = h[i];
		while (p != NULL)
		{
			cout << p->accountNo << "\t\t" << p->name << "\t" <<
				fixed << setprecision(2) << p->balance << "\n";
			p = p->next;
		}
	}
}

float const deposit(node *h[], float depAmt, int num)
{
	int i = HashFun(num);
	node *dep = h[i];
	for (int i = 0; i < 5; i++)
	{
		if (dep->accountNo == num)
		{
			dep->balance += depAmt;
			break;
		}
		dep = dep->next;
	}
	return dep->balance;
}

float const withdraw(node *h[], float withAmt, int num)
{
	int i = HashFun(num);
	node *with = h[i];
	for (int i = 0; i < 5; i++)
	{
		if (with->accountNo == num)
		{
			with->balance -= withAmt;
			break;
		}
		with = with->next;
	}
	return with->balance;
}

string getName(node *h[], int num)
{
	int i = HashFun(num);
	node *gN = h[i];
	string gName;
	for (int i = 0; i < 5; i++)
	{
		if (gN->accountNo == num)
		{
			gName = gN->name;
			break;
		}
		gN = gN->next;
	}
	return gName;
}

float getBalance(node *h[], int num)
{
	int i = HashFun(num);
	node *gB = h[i];
	float gBal;
	for (int i = 0; i < 5; i++)
	{
		if (gB->accountNo == num)
		{
			gBal = gB->balance;
			break;
		}
		gB = gB->next;
	}
	return gBal;
}

bool search(node *h[], int x)
{
	int i = HashFun(x);
	node *p = h[i];
	while (p != NULL && p->accountNo != x)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int main()
{
	node *H[5];
	int AcctNo[6];
	string name[6];
	float bal[6];

	char repeat;
	int choice,
		accNo,
		length = 0;
	string tempN;
	float aDep,
		aWith,
		tempB,
		tempD,
		tempW;

	fstream f;
	f.open("Menu.txt", ios::in);

	for (int i = 0; i < 5; i++)
	{
		H[i] = NULL;
	}
	for (int i = 0; i < 6; i++)
	{
		f >> AcctNo[i] >> name[i] >> bal[i];
		insert(H, AcctNo[i], name[i], bal[i]);
		length++;
	}

	do
	{
		cout << "Please enter your choice (1-4): ";
		cin >> choice;

		if (choice == 1)
		{
			cout << "Enter your account number: ";
			cin >> accNo;
			if (search(H, accNo) != false)
			{
				tempN = getName(H, accNo);
				tempB = getBalance(H, accNo);
				cout << tempN << ", your balance is " <<
					fixed << setprecision(2) << tempB << endl;
			}
		}
		else if (choice == 2)
		{
			cout << "Enter your account number: ";
			cin >> accNo;
			if (search(H, accNo) != false)
			{
				tempN = getName(H, accNo);
				cout << tempN << ", how much would you like to deposit? ";
				cin >> aDep;
				tempD = deposit(H, aDep, accNo);
				cout << tempN << ", your new balance is " <<
					fixed << setprecision(2) << tempD << endl;
			}
		}
		else if (choice == 3)
		{
			cout << "Enter your account number: ";
			cin >> accNo;
			if (search(H, accNo) != false)
			{
				tempN = getName(H, accNo);
				cout << tempN << ", how much would you like to withdraw? ";
				cin >> aWith;
				tempW = withdraw(H, aWith, accNo);
				cout << tempN << ", your new balance is " <<
					fixed << setprecision(2) << tempW << endl;
			}
		}
		else if (choice == 4)
		{
			Display(H);
		}
		else
		{
			cout << "\nChoice number is not valid, please restart\n";
		}

		cout << "\nCONTINUE (y/n)? ";
		cin >> repeat;
	} while (repeat == 'y');

	system("PAUSE");
	return 0;
}