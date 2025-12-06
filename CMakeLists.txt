cmake_minimum_required(VERSION 3.16)
project(FractalGen)

set(CMAKE_CXX_STANDARD 17)

# Static linking configuration
set(BUILD_SHARED_LIBS OFF)
set(SFML_STATIC_LIBRARIES TRUE)

# For MinGW: fully static everything
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

# Find SFML 3
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Add executable
add_executable(FractalGen 
    src/main.cpp
)

# Link libraries
if(WIN32)
    target_link_libraries(FractalGen 
        PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        -static
        -lpthread
        opengl32
        freetype
        winmm
        gdi32
    )
    target_compile_definitions(FractalGen PRIVATE SFML_STATIC)
    target_link_options(FractalGen PRIVATE -static)
else()
    target_link_libraries(FractalGen 
        PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
    )
endif()

# Run these commands to make the file
# cmake .. -DSML_STATIC_LIBRARIES=TRUE
# cmake --build . --config Release

# Run to check for static linking (MSYS64 UCRT)
# ldd FractalGen.exe