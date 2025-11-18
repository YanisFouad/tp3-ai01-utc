#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>

t_processus* creer_processus(int pid, int arrivee, int duree) {
    t_processus* processus = (t_processus*) malloc(sizeof(t_processus));

    processus->pid = pid;
    processus->arrivee = arrivee;
    processus->duree = duree;
    processus->suivant = NULL;

    return processus;
}

void free_processus(t_processus* p) {
    free(p);
}

t_processus* charger_processus(char* nom_fichier, int* nb_processus) {
    FILE* file = fopen(nom_fichier, "r");
    t_processus* tete = NULL;
    t_processus* last_processus = NULL;
    t_processus* current_processus;

    int pid, arrivee, duree;
    int i = 0;

    if (file != NULL) {
        while (fscanf(file, "%d %d %d\n", &pid, &arrivee, &duree) != EOF) {
            current_processus = creer_processus(pid, arrivee, duree);

            if (tete == NULL) {
                tete = current_processus;
            } else {
                last_processus->suivant = current_processus;
            }

            last_processus = current_processus;
            i++;
            (*nb_processus)++;
        }

        fclose(file);

        return tete;
    } else {
        printf("Impossible d'ouvrir le ficher demandé.\n");
        exit(EXIT_FAILURE);
    }

    return tete;
}

void afficher_processus(t_processus* p) {
    while (p != NULL) {
        printf("PID: %d, Arrivee: %d, Duree: %d\n", p->pid, p->arrivee, p->duree);
        p = p->suivant;
    }
}
