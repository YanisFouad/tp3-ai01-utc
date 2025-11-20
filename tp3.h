// Tick en microsecondes
#define TICK_DURATION 500
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

t_processus* creer_processus(int pid, int arrivee, int duree);
void free_processus(t_processus* p);
t_processus* charger_processus(char* nom_fichier, int* nb_processus);
void afficher_processus(t_processus* p);
void mssleep(int ms);
void save_simulation_data(int start_time, int duration, int processus_id, char* name, float y_position, char* file_name);
void generate_single_processus_gantt(char* data_file, char* output_file, char* simulation_name, int simulation_duration);
void open_windows_file(char* file_path);

t_processus* fifo_init();
t_processus* fifo_clear(t_processus* file);
int fifo_vide(t_processus* file); // retourne 1 si la liste est vide, 0 sinon
t_processus* fifo_enfiler(t_processus* file, t_processus* p);
t_processus* fifo_defiler(t_processus** file);
void simuler_fcfs(t_processus* tableau, int nb_processus);

t_processus* lsorted_init();
t_processus* lsorted_clear(t_processus* liste);
int lsorted_vide(t_processus* liste); // retourne 1 si la liste est vide, 0 sinon
t_processus* lsorted_inserer_trie(t_processus* liste, t_processus* p);
t_processus* lsorted_extraire_premier(t_processus** liste);
void simuler_sjf(t_processus* tableau, int nb_processus);