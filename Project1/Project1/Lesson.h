#include <string>
#include <iomanip>
#include <iostream>

class Lesson {
public:
    std::string date;
    std::string time;
    std::string teacher;

    void Print() const;
};