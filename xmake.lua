add_requires("imgui", { configs = { glfw = true, opengl3 = true } })
add_requires("glfw", "opengl", "utfcpp")

target("example")
    set_languages("c++20")

    add_packages("imgui", "glfw", "opengl", "utfcpp")
    add_files("example/main.cpp", "textselect.cpp")
    add_includedirs(".")
