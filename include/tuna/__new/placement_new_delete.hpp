// tuna/__new/placement_new_delete.hpp
// https://github.com/fadli0029/tuna
//
// Placement new and delete declarations. These allow construct_at (and other
// code that needs placement new) to work without pulling in the full <new>
// header.
//
// Placement new and delete live in the global namespace, not in tuna::.
// They are not "tuna's" operators; we just need them declared.
//
// Reference: https://en.cppreference.com/w/cpp/memory/new/operator_new
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__new/placement_new_delete.h

#ifndef TUNA_NEW_PLACEMENT_NEW_DELETE_HPP
#define TUNA_NEW_PLACEMENT_NEW_DELETE_HPP

#include <cstddef>

// Placement new is not constexpr until C++26 (P2747R2). In C++23, the
// constexpr evaluator handles allocation through ::operator new(size_t)
// internally, but placement new goes through a different path that isn't
// supported in constant expressions yet.
// The size_t parameter is unused here (since placement new doesn't allocate),
// it just returns the pointer. But every operator new form must have size_t as
// its first parameter because the compiler fills it in with sizeof(T) at the
// call site. i.e.: it's a uniform signature convention, not a per-overload
// choice.
[[nodiscard]] inline void* operator new(std::size_t, void* ptr) noexcept {
  return ptr;
}
[[nodiscard]] inline void* operator new[](std::size_t, void* ptr) noexcept {
  return ptr;
}

// Matching placement deletes. These are never called directly; the compiler
// calls them implicitly if a placement new expression's constructor throws.
// For placement new (which doesn't actually allocate), the matching delete
// is a no-op, but it must exist so the compiler can guarantee cleanup on
// construction failure.
inline void operator delete(void*, void*) noexcept {}
inline void operator delete[](void*, void*) noexcept {}

#endif  // TUNA_NEW_PLACEMENT_NEW_DELETE_HPP
