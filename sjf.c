#include "tp3.h"
#include <stdlib.h>
#include <stdio.h>

t_processus* lsorted_init() {
    t_processus* liste = NULL;
    return liste;
}

t_processus* lsorted_clear(t_processus* liste) {
    if (lsorted_vide(liste) == 1) {
        printf("La liste triée est vide, pas besoin de libérer de la mémoire\n");
        return NULL;
    }

    t_processus* current = liste;
    while (current != NULL) {
        t_processus* next = current->suivant;
        free_processus(current);
        current = next;
    }

    printf("La mémoire de la liste triée a été libérée avec succès\n");
    return NULL;
}

int lsorted_vide(t_processus* liste) {
    return liste == NULL;
}

t_processus* lsorted_inserer_trie(t_processus* liste, t_processus* p) {
    if (lsorted_vide(liste) == 1) {
        p->suivant = NULL;
        return p;
    }

    // On insère au début de la liste si le processus est plus court que le premier de la liste
    if (p->duree < liste->duree) {
        p->suivant = liste;
        return p;
    }

    t_processus* current = liste;

    while (current->suivant != NULL) {
        // Si la durée du processus actuel est inférieure à p et que le suivant est supérieure à p on insère p
        if (current->duree <= p->duree && current->suivant->duree > p->duree) {
            p->suivant = current->suivant;
            current->suivant = p;
            return liste;
        }
        current = current->suivant;
    }

    // Dans le cas où p est supérieur à tous les autres processus on insère à la fin de la liste
    p->suivant = NULL;
    current->suivant = p;

    return liste;
}

t_processus* lsorted_extraire_premier(t_processus** liste) {
    if (lsorted_vide(*liste) == 1) {
        printf("La liste triée est vide, impossible de retirer une valeur\n");
        return NULL;
    }

    t_processus* extracted_processus = *liste;
    *liste = (*liste)->suivant;

    return extracted_processus;
}

int simuler_sjf(t_processus* tableau, int nb_processus) {
    int nb_tick = 0;
    t_processus* current = tableau;
    t_processus* to_procede = lsorted_init();
    t_processus* proceding = NULL;

    while (current != NULL || proceding != NULL || lsorted_vide(to_procede) == 0) {
        // Fin du processus si arrivé à sa fin si il y en a un en cours d'éxecution
        if (proceding != NULL && proceding->duree == 0) {
            printf("t = %d : fin P%d\n", nb_tick, proceding->pid);
            proceding = NULL;
        }

        // Ajouter les processus à charger au tick actuel
        while (current != NULL && current->arrivee == nb_tick) {
            t_processus* to_insert = current;
            printf("t = %d : arrivee P%d (duree = %d)\n", nb_tick, to_insert->pid, to_insert->duree);
            current = current->suivant;
            to_procede = lsorted_inserer_trie(to_procede, to_insert);
        }

        // Démararer l'exécution du processus
        if (proceding == NULL && lsorted_vide(to_procede) == 0) {
            proceding = lsorted_extraire_premier(&to_procede);
            printf("t = %d : run P%d duree = %d\n", nb_tick, proceding->pid, proceding->duree);
            save_simulation_data(nb_tick, proceding->duree, proceding->pid, "SJF", Y_SJF, SJF_DATA_FILE);
        }

        if (proceding != NULL) {
            proceding->duree--;
        }

        nb_tick++;
        mssleep(TICK_DURATION);
    }

    lsorted_clear(to_procede);
    lsorted_clear(proceding);

    return nb_tick - 1;
}