//
// Created by Petr on 03.12.2019.
//

#ifndef UTILITIES_ZIP_H
#define UTILITIES_ZIP_H

#include <type_traits>
#include <utility>
#include "meta/meta.h"


namespace details {
    template<typename Int, typename, Int Begin>
    struct increasing_integer_range;

    template<typename Int, Int... N, Int Begin>
    struct increasing_integer_range<Int, std::integer_sequence<Int, N...>, Begin> :
            std::integer_sequence<Int, N + Begin...> {
    };

    template<typename Int, typename, Int Begin>
    struct decreasing_integer_range;

    template<typename Int, Int... N, Int Begin>
    struct decreasing_integer_range<Int, std::integer_sequence<Int, N...>, Begin> :
            std::integer_sequence<Int, Begin - N...> {
    };
}

template<typename Int, Int Begin, Int End,
        bool Increasing = (Begin < End)>
struct integer_range;

template<typename Int, Int Begin, Int End>
struct integer_range<Int, Begin, End, true> :
        details::increasing_integer_range<
                Int,
                std::make_integer_sequence<Int, End - Begin>,
                Begin> {
};

template<typename Int, Int Begin, Int End>
struct integer_range<Int, Begin, End, false> :
        details::decreasing_integer_range<
                Int,
                std::make_integer_sequence<Int, Begin - End>,
                Begin> {
};

template<std::size_t Begin, std::size_t End>
using index_range = integer_range<std::size_t, Begin, End>;

template<size_t SN, size_t DN, class TSrc, class TDest, class Func>
void tuple_call_assign(TSrc &&source, TDest &target, Func f) {
    std::get<DN>(target) = f(std::get<SN>(std::forward<TSrc>(source)));
}

template<size_t From, size_t To, class TSrc, class TDest, class Func, size_t...Is, size_t...DIs>
void tuple_transform(TSrc &&source, TDest &target, Func f,
                     std::index_sequence<Is...>, std::index_sequence<DIs...>) {
    using expander = int[];
    (void) expander{0, (tuple_call_assign<Is, DIs>(std::forward<TSrc>(source), target, f), 0)...};
}

template<size_t From, size_t To, size_t FromDest, class TSrc, class TDest, class Func>
void tuple_transform(TSrc &&source, TDest &target, Func f) {
    static_assert(To > From, "Range must be increasing");
    static_assert(To <= std::tuple_size<std::decay_t<TSrc>>::value + 1,
                  "Range must be valid for source tuple");
    constexpr size_t RangeSize = To - From;
    static_assert(FromDest + RangeSize <= std::tuple_size<std::decay_t<TDest>>::value,
                  "Range must be valid for target tuple");

    tuple_transform<From, To>(std::forward<TSrc>(source), target, f,
                              index_range<From, To>(), index_range<FromDest, FromDest + RangeSize>());
}

template<class Func, class Tuple, size_t...Is>
void for_each_in_tuple(Func f, Tuple &&tuple, std::index_sequence<Is...>) {
    using expander = int[];
    (void) expander{0, ((void) f(std::get<Is>(std::forward<Tuple>(tuple))), 0)...};
}

template<class Func, class Tuple>
void for_each_in_tuple(Func f, Tuple &&tuple) {
    for_each_in_tuple(f, std::forward<Tuple>(tuple),
                      std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>());
}

template<typename Func, typename Tuple1, typename Tuple2, size_t...Is>
void for_each_in_tuple_pair(Func f, Tuple1 &&tuple, Tuple2 &&tuple2, std::index_sequence<Is...>) {
    using expander = int[];
    (void) expander{0, ((void) f(std::get<Is>(std::forward<Tuple1>(tuple)),
                                 std::get<Is>(std::forward<Tuple2>(tuple2))), 0)...};
}

template<typename Func, typename Tuple1, typename Tuple2>
void for_each_in_tuple_pair(Func f, Tuple1 &&tuple, Tuple2 &&tuple2) {
    for_each_in_tuple_pair(f, std::forward<Tuple1>(tuple), std::forward<Tuple2>(tuple2),
                           std::make_index_sequence<std::tuple_size<std::decay_t<Tuple1>>::value>());
}

template<typename ...T>
class Zip {
public:
    explicit Zip(const T &...vals) : beginIters(std::begin(vals)...), endIters(std::end(vals)...) {}

    struct iterator {
        using value_type = std::tuple<std::decay_t<decltype(*std::declval<decltype(std::begin(
                std::declval<T>()))>())>...>;
        std::tuple<decltype(std::begin(std::declval<T>()))...> iters;

        explicit iterator(std::tuple<decltype(std::begin(std::declval<T>()))...> iters) : iters(iters) {}

        iterator(const iterator &other) = default;

        iterator(iterator &&other) noexcept = default;

        iterator &operator=(const iterator &other) = default;

        iterator &operator=(iterator &&other) noexcept = default;

        bool operator==(const iterator &rhs) const {
            bool areSame = false;
            for_each_in_tuple_pair([&areSame](const auto &first, const auto &second) {
                areSame = areSame || first == second;
            }, iters, rhs.iters);
            return areSame;
        }

        bool operator!=(const iterator &rhs) const {
            return !(rhs == *this);
        }

        value_type operator*() {
            value_type result;
            tuple_transform<0, std::tuple_size_v<value_type>, 0>(iters, result, [](auto &it) { return *it; });
            return result;
        }

        iterator &operator++() {
            for_each_in_tuple([](auto &val) { ++val; }, iters);
            return *this;
        }

        iterator operator++(int) {
            iterator result{*this};
            ++*this;
            return result;
        }
    };

    iterator begin() {
        return iterator(beginIters);
    }

    iterator end() {
        return iterator(endIters);
    }

private:
    std::tuple<decltype(std::begin(std::declval<T>()))...> beginIters;
    std::tuple<decltype(std::end(std::declval<T>()))...> endIters;
};

template<typename ...T>
Zip<T...> zip(const T &...vals) {
    return Zip(vals...);
}

#endif //UTILITIES_ZIP_H
