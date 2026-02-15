# Example:
#
# add_executable(fuzz_tester fuzz_tester.cpp)
# target_link_libraries(fuzz_tester
#   PRIVATE
#     tuna::tuna_options
#     tuna::tuna_warnings
#     tuna::tuna)
# target_compile_options(fuzz_tester PRIVATE -fsanitize=fuzzer)
# target_link_options(fuzz_tester PRIVATE -fsanitize=fuzzer)
