#pragma once
#include <random>
#include <type_traits>
#include <concepts>


namespace utils {

template <typename T>
concept Numarical = std::is_integral<T>::value or std::is_floating_point<T>::value;


template <typename Numarical>
Numarical random(Numarical a, Numarical b) {
    thread_local std::mt19937 gen;
    if constexpr (std::is_integral<Numarical>::value) {
        std::uniform_int_distribution<Numarical> distrib(a, b);
        return distrib(gen);
    } else {
        std::uniform_real_distribution<Numarical> distrib(a, b);
        return distrib(gen);
    }
}

// template <typename T>
// T rand(T a, T b) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     if constexpr (std::is_integral<T>::value) {
//         std::uniform_int_distribution<T> distrib(a, b);
//         return distrib(gen);
//     } else {
//         std::uniform_real_distribution<T> distrib(a, b);
//         return distrib(gen);
//     }
// }

}
