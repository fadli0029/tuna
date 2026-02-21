A from-scratch reimplementation of the C++ standard library, specifically the libc++ layer (containers, smart pointers, utilities, etc.), not the ABI runtime (exception handling, RTTI, stack unwinding). The ABI layer is the foundation the language itself sits on; `tuna` builds on top of it.

The goal is to produce clean, readable implementations of standard library components in modern C++ (C++23). Whether you're trying to understand how `std::vector` manages memory or how `std::allocator` actually works, `tuna` aims to be a useful reference. That said, readability is not an excuse to cut corners. `tuna` strives to be correct, precise, and faithful to the standard, including optimizations.

Hopefully, after reading a component in `tuna`, reading the corresponding component in, say, the libc++ implementation of the standard library becomes easier. Of course, more experienced C++ developers never had a hard time reading standard library implementations to begin with, but we try to make the on-ramp gentler for everyone else.

Why call it `tuna`? Well, I don't know. I know I like fish though. `tuna` is just one of many fish types I like. I reserve other fish names for my other projects in the future.

One last thing, you will notice that I use "I" and "we" interchangeably throughout this project. There is no meaningful distinction between them; I just use whichever feels more natural at the time. It also means less rewriting if the project ever has more contributors than just myself.

# Design Decisions, Remarks, & `tuna` Philosophies
- `tuna` uses a `detail` namespace for internal helpers (e.g. `tuna::detail::throw_bad_array_new_length()`). libc++ uses `__`-prefixed names for this purpose (e.g. `std::__throw_bad_array_new_length()`), but double-underscore identifiers are reserved by the C++ standard for the implementation. Since `tuna` is a user-space library, not the compiler's standard library, it uses `tuna::detail::` instead.
- `tuna` does not concern itself with platform-specific ABI compatibility, cross-platform workarounds, or feature-detection ifdefs. libc++ files have a lot of such scaffolding, for reasons like Windows/MSVC ABI compat, C++03 fallbacks, etc. `tuna` chooses to skip all of that and implements the C++23 version only. Basically, `tuna` only cares about showing how things work under the hood, not the portability machinery around it.
- `tuna` does not and will not support backward compatibility. This is intentional as `tuna` is meant to target the latest C++ standard, not maintain compatibility with older ones.
- `tuna` intends to always be up-to-date with the evolution of C++, meaning: once compiler support for C++26 matures, `tuna` will make an effort to update its implementations as necessary.
- `tuna` will intentionally omit features that are removed or not present in C++23. For example, according to [cppreference](https://en.cppreference.com/w/cpp/memory/allocator.html), the member function `address` for `std::allocator` only exists until C++20. So, `tuna::allocator` will not have `address` as one of its member functions.
- `tuna` prioritizes clean, easy-to-follow implementations, but never at the cost of correctness.
- `tuna` enforces the standard's prohibition on user specializations of certain templates with a direct `static_assert(false, "...")` and a comment explaining the restriction (libc++ uses `_LIBCPP_NO_SPECIALIZATIONS` for this; `tuna` chooses to keep it explicit).
- `tuna` additionally implements the [named requirements](https://en.cppreference.com/w/cpp/named_req.html) as concepts. The standard describes these as prose/table-based requirements; `tuna` expresses them as actual concepts, in the spirit of a cleaner, more educational implementation.
- ...

# Credits/References

- The C++ standard draft: [eel.is/c++draft](https://eel.is/c++draft/), the primary reference for how things should behave.
- [cppreference.com](https://en.cppreference.com/), for its excellent documentation and examples.
- [LLVM's libc++](https://github.com/llvm/llvm-project/tree/main/libcxx), for being an invaluable reference implementation to study and learn from.
- CMake build infrastructure: [cpp-best-practices/cmake_template](https://github.com/cpp-best-practices/cmake_template) by Jason Turner. Files under `cmake/`, `ProjectOptions.cmake`, `Dependencies.cmake`, and `CMakePresets.json` come from that template (`myproject` renamed to `tuna`, unneeded deps stripped, etc.).
- [C++ Templates - The Complete Guide, 2nd Edition - Vandevoorde et. al.](https://tmplbook.com/): great reference for many things during the development of this project, especially regarding type traits.
- ...

# Regarding AI Usage
I started this project for the fun of it (and for learning, understanding the why's of things in C++, etc.). If I use AI to do a lot of things for me in this project, prompting it then sitting and waiting until it is done with its tasks, where is the *fun* in that?

This is not to say I am against AI or that I don't use AI. I use it and I like it, in fact, I use it at work, for learning, for some of my projects, for many things basically.

Unfortunately, not every part of a project is equally fun. Some stuff is just boring and mundane, nobody wants to do that. That being said, AI is used in the `tuna` project in the following manner:

- Mundane/repetitive tasks: CMake scaffolding (in accordance to best practices; we use Jason Turner's template for that), boilerplate test harnesses, file bootstrapping (include guards, header comments, namespace blocks, etc.), reformatting, etc.
- Documentation: writing and editing README sections, notes, code comments (sometimes AI words things better than I would), etc.
- Trivial implementations: components where the implementation is too trivial to learn much from writing by hand (subjective, of course; what I find trivial, others may not, and vice versa). For example, `tuna::nullptr_t` is just `using nullptr_t = decltype(nullptr);`.
- ...

# TODOs

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
