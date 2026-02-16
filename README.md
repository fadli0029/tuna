My implementation of various stuff from the C++ standard library, whichever ones I find I'd learn the most from by building from scratch. Basically this is for my learning and understanding purposes (I attempted implementing `std::vector` from scratch a while ago when I first read Stroustrup's PPP book, oh man I learn a lot just from that attempt).

To be clear, tuna reimplements the standard library API (the libc++ layer: containers, smart pointers, utilities, etc.), not the ABI runtime (the libc++abi layer: exception handling, RTTI, stack unwinding, etc.). The ABI layer is the foundation the language itself sits on; tuna builds on top of it.

Why call it `tuna`? Well I don't know. I know I like fish though. Tuna is just one of many fish types I like. I reserve other fish names for my other projects in the future.

# Design decisions/Remarks
- `tuna` does not and will not support backward compatibility. This is intentional as `tuna` is meant to target the latest C++ standard, not maintain compatibility with older ones.
- `tuna` intends to always be up-to-date with the evolution of C++, meaning: once compiler support for C++26 matures, `tuna` will make an effort to update its implementations.
- `tuna` will intentionally omit features that are removed or not present in C++23. For example, according to [cppreference](https://en.cppreference.com/w/cpp/memory/allocator.html), the member function `address` for `std::allocator` only exists until C++20. So, `tuna::allocator` will not have `address` as one of its member functions.
- `tuna` prioritizes clean, easy-to-follow implementations, but never at the cost of correctness.
- `tuna` additionally implements the [named requirements](https://en.cppreference.com/w/cpp/named_req.html) as concepts. The standard describes these as prose/table-based requirements; `tuna` expresses them as actual concepts, in the spirit of a cleaner, more educational implementation.
- ...

# Credits

- The C++ standard draft: [eel.is/c++draft](https://eel.is/c++draft/), the primary reference for how things should behave.
- [cppreference.com](https://en.cppreference.com/), for its excellent documentation and examples.
- [LLVM's libc++](https://github.com/llvm/llvm-project/tree/main/libcxx), for being an invaluable reference implementation to study and learn from.
- CMake build infrastructure: [cpp-best-practices/cmake_template](https://github.com/cpp-best-practices/cmake_template) by Jason Turner. Files under `cmake/`, `ProjectOptions.cmake`, `Dependencies.cmake`, `CMakePresets.json`, and `configured_files/` come from that template (`myproject` renamed to `tuna`, unneeded deps stripped).
- ...

# TODO's

- [ ] `tuna::allocator` + `allocator_traits`
- [ ] `tuna::vector`
- [ ] `tuna::unique_ptr`
- [ ] `tuna::optional`
- [ ] `tuna::variant`
- [ ] `tuna::string`
- [ ] `tuna::string_view`
- [ ] `tuna::span`
- [ ] `tuna::shared_ptr` + `tuna::weak_ptr`
- [ ] `tuna::function`
- [ ] `tuna::any`
- [ ] `tuna::expected`
- [ ] `tuna::tuple`
- [ ] ...

Note that at the time of writing, there is no plan for `tuna` to implement the standard library's `type_traits`. This may change in the future, but for now, I do not intend to implement it.
