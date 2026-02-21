// tuna/__memory/allocator_traits.hpp
// https://github.com/fadli0029/tuna
//
// tuna::allocator_traits -- uniform interface to allocator properties and
// operations.
//
// Standard: [allocator.traits] https://eel.is/c++draft/allocator.traits
// Reference: https://en.cppreference.com/w/cpp/memory/allocator_traits
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__memory/allocator_traits.h

#ifndef TUNA_MEMORY_ALLOCATOR_TRAITS_HPP
#define TUNA_MEMORY_ALLOCATOR_TRAITS_HPP

#include <tuna/__config.hpp>
#include <tuna/__cstddef/ptrdiff_t.hpp>
#include <tuna/__cstddef/size_t.hpp>
#include <tuna/__fwd/memory.hpp>
#include <tuna/__memory/construct_at.hpp>
#include <tuna/__memory/pointer_traits.hpp>
#include <tuna/__utility/declval.hpp>
#include <tuna/__utility/forward.hpp>

// TODO: replace with tuna's own type traits once reimplemented. libc++ uses
// detected_or, enable_if, is_constructible, is_empty, is_same, make_unsigned,
// remove_reference, void_t here. Many of these may be unnecessary if we use
// requires/if constexpr instead of the detection idiom.
#include <type_traits>

// TODO: replace with tuna's own numeric_limits once reimplemented. Used by
// max_size for numeric_limits<size_type>::max() / sizeof(value_type).
#include <limits>

TUNA_NAMESPACE_BEGIN

/*

TODO: thinking of doing something like this instead of implementing
detected_or_t like libc++ because i think this is cleaner/more modern (although
it's more code since for detected_or_t you write it once and use for all) and
aligns with tuna philosophies?

namespace detail {

  template <typename Alloc>
  consteval auto pointer_for() {
    if constexpr (requires { typename Alloc::pointer; }) {
      return tuna::type_identity<typename Alloc::pointer>{};
    } else {
      return tuna::type_identity<typename Alloc::value_type*>{};
    }
  }
  template <typename Alloc>
  using pointer_for_t = typename decltype(detail::pointer_for<Alloc>())::type;

  // same idea for others...
  // ... etc.

}  // namespace detail


// then we can do this:
template <typename Alloc>
struct allocator_traits {
    using allocator_type    = Alloc;
    using value_type        = typename Alloc::value_type;
    using pointer           = detail::pointer_for_t<Alloc>;
    // using const_pointer  = detail::const_pointer_for_t<Alloc, pointer>;
    // using void_pointer   = detail::void_pointer_for_t<Alloc, pointer>;
    // ... etc.
};

*/

// TODO: implement allocator_traits

// the standard forbids user specializations of allocator_traits
// [allocator.traits.general] https://eel.is/c++draft/allocator.traits.general
// template <typename T>
// struct allocator_traits<T*> {
//   static_assert(false,
//                 "specialization of tuna::allocator_traits is not allowed");
// };

TUNA_NAMESPACE_END

#endif  // TUNA_MEMORY_ALLOCATOR_TRAITS_HPP
