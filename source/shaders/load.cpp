#include <GL/glew.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/* 
Permet de compiler les shaders via deux fichiers
vtx_shdrs_path: Chemin du fichier du vertex shader (pour les sommets)
frgmt_shdrs_path: Chemin du fichier du fragment shader (pour les pixels d'un triangle)
*/

GLuint LoadShaders(const char* vtx_shdr_path, const char* frgmt_shdr_path){

    //Création des id des shaders
    GLuint VtxShdrID = glCreateShader(GL_VERTEX_SHADER); //Création du shader d'un vertex
    GLuint FrgmtShdr = glCreateShader(GL_FRAGMENT_SHADER); //Création du shader d'un fragment


    //Lecture du code du shader du vertex
    std::string VtxShdrCode; //Code du vertex shader 
    std::ifstream VtxShdrStream( //Lecture d'un fichier depuis un emplacement
        vtx_shdr_path, //Chemin du fichier
        std::ios::in //Mode de lecture
    );

    if(VtxShdrStream.is_open()){ //Si la lecture du contenu est possible
        std::stringstream stringStream; //Création d'un flux de chaîne de caractères
        stringStream << VtxShdrStream.rdbuf(); //On lit le contenu du fichier
        VtxShdrCode = stringStream.str(); //On stocke le contenu dans une chaîne de caractères
        VtxShdrStream.close(); //On ferme le fichier    
    }else{
        printf("Impossible d'ouvrir le fichier %s. Assurez-vous que le chemin est correct.\n", vtx_shdr_path);
        getchar();
        return 0;
    }

    //Lecture du code du shader du fragment
    std::string FrgmtShdrCode; //Code du fragment shader
    std::ifstream FrgmtShdrStream( //Lecture d'un fichier depuis un emplacement
        frgmt_shdr_path, //Chemin du fichier
        std::ios::in //Mode de lecture
    );

    if(FrgmtShdrStream.is_open()){ //Si la lecture du contenu est possible
        std::stringstream stringStream; //Création d'un flux de chaîne de caractères
        stringStream << FrgmtShdrStream.rdbuf(); //On lit le contenu du fichier
        FrgmtShdrCode = stringStream.str(); //On stocke le contenu dans une chaîne de caractères
        FrgmtShdrStream.close(); //On ferme le fichier
    }else{
        printf("Impossible d'ouvrir le fichier %s. Assurez-vous que le chemin est correct.\n", frgmt_shdr_path);
        getchar();
        return 0;
    }

    GLint Result = GL_FALSE; //Initialisation de la variable du résultat (Par défaut sur false car on n'a pas encore compilé le shader)
    int InfoLogLength; //Longueur du message d'erreur

    //Compilation du shader du vertex
    printf("Compilation du shader du vertex : %s\n", vtx_shdr_path);
    const char* VtxSrcPointer = VtxShdrCode.c_str(); //On créer une variable qui pointe vers le code du shader

    glShaderSource( // On lis le code source du shader
        VtxShdrID, //Identifiant du shader
        1, //nb de const char* dans le tableau (1 = un seul)
        &VtxSrcPointer, //Pointeur vers le code source
        NULL //Longueur du code source (NULL = on prend tout le code)
    );
    glCompileShader(VtxShdrID); //On compile le shader

    //Vérification de la compilation du shader du vertex
    glGetShaderiv( //Récupérer l'état du shader du vertex
        VtxShdrID, //Identifiant du shader
        GL_COMPILE_STATUS, //On veut récupérer l'état de la compilation
        &Result //On stocke le résultat dans la variable Result
    );

    glGetShaderiv( //Récupérer la longueur du message d'erreur s'il y a
        VtxShdrID, //Identifiant du shader
        GL_INFO_LOG_LENGTH, //On veut récupérer la longueur du message d'erreur
        &InfoLogLength //On stocke la longueur du message d'erreur dans la variable InfoLogLength
    );

    //On vérifie si le shader du vertex a bien été compilé
    if( InfoLogLength > 0){
        std::vector<char> VtxShdrErrMsg(InfoLogLength + 1); //On crée un vecteur de caractères de la taille du message d'erreur (On ajoute 1 pour le caractère de fin de chaîne)
        glGetShaderInfoLog( //On récupère le message d'erreur d'OpenGL
            VtxShdrID, //Identifiant du shader
            InfoLogLength, //Longueur du message d'erreur (car apparement OPENGL ne le fait pas tout seul xD)
            NULL, //On a déjà la taille du message d'erreur mdr
            &VtxShdrErrMsg[0] //On stocke le message d'erreur dans la variable que vous avons créé juste avant (Le & permet d'avoir la référence de la variable et ainsi la modifier)        
        );
        printf("%s\n", &VtxShdrErrMsg[0]); //On affiche le message d'erreur qui fait peur car tu ne sera pas comment la régler surement
    }


    //Compilation du shader du fragment
    printf("Compilation du shader du fragment : %s\n", frgmt_shdr_path);
    const char* FrgmtSrcPointer = FrgmtShdrCode.c_str(); //On créer une variable qui pointe vers le code du shader

    glShaderSource( // On lis le code source du shader
        FrgmtShdr, //Identifiant du shader
        1, //nb de const char* dans le tableau (1 = un seul)
        &FrgmtSrcPointer, //Pointeur vers le code source
        NULL //Longueur du code source (NULL = on prend tout le code)
    );
    glCompileShader(FrgmtShdr); //On compile le shader

    //Vérification de la compilation du shader du fragment
    glGetShaderiv( //Récupérer l'état du shader du fragment
        FrgmtShdr, //Identifiant du shader
        GL_COMPILE_STATUS, //On veut récupérer l'état de la compilation
        &Result //On stocke le résultat dans la variable Result
    );

    glGetShaderiv( //Récupérer la longueur du message d'erreur s'il y a
        FrgmtShdr, //Identifiant du shader
        GL_INFO_LOG_LENGTH, //On veut récupérer la longueur du message d'erreur
        &InfoLogLength //On stocke la longueur du message d'erreur dans la variable InfoLogLength
    );

    if( InfoLogLength > 0){
        std::vector<char> FrgmtShdrErrMsg(InfoLogLength + 1); //On crée un vecteur de caractères de la taille du message d'erreur (On ajoute 1 pour le caractère de fin de chaîne)
        glGetShaderInfoLog( //On récupère le message d'erreur d'OpenGL
            FrgmtShdr, //Identifiant du shader
            InfoLogLength, //Longueur du message d'erreur (car apparement OPENGL ne le fait pas tout seul xD)
            NULL, //On a déjà la taille du message d'erreur mdr
            &FrgmtShdrErrMsg[0] //On stocke le message d'erreur dans la variable que vous avons créé juste avant (Le & permet d'avoir la référence de la variable et ainsi la modifier)        
        );
        printf("%s\n", &FrgmtShdrErrMsg[0]); //On affiche le message d'erreur qui fait peur car tu ne sera pas comment la régler surement
    }

    //Lèguement des shaders
    printf("Liaison des shaders\n");
    GLuint ProgramID = glCreateProgram(); //Création du programme (C'est un ensemble de shaders)
    glAttachShader(ProgramID, VtxShdrID); //On attache le shader du vertex au programme
    glAttachShader(ProgramID, FrgmtShdr); //On attache le shader du fragment au programme
    glLinkProgram(ProgramID); //On lie les shaders à notre programme

    //Vérification de la création et de la liaison du programme
    glGetProgramiv( //On récupère l'état du programme
        ProgramID, //Identifiant du programme
        GL_LINK_STATUS, //On veut récupérer l'état de la liaison
        &Result //On stocke le résultat dans la variable Result
    );

    glGetProgramiv( //Récupérer la longueur du message d'erreur s'il y a
        ProgramID, //Identifiant du programme
        GL_INFO_LOG_LENGTH, //On veut récupérer la longueur du message d'erreur
        &InfoLogLength //On stocke la longueur du message d'erreur dans la variable InfoLogLength
    );

    if( InfoLogLength > 0){
        std::vector<char> ProgramErrMsg(InfoLogLength + 1); //On crée un vecteur de caractères de la taille du message d'erreur (On ajoute 1 pour le caractère de fin de chaîne)
        glGetProgramInfoLog( //On récupère le message d'erreur d'OpenGL
            ProgramID, //Identifiant du programme
            InfoLogLength, //Longueur du message d'erreur (car apparement OPENGL ne le fait pas tout seul xD)
            NULL, //On a déjà la taille du message d'erreur mdr
            &ProgramErrMsg[0] //On stocke le message d'erreur dans la variable que vous avons créé juste avant (Le & permet d'avoir la référence de la variable et ainsi la modifier)        
        );
        printf("%s\n", &ProgramErrMsg[0]); //On affiche le message d'erreur qui fait peur car tu ne sera pas comment la régler surement
    }

    //On supprime les shaders car on n'en a plus besoin (car ils sont déjà liés au programme et ça libère de la mémoire)
    glDetachShader(ProgramID, VtxShdrID);
    glDetachShader(ProgramID, FrgmtShdr);

    glDeleteShader(VtxShdrID);
    glDeleteShader(FrgmtShdr);

    return ProgramID; //On retourne l'identifiant du programme pour l'utiliser plus tard
}


/*
Vtx = Vertex
Frgmt = Fragment
Shdr = Shader

iv = Integer Value (GLuint)
fv = Float Value (GLfloat)
*/