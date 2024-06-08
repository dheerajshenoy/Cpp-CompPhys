cmake_minimum_required(VERSION 3.28)
project(MonteCarloIntegration)

find_package(Boost 1.83.0 COMPONENTS filesystem system iostreams REQUIRED)
find_package(fmt)
file(GLOB SRCS src/*.cpp)
add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} fmt::fmt)
