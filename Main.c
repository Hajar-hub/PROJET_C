#include <stdio.h>
#include <stdlib.h>
#include "Fonctions.c"

int main(){
    int choix=1;
    char nom1[25];
    char nom2[25];
    kalah k;
    
    initialiser(&k,1);  
    
    while(choix!=0){
  	    printf("********************Menu principal********************");
        printf("******************************************************\n");
  	    printf("1. Jeu 1 joueur\n");
  	    printf("2. Jeu 2 joueurs\n");
  	    printf("3. Afficher les regles du jeu\n");
  	    printf("4. Changer les noms (%s), (%s)\n",k.nom1,k.nom2);
  	    printf("\n0. Quitter\n");
  	    choix=return_valeur(0,4);
        
        switch(choix){
                case 0 : 
                        break;
                case 1 :lance_jeu_1joueur(&a);
                        initialiser(&a,0);
                        break;
                case 2 :
                        break;
                case 3 :
                        break;
                case 4 :changer_noms(&a);
                        break;
        }
    }
    system("PAUSE");
    return 0;
}