cmake_minimum_required(VERSION 3.16)
project(fluidssimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output binary in build/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(WIN32)
    # Windows SDL3 find - adjust paths if needed
    find_path(SDL3_INCLUDE_DIR SDL3/SDL.h PATHS "C:/SDL3/include")
    find_library(SDL3_LIBRARY SDL3 PATHS "C:/SDL3/lib")

    if(NOT SDL3_INCLUDE_DIR OR NOT SDL3_LIBRARY)
        message(FATAL_ERROR "SDL3 not found on Windows. Please set SDL3_INCLUDE_DIR and SDL3_LIBRARY.")
    endif()

    include_directories(${SDL3_INCLUDE_DIR})
    add_executable(fluidssimulator main.cpp)
    target_link_libraries(fluidssimulator PRIVATE ${SDL3_LIBRARY})

else()
    # Linux/macOS find with pkg-config
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
    add_executable(fluidssimulator main.cpp)
    target_link_libraries(fluidssimulator PRIVATE PkgConfig::SDL3)
endif()

add_custom_target(run
    COMMAND ./fluidssimulator
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS fluidssimulator
    COMMENT "Running fluidssimulator"
)
