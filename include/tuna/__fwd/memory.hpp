// tuna/__fwd/memory.hpp
// https://github.com/fadli0029/tuna
//
// Forward declarations for <tuna/memory> components.
//
// These exist to break circular includes. For example, allocator_traits needs
// to name allocator<T> (for its specialization and detection traits) but does
// not need it to be a complete type. Including the full allocator header from
// allocator_traits would create a cycle, so we forward-declare here instead.
//
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__fwd/memory.h

#ifndef TUNA_FWD_MEMORY_HPP
#define TUNA_FWD_MEMORY_HPP

#include <tuna/__config.hpp>

TUNA_NAMESPACE_BEGIN

template <typename T>
class allocator;

// TODO: shared_ptr

TUNA_NAMESPACE_END

#endif  // TUNA_FWD_MEMORY_HPP
