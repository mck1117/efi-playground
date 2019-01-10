add_library(can STATIC)

target_include_directories(can PUBLIC include)

target_sources(can PRIVATE
    src/CanInterface.cpp
    src/CanRemoteSensor.cpp
)

target_link_libraries(can core)
