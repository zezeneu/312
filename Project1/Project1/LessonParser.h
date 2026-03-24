#include "Lesson.h"
#include <string>
#include <vector>

class LessonParser {
public:
    static Lesson Parse(const std::string& line, int lineNumber);
    static std::vector<Lesson> ParseFile(const std::string& filename);
};