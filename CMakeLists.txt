cmake_minimum_required(VERSION 3.19)
project(out)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
find_package(PythonLibs 3.5 REQUIRED)

add_executable(
    out
    src/main.cpp
    src/math/Transform.cpp
    src/math/PerlinNoise.cpp
    src/gui/Application.cpp
    src/gui/Button.cpp
    src/gui/ColorPicker.cpp
    src/gui/Container.cpp
    src/gui/HideShowButton.cpp
    src/gui/ImageButton.cpp
    src/gui/Slider.cpp
    src/gui/Textbox.cpp
    src/gui/TextButton.cpp
    src/gui/Textfield.cpp
    src/gui/ValueSlider.cpp
    src/gui/Widget.cpp
)

target_link_libraries(
    out
    sfml-graphics
    sfml-window
)
# target_compile_options(out PUBLIC -Werror=non-virtual-dtor -O3)
target_compile_options(out PUBLIC -Werror=non-virtual-dtor -fsanitize=address)
target_link_options(out PUBLIC -lGLEW -lGLU -lGL -fsanitize=address)

target_include_directories(out PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(out ${PYTHON_LIBRARIES})
