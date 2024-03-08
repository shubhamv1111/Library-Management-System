#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include <iomanip>
using namespace std;

void gotoxy(int x, int y)//gotoxy is a simple utility function to facilitate console screen manipulation in Windows environments.
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

class Book
{
    char bno[6];    
    char bname[50]; 
    char aname[20]; 

public:
    void createBook()
    {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nENTER BOOK NO.: ";
        cin >> bno;
        cin.ignore(); 
        cout << "\nENTER BOOK NAME: ";
        cin.getline(bname, sizeof(bname));
        cout << "\nENTER AUTHOR NAME: ";
        cin.getline(aname, sizeof(aname));
        cout << "\n\n\nBook Created.";
    }

    void showBook()
    {
        cout << "\nBook Number: " << bno;
        cout << "\nBook Name: " << bname;
        cout << "\nBook Author Name: " << aname;
    }

    void modifyBook()
    {
        cout << "\nBook Number: " << bno;
        cout << "\nModify Book Name: ";
        cin.ignore(); 
        cin.getline(bname, sizeof(bname));
        cout << "\nModify Author's Name: ";
        cin.getline(aname, sizeof(aname));
    }

    char *getBno()
    {
        return bno;
    }

    void report()
    {
        cout << bno << setw(30) << bname << setw(30) << aname << endl;
    }
};

class Student
{
    char admno[6]; 
    char name[20];
    char stbno[6]; 
    int token;     

public:
    void createStudent()
    {
        system("cls");
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter The Admission No.: ";
        cin >> admno;
        cin.ignore(); 
        cout << "Enter The Student Name: ";
        cin.getline(name, sizeof(name));
        token = 0;
        stbno[0] = '\0';
        cout << "\n\nStudent Record Created...";
    }

    void showStudent()
    {
        cout << "\nAdmission Number: " << admno;
        cout << "\nStudent Name: " << name;
        cout << "\nNo of Book Issued: " << token;
        if (token == 1)
        {
            cout << "\nBook Number: " << stbno;
        }
    }

    void modifyStudent()
    {
        cout << "\nAdmission No.: " << admno;
        cout << "\nModify Student Name: ";
        cin.ignore(); 
        cin.getline(name, sizeof(name));
    }

    char *getAdmno()
    {
        return admno;
    }

    char *getStbno()
    {
        return stbno;
    }

    int getToken()
    {
        return token;
    }

    void addToken()
    {
        token = 1;
    }

    void resetToken()
    {
        token = 0;
    }

    void getStbno(char t[])
    {
        strcpy(stbno, t);
    }

    void report()
    {
        cout << "\t" << admno << setw(30) << name << setw(20) << token << endl;
    }
};

fstream fp, fp1;
Book bk;
Student st;
void start();

void writeBook()
{
    char ch;
    fp.open("book.dat", ios::out | ios::app);
    do
    {
        system("cls");
        bk.createBook();
        fp.write((char *)&bk, sizeof(Book));
        cout << "\n\nDo you want to add more record? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writeStudent()
{
    char ch;
    fp.open("student.dat", ios::out | ios::app);
    do
    {
        system("cls");
        st.createStudent();
        fp.write((char *)&st, sizeof(Student));
        cout << "\n\nDo you want to add more record? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void displaySpecificBook(char n[])
{
    cout << "\nBOOK DETAILS\n";
    int flag = 0;
    fp.open("book.dat", ios::in);
    while (fp.read((char *)&bk, sizeof(Book)))
    {
        if (strcmpi(bk.getBno(), n) == 0)
        {
            bk.showBook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout << "\n\nBook does not exist";
    }
    getch();
}

void displaySpecificStudent(char n[])
{
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;
    fp.open("student.dat", ios::in);
    while (fp.read((char *)&st, sizeof(Student)))
    {
        if (strcmpi(st.getAdmno(), n) == 0)
        {
            st.showStudent();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout << "\n\nStudent does not exist";
    }
    getch();
}

void modifyBook()
{
    char n[6];
    int found = 0;
    system("cls");

    cout << "\n\nMODIFY BOOK RECORD...";
    cout << "\n\nEnter the book no.: ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read((char *)&bk, sizeof(Book)) && found == 0)
    {
        if (strcmpi(bk.getBno(), n) == 0)
        {
            bk.showBook();
            cout << "\nEnter the new details of book";
            bk.modifyBook();
            int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&bk, sizeof(Book));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\n\nRecord Not Found";
    }
    getch();
}

void modifyStudent()
{
    char n[6];
    int found = 0;
    system("cls");

    cout << "\n\nMODIFY STUDENT RECORD...";
    cout << "\n\nEnter the Admission no.: ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.getAdmno(), n) == 0)
        {
            st.showStudent();
            cout << "\nEnter the new details of student";
            st.modifyStudent();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&st, sizeof(Student));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\n\nRecord Not Found";
    }
    getch();
}

void deleteStudent()
{
    char n[6];
    int flag = 0;
    system("cls");

    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter the Admission no.: ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&st, sizeof(Student)))
    {
        if (strcmpi(st.getAdmno(), n) != 0)
        {
            fp2.write((char *)&st, sizeof(Student));
        }
        else
        {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
    if (flag == 1)
    {
        cout << "\n\n\tRecord Deleted";
    }
    else
    {
        cout << "\n\nRecord not Found";
    }
    getch();
}

void deleteBook()
{
    char n[6];
    int flag = 0;
    system("cls");

    cout << "\n\n\n\tDELETE BOOK...";
    cout << "\n\nEnter the Book no.: ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&bk, sizeof(Book)))
    {
        if (strcmpi(bk.getBno(), n) != 0)
        {
            fp2.write((char *)&bk, sizeof(Book));
        }
        else
        {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat", "book.dat");
    if (flag == 1)
    {
        cout << "\n\n\tRecord Deleted";
    }
    else
    {
        cout << "\n\nRecord not Found";
    }
    getch();
}

void displayAllStudents()
{
    system("cls");

    fp.open("student.dat", ios::in);
    if (!fp)
    {
        cout << "File Could Not Be Open";
        getch();
        return;
    }
    cout << "\n\n\t\tStudent List\n\n";
    cout << "======================================================================\n";
    cout << "Admission No." << setw(20) << "Name" << setw(35) << "Book Issued\n";
    cout << "======================================================================\n";

    while (fp.read((char *)&st, sizeof(Student)))
    {
        st.report();
    }
    fp.close();
    getch();
}

void displayAllBooks()
{
    system("cls");

    fp.open("book.dat", ios::in);
    if (!fp)
    {
        cout << "File Could Not Be Open";
        getch();
        return;
    }
    cout << "\n\n\t\tBook List\n\n";
    cout << "==================================================================\n";
    cout << "\tBook No." << setw(20) << "Book Name" << setw(25) << "Book Author\n";
    cout << "==================================================================\n";
    while (fp.read((char *)&bk, sizeof(Book)))
    {
        bk.report();
    }
    fp.close();
    getch();
}

void bookIssue()
{
    char sn[6], bn[6];
    int found = 0, flag = 0;
    system("cls");

    cout << "\n\nBOOK ISSUE...";
    cout << "\n\n\tEnter Admission no.: ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.getAdmno(), sn) == 0)
        {
            found = 1;
            if (st.getToken() == 0)
            {
                cout << "\n\n\tEnter The Book No.: ";
                cin >> bn;
                while (fp1.read((char *)&bk, sizeof(Book)) && flag == 0)
                {
                    if (strcmpi(bk.getBno(), bn) == 0)
                    {
                        flag = 1;
                        st.addToken();
                        st.getStbno(bk.getBno());
                        int pos = -1 * sizeof(st);
                        fp.seekg(pos, ios::cur);
                        fp.write((char *)&st, sizeof(Student));
                        cout << "\n\n\tBook Issued Successfully.\n\nPlease Note The Book Issue Date On Backside Of Your Book And Return Book Within 15 Days, Otherwise Fine Of 15 Rs Per Day";
                    }
                }
                if (flag == 0)
                {
                    cout << "Book No. Does Not Exist";
                }
            }

            else
            {
                cout << "You Have Not Returned The Last Book";
            }
        }
    }
    if (found == 0)
    {
        cout << "Student Record Not Exists...";
    }
    getch();
    fp.close();
    fp1.close();
}

void bookDeposit()
{
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;
    system("cls");

    cout << "\n\nBOOK DEPOSIT...";
    cout << "\n\n\tEnter Admission no. Of Student: ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.getAdmno(), sn) == 0)
        {
            found = 1;
            if (st.getToken() == 1)
            {
                while (fp1.read((char *)&bk, sizeof(Book)) && flag == 0)
                {
                    if (strcmpi(bk.getBno(), st.getStbno()) == 0)
                    {
                        flag = 1;
                        bk.showBook();
                        cout << "\n\nBook Deposited In No. Of Days: ";
                        cin >> day;
                        if (day > 15)
                        {
                            fine = (day - 15) * 1;
                            cout << "\n\n Fine = " << fine;
                        }
                        st.resetToken();

                        int pos = -1 * sizeof(st);
                        fp.seekg(pos, ios::cur);
                        fp.write((char *)&st, sizeof(Student));
                        cout << "\n\n\tBook Deposited Successfully";
                    }
                }
                if (flag == 0)
                {
                    cout << "Book No. Does Not Exist";
                }
            }

            else
            {
                cout << "No Book Issued";
            }
        }
    }
    if (found == 0)
    {
        cout << "Student Record Not Exists...";
    }
    getch();
    fp.close();
    fp1.close();
}

void adminMenu();

int main()
{
    char ch;
    system("cls");

    start();
    do
    {
        system("cls");

        cout << "\n\n\n\t MAIN MENU";
        cout << "\n\n\n\t1. BOOK ISSUE";
        cout << "\n\n\n\t2. BOOK DEPOSIT";
        cout << "\n\n\n\t3. ADMINISTRATOR MENU";
        cout << "\n\n\n\t4. EXIT";
        cout << "\n\n\n\t PLEASE SELECT YOUR OPTION(1-4): ";
        ch = _getche();  // Use _getche function instead of getche
        switch (ch)
        {
        case '1':
            bookIssue();
            break;
        case '2':
            bookDeposit();
            break;
        case '3':
            adminMenu();
            break;
        case '4':
            exit(0);
            break;
        default:
            cout << "INVALID CHOICE";
        }
    } while (ch != '4');
}

void adminMenu()
{
    system("cls");

    int ch2;
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\n\t2.DISPLAY ALL STUDENT RECORD";
    cout << "\n\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD";
    cout << "\n\n\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\n\n\t5.DELETE STUDENT RECORD";
    cout << "\n\n\n\t6.CREATE BOOK";
    cout << "\n\n\n\t7.DISPLAY ALL BOOKS";
    cout << "\n\n\n\t8.DISPLAY SPECIFIC BOOK";
    cout << "\n\n\n\t9.MODIFY BOOK RECORD";
    cout << "\n\n\n\t10.DELETE BOOK RECORD";
    cout << "\n\n\n\t11.BACK TO MAIN MENU";
    cout << "\n\n\n\tPLEASE ENTER YOUR CHOICE(1-11): ";
    cin >> ch2;
    switch (ch2)
    {
    case 1:
        writeStudent();
        break;
    case 2:
        displayAllStudents();
        break;
    case 3:
        char num[6];
        system("cls");

        cout << "\n\n\t Please enter admission no.: ";
        cin >> num;
        displaySpecificStudent(num);
        break;
    case 4:
        modifyStudent();
        break;
    case 5:
        deleteStudent();
        break;
    case 6:
        writeBook();
        break;
    case 7:
        displayAllBooks();
        break;
    case 8:
        {
            char num[6];
            system("cls");

            cout << "\n\n\tPlease enter book no.: ";
            cin >> num;
            displaySpecificBook(num);
            break;
        }
    case 9:
        modifyBook();
        break;
    case 10:
        deleteBook();
        break;
    case 11:
        return;
    default:
        cout << "Invalid choice";
    }
    adminMenu();
}

// Added start function for initialization
void start()
{
    cout << "Library Management System";
    // Add any necessary initialization here
}
