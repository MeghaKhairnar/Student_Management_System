#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class Student {
public:
    int roll;
    string name;
    int age;
    string course;

    Student() {}

    Student(int r, string n, int a, string c) {
        roll = r;
        name = n;
        age = a;
        course = c;
    }

    string toString() {
        stringstream ss;
        ss << roll << "," << name << "," << age << "," << course;
        return ss.str();
    }
};

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> data;

        while (getline(ss, token, ',')) {
            data.push_back(token);
        }

        if (data.size() == 4) {
            int roll, age;
            stringstream(data[0]) >> roll;
            stringstream(data[2]) >> age;
            students.push_back(Student(roll, data[1], age, data[3]));
        }
    }

    file.close();
    return students;
}

void saveStudents(vector<Student> &students) {
    ofstream file("students.txt");
    for (int i = 0; i < students.size(); i++) {
        file << students[i].toString() << endl;
    }
    file.close();
}

void addStudent(vector<Student> &students) {
    int roll, age;
    string name, course;

    cout << "Enter Roll: ";
    cin >> roll;
    cin.ignore();

    for (int i = 0; i < students.size(); i++) {
        if (students[i].roll == roll) {
            cout << "Roll Number Already Exists!\n";
            return;
        }
    }

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();

    cout << "Enter Course: ";
    getline(cin, course);

    students.push_back(Student(roll, name, age, course));
    saveStudents(students);

    cout << "Student Added Successfully!\n";
}

void viewStudents(vector<Student> &students) {
    if (students.empty()) {
        cout << "No Students Found!\n";
        return;
    }

    for (int i = 0; i < students.size(); i++) {
        cout << "\nRoll: " << students[i].roll;
        cout << "\nName: " << students[i].name;
        cout << "\nAge: " << students[i].age;
        cout << "\nCourse: " << students[i].course;
        cout << "\n---------------------\n";
    }
}

void searchStudent(vector<Student> &students) {
    int roll;
    cout << "Enter Roll to Search: ";
    cin >> roll;

    for (int i = 0; i < students.size(); i++) {
        if (students[i].roll == roll) {
            cout << "\nStudent Found:\n";
            cout << "Name: " << students[i].name << endl;
            cout << "Age: " << students[i].age << endl;
            cout << "Course: " << students[i].course << endl;
            return;
        }
    }

    cout << "Student Not Found!\n";
}

void deleteStudent(vector<Student> &students) {
    int roll;
    cout << "Enter Roll to Delete: ";
    cin >> roll;

    for (int i = 0; i < students.size(); i++) {
        if (students[i].roll == roll) {
            students.erase(students.begin() + i);
            saveStudents(students);
            cout << "Student Deleted Successfully!\n";
            return;
        }
    }

    cout << "Student Not Found!\n";
}

bool compareByRoll(Student a, Student b) {
    return a.roll < b.roll;
}

bool compareByName(Student a, Student b) {
    return a.name < b.name;
}

void sortByRoll(vector<Student> &students) {
    sort(students.begin(), students.end(), compareByRoll);
    cout << "Sorted by Roll Successfully!\n";
}

void sortByName(vector<Student> &students) {
    sort(students.begin(), students.end(), compareByName);
    cout << "Sorted by Name Successfully!\n";
}

int main() {
    vector<Student> students = loadStudents();
    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Sort by Roll\n";
        cout << "6. Sort by Name\n";
        cout << "7. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                viewStudents(students);
                break;
            case 3:
                searchStudent(students);
                break;
            case 4:
                deleteStudent(students);
                break;
            case 5:
                sortByRoll(students);
                break;
            case 6:
                sortByName(students);
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}
