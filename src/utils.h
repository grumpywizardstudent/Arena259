#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

enum class Color {
    RESET = 0,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37
};

// Helper to output the ANSI escape sequence
inline std::ostream& operator<<(std::ostream& os, Color color) {
    return os << "\033[" << static_cast<int>(color) << "m";
}

inline std::string colorMe(std::string text, Color color) {
    return "\033[" + std::to_string(static_cast<int>(color)) + "m" + text + "\033[0m";
}

#endif