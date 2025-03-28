cmake_minimum_required(VERSION 3.10)
project(main LANGUAGES CXX)

# Установка стандарта C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включение всех предупреждений
add_compile_options(-Wall -Wextra -Wpedantic)

# Исполняемый файл
add_executable(${PROJECT_NAME}
    main.cpp
    exam.cpp
    solver.cpp
    students.cpp
    teacher.cpp
    parser.cpp
)

# Подключение заголовочных файлов
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Для математической библиотеки (Linux/Unix)
if(UNIX)
    target_link_libraries(${PROJECT_NAME} m)
endif()