/*
    Programme de Louis BERTHIER
*/

#include <stdio.h>
#include <stdlib.h>

#define MONTH_IN_YEAR 12
#define DAYS_IN_WEEK 7
#define DAYS_IN_YEAR 365
#define WEEKS_IN_YEAR 55
#define LIGNE_MAX 50
#define LIGNE_CSV 6
#define COLONNE_CSV 7
#define DISTANCE_MAX 5000
#define ANNEE_MIN 1900
#define ANNEE_MAX 2023
#define DEBUT_COMPTEUR -100
#define CONTRAINTE3 28

char matriceCalendrier[WEEKS_IN_YEAR][DAYS_IN_WEEK]; //La matrice calendrier que l'on cherche � construire
char *lesMois[] = {"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"}; //Tableau contenant tous les mois
int nombreJourParMois[]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //Tableau contenant le nombre de jours de chaque mois
int matriceCSV[LIGNE_CSV][COLONNE_CSV] = {0}; //La matrice o� sera stock� le fichier csv lu
struct position  //D�finition d'une structure pour retrouver la position d'un jour dans le calendrier
{
    int ligne;
    int colonne;
} position;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Fonction principale pour le bon fonctionnement du code

//Formule pour calculer le jour 0 d'une ann�e donn�e :
//https://stackoverflow.com/questions/478694/what-is-the-easiest-algorithm-to-find-the-day-of-week-of-day-zero-of-a-given-yea
int premierJour(int num_annee)
{
    int jour0;
    jour0 = (((num_annee - 1) * DAYS_IN_YEAR) + ((num_annee - 1) / 4) - ((num_annee - 1) / 100) + ((num_annee) / 400) + 1) % DAYS_IN_WEEK;
    return jour0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------





//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Fonctions pour r�pondre � la Q1

void afficherCalendrierPropre(int num_annee)
{
    //On initialise nos variables
    int num_mois, num_jour;
    int nombreJourDansMois, jourActuel;
    int jourDeSemaine = 0;

    jourActuel = premierJour(num_annee) - 1; //On calcule le jour0 de l'annee indiquee
    printf("\n\n---------------%d-------------------\n", num_annee);

    //D'abord, on verifie si l'annee est bissextile
    if((num_annee % 4 == 0 && num_annee % 100 != 0) || num_annee % 400 == 0) //https://docs.microsoft.com/en-us/office/troubleshoot/excel/determine-a-leap-year
    {
        nombreJourParMois[1] = 29; //On passe de 28 � 29 jours en Fevrier si on a une annee bissextile
    }

    for(num_mois = 0; num_mois < MONTH_IN_YEAR; num_mois++) //Pour chaque mois de l'annee
    {
        nombreJourDansMois = nombreJourParMois[num_mois]; //On vient recuperer le nombre de jour du mois considerer
        printf("\n\n---------------%s-------------------\n", lesMois[num_mois]); //On affiche chaque nouveau mois d�s que le pr�c�dent est fini
        printf("\n  Lun  Mar  Mer  Jeu  Ven  Sam  Dim \n"); //On affiche les 7 jours directement apr�s le mois
        for(jourDeSemaine = 0; jourDeSemaine < jourActuel; jourDeSemaine++) //Pour determiner quel jour (lundi, mardi, etc...) est � 1
            printf("     "); //On affiche des espaces jusqu'� ce qu'on tombe sur le premier jour

        for(num_jour = 1; num_jour <= nombreJourDansMois; num_jour++)  //Poru chaque jour du mois
        {
            printf("%5d",num_jour); //On affiche le num�ro du jour
            if(++jourDeSemaine > DAYS_IN_WEEK - 1)  //Si on d�passe 6
            {
                printf("\n"); //On retourne � la ligne pour s�parer visuellement les semaines
                jourDeSemaine = 0; // Et on revient au 1er jour de la semaine (ici on consid�re lundi)
            }
            jourActuel = jourDeSemaine;
        }
    }


}

//M�me principe que pr�c�demment sauf qu'on a une construction matricielle au lieu d'un simple affichage
int ** matriceCalendrierFunc(int num_annee)
{
    //On initialise nos variables
    int cpt_ligne = 0;
    int num_mois, num_jour;
    int nombreJourDansMois, jourActuel;
    int jourDeSemaine = 0;
    jourActuel = premierJour(num_annee); //On calcule le jour0 de l'annee indiquee

    //On regarde si on a une ann�e bissextile ou non
    if((num_annee % 4 == 0 && num_annee % 100 != 0) || num_annee % 400 == 0) //https://docs.microsoft.com/en-us/office/troubleshoot/excel/determine-a-leap-year
    {
        nombreJourParMois[1] = 29; //On passe de 28 � 29 jours en Fevrier si on a une annee bissextile
    }

    for (num_mois = 0; num_mois <= MONTH_IN_YEAR; num_mois++ ) //On parcourt l'ensemble des mois
    {
        nombreJourDansMois = nombreJourParMois[num_mois]; //On regarde le nombre de jour de chaque mois
        for ( num_jour = 1; num_jour <= nombreJourDansMois; num_jour++ ) //On parcourt l'ensemble des jours
        {
            if(jourActuel == 0 && cpt_ligne==0) //Si on commence un lundi et qu'il s'agit de l'initialisation de la matrice
            {
                matriceCalendrier[cpt_ligne][6] = 1; //on met 1 au dimanche
                cpt_ligne++;//On passe � la ligne suivante
            }
            if ((num_jour + jourActuel -1) % 7 == 0) //Si on est dimanche
            {
                matriceCalendrier[cpt_ligne-1][6] = num_jour; //On met la date au dimanche
            }
            else //Si on n'est pas dimanche
            {
                matriceCalendrier[cpt_ligne][(num_jour+jourActuel-1) % 7 - 1] = num_jour; //On met la  date au bon jour de la semaine (selon indexation)
            }
            if ((num_jour + jourActuel ) % 7 == 0 ) //On cherche � v�rifier si on passe � la ligne suivante
            {
                cpt_ligne++;
            }
        }
        jourActuel = (jourActuel + nombreJourParMois[num_mois]) % 7; //On se place au jour du mois suivant (continuit� du calendrier)
    }
    return matriceCalendrier;
}

//On copie colle la fonction "afficherCalendrierPropre" et on remplace les printf par fprintf
int exporterCalendrierTxt(int num_annee)  //Exporte notre calendrier dans un fichier au format .txt
{
    int num_mois, num_jour;
    int nombreJourDansMois, jourActuel;
    int jourDeSemaine = 0;

    jourActuel = premierJour(num_annee); //On calcule le jour0 de l'annee indiquee
    matriceCalendrierFunc(num_annee); //Initialisation de la matrice

    char nomFichier[] = "calendrier.txt"; //Nom de notre fichier


    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "w"); //On ouvre le fichier avec droit d'�criture

    if (fichier != NULL) //Si le fichier existe
    {
        fprintf(fichier,"\n\n---------------%d-------------------\n", num_annee);

        //D'abord, on verifie si l'annee est bissextile
        if((num_annee % 4 == 0 && num_annee % 100 != 0) || num_annee % 400 == 0) //https://docs.microsoft.com/en-us/office/troubleshoot/excel/determine-a-leap-year
        {
            nombreJourParMois[1] = 29; //On passe de 28 � 29 jours en Fevrier si on a une annee bissextile
        }

        for(num_mois = 0; num_mois < MONTH_IN_YEAR; num_mois++) //Pour chaque mois de l'annee
        {
            nombreJourDansMois = nombreJourParMois[num_mois]; //On vient recuperer le nombre de jour du mois considerer
            fprintf(fichier,"\n\n---------------%s-------------------\n", lesMois[num_mois]); //On affiche chaque nouveau mois d�s que le pr�c�dent est fini
            fprintf(fichier,"\n  Lun  Mar  Mer  Jeu  Ven  Sam  Dim \n"); //On affiche les 7 jours directement apr�s le mois
            for(jourDeSemaine = 0; jourDeSemaine < jourActuel; jourDeSemaine++) //Pour determiner quel jour (lundi, mardi, etc...) est � 1
                fprintf(fichier,"     "); //On affiche des espaces jusqu'� ce qu'on tombe sur le premier jour

            for(num_jour = 1; num_jour <= nombreJourDansMois; num_jour++)  //Poru chaque jour du mois
            {
                fprintf(fichier,"%5d",num_jour); //On affiche le num�ro du jour
                if(++jourDeSemaine > DAYS_IN_WEEK - 1)  //Si on d�passe 6
                {
                    fprintf(fichier,"\n"); //On retourne � la ligne pour s�parer visuellement les semaines
                    jourDeSemaine = 0; // Et on revient au 1er jour de la semaine (ici on consid�re lundi)
                }
                jourActuel = jourDeSemaine;
            }
        }
    }
    else //Si le fichier n'existe pas
    {
        printf(fichier,"Erreur : le fichier n'existe pas");
    }
    return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------





//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Fonctions pour r�pondre � la Q2

float calculerDistance(struct position jour1, struct position jour2)
{
    //Position de notre jour1 dans le calendrier matriciel
    int absJ1 = jour1.ligne;
    int ordJ1 = jour1.colonne;
    //Posirion de notre jour2 dans le calendrier matriciel
    int absJ2 = jour2.ligne;
    int ordJ2 = jour2.colonne;

    float distance = 0.;

    distance = sqrt((ordJ2-ordJ1) * (ordJ2-ordJ1) + (absJ2-absJ1) * (absJ2-absJ1)); //Distance euclidienne

    return distance;
}

int * contraintes()
{
    static int valeursJours[2]; //Variable contenant nos deux num�ros pour chacune des dates correspondant � l'indice du jour et � la semaine

    int numJ1 = DEBUT_COMPTEUR; //J1(x,y) ou x = numJ1 et y = numS1
    while(numJ1 < 0 || numJ1 > 7) //Les jours sont seulement compris entre 0 et 6
    {
        printf("\n Rentre l'indice du jour de la premiere date : ");
        scanf("%d",&numJ1);
        if (numJ1 < 0 || numJ1 > 7)
        {
            printf("Erreur : Il faut un chiffre compris entre 0 et 6 avec 0 comme lundi et 6 comme dimanche.\n");
        }
    }

    int numS1 = DEBUT_COMPTEUR;
    while(numS1 < 0 || numS1 > 4) //Les semaines sont uniquement comprises entre 0 et 4
    {
        printf("\n Rentre le numero de la semaine de la premiere date : ");
        scanf("%d",&numS1);
        if (numS1 < 0 || numS1 > 4)
        {
            printf("Erreur : Il faut un chiffre compris entre 0 et 4 pour la semaine du mois.\n");
        }
    }

    int numJ2 = DEBUT_COMPTEUR;
    while(numJ2 < 0 || numJ2 > 7) //Les jours sont seulement compris entre 0 et 6
    {
        printf("\n Rentre l'indice du jour de la seconde date : ");
        scanf("%d",&numJ2);
        if (numJ2 < 0 || numJ2 > 7)
        {
            printf("Erreur : Il faut un chiffre compris entre 0 et 6 avec 0 comme lundi et 6 comme dimanche.\n");
        }
    }

    int numS2 = DEBUT_COMPTEUR;
    while(numS2 < 0 || numS2 > 4) //Les semaines sont uniquement comprises entre 0 et 4
    {
        printf("\n Rentre le numero de la semaine de la seconde date :");
        scanf("%d",&numS2);
        if (numS2 < 0 || numS2 > 4)
        {
            printf("Erreur : Il faut un chiffre compris entre 0 et 4 pour la semaine du mois.\n");
        }
        else if(numJ1 == numJ2) //On g�re le conflit final si on a deux dates identiques
        {
            printf("Erreur : Il faut deux dates distinces !. \n");
        }
    }
    if(numJ1 > 27 || numJ2 > 27) //3�me contrainte dans le sujet
    {
        printf("Contraintes num 3 : Max(numJ1, numJ2) <= 27");
    }
    else if(matriceCalendrier[numS1][numJ1] == 0) //Pour ne pas tenir compte des 0 avant le jour correspondant au num�ro 1
    {
        printf("Erreur : on ne peut pas avoir une date \"nulle\" !");
    }
    else if(matriceCalendrier[numS2][numJ2] == 0)
    {
        printf("Erreur : on ne peut pas avoir une date \"nulle\" !");
    }
    else
    {
        valeursJours[0] = matriceCalendrier[numS1][numJ1]; //Valeur dans la matrice du jour 1 d�sir�, on cherche dans la matrice le num�ro du jour
        valeursJours[1] = matriceCalendrier[numS2][numJ2]; //Valeur dans la matrice du jour 2 d�sir�
        return valeursJours;
    }
}

float calculerDistanceAnnee(int valeursJours[2]) //Va chercher pour chaque mois les deux num�ros des jours calcul�s pr�c�demment
{
    int indJours1[MONTH_IN_YEAR]; //Indice du jour pour la premi�re date pour chaque mois
    int indJours2[MONTH_IN_YEAR];
    int numS1[MONTH_IN_YEAR]; //Num�ro de la semaine pour la premi�re date pour chaque mois
    int numS2[MONTH_IN_YEAR];
    int cptDate1 = 0; //Compteur afin d'incr�menter les
    int cptDate2 = 0;
    float distanceAnnee = 0.;

    while(cptDate1 < MONTH_IN_YEAR && cptDate2 < MONTH_IN_YEAR) //On parcourt chaque mois
    {
        for(int num_ligne = 0; num_ligne < WEEKS_IN_YEAR; num_ligne++ ) //On parcout l'ensemble d'un mois en ligne et colonne
        {
            for(int num_colonne = 0; num_colonne < DAYS_IN_WEEK; num_colonne++)
            {
                if (matriceCalendrier[num_ligne][num_colonne] == valeursJours[0]) //Si l'�l�ment de la matrice correspond au num�ro du jour de la 1�re date
                {
                    indJours1[cptDate1] = num_colonne; //On r�cup�re la position
                    numS1[cptDate1] = num_ligne;
                    cptDate1++;
                }
                else if(matriceCalendrier[num_ligne][num_colonne] == valeursJours[1]) //Si l'�l�ment de la matrice correspond au num�ro du jour de la 2�me date
                {
                    indJours2[cptDate2] = num_colonne;
                    numS2[cptDate2] = num_ligne;
                    cptDate2++;
                }
            }
        }
    }

    for(int num_mois = 0; num_mois < MONTH_IN_YEAR; num_mois++) //pour chaque mois on affecte la position � nos jours correspondant aux deux dates
    {
        struct position jour1;
        struct position jour2;
        struct position dateProchaine;

        jour1.ligne = indJours1[num_mois];
        jour1.colonne = numS1[num_mois];
        jour2.ligne = indJours2[num_mois];
        jour2.colonne = numS2[num_mois];

        distanceAnnee = distanceAnnee + calculerDistance(jour1,jour2); //On calcule la distance entre ces deux nouveaux jours � chaque moi et on ajoute � la distance pour avoir la distance sur une ann�e

        if(num_mois <= 10) //On g�re le changement de mois
        {
            jour1 = jour2;
            dateProchaine.ligne = indJours1[num_mois+1];
            dateProchaine.colonne = numS1[num_mois+1];
            distanceAnnee = distanceAnnee + calculerDistance(jour1,dateProchaine);
        }
    }
    return distanceAnnee;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------





//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Fonction pour r�pondre � la Q4
void csvEnMatrice(char * fic)
{
    int cpt_colonne = 0;
    char sep[] = "\t\n,;| {}[]"; //On definit une liste de s�parateurs pour lire un maximum de fichiers diff�rents
    char ligne[LIGNE_MAX]; //Nombre de ligne que l'on va lire au MAX

    FILE* fichier;
    fopen_s(&fichier,fic, "r"); //On vient lire le fichier sp�cifi�

    while (fgets(ligne, sizeof(ligne),fichier)) //Tant que l'on a pas trait� l'ensemble des lignes de notre fichier
    {
        char * decoupage;
        decoupage = strtok(ligne,sep); //On d�coupe chacune de nos lignes
        while(decoupage != NULL)  //Tant qu'il y a un d�limiteurdes colonnes � lire dans le fichier (une colonne = d�limit�e)
        {
            matriceCSV[0][cpt_colonne] = atoi(decoupage); //Transforme la cha�ne de caract�re de la colonne en valeur num�rique
            cpt_colonne++; //On indique � notre affichaque qu'on change de colonne
            decoupage = strtok(NULL,sep); //On demande le token suivant
        }
    }
    fclose(fichier); //On arr�te le traitement du fichier en le fermant
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------





//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Fonction pour r�pondre � la Q5


//Formule : https://fr.wikibooks.org/wiki/Curiosit%C3%A9s_math%C3%A9matiques/Trouver_le_jour_de_la_semaine_avec_une_date_donn%C3%A9e
int indJour(int num_jour, int num_mois, int num_annee) //Pour trouver l'indice et donc le jour de la semaine
{
    int wd;
    if (num_mois < 3)
    {
        wd = ((23 * num_mois) / 9 + 1 + 4 + num_annee + ((num_annee - 1) / 4) - ((num_annee - 1) / 100) + ((num_annee - 1) / 400) - 1 + num_jour - 1 ) % 7;
    }
    else
    {
        wd = ((23 * num_mois) / 9 + 1 + 2 + num_annee + ((num_annee) / 4) - ((num_annee) / 100) + ((num_annee) / 400) - 1 + num_jour - 1) % 7;
    }
    return wd;
}


int identifierPatternCSV()
{
    int indJour1 = DEBUT_COMPTEUR;
    int cpt = 1;
    int nbrJour = 0;
    int nbrJourVar;

    for(int num_ligne = 0; num_ligne < LIGNE_CSV; num_ligne++)
    {
        for(int num_colonne = 0; num_colonne < COLONNE_CSV; num_colonne++)
        {
            if(matriceCSV[num_ligne][num_colonne] != 0)
                nbrJour++; //On augmente notre compteur de jours
        }
        if(matriceCSV[0][num_ligne]!=0 && indJour1== DEBUT_COMPTEUR)
        {
            indJour1 = num_ligne; //On attribue les indices
        }
    }

    for(int num_annee = ANNEE_MIN; num_annee < ANNEE_MAX; num_annee++)
    {
        for(int num_mois = 1; num_mois< MONTH_IN_YEAR + 1; num_mois++)
        {
            if((num_annee % 4 == 0 && num_annee % 100 != 0) || num_annee % 400 == 0) //https://docs.microsoft.com/en-us/office/troubleshoot/excel/determine-a-leap-year
            {
                nombreJourParMois[1] = 29; //On passe de 28 � 29 jours en Fevrier si on a une annee bissextile
                nbrJourVar = nombreJourParMois[num_mois-1];
            }
            else
            {
                nombreJourParMois[1] = 28;
                nbrJourVar = nombreJourParMois[num_mois-1];
            }
            if(indJour(1,num_mois,num_annee) == indJour1 && nbrJourVar == nbrJour) //Condition d'existence d'un pattern
            {
                printf("Pattern numero : %3d, en %9s de l'annee %4d\n",cpt++,lesMois[num_mois-1],num_annee);
            }
        }
    }
    return 0;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int main()
{
    system("Color F0"); //Change couleur de la console en gris (plus lisible/agr�able)

    int num_annee; //L'annee que l'on soouhaite etudier
    printf("\n Rentre l'annee que tu souhaites observer :");
    scanf("%d",&num_annee); //L'utilisateur rentre la date qu'il souhaite afficher

    //-----------------------------------------------------------------------------------------------
    //Question 1
    printf("\n Affichage du calendrier \"propre\" : \n");
    afficherCalendrierPropre(num_annee); //Joli calendrier � exporter en .txt

    printf("\n\n Affichage du calendrier \"matriciel\" : \n");
    matriceCalendrierFunc(num_annee); //Calendrier (matrice) qui va nous servir pour les calculs de distance
    //On affiche la matrice obtenue (v�rification avec le calendrier "propre")
    for (int num_ligne = 0; num_ligne < WEEKS_IN_YEAR; num_ligne++)
    {
        for (int num_colonne = 0; num_colonne < DAYS_IN_WEEK; num_colonne++)
        {
            printf("%2d ", matriceCalendrier[num_ligne][num_colonne]);
        }
        printf("\n");
    }

    exporterCalendrierTxt(num_annee);
    //-----------------------------------------------------------------------------------------------





    //-----------------------------------------------------------------------------------------------
    //Question 2

    float distanceAnnee = calculerDistanceAnnee(contraintes()); //On calcule la distance sur une ann�e compl�te en donnant deux dates avec (indice Jour et num�ro Semaine)
    printf("\n\n Distance sur l'annee complete choisie arbitrairement : %f \n", distanceAnnee);
    //-----------------------------------------------------------------------------------------------





    //-----------------------------------------------------------------------------------------------
    //Question 3
    //On vient appliquer le calcul de distance minimale � la contraine 1 CALCUL DE LA DISTANCE MINIMALE POUR TOUTE LES DATES DE 1900 A 2022

    int valeursJours[2];
    int numJ1Dynamique, numJ2Dynamique, anneeDynamique;
    int cptNumj1[150], cptNumj2[150], cptNumAnnee[150];
    int cpt = 0;  //compteur qui va permettre d'afficher toutes les dates ayant une distance minmale

    float distanceMin, distanceDynamique;
    distanceMin = DISTANCE_MAX; //On donne une barre haute pour permettre � l'algo de tourner

    for(int num_annee = ANNEE_MIN; num_annee < ANNEE_MAX; num_annee++) //On parcourt toutes les annees de la contraine 1 du sujet
    {
        matriceCalendrierFunc(num_annee); //On vient recr�er la matrice associ�e � chaque ann�e
        for(int numJ1 = 1; numJ1 < CONTRAINTE3; numJ1++) //Contrainte num 3
        {
            for(int numJ2 = numJ1 + 1; numJ2 < CONTRAINTE3 + 1; numJ2++) //D�calage forc�e : on veut j2 != j1 et j2 > j1
            {
                if((numJ2-numJ1) % 7 != 0) //2eme contrainte dans le sujet
                {
                    valeursJours[0] = numJ1; //On vient r�cup�rer la valeur de chaque jour
                    valeursJours[1] = numJ2;
                    distanceDynamique = calculerDistanceAnnee(valeursJours); //On calcule chacune des distances

                    if(distanceDynamique <= distanceMin)
                    {
                        numJ1Dynamique = numJ1; //R�affectation des variables pour le prochain tour de boucle
                        numJ2Dynamique = numJ2;
                        anneeDynamique = num_annee;
                        distanceMin = distanceDynamique; //On regarde la plus petite distance parmi toutes celles que nous avons

                    }
                }
            }
        }
    }
    printf("\n\nVoici la distance minimale entre 1900 et 2022 : %f\n\n",distanceMin); //On regarde la plus petite de toutes les distances !

    //On vient maintenant regarder pour chaque annee si une distance correspond � la distance minimale trouv�e pr�c�demment
    //On recopie donc la boucle pr�c�dente en stockant les valeurs
    for(int num_annee = ANNEE_MIN; num_annee < ANNEE_MAX; num_annee++)
    {
        matriceCalendrierFunc(num_annee);
        for(int numJ1 = 1; numJ1 < CONTRAINTE3; numJ1++)
        {
            for(int numJ2 = numJ1 + 1; numJ2 < CONTRAINTE3 + 1; numJ2++)
            {
                if((numJ2 - numJ1) % 7 !=0)
                {
                    valeursJours[0] = numJ1;
                    valeursJours[1] = numJ2;
                    distanceDynamique = calculerDistanceAnnee(valeursJours);

                    if(distanceDynamique == distanceMin)
                    {
                        cptNumAnnee[cpt] = num_annee; //On donne au tableau l'annee o� l'on a retrouv� une telle distance minimale
                        cptNumj1[cpt] = numJ1; //idem pour le num�ro du jour 1
                        cptNumj2[cpt] = numJ2; //idem pour le num�ro du jour 2
                        cpt++;
                    }
                }
            }
        }
    }
    printf("Il y a %d dates qui ont egalement cette distance minimale :\n\n",cpt);
    for(int cptDate = 0; cptDate < cpt; cptDate++)
    {
        printf("On a retrouve la distance minimale pour la date numero : %d\n\n",cptDate);
        printf("\nL'annee correspodante est la suivante  : %d\n",cptNumAnnee[cptDate]);
        printf("\nLe numero du 1er jour correspondant est le suivant : %d\n",cptNumj1[cptDate]);
        printf("\nLe numero du 2nd jour correspondant est le suivant : %d\n\n",cptNumj2[cptDate]);
    }
    //-----------------------------------------------------------------------------------------------





    //-----------------------------------------------------------------------------------------------
    //Question 4
    printf("\n\n Affichage du calendrier csv lu : \n");
    csvEnMatrice("C:\\Users\\Louis\\Desktop\\ProjetC\\yearmonth_05.csv");
    //On affiche la matrice apr�s avoir lu le CSV pour v�rifier le fonctionnement
    for(int num_ligne = 0; num_ligne < LIGNE_CSV; num_ligne++)
    {
        for(int num_colonne = 0; num_colonne < COLONNE_CSV; num_colonne++)
        {
            int valeur = matriceCSV[num_ligne][num_colonne];//On r�cup�re l'�l�ment lu
            //printf("%d \n",valeur); //Pour v�rifier la valeur r�cup�rer
            if(valeur == 0)
            {
                printf("   "); //On met des espaces tant qu'on a pas 1 pour afficher correctement le calendrier
            }
            else
            {
                printf("%2d ", valeur);

            }
        }
        printf("\n");
    }
    //-----------------------------------------------------------------------------------------------





    //-----------------------------------------------------------------------------------------------
    //Question 5
    printf("\n\nVoici l'ensemble des dates qui pr�sentent le m�me pattern que notre fichier CSV : \n");
    identifierPatternCSV();
    //-----------------------------------------------------------------------------------------------

    return 0;
}
















