/*******************************************************
 * Bank Accounts
 *
 * This project reads in a text file that includes
 * one or more account numbers, the name of the
 * person associated with that account, and the balance
 * of the account. From the choices 1-4, the user is
 * prompted to enter their choice. 
 *
 * '1' displays the balance of an individual.
 * '2' deposits money into the existing account.
 * '3' withdraws money from the existing account.
 * '4' displays all existing accounts with their names
 *     and balances.
 *
 *******************************************************/

/**
 * @file Part2.cpp
 * @author Upal Patel
 * @brief File contains implementaion of the functions of a Bank and its accounts.
 */

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

/**
 * @brief HashFun method
 * @param accNo
 * @return The number gained when taking the modulus of the account number using the number 5.
 * @details The method implements the modulus operator on the account number using the number 5.
 */
int HashFun(int accNo)
{
	return accNo % 5;
}

/**
 * @brief Insert method
 * @param *h[], x, y, z
 * @details 
 */

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

/**
 * @brief Display method
 * @param *h[]
 * @details
 */
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

/**
 * @brief Deposit method
 * @param *h[], depAmt, num
 * @return The amount of balance after deposit.
 * @details
 */
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


/**
 * @brief Withdraw method
 * @param *h[], withAmt, num
 * @return balance after withdrawal from account.
 * @details
 */
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

/**
 * @brief getName method
 * @param *h[], num
 * @details
 */
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

/**
 * @brief getBalance method
 * @param *h[], num
 * @details
 */
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

/**
 * @brief Search method
 * @param *h[], x
 * @return true or false to execute a search.
 * @details
 */
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

/**
 * @brief main method
 * @details Execution starts here for the Bank Accounts executable.
 */
int main()
{
    // Initialzes arrays for Node pointer H, account number, name, and balance.
	node *H[5];
	int AcctNo[6];
	string name[6];
	float bal[6];

    // Standard initializations needed for the loops used.
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

    // Read in from the file named "Menu.txt"
	fstream f;
	f.open("Menu.txt", ios::in);

	// Make individual array elements null.
	for (int i = 0; i < 5; i++)
	{
		H[i] = NULL;
	}
	
	// For each increment read in the account number, name, and balance. Then it inserts them into the array and increase the length by one. Repeats until all names are read in.
	for (int i = 0; i < 6; i++)
	{
		f >> AcctNo[i] >> name[i] >> bal[i];
		insert(H, AcctNo[i], name[i], bal[i]);
		length++;
	}

	// After names are read in, this is where the user picks there choice for what to do.
	do
	{
		cout << "Please enter your choice (1-4): ";
		cin >> choice;

		// displays balance of an individual.
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

		// Allows the user to deposit money into an account.
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

		// Allows the user to withdraw money from an account.
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

		// Displays all account numbers, names, and balances for each account.
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
	} while (repeat == 'y'); // Allows user to restart if wrong input is entered.

	system("PAUSE");
	return 0;
}
