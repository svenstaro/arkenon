cmake_minimum_required(VERSION 2.8.0)

PROJECT(bridgeparty)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-extras/")
find_package(Bullet)
find_package(glfw)
find_package(OpenGL)
find_package(ENet)

add_definitions(-Wall -Wextra -Wshadow -g -pedantic -fPIC -std=c++11)
set(CMAKE_BUILD_TYPE "Debug")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(
	"${CMAKE_SOURCE_DIR}/src/"
	${BULLET_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${ENET_INCLUDE_DIRS}
)

file(GLOB_RECURSE sources src/*.cpp)

add_executable(${PROJECT_NAME}
	${sources}
)

target_link_libraries(${PROJECT_NAME}
    ${BULLET_LIBRARIES}
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${ENET_LIBRARIES}
)
