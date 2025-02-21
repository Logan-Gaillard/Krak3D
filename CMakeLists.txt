# Définir la version minimale de CMake
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(Krak3D)

# Définir les options de compilation
set(CMAKE_CXX_STANDARD 11)

# Définir les répertoires d'inclusion
include_directories(
    ./libs/glew/include
    ./libs/glfw/include
)

# Définir les bibliothèques
find_package(OpenGL REQUIRED)

# Création de l'exécutable
add_executable(main ./source/main.cpp)

# Lier les bibliothèques pour Linux
if(UNIX)
    target_link_libraries(main
        glfw
        GLEW
        ${OPENGL_LIBRARIES}
        X11
        pthread
        Xrandr
        Xi
        dl
    )
endif()

# Lier les bibliothèques pour Windows
if(WIN32)
    target_link_libraries(main
        glfw3
        glew32s
        gdi32
        user32
        pthread
        opengl32
    )
endif()

# Nettoyage des fichiers de compilation (optionnel)
set_target_properties(main PROPERTIES CLEAN_COMMAND "rm -f main")