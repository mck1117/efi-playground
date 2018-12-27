add_library(core STATIC)

target_include_directories(core PUBLIC
    include
    ../../libs/units/include)

target_sources(core PRIVATE
    src/Table.cpp
)
