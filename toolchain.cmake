# toolchain.cmake
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 10)

# Spécifie les chemins des compilateurs MinGW
set(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++)

# Définir les chemins des bibliothèques
set(MY_LIB_PATHS ./libs/glfw/lib-mingw-w64 ./libs/glew/lib/x64)

# Inclure les répertoires de bibliothèque
link_directories(${MY_LIB_PATHS})

# Définir les répertoires d'inclusion
include_directories(
    ./libs/glew/include
    ./libs/glfw/include
    ./libs
)

# Si tu as des bibliothèques à lier, tu peux les ajouter ici
set(MY_LIBS
    glew32s
    glfw3
    opengl32
    gdi32
    user32
    pthread
)

# Utilise ces bibliothèques dans ton projet
# Cela lie automatiquement ces bibliothèques lors de la génération
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${MY_LIB_PATHS}")