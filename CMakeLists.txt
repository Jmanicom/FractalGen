cmake_minimum_required(VERSION 3.16)
project(FractalGen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Add executable - just main.cpp if event_handler is header-only
add_executable(main main.cpp)

# Configure the target
target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(main PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Copy shaders to build directory
file(COPY ${CMAKE_SOURCE_DIR}/shaders 
     DESTINATION ${CMAKE_BINARY_DIR})

# For Windows
if (WIN32)
    target_link_libraries(main PRIVATE
        opengl32
        winmm
        gdi32
        freetype
    )
endif()