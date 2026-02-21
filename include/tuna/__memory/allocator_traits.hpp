// tuna/__memory/allocator_traits.hpp
// https://github.com/fadli0029/tuna
//
// TODO

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
