#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "../LessonParser.h"
#include "../Lesson.h"

using namespace std;

// Тест 1: Корректный ввод
TEST(LessonParserTest, ValidInput) {
    EXPECT_NO_THROW({
        Lesson l = LessonParser::Parse("2024.09.01 10:30 \"Иванов И.И.\"");
        EXPECT_EQ(l.date, "2024.09.01");
        EXPECT_EQ(l.time, "10:30");
        EXPECT_EQ(l.teacher, "\"Иванов И.И.\"");
        });
}

// Тест 2: Неверный формат даты
TEST(LessonParserTest, InvalidDate) {
    EXPECT_THROW({
        LessonParser::Parse("2024/09/01 10:30 \"Иванов И.И.\"");
        }, std::invalid_argument);
}

// Тест 3: Неверный формат времени
TEST(LessonParserTest, InvalidTime) {
    EXPECT_THROW({
        LessonParser::Parse("2024.09.01 25:30 \"Иванов И.И.\"");
        }, std::invalid_argument);
}

// Тест 4: Пустое имя преподавателя
TEST(LessonParserTest, EmptyTeacher) {
    EXPECT_THROW({
        LessonParser::Parse("2024.09.01 10:30");
        }, std::invalid_argument);
}

// Тест 5: Пустая строка
TEST(LessonParserTest, EmptyLine) {
    EXPECT_THROW({
        LessonParser::Parse("");
        }, std::invalid_argument);
}

// Тест 6: Даты на границах
TEST(LessonParserTest, BoundaryDates) {
    EXPECT_NO_THROW({
        Lesson l1 = LessonParser::Parse("0001.01.01 00:00 \"Преподаватель\"");
        Lesson l2 = LessonParser::Parse("9999.12.31 23:59 \"Преподаватель\"");
        });
}

// Тест 7: Имя преподавателя без кавычек
TEST(LessonParserTest, TeacherWithoutQuotes) {
    EXPECT_NO_THROW({
        Lesson l = LessonParser::Parse("2024.09.01 10:30 Иванов И.И.");
    // Имя должно быть без кавычек, но программа не должна падать
    EXPECT_EQ(l.teacher, "Иванов И.И.");
        });
}

// Тест 8: Лишние пробелы
TEST(LessonParserTest, ExtraSpaces) {
    EXPECT_NO_THROW({
        Lesson l = LessonParser::Parse("   2024.09.01   10:30   \"Иванов И.И.\"   ");
        EXPECT_EQ(l.date, "2024.09.01");
        EXPECT_EQ(l.time, "10:30");
        });
}

// Тест 9: Чтение из файла
TEST(LessonParserTest, ParseFile) {
    // Создаем временный файл для теста
    ofstream testFile("test_temp.txt");
    testFile << "2024.09.01 10:30 \"Иванов И.И.\"\n";
    testFile << "2024.09.02 14:00 \"Петрова А.В.\"\n";
    testFile << "invalid line\n";
    testFile << "2024.09.03 09:00 \"Сидоров С.С.\"\n";
    testFile.close();

    auto lessons = LessonParser::ParseFile("test_temp.txt");

    // Должно быть 3 корректных записи (некорректная пропускается)
    EXPECT_EQ(lessons.size(), 3);
    EXPECT_EQ(lessons[0].teacher, "\"Иванов И.И.\"");
    EXPECT_EQ(lessons[1].teacher, "\"Петрова А.В.\"");
    EXPECT_EQ(lessons[2].teacher, "\"Сидоров С.С.\"");

    // Удаляем временный файл
    remove("test_temp.txt");
}

// Тест 10: Файл не существует
TEST(LessonParserTest, FileNotFound) {
    EXPECT_THROW({
        LessonParser::ParseFile("nonexistent_file.txt");
        }, std::runtime_error);
}

// Тест 11: Пустой файл
TEST(LessonParserTest, EmptyFile) {
    ofstream testFile("empty.txt");
    testFile.close();

    auto lessons = LessonParser::ParseFile("empty.txt");
    EXPECT_EQ(lessons.size(), 0);

    remove("empty.txt");
}

// Тест 12: Проверка метода Print (проверяем, что не падает)
TEST(LessonTest, PrintMethod) {
    Lesson l;
    l.date = "2024.09.01";
    l.time = "10:30";
    l.teacher = "\"Иванов И.И.\"";

    // Просто проверяем, что метод не выбрасывает исключений
    EXPECT_NO_THROW(l.Print());
}

// Главная функция для запуска тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}