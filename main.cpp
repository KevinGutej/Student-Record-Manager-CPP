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

    Student(string n, int a, float m) : name(move(n)), age(a), marks(m) {}

    void display() const {
        cout << "Name: " << name << ", Age: " << age << ", Marks: " << marks << "\n";
    }
};

void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    if (!file) return;
    for (const auto& s : students)
        file << s.name << ' ' << s.age << ' ' << s.marks << '\n';
}

void loadFromFile(vector<Student>& students, const string& filename) {
    ifstream file(filename);
    if (!file) return;
    string name;
    int age;
    float marks;
    students.clear();
    while (file >> name >> age >> marks)
        students.emplace_back(name, age, marks);
}

void updateStudent(vector<Student>& students) {
    string name;
    cout << "Student name to update: ";
    cin >> name;
    auto it = find_if(students.begin(), students.end(), [&](const Student& s) {
        return s.name == name;
    });
    if (it != students.end()) {
        cout << "New age: "; cin >> it->age;
        cout << "New marks: "; cin >> it->marks;
    } else cout << "Not found.\n";
}

void deleteStudent(vector<Student>& students) {
    string name;
    cout << "Student name to delete: ";
    cin >> name;
    auto it = remove_if(students.begin(), students.end(), [&](const Student& s) {
        return s.name == name;
    });
    if (it != students.end()) students.erase(it, students.end());
    else cout << "Not found.\n";
}

void sortStudents(vector<Student>& students) {
    int opt;
    cout << "Sort by: 1.Marks 2.Age: ";
    cin >> opt;
    if (opt == 1)
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.marks > b.marks;
        });
    else if (opt == 2)
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.age < b.age;
        });
}

void searchStudent(const vector<Student>& students) {
    string name;
    cout << "Search name: ";
    cin >> name;
    auto it = find_if(students.begin(), students.end(), [&](const Student& s) {
        return s.name == name;
    });
    if (it != students.end()) it->display();
    else cout << "Not found.\n";
}

void showTopScorer(const vector<Student>& students) {
    if (students.empty()) return;
    auto it = max_element(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.marks < b.marks;
    });
    it->display();
}

void showAverageMarks(const vector<Student>& students) {
    if (students.empty()) return;
    float avg = accumulate(students.begin(), students.end(), 0.0f, [](float acc, const Student& s) {
        return acc + s.marks;
    }) / students.size();
    cout << "Average Marks: " << avg << '\n';
}

void showOldestStudent(const vector<Student>& students) {
    if (students.empty()) return;
    auto it = max_element(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.age < b.age;
    });
    it->display();
}

int main() {
    vector<Student> students;
    int choice;
    string name;
    int age;
    float marks;

    while (true) {
        cout << "\n1.Add 2.View 3.Save 4.Load 5.Update 6.Delete 7.Sort 8.Search 9.Top 10.Average 11.Oldest 0.Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Name Age Marks: ";
                cin >> name >> age >> marks;
                students.emplace_back(name, age, marks);
                break;
            case 2:
                if (students.empty()) cout << "Empty.\n";
                else for (const auto& s : students) s.display();
                break;
            case 3: saveToFile(students, "students.txt"); break;
            case 4: loadFromFile(students, "students.txt"); break;
            case 5: updateStudent(students); break;
            case 6: deleteStudent(students); break;
            case 7: sortStudents(students); break;
            case 8: searchStudent(students); break;
            case 9: showTopScorer(students); break;
            case 10: showAverageMarks(students); break;
            case 11: showOldestStudent(students); break;
            case 0: return 0;
            default: cout << "Invalid.\n";
        }
    }
}
