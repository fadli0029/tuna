// tuna/__memory/allocator.hpp
// https://github.com/fadli0029/tuna
//
// tuna::allocator — the default allocator.
//
// Standard: [default.allocator] https://eel.is/c++draft/default.allocator
// Reference: https://en.cppreference.com/w/cpp/memory/allocator
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__memory/allocator.h

#ifndef TUNA_MEMORY_ALLOCATOR_HPP
#define TUNA_MEMORY_ALLOCATOR_HPP

#include <tuna/__config.hpp>
#include <tuna/__cstddef/ptrdiff_t.hpp>
#include <tuna/__cstddef/size_t.hpp>
#include <tuna/__new/allocate.hpp>

// at the time of writing, tuna does not reimplement many of the stuff in
// <type_traits>. This may change in the future.
#include <type_traits>  // is_const_v, is_volatile_v, true_type

TUNA_NAMESPACE_BEGIN

template <typename T>
class allocator {
  static_assert(!std::is_const_v<T>, "tuna::allocator does not support const types");
  static_assert(!std::is_volatile_v<T>, "tuna::allocator does not support volatile types");

 public:
  using value_type = T;
  using size_type = tuna::size_t;
  using difference_type = tuna::ptrdiff_t;
  using propagate_on_container_move_assignment = std::true_type;

  // default allocators are stateless, nothing to do here.
  constexpr allocator() noexcept = default;

  // default allocators are stateless, nothing to do here.
  constexpr allocator(const allocator& other) noexcept {}

  // default allocators are stateless, nothing to do here.
  template <typename U>
  constexpr allocator(const allocator<U>& other) noexcept {}

  // default allocators are stateless, nothing to do here.
  constexpr allocator& operator=(const allocator&) = default;

  // default allocators are stateless, nothing to do here.
  constexpr ~allocator() = default;

  [[nodiscard]] constexpr T* allocate(tuna::size_t n) {
    TUNA_ASSERT_COMPLETE_TYPE(T,
                              "cannot allocate memory for an incomplete type");

    // libc++ uses allocator_traits<allocator>::max_size(*this) here, but tuna
    // does not have allocator_traits yet. The check is the same: the maximum
    // number of T's that can fit in size_t bytes. If n exceeds that, the
    // multiplication n * sizeof(T) would overflow, so we bail.
    // TODO: replace with allocator_traits<allocator>::max_size(*this) once
    // allocator_traits is implemented.
    if (n > tuna::size_t(-1) / sizeof(T)) {
      // TODO: throw tuna::bad_array_new_length once tuna/__new/exceptions.hpp
      // is implemented. For now, use the standard library's version.
      throw std::bad_array_new_length();
    }

    // Two code paths: constexpr evaluation vs runtime.
    //
    // During constant evaluation, the compiler's constexpr interpreter handles
    // ::operator new internally (it creates synthetic memory, not a real heap
    // allocation). __builtin_operator_new is not recognized by the constexpr
    // evaluator, so we must call ::operator new directly in that context.
    //
    // At runtime, detail::allocate uses __builtin_operator_new, which resolves
    // to the same ::operator new but opts into allocation elision permitted by
    // [expr.new]/14. See tuna-notes/builtin-operator-new.md.
    if consteval {
      return static_cast<T*>(::operator new(n * sizeof(T)));
    } else {
      return detail::allocate<T>(n);
    }
  }

  // TODO
  //   notes:
  //   - need to implement tuna/__memory/allocation_result.hpp first
  // [[nodiscard]] constexpr allocation_result<T*>
  // allocate_at_least(tuna::size_t n);

  constexpr void deallocate(T* p, tuna::size_t n) {
    // Same consteval split as allocate. See the comment there.
    if consteval {
      ::operator delete(p);
    } else {
      detail::deallocate<T>(p, n);
    }
  }
};

// Since default allocators are stateless, two allocators are always equal,
// even if they allocate different types (e.g. allocator<int> ==
// allocator<double>). C++20's operator== rewrite rules auto-generate operator!=
// from this.
template <typename T1, typename T2>
constexpr bool operator==(const allocator<T1>&, const allocator<T2>&) noexcept {
  return true;
}

TUNA_NAMESPACE_END

#endif  // TUNA_MEMORY_ALLOCATOR_HPP
