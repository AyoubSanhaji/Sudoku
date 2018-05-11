#include "Head.h"

int k=0; //Variable globale : Nombre de case vides

int Random(int a, int b) //[a,b[
{
    return rand()%(b-a) + a;
}

int **Generer(int niveau)
{
    int i , j;
    int k = Random(1,10); //1er chiffre de la grille
    //Allocation memoire de tableau(Sudoku)
    int **t;
    t = malloc(9*sizeof(int *));
    for(i=0 ; i<9 ; i++)
        t[i] = malloc(9*sizeof(int));
    // Generer une grille parfaite
    for(i=0 ; i<9 ; i++)
    {
        for(j=0 ; j<9 ; j++)
        {
            t[i][j] = k; //Affecter la valeur de k a la premiere case
            k++;   //Incrementation de k
            if(k == 10) //Quand k=10 on le remplace par 1
                k = 1;
        }
        if(i==2 || i==5)//le 1er nombre des lignes 4,7 = le 4eme nombre des lignes 3,6  +  1
        {
            k = t[i][3]+1;
            if(k == 10)
                k = 1;
        }
        else
            k = t[i][3];//Le 1er nombre des autres lignes = le 4eme nombre de ligne precedent
    }
    // Supprimer des cases
    for(i=0 ; i<9 ; i=i+3)//Saut par bloc
        for(j=0 ; j<9 ; j=j+3)//Saut par bloc
            for(k=0 ; k<niveau ; k++) //Combien de nombre a supprime
            {
                int ai = i-(i%3);//Indice min
                int bi = ai+3;//Indice max
                int ci = Random(ai,bi);//Indice de ligne d'une case dans un bloc
                int aj = j-(j%3);//Indice min
                int bj = aj+3;//Indice max
                int cj = Random(aj,bj);//Indice de colonne d'une case dans un bloc
                if(t[ci][cj] == 0)
                    k--;
                else
                    t[ci][cj] = 0;
            }
    return t;
}

void AfficherGrille(int **t , int **vide)
{
    int i,j;
    printf("\t\t\t ----- ----- -----\t ----- ----- -----\t ----- ----- -----");
    for(i=0 ; i<9 ; i++)
    {
        if(i%3==0)
        {
            if(i==0)
                printf("\n");
            else
                printf("\n\t\t\t ----- ----- -----\t ----- ----- -----\t ----- ----- -----\n");
        }
        for(j=0 ; j<9 ; j++)
        {
            if(j%3==0)
            {
                if(j==0)
                    printf("\t\t\t");
                else
                    printf("|\t");
            }
            if(Appartient(vide , i+1 , j+1) == 1)
            {
                 if(t[i][j] == 0)
                    printf("|     ");
                else
                    printf("| -%d- " , t[i][j]);
            }
            else
                printf("|  %d  " , t[i][j]);
            if(j==8)
                printf("|");
        }
        printf("\n");
        printf("\t\t\t ----- ----- -----\t ----- ----- -----\t ----- ----- ----- \n");
    }
}

void AfficheLogo()
{
    printf("\n");
    printf("\t######################################################################################################\n");
    printf("\t##                                                                                                  ##\n");
    printf("\t##      ###########    ##       ##    #########       ###########    ##   #####    ##       ##      ##\n");
    printf("\t##      ##             ##       ##    ##      ###     ##       ##    ##  ####      ##       ##      ##\n");
    printf("\t##      ##             ##       ##    ##       ##     ##       ##    ## ###        ##       ##      ##\n");
    printf("\t##      ###########    ##       ##    ##       ###    ##       ##    ###           ##       ##      ##\n");
    printf("\t##               ##    ##       ##    ##       ##     ##       ##    ## ###        ##       ##      ##\n");
    printf("\t##               ##    ##       ##    ##      ###     ##       ##    ##  ####      ##       ##      ##\n");
    printf("\t##      ###########    ###########    #########       ###########    ##   #####    ###########      ##\n");
    printf("\t##                                                                                                  ##\n");
    printf("\t######################################################################################################\n");
}

int AfficheMenuMain()
{
    int choix;
    AfficheLogo();
    printf("\t##                                                                                                  ##\n");
    printf("\t##                               Choisissez L'un Des Options Suivantes :                            ##\n");
    printf("\t##                               1- Jouer Une Nouvelle Partie                                       ##\n");
    printf("\t##                               2- Terminer Une Ancienne Partie                                    ##\n");
    printf("\t##                               3- Comment Jouer ?                                                 ##\n");
    printf("\t##                               4- Quitter                                                         ##\n");
    printf("\t##                                                                                                  ##\n");
    printf("\t######################################################################################################\n");
    printf("\t####################################                              ####################################\n");
    printf("\t                                          : Votre Choix :  ");
    scanf("%d" , &choix);
    printf("\n\n");
    return choix;
}

int AfficheMenuNiveau()
{
    int niveau;
    printf("\n\t######################################################################################################\n");
    printf("\t##                                                                                                  ##\n");
    printf("\t##                              Easy -> 4 :: Medium -> 5 :: Hard -> 6                               ##\n");
    printf("\t##                                                                                                  ##\n");
    printf("\t######################################################################################################\n");
    printf("\t####################################                              ####################################\n");
    do
    {
        getchar();
        fflush(stdin);
        printf("\t                                          : Quel Niveau :  ");
        scanf("%d" , &niveau);
        printf("\n");
    }while(niveau<4 || niveau>6);
    return niveau;
}

void AfficheMenuNB()
{
    printf("\n\t######################################################################################################\n");
    printf("\t##                                                                                                  ##\n");
    printf("\t##                  Les Lignes : i  Et Les Colonnes : j  Sont Entre 1 et 9                          ##\n");
    printf("\t##                            Pour Quitter Le Jeu : i=-1 et j=-1                                    ##\n");
    printf("\t##                      Pour Sauvegarder La Partie Du Jeu : i=0 et j=0                              ##\n");
    printf("\t##                         Pour Recommencer Du Debut : i=-2 et j=-2                                 ##\n");
    printf("\t##                                                                                                  ##\n");
    printf("\t######################################################################################################\n");
}

void AfficheRegle()
{
    printf("\n\t######################################################################################################\n");
    printf("\t##                                                                                                  ##\n");
    printf("\t##      Les regles du sudoku sont tres simples. Un sudoku classique contient neuf lignes et neuf    ##\n");
    printf("\t##    colonnes, donc 81 cases au total.                                                             ##\n");
    printf("\t##      Le but du jeu est de remplir ces cases avec des chiffres allant de 1 a 9 en veillant        ##\n");
    printf("\t##    toujours a ce qu'un meme chiffre ne figure qu'une seule fois par colonne, une seule fois      ##\n");
    printf("\t##    par ligne, et une seule fois par carre de neuf cases (bloc).                                  ##\n");
    printf("\t##      Au debut du jeu, une vingtaine de chiffres sont deja places et il vous reste a trouver      ##\n");
    printf("\t##    les autres. En effet, une grille initiale de sudoku correctement constituee ne peut aboutir   ##\n");
    printf("\t##    qu'a une et une seule solution. Pour trouver les chiffres manquants, tout est une question    ##\n");
    printf("\t##    de logique et d'observation.                                                                  ##\n");
    printf("\t##                                                                                                  ##\n");
    printf("\t##                                                                                                  ##\n");
    printf("\t##                             Appuyez Sur Entrer Pour Continuer                                    ##\n");
    printf("\t##                                                                                                  ##\n");
    printf("\t######################################################################################################\n");
}

int **CaseVide(int **t)
{
    int i,j,l;
    int **res;
    k = NbreCaseVide(t);
    //Allocation de memoire pour le tableau qui va contient les coordonnes des cases vides
    res = malloc(sizeof(int*) * k);
    for(i=0 ; i<k ; i++)
        res[i] = malloc(sizeof(int) * 2);
    l = 0;
    for(i=0 ; i<9 ; i++)
        for(j=0 ; j<9 ; j++)
            if(t[i][j] == 0)
            {
                res[l][0] = i; //Affectation de numero de ligne
                res[l][1] = j; //Affectation de numero de colonne
                l++;
            }
    return res;
}

int NbreCaseVide(int **t)
{
    int i,j,nb=0;
    for(i=0 ; i<9 ; i++) // Parcourir le tableau et compter le nombre des cases vides
        for(j=0 ; j<9 ; j++)
            if(t[i][j] == 0)
                nb++;
    return nb;
}

int Appartient(int **res , int a , int b)
{
    int i;
    if(a<10 && a>0 && b<10 && b>0)
    {
        for(i=0 ; i<k ; i++)
            if(res[i][0]==a-1 && res[i][1]==b-1) //on teste si la case(a,b) est vide ou pas
                return 1;
        return 0;
    }
    else
        return 0;
}

int **RemiseAZero(int **t , int **vide)
{
    int i,j;
    for(i=0 ; i<9 ; i++)
        for(j=0 ; j<9 ; j++)
        {
            if(Appartient(vide , i+1 , j+1) == 1)
                t[i][j] = 0;
        }
    return t;
}

int VerifLigne(int **t , int i , int val)
{
    if(val < 10 && val > 0)
    {
        int j;
        for(j=0 ; j<9 ; j++)
            if(t[i-1][j] == val) //on test si la valeur existe dans la ligne ou pas
                return 0;
        return 1;
    }
    else
        return 0;
}

int VerifColonne(int **t , int j , int val)
{
    if(val < 10 && val > 0)
    {
        int i;
        for(i=0 ; i<9 ; i++)
            if(t[i][j-1] == val) //on test si la valeur existe dans la colonne ou pas
                return 0;
        return 1;
    }
    else
        return 0;
}

int VerifBloc(int **t , int i , int j , int val)
{
    if(val < 10 && val > 0) //on test si la valeur existe dans le bloc ou pas
    {
        int a = (i-1) - ((i-1)%3);
        int b = (j-1) - ((j-1)%3);
        int l , c;
        for(l=a ; l<a+3 ; l++)
            for(c=b ; c<b+3 ; c++)
                if(t[l][c] == val)
                    return 0;
        return 1;
    }
    else
        return 0;
}

void CreerFichier(char nom[] , int **t , int **vide , int *temps)
{
    FILE *f1=NULL , *f2=NULL;
    int i,j;
    char tmp[50];
    strcpy(tmp , nom);
    f1 = fopen(tmp , "w+");
    f2 = fopen(strcat(tmp , "Vide") , "w+");
    if (f1 != NULL && f2 != NULL)
    {
        for(i=0 ; i<9 ; i++)
        {
            for(j=0 ; j<9 ; j++)
                fputc(t[i][j]+'0' , f1); //Convertir les valeurs en caracteres et les ecrires dans le fichier
            fputc('\n' , f1);
        }
        fputc(k+'0' , f1); //Ecrire le nombre de cases vides dans le fichier
        fclose(f1);
        for(i=0 ; i<k ; i++)
        {
            for(j=0 ; j<2 ; j++)
                fputc(vide[i][j]+'0' , f2);
            fputc('\n' , f2); //Effectue un retour a la ligne '\n'
        }
        fputc((*temps)+'0' , f2); //Ecrire le temps effectue dans le fichier
        fclose(f2);
    }
}

int **RecupereFichier(char nom[] , int **t , int **vide , int *temps)
{
    FILE *f1=NULL , *f2=NULL;
    int i,j;
    char tmp[50];
    strcpy(tmp , nom);
    f1 = fopen(tmp , "r+");
    f2= fopen(strcat(tmp , "Vide") , "r+");
    if(f1 != NULL && f2 != NULL)
    {
        for(i=0 ; i<9 ; i++)
        {
            for (j=0; j<9; j++)
               t[i][j] = fgetc(f1)-'0'; //Convertir le caractere en entier
            fgetc(f1);//Recperer le caractere '\n'
        }
        k = fgetc(f1)-'0'; //Nbre de cases vides
        fclose(f1);
        vide = malloc(k*sizeof(int *));
        for(i=0 ; i<k ; i++)
            vide[i] = malloc(2*sizeof(int));
        for(i=0 ; i<k ; i++)
        {
            for (j=0; j<2; j++)
               vide[i][j] = fgetc(f2)-'0'; //Convertir le caractere en entier
            fgetc(f2); //Recupere le caractere '\n'
        }
        (*temps) = fgetc(f2)-'0'; //Convertir le temps effectue par le joueur en entier
        fclose(f2);
        return vide;
    }
    else
        return NULL;
}
