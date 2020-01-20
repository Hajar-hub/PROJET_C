#include <stdio.h>
#include <stdlib.h>
#include "Fonctions.h"

//demander un nombre entre a et b
int return_valeur(int a,int b){
    int choix;
    printf("\nVotre choix : ");
  	scanf("%d",&choix);
    while((choix<a)||(choix>b)){
  	    printf("Entre %d et %d : ",a,b);
  	    scanf("%d",&choix);
    }
    return choix;
}

//creer un kalah
void initialiser(kalah* k,int total){
    int i;
    for (i=0;i<6;i++){
        k->case_moi[i]=3;
        k->case_cpu[i]=3;
    }
    k->score_moi=0;
    k->score_cpu=0;
    k->tour_jeu=1;
    k->fini=0;
    if(total==0) return; //on sort et n'initialise pas la suite
    strcpy(k->nom1,"joueur 1");
    strcpy(k->nom2,"joueur 2 / CPU");
}

void afficher(kalah k){
	printf("\n\n\nTour de jeu : %s\n\n",(k.tour_jeu==1?k.nom1:k.nom2));
	printf("%3d %3d %3d %3d %3d %3d     score : %d\n\n\n",k.case_cpu[5],k.case_cpu[4],k.case_cpu[3],k.case_cpu[2],k.case_cpu[1],k.case_cpu[0],k.score_cpu);
	printf("%3d %3d %3d %3d %3d %3d     score : %d\n\n",k.case_moi[0],k.case_moi[1],k.case_moi[2],k.case_moi[3],k.case_moi[4],k.case_moi[5],k.score_moi);
}

//demande au joueur quel coup (case/pile) il veut jouer
//joue le coup choisi
void demande_joueur(kalah* k){
	
	int coup;
	
	//verifie si le jeu n est pas fini
	if (k->case_moi[0]+k->case_moi[1]+k->case_moi[2]+k->case_moi[3]+k->case_moi[4]+k->case_moi[5]==0|| k->score_moi>=18){
		
			k->fini=1;
			return; // Jeu fini
		
	}
	
	printf("Quel coup : ");
	scanf("%d",&coup);
	
	// Coup entre 1 et 6
	while ((coup<1)||(coup>6)){
		printf("Il faut entre 1 et 6 : ");
		scanf("%d",&coup);
	}
	
	// Joue une case non vide
	while (k->case_moi[coup-1]==0){
		printf("Il faut jouer une case non vide : ");
		scanf("%d",&coup);
	}
	
		
	joueur_joue(k,coup-1);
}

// Le joueur joue un coup entre 0 et 5
//but:deplacer les pions, changer le score
//en parametre, le plateau de jeu et la case a jouer
void joueur_joue(kalah* k,int case_choisie){
	int case_gene=case_choisie;
	int nb_graine=k->case_moi[case_choisie]; // Nombre de graines dans la case a jouer
	
	
	
	k->case_moi[case_choisie]=0; //case a jouer remise a 0
	
	//Deposer les graines
	while(nb_graine!=0){
		case_gene++;
		if (case_gene==12){ //on est dans la case de score de l a dversaire donc on doit passer a la case 0 du joueur
			case_gene=0;
			k->case_moi[case_gene]++;
		}
  		//if (case_gene==case_choisie) case_gene++; // On est dans la case � jouer, on passe � la suivante
		if(case_gene==6){
			k->score_moi++;
			nb_graine--;
			k->case_cpu[case_gene-6]++;}
		}
		if (case_gene>5){
			k->case_cpu[case_gene-6]++;
		}else{
			k->case_moi[case_gene]++;
		}
		nb_graine--;
	}

	k->tour_jeu=2; // C'est au tour de l'autre(ordi)
}

// Demande au cpu quel coup il veut jouer(nbre aleatoire)
// Joue le coup
// Mode 2 joueurs
void demande_cpu(kalah* k){
	int i;
	int coup;

	//verifie si le jeu n est pas fini
	if (k->case_cpu[0]+k->case_cpu[1]+k->case_cpu[2]+k->case_cpu[3]+k->case_cpu[4]+k->case_cpu[5]==0 || k->score_cpu>=18){
		
			k->fini=1;
			return; // Jeu fini
		
	}

	coup=rand()%6;//nombre aleatoire [0..5] ou [0..6[
	
	// Joue une case non vide
	while (k->case_cpu[coup]==0){
		printf("Il faut jouer une case non vide : ");
		coup=rand()%6;
	}
	
	cpu_joue(k,coup);
}


// Le cpu joue un coup entre 0 et 5
//but: deplacer les pions, changer le score
// En parametre le plateau de jeu et la case a jouer
void cpu_joue(kalah* k,int case_choisie){
	int case_gene=case_choisie;
	int nb_graine=k->case_cpu[case_choisie]; // Nombre de graines dans la case a jouer
	
	
	
	k->case_cpu[case_choisie]=0; //case a jouer remise a 0
	
	//Deposer les graines
	while(nb_graine!=0){
		case_gene++;
		if (case_gene==12){ //on est dans la case de score de l a dversaire donc on doit passer a la case 0 du cpu(ordi)
			case_gene=0;
			k->case_cpu[case_gene]++;
		}
  		//if (case_gene==case_choisie) case_gene++; // On est dans la case � jouer, on passe � la suivante
		if(case_gene==6){
			k->score_cpu++;
			nb_graine--;
			k->case_moi[case_gene-6]++;}
		}
		if (case_gene>5){
			k->case_moi[case_gene-6]++;
		}else{
			k->case_cpu[case_gene]++;
		}
		nb_graine--;
	}
	
	k->tour_jeu=1; // Au tour de l'autre(joueur)
}

//fait tourner le jeu entre le joueur et le CPU
void lance_jeu_1joueur(kalah* k){
	int i;
	int nbre_graine;
		
	afficher(*k);
	while (k->fini==0){
		demande_joueur(k); //demande et joue
		afficher(*k);
		if (k->fini==0){
			
			demande_cpu(k);
			afficher(*k);
			
		}
	}
	terminer_jeu(k);
	afficher(*k);
	afficher_gagnant_1joueur(*k);
}

// Affecte les dernieres graines quand le jeu est fini
void terminer_jeu(kalah* k){
	int i;
	k->score_moi+=k->case_moi[0]+k->case_moi[1]+k->case_moi[2]+k->case_moi[3]+k->case_moi[4]+k->case_moi[5];
	k->score_cpu+=k->case_cpu[0]+k->case_cpu[1]+k->case_cpu[2]+k->case_cpu[3]+k->case_cpu[4]+k->case_cpu[5];
	for (i=0;i<6;i++){
		k->case_moi[i]=0;
		k->case_cpu[i]=0;
	}
}

// Affiche le gagnant pour jeu 1 joueur
void afficher_gagnant_1joueur(kalah k){
	if (k.score_moi > k.score_cpu)
		printf("Le gagnant est %s !\n Felicitations.\n\n",k.nom1);
	else
		if (k.score_moi < k.score_cpu)
			printf("Le gagnant est l ordinateur !\n Entraines-toi encore.\n\n");
		else
			printf("Match nul !\n Pas mal du tout.\n\n");
}

void changer_noms(kalah* k){
    printf("\n\nLe nom du premier joueur : ");
    scanf("%s",k->nom1);
    printf("Le nom du deuxieme joueur : ");
    scanf("%s",k->nom2);
}