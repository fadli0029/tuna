// tuna/__config.hpp
//
// Library-wide configuration header. Every tuna header includes this.
// This is analogous to libc++'s <__config>.
//
// This is the place for macros, compiler workarounds, and definitions
// that need to be visible across the entire library. Right now it's
// minimal, it'll grow as the library does.

#ifndef TUNA___CONFIG_HPP
#define TUNA___CONFIG_HPP

#define TUNA_NAMESPACE_BEGIN namespace tuna {
#define TUNA_NAMESPACE_END }

#endif  // TUNA___CONFIG_HPP
