#pragma once
#include <concepts>
#include <random>
#include <type_traits>

namespace utils {

template <typename T>
requires std::integral<T> or std::floating_point<T>
T random(T a, T b) {
    thread_local std::mt19937 gen;
    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> distrib(a, b);
        return distrib(gen);
    } else {
        std::uniform_real_distribution<T> distrib(a, b);
        return distrib(gen);
    }
}

template <typename T>
requires std::floating_point<T>
T normal_distribution(T a, T b) {
    thread_local std::mt19937 gen;
    std::normal_distribution<T> normalDistrib(a, b);
    return normalDistrib(gen);
}

}
