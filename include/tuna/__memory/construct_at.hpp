// tuna/__memory/construct_at.hpp
// https://github.com/fadli0029/tuna
//
// tuna::construct_at, tuna::destroy_at
//
// Standard: [specialized.construct] https://eel.is/c++draft/specialized.construct
//           [specialized.destroy] https://eel.is/c++draft/specialized.destroy
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
#include <type_traits>

TUNA_NAMESPACE_BEGIN

// TODO: implement construct_at
// TODO: implement destroy_at

TUNA_NAMESPACE_END

#endif  // TUNA_MEMORY_CONSTRUCT_AT_HPP
