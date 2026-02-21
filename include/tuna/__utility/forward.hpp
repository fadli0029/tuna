// tuna/__utility/forward.hpp
// https://github.com/fadli0029/tuna
//
// tuna::forward -- perfect forwarding.
//
// Standard: [forward] https://eel.is/c++draft/forward
// Reference: https://en.cppreference.com/w/cpp/utility/forward
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__utility/forward.h

#ifndef TUNA_UTILITY_FORWARD_HPP
#define TUNA_UTILITY_FORWARD_HPP

#include <tuna/__config.hpp>

// TODO: replace with tuna::remove_reference_t and tuna::is_lvalue_reference
// once tuna reimplements those type traits.
#include <type_traits>

TUNA_NAMESPACE_BEGIN

template <typename T>
[[nodiscard]] constexpr T&& forward(std::remove_reference_t<T>& t) noexcept {
  return static_cast<T&&>(t);
}

template <typename T>
[[nodiscard]] constexpr T&& forward(std::remove_reference_t<T>&& t) noexcept {
  static_assert(!std::is_lvalue_reference_v<T>,
                "cannot forward an rvalue as an lvalue");
  return static_cast<T&&>(t);
}

TUNA_NAMESPACE_END

#endif  // TUNA_UTILITY_FORWARD_HPP
