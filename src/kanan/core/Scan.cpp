#include "Scan.hpp"
#include "Module.hpp"
#include "Pattern.hpp"
#include "String.hpp"

using namespace std;

namespace kanan {
optional<uintptr_t> scan(const string& module, const string& pattern) {
    return scan(GetModuleHandle(widen(module).c_str()), pattern);
}

optional<uintptr_t> scan(const string& module, uintptr_t start, const string& pattern) {
    HMODULE mod = GetModuleHandle(widen(module).c_str());
    return scan(start, (getModuleSize(mod).value_or(0) - start + (uintptr_t)mod), pattern);
}

optional<uintptr_t> scan(HMODULE module, const string& pattern) {
    return scan((uintptr_t)module, getModuleSize(module).value_or(0), pattern);
}

optional<uintptr_t> scan(uintptr_t start, size_t length, const string& pattern) {
    if (start == 0 || length == 0) {
        return {};
    }

    Pattern p{pattern};

    return p.find(start, length);
}

std::optional<uintptr_t> scan(const std::string& pattern) {
    auto mod = GetModuleHandle(nullptr);
    auto size = getModuleSize(mod).value_or(0);
    return scan((uintptr_t)mod, size, pattern);
}
} // namespace kanan
