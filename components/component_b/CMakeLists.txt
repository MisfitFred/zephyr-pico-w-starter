# Baut component_b als statische Library (Standard-CMake im App-Kontext).
add_library(component_b STATIC src/component_b.c)
target_include_directories(component_b PUBLIC include)
target_link_libraries(component_b PRIVATE zephyr_interface)
