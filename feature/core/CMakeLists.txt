add_library(core STATIC)

target_include_directories(core PUBLIC include)

target_sources(core PRIVATE
    src/Table.cpp
)
