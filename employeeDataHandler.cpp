#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Employee 
{
    string name; 
    int age;
    string dateEmployed; // xx/xx/xxxx
};

Employee* readEmployees(const string& empFile, int& numEmps);
void displayEmployees(const Employee emps[], int numEmps);
void inputEmployees(Employee*& emps, int& numEmps);
Employee* updateEmpFile(const string& empFile, const Employee emps[], int numEmps);

//****************************************************************************************************

int main ()
{
    Employee* emp = nullptr;
    ifstream f;
    int empNums;
    string choice;

    emp = readEmployees("Employees.txt", empNums);

    displayEmployees(emp, empNums);

    cout << "Would you like to add additional employee(s) [Yes/No]? ";
    cin >> choice; 

    if(choice == "Yes" || choice == "yes")
    {
        inputEmployees(emp, empNums);
        cout << endl;
        displayEmployees(emp, empNums);
        emp = updateEmpFile("Employees.txt", emp, empNums);
    }
    else
    {
        cout << "Thank you for your time!" << endl;
    }

    delete[] emp;
    f.close();

    return 0;
}

//****************************************************************************************************

Employee* readEmployees(const string& empFile, int& numEmps)
{
    Employee* emp; 
    ifstream f;

    f.open(empFile);

    if(!f.fail())
    {
        f >> numEmps;

        f.ignore();

        emp = new Employee[numEmps];

        for(int i = 0; i < numEmps; i++)
        {
            getline(f, emp[i].name, ',');
            f >> emp[i].age;
            f.ignore();
            getline(f, emp[i].dateEmployed);
        }
    }

    f.close();
    
    return emp;
}

void displayEmployees(const Employee emps[], int numEmps)
{
    cout << left << setw(32) << "NAME" << setw(24) << "AGE" << "DATE EMPLOYED\n";

    for (int i = 0; i < numEmps; i++)
    {
        cout << left 
             << setw(32) << emps[i].name
             << setw(24) << emps[i].age 
             << emps[i].dateEmployed << endl;
    }
}

void inputEmployees(Employee*& emps, int& numEmps)
{
    int temp;
    int newNum;

    cout << "How many employees do you wish to add? ";
    cin >> temp;

    newNum = temp + numEmps;

    Employee* newEmps = new Employee[newNum];

    for (int i = 0; i < numEmps; i++)
    {
        newEmps[i] = emps[i];
    }

    for (int i = numEmps; i < (newNum); i++)
    {
        cin.ignore();

        cout << left << setw(10);
        cout << "NAME:"
             << left << setw(10);
        getline(cin, newEmps[i].name);

        cout << "AGE:"
             << setw(10);
        cin >> newEmps[i].age;
        cin.ignore();

        cout << "EMPLOYED:"
             << setw(10);
        getline(cin, newEmps[i].dateEmployed);
    }

    delete[] emps;

    emps = newEmps;

    numEmps = newNum;
}

Employee* updateEmpFile(const string& empFile, const Employee emps[], int numEmps)
{
    ofstream f;
    f.open(empFile);

    if(f.is_open())
    {
        f << numEmps << endl;

        for(int i = 0; i < numEmps; i++)
        {
            f << emps[i].name << "," << emps[i].age << "," << emps[i].dateEmployed << endl;
        }
    }

    f.close();
}

/*

NAME                            AGE                     DATE EMPLOYED
Stephen Smith                   25                      15/12/2001
Susan Kim-Jones                 33                      9/1/2012
Kun Joom Jadav                  52                      22/8/1999
Would you like to add additional employee(s)? yes
How many employees do you wish to add? 3
NAME:     Jack Hams
AGE:      29
EMPLOYED: 03/11/1994

NAME:     Kenny Smith
AGE:      36
EMPLOYED: 01/20/2009

NAME:     Lloyd Junior
AGE:      50
EMPLOYED: 09/12/2001

NAME                            AGE                     DATE EMPLOYED
Stephen Smith                   25                      15/12/2001
Susan Kim-Jones                 33                      9/1/2012
Kun Joom Jadav                  52                      22/8/1999
Jack Hams                       29                      03/11/1994
Kenny Smith                     36                      01/20/2009
Lloyd Junior                    50                      09/12/2001

*/