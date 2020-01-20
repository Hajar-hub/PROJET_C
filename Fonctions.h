//definition de la structure de kalah
typedef struct kalah{
    char nom1[25];
    char nom2[25];
	int case_moi[6];
	int case_cpu[6];
	int score_moi;
	int score_cpu;
	int tour_jeu;  //ne sert que dans l affichage
	int fini;     //1 si le jeu est termine
}kalah;






int return_valeur(int a,int b);
void initialiser(kalah* k,int total); //total doit etre=1
void afficher(kalah k);

void changer_noms(kalah* k);



#include <stdio.h>
#include <stdlib.h>
#include "Fonctions.h"


int return_valeur(int a,int b);
void initialiser(kalah* k,int total);
void afficher(kalah k);
void demande_joueur(kalah* k);
void joueur_joue(kalah* k,int case_choisie);
void demande_cpu(kalah* k);
void cpu_joue(kalah* k,int case_choisie);
void lance_jeu_1joueur(kalah* k);
void terminer_jeu(kalah* k);
void afficher_gagnant_1joueur(kalah k);
void changer_noms(kalah* k);