cmake_minimum_required(VERSION 3.0.0)
project(XMAIRLINE VERSION 0.1.0)

include(CTest)
enable_testing()

set(SOURCES
    airline.cpp
    datetime.cpp
    graph.cpp
    main.cpp
)

add_executable(XMAIRLINE main.cpp)

target_include_directories(XMAIRLINE
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


