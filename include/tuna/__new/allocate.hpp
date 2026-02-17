// tuna/__new/allocate.hpp
//
// Internal allocation helpers used by tuna::allocator and friends.
//
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__new/allocate.h

#ifndef TUNA_NEW_ALLOCATE_HPP
#define TUNA_NEW_ALLOCATE_HPP

#include <tuna/__config.hpp>
#include <tuna/__cstddef/size_t.hpp>
#include <tuna/__type_traits/type_identity.hpp>

// Not directly used here (we cast to std::align_val_t for ::operator new),
// but kept here to mirror libc++'s allocate.h include list.
#include <tuna/__new/align_val_t.hpp>

// We need std::align_val_t from <new> because the global allocation functions
// (::operator new, ::operator delete) use std::align_val_t in their
// signatures. tuna::align_val_t is a separate type for tuna's own API; it
// cannot be passed to the real ::operator new. This dependency is intentional
// because <new> declares the ABI runtime's allocation functions, and tuna does
// not reimplement the ABI runtime (that's libc++abi / libsupc++). tuna builds
// on top of it, so at the point where we actually call ::operator new, we must
// use the runtime's types. See tuna's README.md for tuna's philosophies.
#include <new>

TUNA_NAMESPACE_BEGIN

namespace detail {

// Returns true if `align` exceeds the alignment that plain ::operator new
// guarantees. The predefined macro __STDCPP_DEFAULT_NEW_ALIGNMENT__ (C++17,
// [cpp.predefined]) is that guarantee, typically 16 on x86-64. When true, the
// caller must use the alignment-aware overload:
//   ::operator new(size, std::align_val_t(align))
// instead of the plain:
//   ::operator new(size)
// See tuna-notes/stdcpp-default-new-alignment.md for a deeper dive on this.
constexpr bool is_overaligned_for_new(tuna::size_t align) noexcept {
  return align > __STDCPP_DEFAULT_NEW_ALIGNMENT__;
}

// Allocates raw memory for n objects of type T with the given alignment.
//
// __builtin_operator_new is a compiler intrinsic (Clang/GCC) that resolves to
// ::operator new at link time but, unlike a direct ::operator new call, opts
// into allocation elision permitted by [expr.new]/14. See
// tuna-notes/builtin-operator-new.md for details.
//
// The two branches select between the alignment-unaware and alignment-aware
// overloads of ::operator new. If T's alignment fits within what plain
// ::operator new already guarantees (__STDCPP_DEFAULT_NEW_ALIGNMENT__), we
// call the simple form. Otherwise we pass the alignment explicitly via
// std::align_val_t so the runtime can use aligned allocation (e.g.
// aligned_alloc, _aligned_malloc).
template <typename T>
T* allocate(tuna::size_t n, tuna::size_t align = alignof(T)) {
  tuna::size_t size = n * sizeof(T);
  if (is_overaligned_for_new(align)) {
    return static_cast<T*>(__builtin_operator_new(size, static_cast<std::align_val_t>(align)));
  }
  return static_cast<T*>(__builtin_operator_new(size));
}

// Deallocates memory previously obtained from detail::allocate. Passes the
// size to ::operator delete (sized deallocation, C++14) so the runtime can
// reclaim memory without looking up the allocation size itself.
//
// The first parameter uses type_identity_t<T>* instead of T* to prevent the
// compiler from deducing T from the pointer argument. This forces T to be
// deduced from the other arguments or specified explicitly, avoiding
// ambiguity when the pointer type and the intended T differ (e.g. a void*
// being passed). libc++ does the same thing for __libcpp_deallocate.
template <typename T>
void deallocate(type_identity_t<T>* ptr, tuna::size_t n,
                tuna::size_t align = alignof(T)) noexcept {
  tuna::size_t size = n * sizeof(T);
  if (is_overaligned_for_new(align)) {
    __builtin_operator_delete(ptr, size, static_cast<std::align_val_t>(align));
    return;
  }
  __builtin_operator_delete(ptr, size);
}

// Same as deallocate, but without passing the size. Used when the element
// count is not available at the deallocation site.
template <typename T>
void deallocate_unsized(type_identity_t<T>* ptr,
                        tuna::size_t align = alignof(T)) noexcept {
  if (is_overaligned_for_new(align)) {
    __builtin_operator_delete(ptr, static_cast<std::align_val_t>(align));
    return;
  }
  __builtin_operator_delete(ptr);
}

}  // namespace detail

TUNA_NAMESPACE_END

#endif  // TUNA_NEW_ALLOCATE_HPP
