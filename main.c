#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    system("clear");
    t_processus* tableau = NULL; // tableau de processus
    int nb_processus = 0;
    int choix;
    char nom_fichier[256];
    do {
        printf("\n===== Menu =====\n");
        printf("1. Charger processus depuis un fichier\n");
        printf("2. Simuler FCFS\n");
        printf("3. Simuler SJF\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
        case 1: // Charger processus
            system("clear");
            printf("Entrez le nom du fichier : ");
            scanf("%s", nom_fichier);
            tableau = charger_processus(nom_fichier, &nb_processus);
            printf("%d processus chargés depuis %s.\n", nb_processus, nom_fichier);
            break;

        case 2: // Simuler FCFS
            if (tableau == NULL) {
                printf("Veuillez charger un fichier d'abord.\n");
            } else {
                // Nettoyage des données de la dernière simulation
                // remove(FCFS_DATA_FILE);
                simuler_fcfs(tableau, nb_processus);
            }
            break;

        case 3: // Simuler SJF
            if (tableau == NULL) {
                printf("Veuillez charger un fichier d'abord.\n");
            } else {
                // Nettoyage des données de la dernière simulation
                // remove(SJF_DATA_FILE);

                system("clear");
                printf("Simulation SJF en cours...\n");
                simuler_sjf(tableau, nb_processus);
            }
            break;

        case 4: // Quitter
            printf("Au revoir !\n");
            break;

        default:
            printf("Choix invalide.\n");
        }

    } while (choix != 4);

    // Nettoyage mémoire avant sortie
    if (tableau != NULL) {
        free(tableau);
    }

    return 0;
}