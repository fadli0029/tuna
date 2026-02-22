// tuna/__utility/declval.hpp
// https://github.com/fadli0029/tuna
//
// tuna::declval -- converts a type to a reference in unevaluated contexts.
//
// Standard: [declval] https://eel.is/c++draft/declval
// Reference: https://en.cppreference.com/w/cpp/utility/declval
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__utility/declval.h
// Notes: See tuna-notes/declval.md for a detailed walkthrough.

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

// The return type is decltype(declval_helper<T>(0)) rather than T&& because
// void&& is ill-formed. The indirection through declval_helper lets overload
// resolution pick the T&& overload for non-void types (int param, exact match)
// and fall back to the T overload for void types (long param, SFINAE removes
// the T&& overload since void&& is ill-formed).
//
// The static_assert uses !__is_same(T, T) (always false) to prevent evaluated
// use. The condition is dependent on T so the compiler defers the check to
// instantiation time rather than diagnosing it at parse time. In C++23,
// static_assert(false) in templates is well-formed until instantiation (P2593R1)
// so the dependent trick is no longer strictly necessary, but we keep it to
// mirror libc++.
template <typename T>
decltype(detail::declval_helper<T>(0)) declval() noexcept {
  static_assert(!__is_same(T, T),
                "tuna::declval can only be used in an unevaluated context");
}

TUNA_NAMESPACE_END

#endif  // TUNA_UTILITY_DECLVAL_HPP
