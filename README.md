# Krak3D
Moteur 3D sous OpenGL en cours de développement...

Seul Octokling travail sur ce projet, veuillez l'excuser pour la fréquence des mises à jours

# Prérequis

Assurez-vous d'avoir les éléments suivants installés sur votre système:

- **Git**: pour cloner le dépôt.
- **CMake**: pour générer les fichiers de build.
- **GCC**: le compilateur GNU.
- **Make**: pour construire le projet.
- **OpenGL**: pour le rendu graphique.
- **GLFW**: pour la gestion des fenêtres et des entrées.

Vous pouvez installer ces dépendances avec les commandes suivantes:

```bash
sudo apt update
sudo apt install git cmake gcc g++ make libgl1-mesa-dev libglfw3-dev
```

# Build

Suivez ces étapes pour construire le projet sur Ubuntu:

1. Clonez le dépôt:

    ```bash
    git clone https://github.com/Octokling/Krak3D.git
    cd Krak3D
    ```

2. Construisez le projet avec Make:

    ```bash
    make 
    ```

    Vous pouvez également compiler le programme pour Windows

    ```bash
    make windows
    ```

3. Exécutez l'application:

    ```bash
    ./main
    ```



Et voilà! Vous avez construit et exécuté Krak3D sur Ubuntu.