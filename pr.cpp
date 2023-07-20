#include<iostream>
#include<fstream>
#include<limits>
#include<string>
//#include<io.h>
//#include<windows.h> 
//#include <cstdlib>
//#include<ctime>

using namespace std;
class Signup
{
	string musername;
	int mpin;
	int mbalance;


public:
	void getData(void);
	void ShowData(void);
	string Usernames(void);
	int Pin(void);
	void AddUser(void);
	void DeleteUser(string);
	void BalanceUpdateForWithdraw(string);
	void BalanceUpdateForDeposit(string);
	int Authentication(string, int);
	void BalanceEnquiry(string);

}New;

string Signup::Usernames()
{
	// Return username
	return musername;
}

int Signup::Pin()
{
	// Return the pin
	return mpin;
}

void Signup::getData()
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter username:" << endl;

	getline(cin, musername);
	cout << "Enter 4-digit " << "pin:" << endl;
	cin >> mpin;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter initial" << " balance:" << endl;
	cin >> mbalance;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void Signup::ShowData()
{
	cout << "Username:" << musername << "  "<< "Balance:" << mbalance << endl;
}

void Signup::AddUser()
{

	ofstream file;

	// Open file in write mode
	file.open("database.txt", ios::out | ios::app);
	if (!file) {
		cout << "Error in creating file.." << endl;
		return;
	}

	New.getData();

	// Write into file
	file.write((char*)&New, sizeof(New));
	//file<<name<<'\n'<<pin<<'\n'<<balance<<endl;


	// Close the file
	file.clear();
	file.close();
}


void Signup::DeleteUser(string ipname)
{
	fstream file, tempfile;
	file.open("database.txt", ios::in);
	if (!file)
	{
		cout << "server error" << endl;
		return;
	}
	else
	{
		tempfile.open("temp.txt", ios::out | ios::app);
		file.read((char*)&New, sizeof(New));
		while (!file.eof())
		{
			if (New.Usernames() == ipname)
			{
				cout << "Data is deleted" << endl;
			}
			else
			{
				tempfile.write((char*)&New, sizeof(New));
			}
			file.read((char*)&New, sizeof(New));

		}
	}
	file.close();
	tempfile.close();
	remove("database.txt");
	rename("temp.txt", "database.txt");

}

int Signup::Authentication(string ipname, int inpin)
{
	fstream file;

	// Open the file
	file.open("database.txt", ios::in);
	if (!file) {
		cout << "Error in opening file..";
		return 0;
	}

	// Read data from file
	file.read((char*)&New, sizeof(New));
	while (!file.eof()) {

		if (New.Usernames() == ipname) {
			if (New.Pin() == inpin) {
				return 1;
			}
		}
		file.read((char*)&New, sizeof(New));
	}

	// Close the file
	file.close();
	return 0;
}

void Signup::BalanceUpdateForDeposit(string ipname)
{
	int deposit;
	fstream file, temp;
	file.open("database.txt", ios::in | ios::out | ios::ate);
	temp.open("temp.txt", ios::out | ios::app);
	file.seekg(0);
	file.read((char*)&New, sizeof(New));

	// Till end of the file
	while (!file.eof()) {
		if (New.Usernames() == ipname) {
			cout << "Enter amount to deposit:" << endl;
			cin >> deposit;
			New.mbalance += deposit;
			cout << "Balance is:" << New.mbalance << endl;
			temp.write((char*)&New, sizeof(New));
		}
		else {
			temp.write((char*)&New, sizeof(New));
		}
		file.read((char*)&New, sizeof(New));
	}
	file.close();
	temp.close();
	remove("database.txt");
	rename("temp.txt", "database.txt");
}

void Signup::BalanceUpdateForWithdraw(string ipname)
{
	int withdraw;
	
	fstream file, temp;
	file.open("user.txt", ios::in | ios::out | ios::ate);
	temp.open("temp.txt", ios::out | ios::app);
	file.seekg(0);
	file.read((char*)&New, sizeof(New));

	// Till end of file is reached
	while (!file.eof()) {
		if ((New.Usernames() == ipname)) {
			cout << "Enter amount to withdraw:" << endl;
			cin >> withdraw;
			
			if (New.mbalance < withdraw) {
				
				cout << "Insufficient balance to withdraw" << endl;
			}
			else {
				New.mbalance = New.mbalance - withdraw;
				temp.write((char*)&New, sizeof(New));
				cout << "Balance is : " << New.mbalance<< endl;
			}
		}
		else {
			temp.write((char*)&New, sizeof(New));
		}
		file.read((char*)&New, sizeof(New));
	}

	// Close the file
	file.close();
	temp.close();
	remove("database.txt");
	rename("temp.txt", "database.txt");
}


void Signup :: BalanceEnquiry(string ipname)
{
	fstream file;

	// Open the file
	file.open("database.txt", ios::in);
	if (!file) {
		cout << "server error" << endl;
		return;
	}

	// Read data from file
	file.read((char*)&New, sizeof(New));
	while (!file.eof()) {
		if (New.Usernames()== ipname) {
			New.ShowData();
			return;
		}
		file.read((char*)&New, sizeof(New));
	}

	// Close the file
	file.close();
	return ;
}





/*
void checkpin(char* uname, int upin)
{
	string line;
	ifstream file1;
	file1.open("database.txt",ios::in);
	while(file1)
	{
		//char* l=line;
		//if(strstr(line,uname))
		//{
		getline(file1,line);
			cout<<line<<endl;
			break;
		//}
	}

}
*/
int main()
{
	string ipname;
	int Option, inpin, Opt, UserFound;
	cout << "enter the option\n" << "1.admin\n" << "2.user" << endl;
	cin >> Option;
	switch (Option)
	{
	case 1:
		while (1)
		{
			cout << "1.adduser\n2.deleteuser\n3.exit" << endl;
			cin >> Opt;
			switch (Opt)
			{
			case 1:
				New.AddUser();
				break;
			case 2:
				cout << "enter the name to delete" << endl;
				cin.ignore();
				getline(cin, ipname);
				New.DeleteUser(ipname);
				break;
			case 3:
				return 0;
			default:
				cout << "enter the valied option" << endl;
				break;
			}

		}
		break;
	case 2:
		cout << "enter the name" << endl;
		cin.ignore();
		getline(cin, ipname);
		cout << "Enter 4-digit " << "pin:" << endl;
		cin >> inpin;
		UserFound = New.Authentication(ipname, inpin);
		if (UserFound)
		{
			while (1)
			{
				cout << "welcome " << ipname << endl;
				cout << "1.Deposit\n2.Withdraw\n3.Balance Enquiry\n4.exit" << endl;
				cin >> Opt;
				switch (Opt)
				{
				case 1:
					New.BalanceUpdateForDeposit(ipname);
					break;
				case 2:
					New.BalanceUpdateForWithdraw(ipname);
					break;
				case 3:
					New.BalanceEnquiry(ipname);
					break;
				case 4:
					return 0;
				default:
					cout << "enter valied option" << endl;

				}
			}
		}
		else
		{
			cout << "authentication failed" << endl;
			return 0;
		}
		break;
	default:
		cout << "enter valied option" << endl;
		return 0;
	}
}
