#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include <sys/time.h>

int Random(int a, int b);
void AfficherGrille(int **t , int **vide);
int AfficheMenuMain();
int AfficheMenuNiveau();
void AfficheMenuNB();
void AfficheRegle();
void AfficheLogo();
int **Generer();
int **CaseVide(int **t);
int NbreCaseVide(int **t);
int Appartient(int **res , int a , int b);
int **RemiseAZero(int **t , int **vide);
int VerifBloc(int **t , int i , int j , int val);
int VerifLigne(int **t , int i , int val);
int VerifColonne(int **t , int j , int val);
void CreerFichier(char nom[] , int **t , int **vide , int *temps);
int **RecupereFichier(char nom[] , int **t , int **vide , int *temps);
