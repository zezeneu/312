#include <iostream>
#include <vector>
#include <clocale>
#include <windows.h>
#include "Lesson.h"
#include "LessonParser.h"

using namespace std;

static void PrintHeader() {
    cout << setw(15) << left << "Дата"
        << setw(10) << left << "Время"
        << setw(30) << left << "Преподаватель" << endl;
    cout << string(55, '-') << endl;
}

static void PrintLessons(const vector<Lesson>& lessons) {
    if (lessons.empty()) {
        cout << "Нет данных для отображения." << endl;
        return;
    }

    PrintHeader();
    for (const auto& lesson : lessons) {
        lesson.Print();
    }
    cout << "\nВсего занятий: " << lessons.size() << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        vector<Lesson> lessons = LessonParser::ParseFile("text.txt");

        cout << "\n=== Список учебных занятий ===\n" << endl;
        PrintLessons(lessons);

    }
    catch (const runtime_error& e) {
        cerr << "Критическая ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}