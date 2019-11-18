//
// Created by Petr on 18.11.2019.
//

#ifndef UTILITIES_BYTELITERALS_H
#define UTILITIES_BYTELITERALS_H

namespace ByteLiterals {
    constexpr unsigned long long operator"" _B(unsigned long long value) {
        return value;
    }
    constexpr unsigned long long operator"" _KB(unsigned long long value) {
        return value * 1024;
    }
    constexpr unsigned long long operator"" _MB(unsigned long long value) {
        return value * 1048576;
    }
    constexpr unsigned long long operator"" _GB(unsigned long long value) {
        return value * 1073741824;
    }

}  // namespace ByteLiterals

#endif //UTILITIES_BYTELITERALS_H
