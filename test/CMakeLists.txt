
add_executable(efi_os_tests)

target_sources(efi_os_tests PRIVATE 
    fuel/FuelComputer.cpp
    fuel/MassAirFlow.cpp
    fuel/SpeedDensity.cpp
)

target_link_libraries(efi_os_tests gtest_main core gasoline)
