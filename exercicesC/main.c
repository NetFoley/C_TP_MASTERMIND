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
    int compteur = 0; //Compte le nombre d'entr�es du joueur
    char codeSecret[TCODE]; //Code g�n�r� al�atoirement
    char codeTest[TCODE]; //Code envoy� par le joueur
    srand(time(NULL)); //Fonction qui g�n�re de l'al�atoire
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //Colorier le texte en gris de base

    for (int i = 0; i < TCODE-1; i++) //G�n�ration du nombre al�atoire
    {
        codeSecret[i] = getRandom();
    }

    //Boucle de jeu
    while(!verifTableau(codeSecret, codeTest, TCODE-1) && compteur < 12) //Tant que les codes sont diff�rents et le nombre d'entr�es inf�rieur � 12..
    {
        askNombres(codeTest, TCODE-1);
        compteur++;
    }

    //Condition de victoire
    if(compteur < 12)
        printf("GAGNE\n"); //La r�compense :)

    printf("%s", codeSecret); //Affiche le code
    return 0;
}

int verifTableau(char * tab1, char * tab2, int tMax)
{
    //Verifier la condition de victoire o� les 4 caract�res d'un tableau sont identiques et affiche mes les diff�rences / ressemblances
    //Entr�es : adresses de 2 tableaux
    int idem = 1; //Variable renvoy� : 1 si les 2 tableaux sont idem, 0 sinon
    int drawColor = 7;//Variable d�finissant la couleur � dessiner
    for(int i = 0; i < tMax; i++)
    {
        for(int j = 0; j < tMax; j++)
        {
            //V�rifie si un caract�re est pr�sent dans le code et s'il est bien positionn�
            if(tab1[j] == tab2[i] && drawColor != 15)
            {
                drawColor = 11;
            if(i == j)
                drawColor = 15;
            }
        }

        //V�rifie la condition de non-victoire
        if (tab1[i] != tab2[i])
        {
            idem = 0;
        }

        //Affichage du code colori�
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), drawColor);
        printf("%c", tab2[i]);
        drawColor = 7;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    printf("\n");
    return idem;
}

void askNombres(char * tab, int tMax)
//Demande une chaine de caract�re � l'utilisateur et prendre les 4 premieres lettres. Recommence si ce ne sont pas des chiffres.
{
    do
    {
        printf("Entrez un code a %i chiffre\n", tMax);
        scanf("%4s", tab);
        fflush(stdin); //Vider le buffer de m�moire
    }while(tab[1] < '0' || tab[1] > '9' || tab[0] < '0' || tab[0] > '9' || tab[2] < '0' || tab[2] > '9' || tab[3] < '0' || tab[3] > '9');
}

int getRandom()
//Renvoie un entier al�atoire
{
    printf("Generation d'un nombre aleatoire\n");
    int r = '0' + rand()%10;
    return r;
}
