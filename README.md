# Krak3D (Nom optionnel)
Moteur 3D sous OpenGL en cours de développement...
Si vous avez des suggestions de noms, n'hesitez pas ;)

Seul Octokling travail sur ce projet, veuillez l'excuser pour la fréquence des mises à jours

# Prérequis

Assurez-vous d'avoir les éléments suivants installés sur votre système:

- **Git**: pour cloner le dépôt.
- **CMake**: pour générer les fichiers de build.
- **GCC**: le compilateur GNU.
- **Make**: pour construire le projet.
- **OpenGL**: pour le rendu graphique.
- **GLFW**: pour la gestion des fenêtres et des entrées.

# Installation

Suivez ces étapes pour construire le projet sur Ubuntu:

1. Clonez le dépôt:

        git clone https://github.com/Logan-Gaillard/Krak3D.git
        cd Krak3D


2. Vous pouvez installer ces dépendances avec les commandes suivantes:

    **Ubuntu/Debian**

        sudo apt update && sudo apt upgrade
        sudo apt install cmake gcc g++ make libgl1-mesa-dev libglfw3-dev libglu1-mesa-dev libglm-dev libglew-dev libxi-dev

    **Arch Linux**

        sudo pacman -Syu
        sudo pacman -S cmake gcc g++ make mesa glfw glu glm glew xi
    

# Compilation
## Linux

    make linux
    

## Windows

    make windows

### NOTES
Vous avez besoin du compilateur ``x86_64-w64-mingw32-gcc``

Installez-le avec cette commande :
    
    sudo apt install gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64



Et voilà! Vous savez construire et exécuter Krak3D sur Ubuntu.
