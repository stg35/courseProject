cmake_minimum_required(VERSION 3.5)

project(m_tests LANGUAGES CXX)

enable_testing()

SET(CMAKE_CXX_STANDARD 11)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Catch2 3 REQUIRED)

add_executable(${PROJECT_NAME} tst_m_tests.cpp main.cpp)
target_link_libraries(m_tests PRIVATE Catch2::Catch2WithMain)

target_link_libraries(m_tests PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(m_tests PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Network)


if (DEFINED ENV{CATCH_INCLUDE_DIR})
    set(CATCH_INCLUDE_DIR $ENV{CATCH_INCLUDE_DIR})
else ()
    set(CATCH_INCLUDE_DIR "") # set by Qt Creator wizard
endif ()
if (CATCH_INCLUDE_DIR STREQUAL "")
    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
elseif (EXISTS ${CATCH_INCLUDE_DIR})
    include_directories(${CATCH_INCLUDE_DIR})
endif ()
