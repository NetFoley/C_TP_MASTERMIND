#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define TCODE 5


int verifTableau(char * tab1, char * tab2, int tMax);
void askNombres(char * tab, int tMax);
int getRandom();

int main()
{
    //Definition des variables
    int compteur = 0; //Compte le nombre d'entrées du joueur
    char codeSecret[TCODE]; //Code généré aléatoirement
    char codeTest[TCODE]; //Code envoyé par le joueur
    srand(time(NULL)); //Fonction qui génère de l'aléatoire
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //Colorier le texte en gris de base

    for (int i = 0; i < TCODE-1; i++) //Génération du nombre aléatoire
    {
        codeSecret[i] = getRandom();
    }

    //Boucle de jeu
    while(!verifTableau(codeSecret, codeTest, TCODE-1) && compteur < 12) //Tant que les codes sont différents et le nombre d'entrées inférieur à 12..
    {
        askNombres(codeTest, TCODE-1);
        compteur++;
    }

    //Condition de victoire
    if(compteur < 12)
        printf("GAGNE\n"); //La récompense :)

    printf("%s", codeSecret); //Affiche le code
    return 0;
}

int verifTableau(char * tab1, char * tab2, int tMax)
{
    //Verifier la condition de victoire où les 4 caractères d'un tableau sont identiques et affiche mes les différences / ressemblances
    //Entrées : adresses de 2 tableaux
    int idem = 1; //Variable renvoyé : 1 si les 2 tableaux sont idem, 0 sinon
    int drawColor = 7;//Variable définissant la couleur à dessiner
    for(int i = 0; i < tMax; i++)
    {
        for(int j = 0; j < tMax; j++)
        {
            //Vérifie si un caractère est présent dans le code et s'il est bien positionné
            if(tab1[j] == tab2[i] && drawColor != 15)
            {
                drawColor = 11;
            if(i == j)
                drawColor = 15;
            }
        }

        //Vérifie la condition de non-victoire
        if (tab1[i] != tab2[i])
        {
            idem = 0;
        }

        //Affichage du code colorié
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), drawColor);
        printf("%c", tab2[i]);
        drawColor = 7;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    printf("\n");
    return idem;
}

void askNombres(char * tab, int tMax)
//Demande une chaine de caractère à l'utilisateur et prendre les 4 premieres lettres. Recommence si ce ne sont pas des chiffres.
{
    do
    {
        printf("Entrez un code a %i chiffre\n", tMax);
        scanf("%4s", tab);
        fflush(stdin); //Vider le buffer de mémoire
    }while(tab[1] < '0' || tab[1] > '9' || tab[0] < '0' || tab[0] > '9' || tab[2] < '0' || tab[2] > '9' || tab[3] < '0' || tab[3] > '9');
}

int getRandom()
//Renvoie un entier aléatoire
{
    printf("Generation d'un nombre aleatoire\n");
    int r = '0' + rand()%10;
    return r;
}
