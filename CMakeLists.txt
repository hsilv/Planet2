cmake_minimum_required(VERSION 3.25)
project(Planet VERSION 1.0)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)
find_package(TBB REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Planet src/main.cpp)

target_include_directories(Planet PRIVATE ${SDL2_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Planet PRIVATE TBB::tbb ${SDL2_LIBRARIES} ${GLM_LIBRARIES})

link_directories(${CMAKE_SOURCE_DIR}/lib)
