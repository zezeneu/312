#include "LessonParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

static bool IsValidDateFormat(const string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '.' || date[7] != '.') return false;
    for (size_t i = 0; i < date.length(); ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }
    return true;
}

static bool IsValidTimeFormat(const string& time) {
    if (time.length() != 5) return false;
    if (time[2] != ':') return false;
    for (size_t i = 0; i < time.length(); ++i) {
        if (i == 2) continue;
        if (!isdigit(time[i])) return false;
    }

    int hours = stoi(time.substr(0, 2));
    int minutes = stoi(time.substr(3, 2));

    return (hours >= 0 && hours <= 23) && (minutes >= 0 && minutes <= 59);
}

static string ExtractTeacherName(const string& line) {
    size_t quoteStart = line.find('"');
    size_t quoteEnd = line.rfind('"');

    if (quoteStart != string::npos && quoteEnd != string::npos && quoteEnd > quoteStart) {
        return line.substr(quoteStart, quoteEnd - quoteStart + 1);
    }

    return "";
}

Lesson LessonParser::Parse(const string& line, int lineNumber) {
    Lesson lesson;
    stringstream ss(line);

    ss >> lesson.date >> lesson.time;
    lesson.teacher = ExtractTeacherName(line);

    if (!IsValidDateFormat(lesson.date)) {
        throw invalid_argument("Строка " + to_string(lineNumber) +
            ": Неверный формат даты '" + lesson.date + "'");
    }

    if (!IsValidTimeFormat(lesson.time)) {
        throw invalid_argument("Строка " + to_string(lineNumber) +
            ": Неверный формат времени '" + lesson.time + "'");
    }

    if (lesson.teacher.empty()) {
        throw invalid_argument("Строка " + to_string(lineNumber) +
            ": Отсутствует имя преподавателя");
    }

    return lesson;
}

vector<Lesson> LessonParser::ParseFile(const string& filename) {
    vector<Lesson> lessons;
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }

    string line;
    int lineNumber = 0;

    while (getline(inputFile, line)) {
        lineNumber++;

        if (line.empty()) {
            continue;
        }

        try {
            Lesson l = Parse(line, lineNumber);
            lessons.push_back(l);
        }
        catch (const invalid_argument& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }

    inputFile.close();
    return lessons;
}