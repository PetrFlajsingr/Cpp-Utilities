//
// Created by Petr on 18.11.2019.
//

#ifndef UTILITIES_CHRONO_H
#define UTILITIES_CHRONO_H

template <typename T>
static inline constexpr bool is_duration_v =
        is_specialization<T, std::chrono::duration>::value;

#endif //UTILITIES_CHRONO_H
