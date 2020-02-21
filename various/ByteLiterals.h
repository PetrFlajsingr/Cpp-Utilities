//
// Created by Petr on 18.11.2019.
//

#ifndef UTILITIES_BYTELITERALS_H
#define UTILITIES_BYTELITERALS_H

namespace ByteLiterals {
namespace detail {
constexpr auto byteOrderMultiplier = 1000;
constexpr auto biByteOrderMultiplier = 1024;
} // namespace detail
constexpr unsigned long long operator"" _B(unsigned long long value) { return value; }
constexpr unsigned long long operator"" _KB(unsigned long long value) { return value * byteOrderMultiplier; }
constexpr unsigned long long operator"" _MB(unsigned long long value) { return value * std::pow(byteOrderMultiplier, 2); }
constexpr unsigned long long operator"" _GB(unsigned long long value) { return value * std::pow(byteOrderMultiplier, 3); }
constexpr unsigned long long operator"" _TB(unsigned long long value) { return value * std::pow(byteOrderMultiplier, 4); }
constexpr unsigned long long operator"" _PB(unsigned long long value) { return value * std::pow(byteOrderMultiplier, 5); }

constexpr unsigned long long operator"" _KiB(unsigned long long value) { return value * biByteOrderMultiplier; }
constexpr unsigned long long operator"" _MiB(unsigned long long value) { return value * std::pow(biByteOrderMultiplier, 2); }
constexpr unsigned long long operator"" _GiB(unsigned long long value) { return value * std::pow(biByteOrderMultiplier, 3); }
constexpr unsigned long long operator"" _TiB(unsigned long long value) { return value * std::pow(biByteOrderMultiplier, 4); }
constexpr unsigned long long operator"" _PiB(unsigned long long value) { return value * std::pow(biByteOrderMultiplier, 5); }

} // namespace ByteLiterals

#endif // UTILITIES_BYTELITERALS_H
