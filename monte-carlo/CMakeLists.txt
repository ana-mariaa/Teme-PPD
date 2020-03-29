cmake_minimum_required(VERSION 3.8)
project(monte-carlo)

find_package(OpenMP REQUIRED)
if( NOT OpenMP_FOUND )
    message( FATAL_ERROR "Cannot build without OpenMP!" )
endif()

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

set(SOURCES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OpenMP_CXX})