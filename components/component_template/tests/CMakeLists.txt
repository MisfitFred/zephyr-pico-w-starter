cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(test___COMPONENT_NAME__)

target_sources(app PRIVATE
    src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/__COMPONENT_NAME__.c
)

target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
