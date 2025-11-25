#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

// Définitions pour les positions Y
#define Y_FCFS 1.0
#define Y_SJF 2.0
#define HEIGHT 0.8

void generate_single_processus_gantt(char* data_file, char* output_file, char* simulation_name, int simulation_duration) {
    printf("Génération du diagramme en cours...");
    FILE* gp = open_gnuplot_pipe();

    if (gp == NULL) {
        printf("Erreur lors de l'ouverture du pipe vers gnuplot.");
        return;
    }

    create_basic_graph_configuration(gp, simulation_duration * 75, 500, simulation_name);

    fprintf(gp, "set xrange [0:%d]\n", simulation_duration);
    fprintf(gp, "set yrange [-0.3:1.1]\n");
    fprintf(gp, "unset ytics\n");
    fprintf(gp, "set output '%s'\n", output_file);

    // Ajout barre processus
    fprintf(gp, "plot '%s' using ($2 + $3/2):(%f):($3/2):(%f/2) with boxxyerror fillcolor rgb '#D3D3D3' notitle, \\\n", data_file, HEIGHT / 2, HEIGHT);

    // Ajout label processus
    fprintf(gp, "  '' using ($2 + $3/2):(%f):4 with labels font 'Arial,10' textcolor rgb 'black' notitle\n", HEIGHT / 2);

    pclose(gp);
    printf("Diagramme généré dans %s.\n", output_file);

    open_windows_file(output_file);
}

void generate_comparative_gantt(char* fp_data_file, char* sp_data_file, char* output_file, char* fp_simulation_name, char* sp_simulation_name, int max_duration, char* gantt_name) {
    printf("Génération du diagramme comparatif en cours...\n");
    FILE* gp = open_gnuplot_pipe();

    if (gp == NULL) {
        printf("Erreur lors de l'ouverture du pipe vers gnuplot.\n");
        return;
    }

    create_basic_graph_configuration(gp, max_duration * 75, 500, gantt_name);

    fprintf(gp, "set xrange [0:%d]\n", max_duration);
    fprintf(gp, "set yrange [0.5:2.5]\n");
    fprintf(gp, "set ytics ('%s' %f, '%s' %f)\n", fp_simulation_name, Y_FCFS, sp_simulation_name, Y_SJF);
    fprintf(gp, "set output '%s'\n", output_file);

    // Ajout barre premier processus
    fprintf(gp, "plot '%s' using ($2 + $3/2):(%f):($3/2):(%f/2) with boxxyerror fillcolor rgb '#ADD8E6' notitle, \\\n", fp_data_file, Y_FCFS, HEIGHT);

    // Ajout label premier processus
    fprintf(gp, "     '' using ($2 + $3/2):(%f):4 with labels font 'Arial,10' textcolor rgb 'black' notitle, \\\n", Y_FCFS);

    // Ajout barre second processus
    fprintf(gp, "     '%s' using ($2 + $3/2):(%f):($3/2):(%f/2) with boxxyerror fillcolor rgb '#90EE90' notitle, \\\n", sp_data_file, Y_SJF, HEIGHT);

    // Ajout label second processus
    fprintf(gp, "     '' using ($2 + $3/2):(%f):4 with labels font 'Arial,10' textcolor rgb 'black' notitle\n", Y_SJF);

    pclose(gp);
    printf("Diagramme comparatif généré dans %s.\n", output_file);
    open_windows_file(output_file);
}

void create_basic_graph_configuration(FILE* gp, int width, int height, char* title) {
    // Configuration de la sortie
    fprintf(gp, "set terminal pngcairo size %d, %d\n", width, height);

    // Configuration du style et des axes
    fprintf(gp, "set title '%s'\n", title);
    fprintf(gp, "set style fill solid 1.0 border -1\n");
    fprintf(gp, "set grid xtics\n");
    fprintf(gp, "set xlabel 'Temps t'\n");
    fprintf(gp, "set xtics 1\n");
}

FILE* open_gnuplot_pipe() {
    FILE* gp = popen("gnuplot", "w");
    return gp != NULL ? gp : NULL;
}