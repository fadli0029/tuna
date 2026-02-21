// tuna/__utility/declval.hpp
// https://github.com/fadli0029/tuna
//
// tuna::declval -- converts a type to a reference in unevaluated contexts.
//
// Standard: [declval] https://eel.is/c++draft/declval
// Reference: https://en.cppreference.com/w/cpp/utility/declval
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__utility/declval.h

#ifndef TUNA_UTILITY_DECLVAL_HPP
#define TUNA_UTILITY_DECLVAL_HPP

#include <tuna/__config.hpp>

TUNA_NAMESPACE_BEGIN

namespace detail {

// Two overloads to handle void types. T&& is ill-formed when T is void (or
// cv-void), so the int overload (preferred) handles non-void types, and the
// long overload (fallback via implicit int-to-long conversion) handles void.
//
// TUNA_SUPPRESS_DEPRECATED_PUSH/POP suppresses -Wdeprecated-volatile for
// volatile-qualified T (e.g. declval<volatile int>() produces volatile int&&).
TUNA_SUPPRESS_DEPRECATED_PUSH
template <typename T>
T&& declval_helper(int) noexcept;

template <typename T>
T declval_helper(long) noexcept;
TUNA_SUPPRESS_DEPRECATED_POP

}  // namespace detail

template <typename T>
decltype(detail::declval_helper<T>(0)) declval() noexcept {
  static_assert(!__is_same(T, T),
                "tuna::declval can only be used in an unevaluated context");
}

TUNA_NAMESPACE_END

#endif  // TUNA_UTILITY_DECLVAL_HPP
