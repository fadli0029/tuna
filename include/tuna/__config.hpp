// tuna/__config.hpp
// https://github.com/fadli0029/tuna
//
// Library-wide configuration header. Every tuna header includes this.
// This is analogous to libc++'s <__config>.
//
// This is the place for macros, compiler workarounds, and definitions
// that need to be visible across the entire library. Right now it's
// minimal, it'll grow as the library does.

#ifndef TUNA_CONFIG_HPP
#define TUNA_CONFIG_HPP

#define TUNA_NAMESPACE_BEGIN namespace tuna {
#define TUNA_NAMESPACE_END }

// sizeof(T) >= 0 is always true since sizeof returns a size_t (unsigned).
// Since sizeof is ill-formed on an incomplete type, if T is
// incomplete, the compiler rejects sizeof(T) before the comparison ever
// happens. The optional message is never shown in the compiler diagnostic
// (sizeof fails first), it's just for developers reading the call site.
// As for the `...` and `__VA_OPT__`: the `...` captures zero or more extra
// arguments into `__VA_ARGS__`. `__VA_OPT__(, __VA_ARGS__)` (C++20) expands
// to nothing when no extra arguments are given, or to `, "the message"` when
// one is provided. This lets the macro work both ways:
//  TUNA_ASSERT_COMPLETE_TYPE(T)         -> static_assert(sizeof(T) >= 0)
//  TUNA_ASSERT_COMPLETE_TYPE(T, "msg")  -> static_assert(sizeof(T) >= 0, "msg")
#define TUNA_ASSERT_COMPLETE_TYPE(T, ...) \
  static_assert(sizeof(T) >= 0 __VA_OPT__(, __VA_ARGS__))

// Suppress warnings about deprecated volatile operations. C++20 deprecated
// certain uses of volatile (volatile-qualified return types, parameters, etc.).
// Some components like declval legitimately produce volatile-qualified return
// types when instantiated with volatile T, which triggers -Wdeprecated-volatile.
// #pragma GCC diagnostic works on both GCC and Clang.
#define TUNA_SUPPRESS_DEPRECATED_PUSH \
  _Pragma("GCC diagnostic push")     \
  _Pragma("GCC diagnostic ignored \"-Wdeprecated\"")
#define TUNA_SUPPRESS_DEPRECATED_POP _Pragma("GCC diagnostic pop")

#endif  // TUNA_CONFIG_HPP
