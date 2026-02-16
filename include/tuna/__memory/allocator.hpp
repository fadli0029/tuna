// tuna/__memory/allocator.hpp
//
// tuna::allocator — the default allocator.
//
// Standard: [default.allocator] https://eel.is/c++draft/default.allocator
// Reference: https://en.cppreference.com/w/cpp/memory/allocator
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__memory/allocator.h

#ifndef TUNA___MEMORY_ALLOCATOR_HPP
#define TUNA___MEMORY_ALLOCATOR_HPP

#include <tuna/__config.hpp>
#include <tuna/__cstddef/ptrdiff_t.hpp>
#include <tuna/__cstddef/size_t.hpp>

// at the time of writing, tuna does not reimplement <type_traits>. This may
// change in the future.
#include <type_traits>  // std::true_type

TUNA_NAMESPACE_BEGIN

template <typename T>
class allocator {
 public:
  using value_type = T;
  using size_type = tuna::size_t;
  using difference_type = tuna::ptrdiff_t;
  using propagate_on_container_move_assignment = std::true_type;

  constexpr allocator() noexcept;

  constexpr allocator(const allocator&) noexcept;

  template <typename U>
  constexpr allocator(const allocator<U>&) noexcept;

  constexpr ~allocator();

  constexpr allocator& operator=(const allocator&) = default;

  constexpr T* allocate(tuna::size_t n);

  // TODO
  //   notes:
  //   - need to implement tuna/_memory/allocation_result.hpp first
  // constexpr allocation_result<T*> allocate_at_least(tuna::size_t n);

  constexpr void deallocate(T* p, tuna::size_t n);
};

TUNA_NAMESPACE_END

#endif  // TUNA___MEMORY_ALLOCATOR_HPP
