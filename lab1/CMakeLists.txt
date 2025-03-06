cmake_minimum_required(VERSION 3.10)
project(QuadraticSolver)

# Используем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Включаем поддержку Google Test
enable_testing()

# Добавляем Google Test через FetchContent (если его нет в системе)
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Предотвращаем установку GTest как отдельного проекта
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавляем основные исходники
add_executable(quadratic_solver
    main.cpp
    parser.cpp
    quadratic_solver.cpp
)

# Добавляем тесты
add_executable(test_quadratic_solver
    test.cpp
    parser.cpp
    quadratic_solver.cpp
)

# Линкуем Google Test к тестам
target_link_libraries(test_quadratic_solver
    gtest_main
    gtest
    pthread
)

# Добавляем тестирование
add_test(NAME QuadraticSolverTests COMMAND test_quadratic_solver)

# Прекращаем сборку, если тесты не прошли
add_custom_target(run_tests
    COMMAND test_quadratic_solver
    COMMENT "Running unit tests..."
)

add_dependencies(quadratic_solver run_tests)