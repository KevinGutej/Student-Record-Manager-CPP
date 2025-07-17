#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Student {
public:
    string name;
    int age;
    float marks;

    Student(string n, int a, float m) {
        name = n;
        age = a;
        marks = m;
    }

    void display() const {
        cout << "Name: " << name << ", Age: " << age << ", Marks: " << marks << "\n";
    }
};

void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    for (const auto& s : students) {
        file << s.name << " " << s.age << " " << s.marks << "\n";
    }
    file.close();
    cout << "Data saved to file.\n";
}

void loadFromFile(vector<Student>& students, const string& filename) {
    ifstream file(filename);
    string name;
    int age;
    float marks;
    students.clear();
    while (file >> name >> age >> marks) {
        students.emplace_back(name, age, marks);
    }
    file.close();
    cout << "Data loaded from file.\n";
}

int main() {
    vector<Student> students;
    int choice;

    do {
        cout << "\n1. Add Student\n2. Show All\n3. Save to File\n4. Load from File\n0. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int age;
            float marks;

            cout << "Enter name: ";
            cin >> name;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter marks: ";
            cin >> marks;

            students.emplace_back(name, age, marks);
        } else if (choice == 2) {
            for (const auto& s : students)
                s.display();
        } else if (choice == 3) {
            saveToFile(students, "students.txt");
        } else if (choice == 4) {
            loadFromFile(students, "students.txt");
        }

    } while (choice != 0);

    return 0;
}
