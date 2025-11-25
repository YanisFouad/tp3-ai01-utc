#include <stdio.h>

// Tick en microsecondes
#define TICK_DURATION 50
#define SJF_DATA_FILE "./data/sjf_data"
#define FCFS_DATA_FILE "./data/fcfs_data"
#define Y_FCFS 1.0
#define Y_SJF 2.0

typedef struct s_processus {
    int pid; // identifiant du processus
    int arrivee; // temps d'arrivee
    int duree; // duree d'execution
    struct s_processus* suivant; // pointeur vers le processus suivant
} t_processus;

/**
 * Gestion des processus
 */
t_processus* creer_processus(int pid, int arrivee, int duree);
void free_processus(t_processus* p);
t_processus* charger_processus(char* nom_fichier, int* nb_processus);
void afficher_processus(t_processus* p);
void mssleep(int ms);
void save_simulation_data(int start_time, int duration, int processus_id, char* name, float y_position, char* file_name);

/**
 * Génération de diagrammes de Gantt avec gnuplot
 */
void create_basic_graph_configuration(FILE* gp, int width, int height, char* title);
void open_windows_file(char* file_path);
void generate_single_processus_gantt(char* data_file, char* output_file, char* simulation_name, int simulation_duration);
void generate_comparative_gantt(char* fp_data_file, char* sp_data_file, char* output_file, char* fp_simulation_name, char* sp_simulation_name, int max_duration, char* gantt_name);
FILE* open_gnuplot_pipe();

/**
 *  FIFO (First In First Out) - File d'attente pour FCFS
 */
t_processus* fifo_init();
t_processus* fifo_clear(t_processus* file);
int fifo_vide(t_processus* file); // retourne 1 si la liste est vide, 0 sinon
t_processus* fifo_enfiler(t_processus* file, t_processus* p);
t_processus* fifo_defiler(t_processus** file);
int simuler_fcfs(t_processus* tableau, int nb_processus);

/**
 *  Liste triée - Liste pour SJF
 */
t_processus* lsorted_init();
t_processus* lsorted_clear(t_processus* liste);
int lsorted_vide(t_processus* liste); // retourne 1 si la liste est vide, 0 sinon
t_processus* lsorted_inserer_trie(t_processus* liste, t_processus* p);
t_processus* lsorted_extraire_premier(t_processus** liste);
int simuler_sjf(t_processus* tableau, int nb_processus);