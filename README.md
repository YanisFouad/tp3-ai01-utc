# TP3 AI01 - Simulateur d'ordonnancement de processus

## 📋 Description

Projet de simulation d'algorithmes d'ordonnancement de processus (FCFS et SJF) développé en C.

## 🛠️ Prérequis

- **Compilateur** : GCC (GNU Compiler Collection)
- **Système** : Linux/Unix
- **Outils** : Make

## 📁 Structure du projet

```
tp3-ai01-utc/
├── main.c           # Point d'entrée du programme
├── global.c         # Fonctions générales (création, chargement, affichage)
├── fcfs.c           # Implémentation de l'algorithme FCFS (First Come First Served)
├── sjf.c            # Implémentation de l'algorithme SJF (Shortest Job First)
├── tp3.h            # Fichier d'en-tête avec les structures et prototypes
├── data             # Fichier de données contenant les processus
├── Makefile         # Script de compilation
└── README.md        # Documentation
```

## 🔧 Compilation

### Compilation standard
```bash
make build
```

Cette commande génère l'exécutable `main` avec les flags suivants :
- `-Wall` : Active tous les avertissements
- `-Wextra` : Active des avertissements supplémentaires
- `-g` : Inclut les symboles de débogage

### Compilation manuelle
```bash
gcc -o main main.c global.c fcfs.c sjf.c -Wall -Wextra -g
```

## 🚀 Exécution

```bash
./main
```

Le programme charge automatiquement les processus depuis le fichier `./data`.

## 📊 Format du fichier de données

Le fichier `data` doit contenir les processus au format suivant :
```
PID ARRIVEE DUREE
```

**Exemple** :
```
1 0 5
2 2 2
3 4 1
```

Où :
- **PID** : Identifiant du processus
- **ARRIVEE** : Temps d'arrivée du processus
- **DUREE** : Durée d'exécution du processus