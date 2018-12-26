cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(efi_os)

set(CMAKE_CXX_STANDARD 17)

# Add all features
add_subdirectory(feature/core)
add_subdirectory(feature/can)

# Add MCUs
add_subdirectory(mcu/stm32f4)

# Add configurations
# add_subdirectory(configurations/frankenso)

# google test
set(INSTALL_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(googletest)
Include(googletest)

# Unit tests
add_subdirectory(test)

