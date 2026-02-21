// tuna/__cstddef/max_align_t.hpp
// https://github.com/fadli0029/tuna
//
// tuna::max_align_t — a type whose alignment is at least as strict as that of
// every scalar type.
//
// Standard: [support.types.layout] https://eel.is/c++draft/support.types.layout
// Reference: https://en.cppreference.com/w/cpp/types/max_align_t
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__cstddef/max_align_t.h

#ifndef TUNA_CSTDDEF_MAX_ALIGN_T_HPP
#define TUNA_CSTDDEF_MAX_ALIGN_T_HPP

#include <tuna/__config.hpp>

// max_align_t cannot be derived from language builtins (unlike size_t).
// The C standard library defines it in <stddef.h>, so we pull it from there.
#include <stddef.h>

TUNA_NAMESPACE_BEGIN

using max_align_t = ::max_align_t;

TUNA_NAMESPACE_END

#endif  // TUNA_CSTDDEF_MAX_ALIGN_T_HPP
