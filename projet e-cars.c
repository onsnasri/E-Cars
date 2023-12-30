#include <stdio.h>
#include <string.h>

#define max_voitures 150
#define max_locations 150

typedef struct locataire
{
    int cin;
    char nom[20];
    char prenom[20];
    char adresse[20];
    int age;
    int datePermis;
} locataire;

typedef struct voiture
{
    int id;
    char marque[20];
    char modele[20];
    char couleur[10];
    char etat[15];
    int kilometrage;
    int prixJour;
    int nombrePlace;
} voiture;

typedef struct location
{
    int NumLocation;
    int id;
    int cin;
} location;

int ConditionLocation(locataire loc)
{
    if (loc.age >= 23 && loc.datePermis >= 2)
    {
        return 1;
    }
    else
    {
        printf("Vous devez avoir au moins 23 ans et etre titulaire du permis depuis au moins 2 ans pour louer une voiture\n");
        return 0;
    }
}
voiture TabVoit[max_voitures];
location Tabloc[max_locations];
int numVoitures = 0;
int numLocation = 0;
void AjouterVoiture()
{
    if (numVoitures < max_voitures)
    {
        printf("Entrez les informations de la nouvelle voiture :\n");
        printf("ID : ");
        scanf("%d", &TabVoit[numVoitures].id);

        printf("Marque : ");
        scanf("%s", TabVoit[numVoitures].marque);

        printf("Modele : ");
        scanf("%s", TabVoit[numVoitures].modele);

        printf("Couleur : ");
        scanf("%s", TabVoit[numVoitures].couleur);

        printf("etat (disponible, louee, panne, etc.) : ");
        scanf("%s", TabVoit[numVoitures].etat);

        printf("Kilometrage : ");
        scanf("%d", &TabVoit[numVoitures].kilometrage);

        printf("Nombre de places : ");
        scanf("%d", &TabVoit[numVoitures].nombrePlace);

        printf("Prix par jour : ");
        scanf("%d", &TabVoit[numVoitures].prixJour);

        numVoitures++;
        printf("La voiture a ete ajoutee avec succes.\n");
    }
    else
    {
        printf("Impossible d'ajouter plus de voitures, le parc est plein.\n");
    }
}
void VoituresDisponibles()
{
    for (int i = 0; i < numVoitures; i++)
    {
        if (strcmp(TabVoit[i].etat, "disponible") == 0)
        {
            printf("ID:%d\n marque:%s\n modele:%s\n couleur:%s\n etat:%s\n kilometrage:%d\n nombre de place:%d\n prix par jour:%d\n",
                   TabVoit[i].id, TabVoit[i].marque, TabVoit[i].modele, TabVoit[i].couleur, TabVoit[i].etat,
                   TabVoit[i].kilometrage, TabVoit[i].nombrePlace, TabVoit[i].prixJour);
        }
    }
}

char mar[20];
char mod[20];

int choixDispo()
{
    printf("Quelle marque vous preferez : ");
    scanf("%s", mar);
    printf("Quel modele vous preferez : ");
    scanf("%s", mod);

    for (int i = 0; i < numVoitures; i++)
    {
        if (strcmp(TabVoit[i].marque, mar) == 0 && strcmp(TabVoit[i].modele, mod) == 0 && strcmp(TabVoit[i].etat, "disponible") == 0)
        {
            printf("La voiture que vous avez choisie est disponible pour la location.\n");
            return 1;
        }
    }
    printf("La voiture que vous avez choisie n'est pas disponible ou n'existe pas dans le parc.\n");
    return 0;
}

int ident;
locataire SaisirInformationsClient()
{
    locataire loc;
    printf("Entrez les informations du client :\n");
    printf("CIN : ");
    scanf("%d", &loc.cin);
    printf("Nom : ");
    scanf("%s", loc.nom);
    printf("Prenom : ");
    scanf("%s", loc.prenom);
    printf("Adresse : ");
    scanf("%s", loc.adresse);
    printf("Age : ");
    scanf("%d", &loc.age);
    printf("depuis quelle annee vous avez eu votre permis : ");
    scanf("%d", &loc.datePermis);
    return loc;
}

void louer(locataire loc)
{
    printf("Entrez l'identificateur de la voiture que vous voulez louer : ");
    scanf("%d", &ident);

    for (int i = 0; i < numVoitures; i++)
    {
        if (TabVoit[i].id == ident && strcmp(TabVoit[i].etat, "disponible") == 0)
        {
            strcpy(TabVoit[i].etat, "louee");
            Tabloc[numLocation].NumLocation = numLocation + 1;
            Tabloc[numLocation].id = TabVoit[i].id;
            Tabloc[numLocation].cin = loc.cin;
            numLocation++;

            printf("Location effectuee avec succes.\n");
            return;
        }
    }

    printf("Erreur : La voiture choisie n'est pas disponible ou n'existe pas dans le parc.\n");
}

void supprimerVoitureEnPanne()
{
    int idASupprimer;
    printf("Entrez l'ID de la voiture a supprimer : ");
    scanf("%d", &idASupprimer);
    for (int i = 0; i < numVoitures; i++)
    {
        if (TabVoit[i].id == idASupprimer && strcmp(TabVoit[i].etat, "panne") == 0)
        {
            for (int j = i; j < numVoitures - 1; j++)
            {
                TabVoit[j] = TabVoit[j + 1];
            }
            numVoitures--;

            printf("La voiture en panne a ete supprimee avec succes.\n");
            return;
        }
    }
    printf("Erreur : La voiture avec l'ID spécifié n'a pas été trouvee ou n'est pas en panne.\n");
}

void afficherDescriptionVoiture()
{
    int idAAfficher;
    printf("Entrez l'ID de la voiture dont vous voulez afficher la description : ");
    scanf("%d", &idAAfficher);
    for (int i = 0; i < numVoitures; i++)
    {
        if (TabVoit[i].id == idAAfficher)
        {
            printf("Description de la voiture (ID:%d):\n", TabVoit[i].id);
            printf("Marque: %s\n", TabVoit[i].marque);
            printf("Modele: %s\n", TabVoit[i].modele);
            printf("Couleur: %s\n", TabVoit[i].couleur);
            printf("Etat: %s\n", TabVoit[i].etat);
            printf("Kilometrage: %d\n", TabVoit[i].kilometrage);
            printf("Nombre de places: %d\n", TabVoit[i].nombrePlace);
            printf("Prix par jour: %d\n", TabVoit[i].prixJour);
            return;
        }
    }
    printf("Erreur : La voiture avec l'ID spécifie n'a pas ete trouvee.\n");
}

void modifierDescriptionEtatVoiture()
{
    int idAModifier;
    printf("Entrez l'ID de la voiture que vous voulez modifier : ");
    scanf("%d", &idAModifier);
    for (int i = 0; i < numVoitures; i++)
    {
        if (TabVoit[i].id == idAModifier)
        {
            printf("Entrez la nouvelle marque de la voiture : ");
            scanf("%s", TabVoit[i].marque);

            printf("Entrez le nouveau modele de la voiture : ");
            scanf("%s", TabVoit[i].modele);

            printf("Entrez la nouvelle couleur de la voiture : ");
            scanf("%s", TabVoit[i].couleur);

            printf("Entrez le nouvel etat de la voiture : ");
            scanf("%s", TabVoit[i].etat);
            printf("La description et l'etat de la voiture ont été modifiés avec succès.\n");
            return;
        }
    }
    printf("Erreur : La voiture avec l'ID specifie n'a pas ete trouvee.\n");
}

void afficherHistoriqueLocations()
{
    if (numLocation == 0)
    {
        printf("Aucune location n'a ete enregistree.\n");
        return;
    }

    printf("Historique des locations :\n");
    for (int i = 0; i < numLocation; i++)
    {
        printf("Location %d :\n", Tabloc[i].NumLocation);
        printf("ID de la voiture : %d\n", Tabloc[i].id);
        printf("CIN du locataire : %d\n", Tabloc[i].cin);
        printf("\n");
    }
}

void retourVoitureReclamation()
{
    int idARetourner;
    printf("Entrez l'ID de la voiture a retourner suite a une reclamation : ");
    scanf("%d", &idARetourner);
    for (int i = 0; i < numVoitures; i++)
    {
        if (TabVoit[i].id == idARetourner && strcmp(TabVoit[i].etat, "louee") == 0)
        {
            strcpy(TabVoit[i].etat, "disponible");
            printf("La voiture a ete retournee avec succes suite a une réclamation.\n");
            return;
        }
    }
    printf("Erreur : La voiture avec l'ID spécifie n'a pas ete trouvee ou n'est pas en location suite a une reclamation.\n");
}
int main()
{
    int choix;
    locataire loc;
    TabVoit[numVoitures].id=1;
    strcpy(TabVoit[numVoitures].marque, "Toyota");
    strcpy(TabVoit[numVoitures].modele,"Corolla");
    strcpy(TabVoit[numVoitures].couleur,"Rouge");
    strcpy(TabVoit[numVoitures].etat,"disponible");
    TabVoit[numVoitures].kilometrage=50000;
    TabVoit[numVoitures].nombrePlace=5;
    TabVoit[numVoitures].prixJour=50;
    numVoitures++;
    TabVoit[numVoitures].id=2;
    strcpy(TabVoit[numVoitures].marque,"Honda");
    strcpy(TabVoit[numVoitures].modele,"Civic");
    strcpy(TabVoit[numVoitures].couleur,"Bleu");
    strcpy( TabVoit[numVoitures].etat,"disponible");
    TabVoit[numVoitures].kilometrage=60000;
    TabVoit[numVoitures].nombrePlace=5;
    TabVoit[numVoitures].prixJour=60;
    numVoitures++;
    TabVoit[numVoitures].id=3;
    strcpy(TabVoit[numVoitures].marque,"Ford");
    strcpy(TabVoit[numVoitures].modele,"Fusion");
    strcpy(TabVoit[numVoitures].couleur,"Noir");
    strcpy(TabVoit[numVoitures].etat,"disponible");
    TabVoit[numVoitures].kilometrage=75000;
    TabVoit[numVoitures].nombrePlace=5;
    TabVoit[numVoitures].prixJour=70;
    numVoitures++;
    do
    {
        printf("\nMenu Principal :\n");
        printf("1. Afficher les voitures disponibles\n");
        printf("2. Louer une voiture\n");
        printf("3. Supprimer une voiture en panne\n");
        printf("4. Afficher la description d'une voiture\n");
        printf("5. Modifier la description et l'etat d'une voiture\n");
        printf("6. Afficher l'historique des locations\n");
        printf("7. Retourner une voiture suite a une reclamation\n");
        printf("8. Ajouter une voiture au parc\n");
        printf("0. Quitter\n");
        printf("\nFaites votre choix : ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            VoituresDisponibles();
            break;
        case 2:
            if (choixDispo())
            {
                locataire loc = SaisirInformationsClient();
                ConditionLocation(loc);
                if (ConditionLocation(loc))
                {
                    louer(loc);
                }
            }
            break;
        case 3:
            supprimerVoitureEnPanne();
            break;
        case 4:
            afficherDescriptionVoiture();
            break;
        case 5:
            modifierDescriptionEtatVoiture();
            break;
        case 6:
            afficherHistoriqueLocations();
            break;
        case 7:
            retourVoitureReclamation();
            break;
        case 8:
            AjouterVoiture();
            break;
        case 0:
            printf("Merci d'avoir utilise notre service de location de voitures. A bientot !\n");
            break;
        default:
            printf("Choix invalide. Veuillez choisir une option valide.\n");
        }

    } while (choix != 0);

    return 0;
}
