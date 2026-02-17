// tuna/__cstddef/ptrdiff_t.hpp
//
// tuna::ptrdiff_t — signed integer type returned by pointer subtraction.
//
// Standard: [support.types.layout] https://eel.is/c++draft/support.types.layout
// Reference: https://en.cppreference.com/w/cpp/types/ptrdiff_t
// libc++: https://github.com/llvm/llvm-project/blob/main/libcxx/include/__cstddef/ptrdiff_t.h

#ifndef TUNA_CSTDDEF_PTRDIFF_T_HPP
#define TUNA_CSTDDEF_PTRDIFF_T_HPP

#include <tuna/__config.hpp>

TUNA_NAMESPACE_BEGIN

// Pointer subtraction always yields std::ptrdiff_t. We derive it from the
// language itself, without depending on the host standard library's <cstddef>.
using ptrdiff_t =
    decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr));

TUNA_NAMESPACE_END

#endif // TUNA_CSTDDEF_PTRDIFF_T_HPP
