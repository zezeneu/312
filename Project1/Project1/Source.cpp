#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <clocale>
#include <windows.h>

using namespace std;

class Lesson {
public:
    string date; 
    string time;
    string teacher;

    void print() const {
        cout << setw(15) << left << date
            << setw(10) << left << time
            << setw(30) << left << teacher << endl;
    }
};

Lesson parseLesson(const string& line) {
    Lesson lesson;
    stringstream ss(line);

    ss >> lesson.date;

    ss >> lesson.time;

    string teacherWithQuotes;
    getline(ss, teacherWithQuotes);

    size_t start = teacherWithQuotes.find_first_not_of(" \t");
    if (start != string::npos) {
        teacherWithQuotes = teacherWithQuotes.substr(start);
    }
    size_t end = teacherWithQuotes.find_last_not_of(" \t");
    if (end != string::npos) {
        teacherWithQuotes = teacherWithQuotes.substr(0, end + 1);
    }

    lesson.teacher = teacherWithQuotes;

    return lesson;
}

void printHeader() {
    cout << "\n==============================================================" << endl;
    cout << setw(15) << left << "Дата"
        << setw(10) << left << "Время"
        << setw(30) << left << "Преподаватель" << endl;
    cout << "==============================================================" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ifstream inputFile("text.txt");

    if (!inputFile.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл text.txt" << endl;
        return 1;
    }

    vector<Lesson> lessons;
    string line;
    while (getline(inputFile, line)) {
        if (!line.empty()) {
            lessons.push_back(parseLesson(line));
        }
    }

    inputFile.close();
    cout << "Список учебных занятий из файла text.txt:" << endl;
    printHeader();
    for (const auto& lesson : lessons) {
        lesson.print();
    }

    return 0;
}