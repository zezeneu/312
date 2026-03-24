#include "Lesson.h"

void Lesson::Print() const {
    std::cout << std::setw(15) << std::left << date
        << std::setw(10) << std::left << time
        << std::setw(30) << std::left << teacher << std::endl;
}