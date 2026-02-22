// tuna/__memory/construct_at.hpp
// https://github.com/fadli0029/tuna
//
// tuna::construct_at, tuna::destroy_at
//
// Standard: [specialized.construct] https://eel.is/c++draft/specialized.construct
//           [specialized.destroy]   https://eel.is/c++draft/specialized.destroy
// Reference: https://en.cppreference.com/w/cpp/memory/construct_at
//            https://en.cppreference.com/w/cpp/memory/destroy_at
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__memory/construct_at.h

#ifndef TUNA_MEMORY_CONSTRUCT_AT_HPP
#define TUNA_MEMORY_CONSTRUCT_AT_HPP

#include <tuna/__config.hpp>
#include <tuna/__memory/addressof.hpp>
#include <tuna/__new/placement_new_delete.hpp>
#include <tuna/__utility/declval.hpp>
#include <tuna/__utility/forward.hpp>

// TODO: replace with tuna::is_array once tuna reimplements it.
#include <cassert>
#include <type_traits>

TUNA_NAMESPACE_BEGIN

// The requires clause checks, in an unevaluated context, whether placement-new
// of T from Args is well-formed. declval conjures fake values; nothing runs.
// If T is not constructible from Args, the expression is ill-formed, the
// constraint fails, and construct_at drops out of the overload set instead of
// producing a hard error inside the function body. The standard mandates this:
// [specialized.construct] lists it as a Constraint, meaning SFINAE/concepts,
// not a hard error.
//
// static_cast<void*> in the return statement ensures we select the standard's
// non-replaceable placement new (void* operator new(size_t, void*)), not a
// user-defined global operator new overload that might be a better match for
// T*. The :: already prevents class-specific operator new from being found;
// the cast handles global overloads.
template <typename T, typename... Args>
  requires requires {
    ::new (tuna::declval<void*>()) T(tuna::declval<Args>()...);
  }
constexpr T* construct_at(T* ptr, Args&&... args) {
  assert(ptr != nullptr && "null pointer given to construct_at");
  return ::new (static_cast<void*>(ptr)) T(tuna::forward<Args>(args)...);
}

template <class T>
constexpr void destroy_at(T* ptr) {
  assert(ptr != nullptr && "null pointer given to destroy_at");
  if constexpr (std::is_array_v<T>) {
    // auto& works here since array elements are always lvalues. auto&& is
    // strictly more general (binds to anything: lvalues, rvalues, const,
    // non-const) and has no downside in a range-for. We use auto&& to mirror
    // libc++. See:
    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3853.htm
    // https://quuxplusone.github.io/blog/2018/12/15/autorefref-always-works/
    for (auto&& elem : *ptr) {
      (destroy_at)(tuna::addressof(elem));
    }
  } else {
    ptr->~T();
  }
}

TUNA_NAMESPACE_END

#endif  // TUNA_MEMORY_CONSTRUCT_AT_HPP
