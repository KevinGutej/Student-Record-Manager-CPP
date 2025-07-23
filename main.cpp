#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>

using namespace std;

class Student {
public:
    string name;
    int age;
    float marks;

    Student(string n, int a, float m) : name(n), age(a), marks(m) {}

    void display() const {
        cout << "Name: " << name << ", Age: " << age << ", Marks: " << marks << "\n";
    }
};

void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }
    for (const auto& s : students) {
        file << s.name << " " << s.age << " " << s.marks << "\n";
    }
    file.close();
    cout << "Data saved to file.\n";
}

void loadFromFile(vector<Student>& students, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file for reading.\n";
        return;
    }
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

void updateStudent(vector<Student>& students) {
    string targetName;
    cout << "Enter the name of the student to update: ";
    cin >> targetName;

    for (auto& s : students) {
        if (s.name == targetName) {
            cout << "Enter new age: ";
            cin >> s.age;
            cout << "Enter new marks: ";
            cin >> s.marks;
            cout << "Student updated.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void deleteStudent(vector<Student>& students) {
    string targetName;
    cout << "Enter the name of the student to delete: ";
    cin >> targetName;

    auto it = remove_if(students.begin(), students.end(), [&](const Student& s) {
        return s.name == targetName;
    });

    if (it != students.end()) {
        students.erase(it, students.end());
        cout << "Student deleted.\n";
    } else {
        cout << "Student not found.\n";
    }
}

void sortStudents(vector<Student>& students) {
    int option;
    cout << "Sort by: 1. Marks  2. Age\nEnter choice: ";
    cin >> option;

    if (option == 1) {
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.marks > b.marks;
        });
        cout << "Sorted by marks (high to low).\n";
    } else if (option == 2) {
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.age < b.age;
        });
        cout << "Sorted by age (youngest first).\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

void searchStudent(const vector<Student>& students) {
    string targetName;
    cout << "Enter name to search: ";
    cin >> targetName;

    bool found = false;
    for (const auto& s : students) {
        if (s.name == targetName) {
            s.display();
            found = true;
        }
    }
    if (!found) cout << "Student not found.\n";
}

void showTopScorer(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }
    auto top = max_element(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.marks < b.marks;
    });
    cout << "Top Scorer:\n";
    top->display();
}

void showAverageMarks(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }
    float total = accumulate(students.begin(), students.end(), 0.0f, [](float sum, const Student& s) {
        return sum + s.marks;
    });
    cout << "Average Marks: " << total / students.size() << "\n";
}

void showOldestStudent(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }
    auto oldest = max_element(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.age < b.age;
    });
    cout << "Oldest Student:\n";
    oldest->display();
}

int main() {
    vector<Student> students;
    int choice;

    do {
        cout << "\nMenu:\n"
             << "1. Add Student\n"
             << "2. Show All Students\n"
             << "3. Save to File\n"
             << "4. Load from File\n"
             << "5. Update Student\n"
             << "6. Delete Student\n"
             << "7. Sort Students\n"
             << "8. Search Student\n"
             << "9. Show Top Scorer\n"
             << "10. Show Average Marks\n"
             << "11. Show Oldest Student\n"
             << "0. Exit\n"
             << "Enter choice: ";
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
            if (students.empty()) {
                cout << "No students to display.\n";
            } else {
                for (const auto& s : students)
                    s.display();
            }
        } else if (choice == 3) {
            saveToFile(students, "students.txt");
        } else if (choice == 4) {
            loadFromFile(students, "students.txt");
        } else if (choice == 5) {
            updateStudent(students);
        } else if (choice == 6) {
            deleteStudent(students);
        } else if (choice == 7) {
            sortStudents(students);
        } else if (choice == 8) {
            searchStudent(students);
        } else if (choice == 9) {
            showTopScorer(students);
        } else if (choice == 10) {
            showAverageMarks(students);
        } else if (choice == 11) {
            showOldestStudent(students);
        } else if (choice != 0) {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    cout << "Exiting program.\n";
    return 0;
}
