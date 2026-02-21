// tuna/__type_traits/type_identity.hpp
// https://github.com/fadli0029/tuna
//
// tuna::type_identity, tuna::type_identity_t
//
// Standard: [meta.trans.other] https://eel.is/c++draft/meta.trans.other
// Reference: https://en.cppreference.com/w/cpp/types/type_identity
// libc++:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__type_traits/type_identity.h

#ifndef TUNA_TYPE_TRAITS_TYPE_IDENTITY_HPP
#define TUNA_TYPE_TRAITS_TYPE_IDENTITY_HPP

#include <tuna/__config.hpp>

TUNA_NAMESPACE_BEGIN

// type_identity wraps a type T so that it becomes a non-deduced context.
// This is useful for preventing template argument deduction on specific
// parameters, forcing the caller to rely on deduction from other arguments
// or to specify the template argument explicitly.
// Here's a good and usefull read on "What’s the deal with std::type_identity?":
// https://devblogs.microsoft.com/oldnewthing/20240607-00/?p=109865

template <typename T>
struct type_identity {
  using type = T;
};

template <typename T>
using type_identity_t = typename type_identity<T>::type;

TUNA_NAMESPACE_END

#endif  // TUNA_TYPE_TRAITS_TYPE_IDENTITY_HPP
