#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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
    FILE* file = fopen(nom_fichier, "r"); // Ouvre le fichier en mode lecture
    t_processus* tete = NULL; // Pointeur vers la tête de la liste chaînée
    t_processus* last_processus = NULL;// Pointeur vers le dernier processus ajouté
    t_processus* current_processus; // Pointeur temporaire pour le processus courant

    int pid, arrivee, duree; // Variables pour stocker les données lues
    int i = 0; // Compteur de processus

    if (file != NULL) { // Vérifie si le fichier a été ouvert 
        while (fscanf(file, "%d %d %d\n", &pid, &arrivee, &duree) != EOF) {// Lit les données ligne par ligne
            // Continue de lire jusqu'à la fin du fichier(EOF - End Of File)
            //fscanf lit les données formatées à partir du fichier et les stocke dans les variables pid, arrivee et duree
            current_processus = creer_processus(pid, arrivee, duree);// Crée un nouveau processus avec les données lues

            if (tete == NULL) {// Si c'est le premier processus, on initialise la tête de la liste
                tete = current_processus;// Initialisation de la tête de la liste
            } else {
                last_processus->suivant = current_processus;// Ajoute le processus courant à la fin de la liste
            }

            last_processus = current_processus; // Met à jour le pointeur vers le dernier processus ajouté
            i++;// incrémente le compteur de processus
            (*nb_processus)++;// incrémente le nombre de processus via le pointeur
        }

        fclose(file);// Ferme le fichier après la lecture

        return tete;// retourne la tête de la liste chaînée des processus
    } else {
        printf("Impossible d'ouvrir le ficher demandé.\n"); //Si on n'arrive pas à ouvrir le fichier 
    }

    return tete;
}

void afficher_processus(t_processus* p) {
    if (p == NULL) {
        printf("La liste des processus est vide, impossible de l'afficher.\n");
        return;
    }

    while (p != NULL) {
        printf("PID: %d, Arrivee: %d, Duree: %d\n", p->pid, p->arrivee, p->duree);
        p = p->suivant;
    }
}

void mssleep(int ms) {
    struct timespec req = { 0 };
    req.tv_sec = ms / 1000;
    req.tv_nsec = (ms % 1000) * 1000000L;
    nanosleep(&req, (struct timespec*) NULL);
}

void save_simulation_data(int start_time, int duration, int processus_id, char* name, float y_position, char* file_name) {
    FILE* file = fopen(file_name, "a");

    if (file != NULL) {
        fprintf(file, "%f %d %d %d %s \n", y_position, start_time, duration, processus_id, name);
        fclose(file);
    } else {
        printf("Impossible d'ouvrir le fichier : %s", file_name);
    }
}

void open_windows_file(char* file_path) {
    char command[512];
    sprintf(command, "code %s", file_path);

    printf("Ouverture de l'image...\n");
    int command_result = system(command);
    
    if (command_result == -1) {
        printf("Erreur lors de l'ouverture du fichier %s\n", file_path);
    }
}