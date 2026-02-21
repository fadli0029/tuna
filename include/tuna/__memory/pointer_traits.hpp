// tuna/__memory/pointer_traits.hpp
// https://github.com/fadli0029/tuna
//
// tuna::pointer_traits -- provides information about pointer-like types.
//
// Standard: [pointer.traits] https://eel.is/c++draft/pointer.traits
// Reference: https://en.cppreference.com/w/cpp/memory/pointer_traits
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__memory/pointer_traits.h

#ifndef TUNA_MEMORY_POINTER_TRAITS_HPP
#define TUNA_MEMORY_POINTER_TRAITS_HPP

#include <tuna/__config.hpp>
#include <tuna/__cstddef/ptrdiff_t.hpp>
#include <tuna/__memory/addressof.hpp>
#include <tuna/__utility/declval.hpp>
#include <tuna/__utility/forward.hpp>

// TODO: replace with tuna's own type traits once reimplemented. libc++ uses
// conditional, conjunction, decay, detected_or, enable_if, integral_constant,
// is_class, is_function, is_void, void_t here. Many of these may be
// unnecessary if we use requires/if constexpr instead of the detection idiom.
#include <type_traits>

TUNA_NAMESPACE_BEGIN

// TODO: implement pointer_traits primary template (for fancy pointers)
// TODO: implement pointer_traits<T*> specialization (for raw pointers)

TUNA_NAMESPACE_END

#endif  // TUNA_MEMORY_POINTER_TRAITS_HPP
