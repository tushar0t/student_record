#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

class Student
{
public:
    std::string name;
    std::string phone;
    std::string email;
    int studentID;
    int universityRollNumber;
    std::string course;
    std::string section;
    int rollNumber;
    float marks10;
    float marks12;
    std::string scholarType;
    std::string additionalInfo;
    std::string hostelRoom;
    Student* next;

    Student(std::string n, std::string p, std::string e, int sid, int ur, std::string c, std::string sec, int rn, float m10, float m12, std::string st, std::string ai, std::string hr = "N/A")
        : name(n), phone(p), email(e), studentID(sid), universityRollNumber(ur), course(c), section(sec), rollNumber(rn),
          marks10(m10), marks12(m12), scholarType(st), additionalInfo(ai), hostelRoom(hr), next(nullptr) {}
};

class StudentList
{
private:
    Student* head;

public:
    StudentList() : head(nullptr) {}

    void addStudent(Student* newStudent)
    {
        if (!head)
        {
            head = newStudent;
        }
        else
        {
            Student* temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newStudent;
        }
        std::cout << "Record added successfully!" << std::endl;
    }

    void displayRecords()
    {
        if (!head)
        {
            std::cout << "No records to display." << std::endl;
            return;
        }

        std::cout << "\n*** Student Records ***" << std::endl;
        Student* temp = head;
        while (temp)
        {
            std::cout << "--------------------------------------------------" << std::endl;
            std::cout << "Name: " << temp->name << "\nPhone: " << temp->phone << "\nEmail: " << temp->email << std::endl;
            std::cout << "Student ID: " << temp->studentID << "\nUniversity Roll Number: " << temp->universityRollNumber << "\nCourse: " << temp->course << std::endl;
            std::cout << "Section: " << temp->section << "\nRoll Number: " << temp->rollNumber << std::endl;
            std::cout << "10th Marks: " << std::fixed << std::setprecision(2) << temp->marks10 << ", 12th Marks: " << temp->marks12 << std::endl;
            std::cout << "Scholar Type: " << temp->scholarType << std::endl;
            if (temp->scholarType == "Day Scholar")
            {
                std::cout << "Address: " << temp->additionalInfo << std::endl;
            }
            else if (temp->scholarType == "Hostler")
            {
                std::cout << "Hostel Name: " << temp->additionalInfo << "\nRoom Number: " << temp->hostelRoom << std::endl;
            }
            temp = temp->next;
        }
    }

    void deleteStudent(int studentID)
    {
        if (!head)
        {
            std::cout << "No records found to delete." << std::endl;
            return;
        }

        if (head->studentID == studentID)
        {
            Student* temp = head;
            head = head->next;
            delete temp;
            std::cout << "Record deleted successfully!" << std::endl;
            return;
        }

        Student* current = head;
        Student* previous = nullptr;

        while (current && current->studentID != studentID)
        {
            previous = current;
            current = current->next;
        }

        if (current)
        {
            previous->next = current->next;
            delete current;
            std::cout << "Record deleted successfully!" << std::endl;
        }
        else
        {
            std::cout << "Record not found for Student ID: " << studentID << std::endl;
        }
    }
};

int main()
{
    StudentList studentList;
    int choice;

    while (true)
    {
        std::cout << "\n--- Student Record System ---" << std::endl;
        std::cout << "1. Add Record" << std::endl;
        std::cout << "2. Display Records" << std::endl;
        std::cout << "3. Delete Record" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear(); // clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue;
        }

        if (choice == 1)
        {
            std::string name, phone, email, course, section, scholarType, additionalInfo, hostelRoom;
            int studentID, universityRollNumber, rollNumber;
            float marks10, marks12;

            std::cout << "Enter Full Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter Phone Number: ";
            std::getline(std::cin, phone);
            std::cout << "Enter Email ID: ";
            std::getline(std::cin, email);
            std::cout << "Enter Student ID: ";
            std::cin >> studentID;
            std::cout << "Enter University Roll Number: ";
            std::cin >> universityRollNumber;
            std::cin.ignore();
            std::cout << "Enter Course: ";
            std::getline(std::cin, course);
            std::cout << "Enter Section: ";
            std::getline(std::cin, section);
            std::cout << "Enter Roll Number: ";
            std::cin >> rollNumber;
            std::cout << "Enter 10th Marks: ";
            std::cin >> marks10;
            std::cout << "Enter 12th Marks: ";
            std::cin >> marks12;
            std::cin.ignore();
            std::cout << "Enter Scholar Type (Day Scholar/Hostler): ";
            std::getline(std::cin, scholarType);
            if (scholarType == "Day Scholar")
            {
                std::cout << "Enter Address: ";
                std::getline(std::cin, additionalInfo);
                hostelRoom = "N/A";
            }
            else if (scholarType == "Hostler")
            {
                std::cout << "Enter Hostel Name: ";
                std::getline(std::cin, additionalInfo);
                std::cout << "Enter Hostel Room Number: ";
                std::getline(std::cin, hostelRoom);
            }

            Student* newStudent = new Student(name, phone, email, studentID, universityRollNumber, course, section, rollNumber, marks10, marks12, scholarType, additionalInfo, hostelRoom);
            studentList.addStudent(newStudent);
        }
        else if (choice == 2)
        {
            studentList.displayRecords();
        }
        else if (choice == 3)
        {
            int studentID;
            std::cout << "Enter Student ID to Delete: ";
            std::cin >> studentID;
            studentList.deleteStudent(studentID);
        }
        else if (choice == 4)
        {
            std::cout << "Exiting..." << std::endl;
            break;
        }
        else
        {
            std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }

    return 0;
}
