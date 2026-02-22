# Baut component_a als statische Library (Standard-CMake im App-Kontext).
add_library(component_a STATIC src/component_a.c)
target_include_directories(component_a PUBLIC include)
target_link_libraries(component_a PRIVATE zephyr_interface)
