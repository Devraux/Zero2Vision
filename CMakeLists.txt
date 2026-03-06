cmake_minimum_required(VERSION 3.10)

project(Zero2Vision)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

set(SOURCES
    main.cpp
    Camera/Camera.cpp
    HTTP/http.cpp
)

add_executable(Zero2Vision ${SOURCES})

target_include_directories(Zero2Vision PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    Camera
    HTTP
)

target_link_libraries(Zero2Vision ${OpenCV_LIBS} pthread)
