cmake_minimum_required(VERSION 3.15)

project(EngineWrapper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    "${CMAKE_SOURCE_DIR}/Engine/Engine.cpp"
    "${CMAKE_SOURCE_DIR}/Subject/Subject.cpp"
    "${CMAKE_SOURCE_DIR}/Wrapper/Wrapper.cpp"
    "${CMAKE_SOURCE_DIR}/main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})