// tuna/__memory/addressof.hpp
// https://github.com/fadli0029/tuna
//
// tuna::addressof -- obtains the actual address of an object, even if
// operator& is overloaded.
//
// Standard: [specialized.addressof] https://eel.is/c++draft/specialized.addressof
// Reference: https://en.cppreference.com/w/cpp/memory/addressof
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__memory/addressof.h

#ifndef TUNA_MEMORY_ADDRESSOF_HPP
#define TUNA_MEMORY_ADDRESSOF_HPP

#include <tuna/__config.hpp>

TUNA_NAMESPACE_BEGIN

template <typename T>
[[nodiscard]] constexpr T* addressof(T& arg) noexcept {
  return __builtin_addressof(arg);
}

// deleted to prevent taking the address of rvalues. Without this, a call like
// addressof(T{}) would bind to the lvalue reference overload above via a
// const lvalue reference (temporaries can bind to const T&), giving back a
// pointer to a temporary that's about to be destroyed.
template <typename T>
T* addressof(const T&&) = delete;

TUNA_NAMESPACE_END

#endif  // TUNA_MEMORY_ADDRESSOF_HPP
