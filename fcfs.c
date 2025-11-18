#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>

t_processus* fifo_init (){
t_processus* file = malloc(sizeof(t_processus));
if (file == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    return NULL;
}
file->suivant = NULL;
return file;
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
    return (file->suivant == NULL);
}



t_processus* fifo_enfiler (t_processus* file, t_processus* p){
   p->suivant = NULL;
   if (file == NULL) {
       return p;
   }
   t_processus* current = file;
   while(current->suivant != NULL){
       current = current->suivant;
   }   
    current->suivant = p;

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
