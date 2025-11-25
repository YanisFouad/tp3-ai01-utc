#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int generer_image() {
    char choice;
    printf("Voulez vous générer le gantt de cette simulation ? Y/N\n");

    while (choice != 'Y' && choice != 'N') {
        scanf("%c", &choice);
    }

    return choice == 'Y' ? 1 : 0;
}

int main() {
    system("clear");
    t_processus* tableau = NULL; // tableau de processus
    int nb_processus = 0;
    int choix;
    char nom_fichier[256];
    int simulation_duration;

    do {
        printf("\n===== Menu =====\n");
        printf("1. Charger processus depuis un fichier\n");
        printf("2. Simuler FCFS\n");
        printf("3. Simuler SJF\n");
        printf("4. Générer diagramme comparatif\n");
        printf("5. Quitter\n");
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
                remove(FCFS_DATA_FILE);

                system("clear");
                printf("Simulation SJF en cours...\n");
                simulation_duration = simuler_fcfs(tableau, nb_processus);
                if (generer_image()) {
                    generate_single_processus_gantt(FCFS_DATA_FILE, "./img/fcfs_gantt.png", "FCFS Simulation", simulation_duration);
                }
            }
            break;

        case 3: // Simuler SJF
            if (tableau == NULL) {
                printf("Veuillez charger un fichier d'abord.\n");
            } else {
                // Nettoyage des données de la dernière simulation
                remove(SJF_DATA_FILE);

                system("clear");
                printf("Simulation SJF en cours...\n");
                simulation_duration = simuler_sjf(tableau, nb_processus);
                if (generer_image()) {
                    generate_single_processus_gantt(SJF_DATA_FILE, "./img/sjf_gantt.png", "SJF Simulation", simulation_duration);
                }
            }
            break;

        case 4: // Générer diagramme comparatif
            if (tableau == NULL) {
                printf("Veuillez charger un fichier d'abord.\n");
            } else {
                if (access(FCFS_DATA_FILE, F_OK) == -1 || access(SJF_DATA_FILE, F_OK) == -1) {
                    printf("Veuillez exécuter les deux simulations avant de générer le diagramme comparatif.\n");
                } else {
                    generate_comparative_gantt(FCFS_DATA_FILE, SJF_DATA_FILE, "./img/comparative_gantt.png", "FCFS", "SJF", simulation_duration, "Comparatif FCFS vs SJF");
                }
            }
            break;
        case 5: // Quitter
            printf("Au revoir !\n");
            break;

        default:
            printf("Choix invalide.\n");
        }

    } while (choix != 5);

    // Nettoyage mémoire avant sortie
    if (tableau != NULL) {
        t_processus* current = tableau;
        t_processus* next;

        while (current != NULL) {
            next = current->suivant;
            free_processus(current);
            current = next;
        }
        tableau = NULL;
        next = NULL;
    }

    return 0;
}