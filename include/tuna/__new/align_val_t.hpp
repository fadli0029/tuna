// tuna/__new/align_val_t.hpp
//
// tuna::align_val_t — scoped enumeration for alignment values.
//
// Standard: [new.delete] https://eel.is/c++draft/new.delete
// Reference: https://en.cppreference.com/w/cpp/memory/new/align_val_t
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__new/align_val_t.h

#ifndef TUNA_NEW_ALIGN_VAL_T_HPP
#define TUNA_NEW_ALIGN_VAL_T_HPP

#include <tuna/__config.hpp>
#include <tuna/__cstddef/size_t.hpp>

TUNA_NAMESPACE_BEGIN

// A scoped enum (enum class) rather than a plain integer for two reasons:
// 1. It prevents implicit conversions to/from size_t, so a byte count cannot
//    be accidentally passed where an alignment is expected, or vice versa.
// 2. It disambiguates overloads. The standard already has operator new(size_t),
//    so if alignment were also size_t, operator new(size_t, size_t) would be
//    ambiguous with existing placement forms. A distinct type avoids this.
// The underlying type is size_t because alignments are sizes in bytes.
enum class align_val_t : tuna::size_t {};

TUNA_NAMESPACE_END

#endif  // TUNA_NEW_ALIGN_VAL_T_HPP
