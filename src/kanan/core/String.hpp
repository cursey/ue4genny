#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace kanan {
//
// String utilities.
//

// Conversion functions for UTF8<->UTF16.
std::string narrow(std::wstring_view str);
std::wstring widen(std::string_view str);

std::string formatString(const char* format, va_list args);

std::vector<std::string> split(std::string str, const std::string& delim);

// FNV-1a
static constexpr auto hash(std::string_view data) {
    size_t result = 0xcbf29ce484222325;

    for (char c : data) {
        result ^= c;
        result *= (size_t)1099511628211;
    }

    return result;
}
} // namespace kanan
