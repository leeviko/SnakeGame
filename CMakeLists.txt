cmake_minimum_required(VERSION 3.16)
project(SnakeGame)

file(GLOB SOURCES "src/*.cpp")

find_package (Threads)
find_package (Curses)
# Add an executable with the above sources
add_executable(SnakeGame ${SOURCES})
target_link_libraries (SnakeGame Threads::Threads)
target_link_libraries (SnakeGame ${CURSES_LIBRARIES})
# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(SnakeGame
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src/includes
)