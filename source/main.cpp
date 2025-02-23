#include <stdio.h>
#include <stdlib.h>

//Inclut GLEW pour avoir les prototypes des fonctions OpenGL
#define GLEW_STATIC
#include <GL/glew.h>

//Inclut GLFW qui est une bibliothèque de gestion de fenêtre
#include <GLFW/glfw3.h>

//Inclut GLM qui est une bibliothèque de gestion de matrice
#include <glm/glm.hpp>
using namespace glm;


//Les shaders
#include "shaders/load.cpp"

int main(){

    //Initialisation de GLFW
    if(!glfwInit()){
        fprintf(stderr, "Erreur d'initialisation de GLFW\n");
        return -1;
    }

    //Création d'une fenêtre
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // La version mineure est 3
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //GLFW_OPENGL_FORWARD_COMPAT permet de rendre le programme compatible avec les versions futures d'OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //On utilise le profil de base de OpenGL car on ne veut pas utiliser les fonctions dépréciées

    //Ouverture d'une fenêtre en 1920x1080
    GLFWwindow* window; //Pointeur vers la fenêtre
    window = glfwCreateWindow( //Création de la fenêtre en 1920x1080 avec le titre "OpenGL"
        1920, //La largeur de la fenêtre
        1080, //La hauteur de la fenêtre
        "Krak3D", //Le titre de la fenêtre
        NULL, //La fenêtre parent (NULL si on n'en a pas) sert à créer une fenêtre enfant
        NULL //La fenêtre partagée (NULL si on n'en a pas) sert à partager les ressources OpenGL entre plusieurs fenêtres
    ); 

    if(window == NULL){ // Si la fenêtre n'a pas pu être créée
        fprintf(stderr, "Erreur lors de l'ouverture de la fenêtre\n"); // On affiche un message d'erreur dans la console
        glfwTerminate(); // On ferme GLFW
        return -1; // On quitte le programme
    }

    glfwMakeContextCurrent(window); // On rend la fenêtre courante pour dessiner
    glewExperimental = true; // Nécessaire pour que GLEW fonctionne correctement
    if(glewInit() != GLEW_OK){ //Si l'initialisation de GLEW a échoué
        fprintf(stderr, "Erreur lors l'initialisation de GLEW\n"); // On affiche un message d'erreur dans la console
        return -1; // On quitte le programme
    }

    //Création d'un VAO
    GLuint VertexArrayID; // Identifiant de notre Vertex Array Object
    glGenVertexArrays(1, &VertexArrayID); // Crée un seul Vertex Array Object
    glBindVertexArray(VertexArrayID); // On rend ce VAO courant

    // On crée un triangle et on positionne ses sommets
    static const GLfloat triangle_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f, //Vertex inférieur gauche
        1.0f, -1.0f, 0.0f, //Vertex inférieur droit
        0.0f, 1.0f, 0.0f, //Vertex supérieur
    };

    //Création d'un VBO
    //Création d'une mémoire tampon pour le triangle
    GLuint vertexBuffer; //Identifiant de notre Vertex Buffer Object
    glGenBuffers( //On crée un VBO
        1, //Le nombre de VBOs que l'on veut créer
        &vertexBuffer //L'adresse de la variable qui va stocker l'identifiant du premier VBO créé
    );

    // On lie ce VBO courant
    glBindBuffer(
        GL_ARRAY_BUFFER, // On définit le VBO comme un VBO de type GL_ARRAY_BUFFER
        vertexBuffer // On lie vertexbuffer ce VBO pour le rendre actif
    ); 

    glBufferData( // On envoie les données à OpenGL qui va les donner à la carte graphique
        GL_ARRAY_BUFFER, // On définit le VBO comme un VBO de type GL_ARRAY_BUFFER
        sizeof(triangle_vertex_buffer_data), // On envoie la taille des données
        triangle_vertex_buffer_data, // On envoie les données
        GL_STATIC_DRAW // On envoie les données une fois et on les utilise souvent
    );

    GLuint programID = LoadShaders( "./shaders/SimpleVertexShader.vxs", "./shaders/SimpleFragmentShader.fts" );

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // On active le mode de saisie des touches
    do{
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // On efface le tampon de couleur et le tampon de profondeur

        glUseProgram(programID); // On utilise le programme

        //DESSINS
        glEnableVertexAttribArray(0); // Elle permet de dire à OpenGL que l'on va utiliser l'attribut 0
        glBindBuffer(
            GL_ARRAY_BUFFER, // On définit le VBO comme un VBO de type GL_ARRAY_BUFFER
            vertexBuffer // On lie vertexbuffer ce VBO pour le rendre actif
        );

        glVertexAttribPointer(
            0, // On définit l'attribut 0
            3, //3 = Le nombre de sommets (x, y, z)
            GL_FLOAT, // Le type des sommets
            GL_FALSE, //Normalisation
            0, // Pas de décalage
            (void*)0 // Offset de la mémoire tampon (On dessiner à la position 0)
        );

        glDrawArrays(
            GL_TRIANGLES, // On dessine des triangles
            0, // On commence à partir du sommet 0
            3 // On dessine 3 sommets
        );

        glDisableVertexAttribArray(0); // On désactive l'attribut 0
        //La modification du dessin du triangles n'est plus faisaible ici
        
        // Swap buffers
        glfwSwapBuffers(window); // On échange les buffers pour afficher ce que l'on vient de dessiner
        glfwPollEvents(); // On vérifie s'il y a des événements (comme les touches enfoncées par l'utilisateur)
    }while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0); //Tant que l'utilisateur n'appuie pas sur la touche d'échappement et que la fenêtre n'est pas fermée)
}

/*
    Vocabulaire :
    Vert(ex/ices) : Sommet(s) d'une figure géométrique
    Buffer : Zone de mémoire (tampon) utilisée pour stocker temporairement des données
    VAO : Vertex Array Object
    VBO : Vertex Buffer Object

    Qu'est-ce qu'un VAO ?
    Est un objet qui stocke l'état de la configuration des vertex, comme les attributs de position, de couleur, de texture, etc... pour un géométrie donnée.
    Il permet de simplifier la gestion des objets en 3D en regroupant tout cela dans un seul objet.

    Qu'est-ce qu'un VBO ?
    Est un tampon qui stocke les données des vertex (position, couleur, texture, etc...).
    Il permet de transférer ces données directement sur la carte graphique pour un rendu plus rapide.

    Qu'est ce que la normalisation ?
    La normalisation est une opération qui consiste à ramener une valeur à une échelle donnée.
    Par exemple, si on a des valeurs de 0 à 255 et qu'on les normalise entre 0 et 1, on divise chaque valeur par 255.


    C++ :
    * = Pointeur vers la donnnée de la variable (ex : int* pointeur) | Une autre variable créé mais qui pointe vers la même donnée
    & = Référence de la variable (ex : int& reference) | Même variable mais avec un autre nom (On peut s'en servir pour modifier les valeurs de la variable)
*/




/*
LES COORDONNEES HOMOGENES :
    En 3D nous utilisons X, Y et Z pour définir la position d'un point dans l'espace.
    Cependant nous utilisons un 4ème paramètre : le W (ou w).
    Ce paramètre est appelé coordonnée homogène.
    Si w = 1, alors le vecteur (x, y, z, 1) est une position dans l’espace.
    Si w = 0, alors le vecteur (x, y, z, 0) est un vecteur direction.

LES MATRICES : 
    Nous utilisons principelement des matrices le longueur 4x4 pour effectuer des transformations sur les objets en 3D.


    Les matrices de translation :
        La matrice correspond à cela :
        | 1 0 0 x |
        | 0 1 0 y |
        | 0 0 1 z |
        | 0 0 0 1 |
        x, y, z sont les coordonnées actuelle de la translation. 1 correspond à w alors c'est une position dans l'espace.

        Comment changer la position d'un objet ?
        Il suffit de multiplier la matrice par les nouvelles coordonnées de l'objet.
        Exemple notre object est à la position (12, 2, 5, 1) et on veut déplacer sur l'axe X de 6 unités.

        | 1 0 0 6 |   | 12 |   | 18 |
        | 0 1 0 0 | x | 2  | = | 2  |
        | 0 0 1 0 |   | 5  |   | 5  |
        | 0 0 0 1 |   | 1  |   | 1  |

*/

