cmake_minimum_required(VERSION 3.10)
project(gems LANGUAGES CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-graphics sfml-window sfml-system)

# Add executable and its sources
add_executable(gems
    src/main.cpp
    src/Game.cpp
    src/Grid.cpp
    src/Gem.cpp
    src/Bonus.cpp
)

# Include directories
target_include_directories(gems PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SFML_INCLUDE_DIRS}
)

# Link SFML libraries
target_link_libraries(gems PRIVATE
    ${SFML_LIBRARIES}
)

# Add compiler flags
target_compile_options(gems PRIVATE
    -I/usr/include
    ${SFML_CFLAGS_OTHER}
)
