My implementation of various stuff from the C++ standard library, whichever ones I find I'd learn the most from by building from scratch. Basically this is for my learning and understanding purposes (I attempted implementing `std::vector` from scratch a while ago when I first read Stroustrup's PPP book, oh man I learn a lot just from that attempt).

To be clear, tuna reimplements the standard library API (the libc++ layer: containers, smart pointers, utilities, etc.), not the ABI runtime (the libc++abi layer: exception handling, RTTI, stack unwinding, etc.). The ABI layer is the foundation the language itself sits on; tuna builds on top of it.

Why call it `tuna`? Well I don't know. I know I like fish though. Tuna is just one of many fish types I like. I reserve other fish names for my other projects in the future.

# Credits

- CMake build infrastructure: [cpp-best-practices/cmake_template](https://github.com/cpp-best-practices/cmake_template) by Jason Turner. Files under `cmake/`, `ProjectOptions.cmake`, `Dependencies.cmake`, `CMakePresets.json`, and `configured_files/` come from that template (`myproject` renamed to `tuna`, unneeded deps stripped).
- ...

# TODO's

- [ ] `tuna::vector`
- [ ] `tuna::unique_ptr`
- [ ] `tuna::optional`
- [ ] `tuna::variant`
- [ ] `tuna::string`
- [ ] `tuna::string_view`
- [ ] `tuna::span`
- [ ] `tuna::allocator` + `allocator_traits`
- [ ] `tuna::shared_ptr` + `tuna::weak_ptr`
- [ ] `tuna::function`
- [ ] `tuna::any`
- [ ] `tuna::expected`
- [ ] `tuna::tuple`
- [ ] ...

# Regarding The Implementation Order

The order above is intentional (though it may be subject to changes). The idea is to build the concrete thing first, feel the problems it has, then build the abstraction that solves those problems. For example, allocator comes after containers (not before) because I feel I can understand/appreciate better what an allocator abstracts *after* I've manually managed memory inside a container. But of course going the other way also works, this is just my preference.

Note that `type_traits` are not listed as a standalone item. I plan to build them incrementally: when `tuna::vector` needs `std::is_nothrow_move_constructible` to decide between move and copy during reallocation, I implement that trait. When `tuna::unique_ptr` needs `std::remove_extent` for array support, I implement it. By the end of the list, I think quite a lot of stuff from `<type_traits>` will have been built, each trait motivated by a clear use case.
