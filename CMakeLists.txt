cmake_minimum_required(VERSION 3.16)
project(FractalGen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If SFML is installed system-wide:
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# For MinGW or MSVC, you may need to add these system libs:
if (WIN32)
    target_link_libraries(main PRIVATE
        opengl32
        winmm
        gdi32
        freetype
    )
endif()