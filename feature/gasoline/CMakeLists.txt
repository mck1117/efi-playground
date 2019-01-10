add_library(gasoline STATIC)

target_include_directories(gasoline PUBLIC include)

target_sources(gasoline PRIVATE
    src/GasolineEngine.cpp
    src/SpeedDensity.cpp
    src/MassAirFlow.cpp
    src/GasolineFuelComputer.cpp
)

target_link_libraries(gasoline core)
