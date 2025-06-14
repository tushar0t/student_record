#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Student
{
public:
    string name;
    string phone;
    string email;
    int studentID;
    int universityRollNumber;
    string course;
    string section;
    int rollNumber;
    float marks10;
    float marks12;
    string scholarType;
    string additionalInfo;
    string hostelRoom;
    Student *next;

    Student(string n, string p, string e, int sid, int ur, string c, string sec, int rn, float m10, float m12, string st, string ai, string hr = "N/A")
        : name(n), phone(p), email(e), studentID(sid), universityRollNumber(ur), course(c), section(sec), rollNumber(rn),
          marks10(m10), marks12(m12), scholarType(st), additionalInfo(ai), hostelRoom(hr), next(NULL) {}
};

class StudentList
{
private:
    Student *head;

public:
    StudentList() : head(NULL) {}

    void addStudent(Student *newStudent)
    {
        if (!head)
        {
            head = newStudent;
        }
        else
        {
            Student *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newStudent;
        }
        cout << "Record added successfully!" << endl;
    }

    void displayRecords()
    {
        if (!head)
        {
            cout << "No records to display." << endl;
            return;
        }
        cout << "\n*** Student Records ***" << endl;
        Student *temp = head;
        while (temp)
        {
            cout << "--------------------------------------------------" << endl;
            cout << "Name: " << temp->name << "\nPhone: " << temp->phone << "\nEmail: " << temp->email << endl;
            cout << "Student ID: " << temp->studentID << "\nUniversity Roll Number: " << temp->universityRollNumber << "\nCourse: " << temp->course << endl;
            cout << "Section: " << temp->section << "\nRoll Number: " << temp->rollNumber << endl;
            cout << "10th Marks: " << fixed << setprecision(2) << temp->marks10 << ", 12th Marks: " << temp->marks12 << endl;
            cout << "Scholar Type: " << temp->scholarType << endl;
            if (temp->scholarType == "Day Scholar")
            {
                cout << "Address: " << temp->additionalInfo << endl;
            }
            else if (temp->scholarType == "Hostler")
            {
                cout << "Hostel Name: " << temp->additionalInfo << "\nRoom Number: " << temp->hostelRoom << endl;
            }
            temp = temp->next;
        }
    }

    void deleteStudent(int studentID)
    {
        if (!head)
        {
            cout << "No records found to delete." << endl;
            return;
        }

        if (head->studentID == studentID)
        {
            Student *temp = head;
            head = head->next;
            delete temp;
            cout << "Record deleted successfully!" << endl;
            return;
        }

        Student *current = head;
        Student *previous = NULL;

        while (current && current->studentID != studentID)
        {
            previous = current;
            current = current->next;
        }

        if (current)
        {
            previous->next = current->next;
            delete current;
            cout << "Record deleted successfully!" << endl;
        }
        else
        {
            cout << "Record not found for Student ID: " << studentID << endl;
        }
    }
};

int main()
{
    StudentList studentList;
    int choice;

    while (true)
    {
        cout << "\n--- Student Record System ---" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. Display Records" << endl;
        cout << "3. Delete Record" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string name, phone, email, course, section, scholarType, additionalInfo, hostelRoom;
            int studentID, universityRollNumber, rollNumber;
            float marks10, marks12;

            cout << "Enter Full Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Phone Number: ";
            getline(cin, phone);
            cout << "Enter Email ID: ";
            getline(cin, email);
            cout << "Enter Student ID: ";
            cin >> studentID;
            cout << "Enter University Roll Number: ";
            cin >> universityRollNumber;
            cin.ignore();
            cout << "Enter Course: ";
            getline(cin, course);
            cout << "Enter Section: ";
            getline(cin, section);
            cout << "Enter Roll Number: ";
            cin >> rollNumber;
            cout << "Enter 10th Marks: ";
            cin >> marks10;
            cout << "Enter 12th Marks: ";
            cin >> marks12;
            cin.ignore();
            cout << "Enter Scholar Type (Day Scholar/Hostler): ";
            getline(cin, scholarType);
            if (scholarType == "Day Scholar")
            {
                cout << "Enter Address: ";
                getline(cin, additionalInfo);
                hostelRoom = "N/A";
            }
            else if (scholarType == "Hostler")
            {
                cout << "Enter Hostel Name: ";
                getline(cin, additionalInfo);
                cout << "Enter Hostel Room Number: ";
                getline(cin, hostelRoom);
            }

            Student *newStudent = new Student(name, phone, email, studentID, universityRollNumber, course, section, rollNumber, marks10, marks12, scholarType, additionalInfo, hostelRoom);
            studentList.addStudent(newStudent);
        }
        else if (choice == 2)
        {
            studentList.displayRecords();
        }
        else if (choice == 3)
        {
            int studentID;
            cout << "Enter Student ID to Delete: ";
            cin >> studentID;
            studentList.deleteStudent(studentID);
        }
        else if (choice == 4)
        {
            cout << "Exiting..." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
