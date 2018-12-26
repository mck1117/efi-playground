
add_executable(efi_frankenso)

target_sources(efi_frankenso PRIVATE stub.cpp)
target_link_libraries(efi_frankenso core can)
