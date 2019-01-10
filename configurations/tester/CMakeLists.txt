
add_executable(efi_tester)

target_sources(efi_tester PRIVATE main.cpp)
target_link_libraries(efi_tester core can gasoline)
