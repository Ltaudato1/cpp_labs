cmake_minimum_required(VERSION 3.10)
project(Arkanoid LANGUAGES CXX)

# Force using system compiler
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-graphics sfml-window sfml-system)

# Add executable and its sources
add_executable(Arkanoid
    main.cpp
    src/GameObject.cpp
    src/Ball.cpp
    src/Paddle.cpp
    src/Block.cpp
    src/Game.cpp
)

# Include directories
target_include_directories(Arkanoid PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SFML_INCLUDE_DIRS}
)

# Link SFML libraries
target_link_libraries(Arkanoid PRIVATE
    ${SFML_LIBRARIES}
)

# Add compiler flags
target_compile_options(Arkanoid PRIVATE
    -I/usr/include
    ${SFML_CFLAGS_OTHER}
) 