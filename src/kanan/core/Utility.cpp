#include <Windows.h>

#include "Utility.hpp"

using namespace std;

namespace kanan {
bool isKeyDown(int key) {
    return (GetAsyncKeyState(key) & (1 << 15)) != 0;
}

bool wasKeyPressed(int key) {
    static bool keys[0xFF]{false};

    if (isKeyDown(key) && !keys[key]) {
        keys[key] = true;

        return true;
    }

    if (!isKeyDown(key)) {
        keys[key] = false;
    }

    return false;
}

string hexify(const uint8_t* data, size_t length) {
    constexpr char hexmap[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    string result{};

    result.resize(length * 2);

    for (size_t i = 0; i < length; ++i) {
        result[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
        result[2 * i + 1] = hexmap[data[i] & 0x0F];
    }

    return result;
}

string hexify(const vector<uint8_t>& data) {
    return hexify(data.data(), data.size());
}
} // namespace kanan
