#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>

// t_processus* fifo_init (){
//     t_processus* file = malloc(sizeof(t_processus));
//     if (file == NULL) {
//         fprintf(stderr, "Erreur d'allocation mémoire\n");
//         return NULL;
//     }
//     file = NULL;
//     return file;
// }

 t_processus* fifo_init (){ // On itinialise une file vide
    return NULL;
    }
 t_processus* fifo_clear (t_processus* file){

    t_processus* current = file;
    t_processus* next;

    while (current != NULL){
        next = current->suivant;
        free(current);
        current = next;
    }
    return NULL;
}
 int fifo_vide (t_processus* file){
    return (file == NULL);
}



t_processus* fifo_enfiler (t_processus* file, t_processus* p){
   p->suivant = NULL;// 
   if (file == NULL) {// Si la file est vide on retourne le nouveau processus comme tête de file
       return p;
   }
   t_processus* current = file;// On parcourt la file jusqu'à la fin
   while(current->suivant != NULL){
       current = current->suivant;// On avance dans la file
   }   
    current->suivant = p;//QUand on arrive à la fin de la file, on ajoute le nouveau processus à la fin de la file

    return file;
}

t_processus* fifo_defiler(t_processus** file){
    if (*file == NULL){ //Si la file est vide alors on retourne vide 
        return NULL; // retourne vide :pointe vers rien 
    }
    t_processus* tete = *file; // On régupére le première élement de la file 
    *file = (*file)->suivant; // On incrémente la file pour pointé ver l'élément suivant 
    tete->suivant = NULL ;  // et on détache l'élement défiler de la liste 

    return tete; // on retourne l'élement seul 

}

void simuler_fcfs(t_processus* tableau, int nb_processus){//
    int t = 0; // temps courant
    int nb_termines = 0; // nombre de processus terminés
    t_processus* file = fifo_init(); // initialisation de la file d'attente
    t_processus* suivant = tableau;
    t_processus* courant = NULL;
// Tant que tout les processus ne sont pas terminés
    while (nb_termines < nb_processus ){//
        while(suivant != NULL && suivant->arrivee == t){//
            //if (suivant->arrivee == t){ // vérifier les processus arrivés au temps courant
                t_processus* p = creer_processus(suivant->pid, suivant->arrivee, suivant->duree);
                file = fifo_enfiler(file, p); // ajouter le processus à la file d'attente
                printf("Temps %d : Arrivée du processus PID %d\n", t, p->pid);
           // }
            suivant = suivant->suivant;
        }


        //si aucun processus n'est en cours d'exécution, on défiler le premier processus de la file si elle n'est pas vide
        if((courant == NULL) && !fifo_vide(file)){

            courant = fifo_defiler(&file); // défiler le premier processus
            printf("Temps %d : Début de l'exécution du processus PID %d pour une durée de %d\n", t, courant->pid, courant->duree);
        }


        // Exécution du processus courant si il y en a un
        if(courant != NULL){
            courant->duree--; // simuler l'exécution du processus
            if(courant->duree == 0){
                printf("Temps %d: Processus PID %d terminé\n", t + 1, courant->pid);
                free_processus(courant);
                nb_termines++; // incrémenter le nombre de processus terminés
                courant = NULL;
            }
        }
        else
        {
            //printf("Temps %d : Aucun processus en cours d'exécution\n", t);
        }
        t++; // si la file est vide, on incrémente le temps courant
        
    }
        
}


//initialisation de la file d'attente
//tant que le nombre de processus arrivés est inférieur au nombre total de processus
    //vérifier les processus arrivés au temps courant et les ajouter à la file d'attente
    //si la file n'est pas vide, défiler le premier processus et simuler son exécution
    //sinon, incrémenter le temps courant
