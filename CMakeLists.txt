cmake_minimum_required(VERSION 3.15) # версия CMake
project(TelemetryCore VERSION 1.0 LANGUAGES CXX) # название проекта и используемый язык С++

set(CMAKE_CXX_STANDARD 17) # Устанавливаем стандарт C++17 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опция сборки теста (при подключении на устройство можно отключить)
option(BUILD_TESTS "Build unit tests" ON) 

# Сборка статической библиотекуи из всех .cpp в папке src/
file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")
add_library(telemetry_core STATIC ${LIB_SOURCES})

# Указываем, где лежат публичные заголовки (папка include)
target_include_directories(telemetry_core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# ========== ПРИМЕР (исполняемый файл) ==========
add_executable(telemetry_example examples/example.cpp)
target_link_libraries(telemetry_example telemetry_core)

# ========== ТЕСТЫ ==========
if(BUILD_TESTS)
    # Подключаем GoogleTest через FetchContent (автоматически скачает из GitHub)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
    add_executable(telemetry_tests ${TEST_SOURCES})
    target_link_libraries(telemetry_tests 
        telemetry_core
        gtest_main
        gmock
    )

    include(GoogleTest)
    gtest_discover_tests(telemetry_tests)
endif()