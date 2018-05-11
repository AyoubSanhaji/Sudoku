#include "Head.h"

int main()
{
    srand(time(NULL));
    int **t; //Grille
    int i,j,val; //Indices et valeur
    int **vide; //Tableau des indices des cases vides
    int niveau; //4:Easy 5:Medium 6:Hard
    int choix;
    int temps = 0;
    int ifexist = 0; //Si un fichier est deja recuperer
    char nom[20];
    char doss[] = "Sauv/";
    struct timeval temps_avant, temps_apres; //Temps de l'execution
    begin :
    choix = AfficheMenuMain();
    do
    {
        switch(choix)
        {
            case 1 :
            {
                niveau = AfficheMenuNiveau();
                t = Generer(niveau);
                vide = CaseVide(t);
                play2 :
                gettimeofday (&temps_avant, NULL);
                system("cls");
                AfficheLogo();
                printf("\n");
                AfficherGrille(t , vide);
                AfficheMenuNB();
                do
                {
                    printf("\n\tDonnez Le Numero De Ligne : ");
                    scanf("%d" , &i);
                    fflush(stdin);
                    printf("\n\tDonnez Le Numero De Colonne : ");
                    scanf("%d" , &j);
                    fflush(stdin);
                    if(i == -1 && j == -1)
                        exit(0);
                    if(i == -2 && j == -2)
                    {
                        t = RemiseAZero(t , vide);
                        goto play2;
                    }
                    if(i == 0 && j == 0)
                    {
                        if(ifexist == 0)
                        {
                            printf("\n\tDonner le nom de fichier : ");
                            scanf("%s" , nom);
                            strcat(doss , nom);
                        }
                        gettimeofday (&temps_apres, NULL);
                        temps += (((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec)/1000000;
                        printf("\n\n\tVous avez jouer pendant %d seconds" , temps);
                        CreerFichier(doss , t , vide , &temps);
                        printf("\n\tVotre Partie A Ete Bien Enregistrer");
                        exit(0);
                    }
                    if(Appartient(vide , i , j) == 1)//Si la case (i,j) est vide
                    {
                        printf("\n\tDonnez la valeur : ");
                        scanf("%d" , &val);
                        fflush(stdin);
                        if(val>9 || val<1)
                        {
                            printf("\n\tValeur Incorrecte !\n");
                            fflush(stdin);
                        }
                        else
                            if(VerifBloc(t,i,j,val)==1 && VerifColonne(t,j,val)==1 && VerifLigne(t,i,val)==1) //Verification de valeur sur ligne-colonne-bloc
                            {
                                t[i-1][j-1] = val; //Remplissage de la val dans la grille
                                system("cls");
                                AfficheLogo();
                                printf("\n");
                                AfficherGrille(t,vide);
                                if(NbreCaseVide(t) != 0)
                                    AfficheMenuNB();
                            }
                            else
                            {
                                if(VerifBloc(t,i,j,val)==0)
                                    printf("\n\tLa Valeur Existe Deja Dans Le Bloc\n");
                                else
                                {
                                    if(VerifColonne(t,j,val)==0)
                                        printf("\n\tLa Valeur Existe Deja Dans La Colonne\n");
                                    else
                                        if(VerifLigne(t,i,val)==0)
                                            printf("\n\tLa Valeur Existe Deja Dans La Ligne\n");
                                }
                            }
                    }
                    else
                        if(i>9 || i<1 || j>9 || j<1)
                            printf("\n\tLes lignes et les colonnes doivent etre entre 1 et 9 !\n");
                        else
                            printf("\n\tT'as Pas Le Droit De Modifier Cette Case\n");
                }while(NbreCaseVide(t) != 0);
                gettimeofday (&temps_apres, NULL);
                temps += (((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec)/1000000;
                printf("\t######################################################################################################\n");
                printf("\t##                                                                                                  ##\n");
                printf("\t##                             ^^ Bravo !! Vous Avez Gangne !! ^^                                   ##\n");
                printf("\t##                               -- Resolu dans %d secondes --                                      ##\n",temps);
                printf("\t##                                                                                                  ##\n");
                printf("\t######################################################################################################\n");
                break;
            }
            case 2 :
            {
                printf("\t\tDonner le nom de fichier : ");
                scanf("%s" , nom);
                strcat(doss , nom);
                ifexist = 1;
                t = malloc(9*sizeof(int *));
                for(i=0 ; i<9 ; i++)
                    t[i] = malloc(9*sizeof(int));
                vide = RecupereFichier(doss , t , vide , &temps);
                if(vide == NULL)
                {
                    system("cls");
                    printf("\n\t\t\t\t\t   Aucun Partie A Ete Enregistrer !\n");
                    goto begin;
                }
                else
                    goto play2;
                break;
            }
            case 3 :
            {
                AfficheRegle();
                char c;
                scanf("%c" , &c);
                getchar();
                fflush(stdin);
                system("cls");
                goto begin;
                break;
            }
            case 4 :
            {
                exit(0);
                break;
            }
            default :
            {
                system("cls");
                printf("\n\t\t\t\t\t\tChoix Invalide !\n");
                fflush(stdin);
                goto begin;
            }
        }
    }while(choix<1 && choix>4);
    return 0;
}
