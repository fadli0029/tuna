// tuna/__cstddef/nullptr_t.hpp
// https://github.com/fadli0029/tuna
//
// tuna::nullptr_t — the type of the null pointer literal nullptr.
//
// Standard: [support.types.nullptr] https://eel.is/c++draft/support.types.nullptr
// Reference: https://en.cppreference.com/w/cpp/types/nullptr_t
// libc++: https://github.com/llvm/llvm-project/blob/main/libcxx/include/__cstddef/nullptr_t.h

#ifndef TUNA_CSTDDEF_NULLPTR_T_HPP
#define TUNA_CSTDDEF_NULLPTR_T_HPP

#include <tuna/__config.hpp>

TUNA_NAMESPACE_BEGIN

// The nullptr literal always has type std::nullptr_t. We derive it from the
// language itself, without depending on the host standard library's <cstddef>.
using nullptr_t = decltype(nullptr);

TUNA_NAMESPACE_END

#endif  // TUNA_CSTDDEF_NULLPTR_T_HPP
