// tuna/__cstddef/size_t.hpp
//
// tuna::size_t — unsigned integer type returned by sizeof.
//
// Standard: [support.types.layout] https://eel.is/c++draft/support.types.layout
// Reference: https://en.cppreference.com/w/cpp/types/size_t
// libc++: https://github.com/llvm/llvm-project/blob/main/libcxx/include/__cstddef/size_t.h

#ifndef TUNA___CSTDDEF_SIZE_T_HPP
#define TUNA___CSTDDEF_SIZE_T_HPP

#include <tuna/__config.hpp>

TUNA_NAMESPACE_BEGIN

// sizeof is a built-in operator that always returns std::size_t. We use
// decltype(sizeof(int)) to derive size_t from the language itself, without
// depending on the host standard library's <cstddef>.
using size_t = decltype(sizeof(int));

TUNA_NAMESPACE_END

#endif  // TUNA___CSTDDEF_SIZE_T_HPP
