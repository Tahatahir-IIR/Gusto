#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct plat{
    int prix;
    char nom[20],description[55],categorie[30];
    float note;
    struct plat* next;
    struct plat* prev;
}plat;

plat *last_find(plat *l)
{
    plat *tmp = l;
    if (!tmp->next)
        return (tmp);
    do{
        tmp = tmp->next;
    }while(tmp->next != l);
    return (tmp);
}

void vider_Chaine() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char* Saisir_Chaine_Du_Caractere() {
    char temp[100];
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    char* chaine = malloc(strlen(temp) + 1);
    if (chaine != NULL) {
        strcpy(chaine, temp);
    }
    return chaine;
}

void Free_list(plat* l){
    plat* tmp=l;
    plat* ptr;
    if(l == NULL){
        return;
    }
    do{
        ptr = tmp->next;
        free(tmp);
        tmp = ptr;
    }while(tmp != l);
}

plat* creer_Plat(char* nom, char* description, char* categorie, float note, int prix) {
    plat* nv = malloc(sizeof(plat));
    strcpy(nv->nom, nom);
    strcpy(nv->description, description);
    strcpy(nv->categorie, categorie);
    nv->prix = prix;
    nv->note = note;
    nv->next = NULL;
    nv->prev = NULL;
    return nv;
}

plat* ajout_Debut(plat* l,char* nom,char* description,char* categorie,float note, int prix){
    plat *last;
    plat* nv=creer_Plat(nom, description, categorie, note, prix);
    if(l==NULL){
        nv->next= nv->prev= NULL;
        l=nv;
    }else{
        last = last_find(l);
        nv->next=l;
        nv->prev=last;
        last->next=nv;
        l->prev=nv;
        l=nv;

    }
    return l;
}

plat* ajout_Mileu(plat* l,char* nom,char* description,char* categorie,float note,char* nom_Plat,int prix){
    plat* tmp=l;
    plat* nv;
    do{
        if(strcmp(tmp->nom,nom_Plat)==0){
        nv=creer_Plat(nom, description, categorie, note,prix);
            if (tmp == NULL) {
                printf("Error\n");
                return l;
            }
            nv->next=tmp->next;
            nv->prev=tmp;
            tmp->next->prev=nv;
            tmp->next=nv;
            break;
        }else{
            tmp=tmp->next;
        }
    }while(tmp!=l);
    return l;
}

plat* ajout_Fin(plat* l,char* nom,char* description,char* categorie,float note,int prix){
    plat *last = last_find(l);
    plat* nv=creer_Plat(nom, description, categorie, note, prix);
    if(l==NULL){
        nv->next= nv->prev= NULL;
        l=nv;
    }else{
        nv->next=l;
        nv->prev=last;
        last->next=nv;
        l->prev=nv;
    }
    return l;
}

int rechercher_plat(plat* l,char* nom_Rech){
    int p=0;
    plat* tmp = l;
    if(l != NULL){
        do{
           if(strcmp(tmp->nom,nom_Rech)==0){
            p=1;
            break;
           }
           tmp = tmp->next;
        }while(tmp != l);
    }
  return p;
}

plat* modifier_Plat(plat* l,char* nom_Rech,char* nv_Nom,char* nv_Description,char* nv_Categorie,float nv_Note,int nv_Prix){
    plat* tmp=l;
    if(l == NULL){
        printf("List est vide.\n");
        return l;
    }else{
        do{
            if(strcmp(tmp->nom,nom_Rech)==0){
                strcpy(tmp->nom,nv_Nom);
                strcpy(tmp->description,nv_Description);
                strcpy(tmp->categorie,nv_Categorie);
                tmp->note=nv_Note;
                tmp->prix=nv_Prix;
                break;
            }
            tmp=tmp->next;
        }while(tmp!=l);
    }
    return l;
}

plat* suppression_Debut(plat* l){
    if(l==NULL)
    {
        printf("La liste est vide");
    }
    else if (l->next == NULL)
    {
        free(l);
        l=NULL;
    }
    else
    {
        plat* dernier = l->prev;
        dernier->next = l->next;
        l=l->next;
        free(l->prev);
        l->prev = dernier;
    }
    return l;
}

plat* suppression_Mileu(plat* l, char* nom_A_Supprimer) {
    int trouver = 0;
    plat* tmp = l;
    if (l == NULL) {
        printf("La liste est vide\n");
        return NULL;
    } else {
        do {
            if (strcmp(tmp->nom, nom_A_Supprimer) == 0) {
                if (tmp->next == tmp) {
                    free(tmp);
                    return NULL;
                }
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                free(tmp);
                trouver = 1;
                break;
            }
            tmp = tmp->next;
        } while (tmp != l);
        if (trouver == 0) {
            printf("Ce plat %s n'existe pas\n", nom_A_Supprimer);
        }
    }
    return l;
}

plat* suppression_Fin(plat* l){
    if(l==NULL)
    {
        printf("La liste est vide");
        return NULL;
    }
    else if (l->next != NULL)
    {
        plat* dernier=l->prev;
        l->prev=dernier->prev;
        dernier->prev->next=l;
        free(dernier);
    }
    else
    {
        free(l);
        l=NULL;
    }
    return l;
}

plat* recherche_Plat_Par_Nom(plat* l,char nomR[30]){
    plat* tmp=l;
    int trouver=0;
    if(l == NULL){
        printf("List est vide.\n");
        return l;
    }else{
        do{
            if(strcmp(tmp->nom,nomR)==0){
                trouver=1;
                break;
            }
            tmp=tmp->next;
        }while(tmp!=l);
        if (trouver == 1) {
            printf("Le plat '%s' a ete trouve.\n", nomR);
            return tmp;
        } else {
            printf("Le plat '%s' n'a pas ete trouve.\n", nomR);
            return NULL;
        }
    }
    return l;
}

plat* recherche_Plat_Par_Categorie(plat* l,char categorieR[30]){
    plat* tmp=l;
    if(l == NULL){
        printf("List est vide.\n");
        return l;
    }else{
        do{
            if(strcmp(tmp->categorie,categorieR)==0){
                return tmp;
            }
            tmp=tmp->next;
        }while(tmp!=l);
    }
    return l;
}

void afficher_plat(plat* l){
    plat* tmp=l;
    if(l == NULL){
        printf("+-----------------------+\n");
        printf("|   Le menu est vide.   |\n");
        printf("+-----------------------+\n");
        return ;
    }
    else if (tmp->next == NULL) {
        printf("+---------------------------+\n");
        printf("|   Le plat : %s          |\n", tmp->nom);
        printf("|   La description : %s   |\n", tmp->description);
        printf("|   La catégorie : %s     |\n", tmp->categorie);
        printf("|   Le prix : %d          |\n", tmp->prix);
        printf("|   La note : %.2f        |\n", tmp->note);
        printf("+---------------------------+\n");
    } else {
        printf("+---------------------------+\n");
        do {
            printf("|   Le plat : %s          |\n", tmp->nom);
            printf("|   La description : %s   |\n", tmp->description);
            printf("|   La catégorie : %s     |\n", tmp->categorie);
            printf("|   Le prix : %d        |\n", tmp->prix);
            printf("|   La note : %.2f        |\n", tmp->note);
            printf("+---------------------------+\n");
            tmp = tmp->next;
        } while (tmp != l);
    }
}

void afficher_nom_plat(plat* l){
    plat* tmp=l;
    int cmp=1;
    if(l == NULL){
        printf("+-----------------------+\n");
        printf("|   Le menu est vide.   |\n");
        printf("+-----------------------+\n");
        return ;
    }
    else if (tmp->next == NULL) {
        printf("+-----------------------+\n");
        printf("|   %d - %s   |\n", cmp, tmp->nom);
        printf("+-----------------------+\n");
    } else {
        printf("+-----------------------+\n");
        do {
            printf("|   %d - %s   |\n", cmp, tmp->nom);
            printf("+-----------------------+\n");
            tmp = tmp->next;
            cmp += 1;
        } while (tmp != l);
    }
}



plat* trier(plat* l){
    plat* tmp,*p;
    float val;
    char temp_nom[30];
     for(tmp=l;tmp->next!=l;tmp=tmp->next){
        for(p=tmp->next;p!=l;p=p->next){
            if(p->note < tmp->note){
                 val=tmp->note;
                 tmp->note=p->note;
                 p->note=val;

                 strcpy(temp_nom, tmp->nom);
                 strcpy(tmp->nom, p->nom);
                 strcpy(p->nom, temp_nom);
            }
        }
     }
     return l;
}

void sauvegarder_menu(plat* l) {
    FILE* fichier = fopen("menu.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    plat* tmp = l;

    if (tmp == NULL) {
        printf("Le menu est vide. Aucune donnée à sauvegarder.\n");
        fclose(fichier);
        return;
    }

    do {
        printf("%s,%s,%s,%.2f\n", tmp->nom, tmp->description, tmp->categorie, tmp->note , tmp->prix);
        fprintf(fichier, "%s,%s,%s,%.2f\n", tmp->nom, tmp->description, tmp->categorie, tmp->note , tmp->prix);
        tmp = tmp->next;
    } while (tmp != l && tmp != NULL);

    fclose(fichier);
    printf("Menu sauvegarde avec succes dans le fichier 'menu.txt'.\n");
}

void charger_menu(plat** l) {
    FILE* fichier = fopen("menu.txt", "r");
    if (fichier == NULL) {
        printf("Aucun fichier de sauvegarde n'a été trouvé.\n");
        return;
    }

    plat* tmp = NULL;
    char nom[20], description[55], categorie[30];
    float note;
    int prix;
    while (fscanf(fichier, "%19[^,],%54[^,],%29[^,],%f,%d\n", nom, description, categorie, &note,&prix) == 5) {

        plat* nouveau = creer_Plat(nom, description, categorie, note,prix);
        if (*l == NULL) {
            *l = nouveau;
            (*l)->next = *l;
            (*l)->prev = *l;
        } else {
            tmp = last_find(*l);
            tmp->next = nouveau;
            nouveau->prev = tmp;
            nouveau->next = *l;
            (*l)->prev = nouveau;
        }
    }

    fclose(fichier);
}

// Fonction pour gerer les plats par categorie
plat* gerer_categories_plat(plat* l){
    plat* l1=NULL,*l2=NULL,*l3=NULL,*l4=NULL,*l5=NULL,*tmp=l,*nv,*last = last_find(l);
    if(l == NULL){
        printf("List est vide.\n");
        return NULL;
    }else{
        do{
            nv=malloc(sizeof(plat));
            strcpy(nv->categorie,tmp->categorie);
            strcpy(nv->nom,tmp->nom);
            nv->note = tmp->note;
            strcpy(nv->description,tmp->description);
            nv->prix = tmp->prix;
            nv->next = NULL;
            nv->prev = NULL;
            if(strcmp(tmp->categorie,"Entrees")==0){
                if( l1 == NULL){
                    nv->next =  nv->prev = l1;
                    l1 = nv;
                }else{
                    nv->next=l1;
                    nv->prev=last;
                    last->next=nv;
                    l1->prev=nv;
                }
            }else if(strcmp(tmp->categorie,"Plats principaux")==0){
                if(l2 == NULL){
                    nv->next =  nv->prev = l2;
                    l2 = nv;
                }else{
                    nv->next=l2;
                    nv->prev=last;
                    last->next=nv;
                    l2->prev=nv;
                }
            }else if(strcmp(tmp->categorie,"Desserts")==0){
                if(l3 == NULL){
                    nv->next =  nv->prev = l3;
                    l3 = nv;
                }else{
                    nv->next=l3;
                    nv->prev=last;
                    last->next=nv;
                    l3->prev=nv;
                }
            }else if(strcmp(tmp->categorie,"Salades")==0){
                if(l4 == NULL){
                    nv->next =  nv->prev = l4;
                    l4 = nv;
                }else{
                    nv->next=l4;
                    nv->prev=last;
                    last->next=nv;
                    l4->prev=nv;
                }
            }else if(strcmp(tmp->categorie,"Soupes")==0){
                if(l5 == NULL){
                    nv->next =  nv->prev = l5;
                    l3 = nv;
                }else{
                    nv->next=l5;
                    nv->prev=last;
                    last->next=nv;
                    l5->prev=nv;
                }
            }
            last = nv;
            tmp = tmp->next;
        }while (tmp != l);
    }
    if(l1 != NULL)
        return l1;
    else if(l2 != NULL)
        return l2;
    else if(l3 != NULL)
        return l3;
    else if(l4 != NULL)
        return l4;
    else if(l5 != NULL)
        return l5;
    else
        return NULL;
}

// Fonction pour trier les plats par note
plat* trier_par_note(plat* l) {
    plat *tmp, *p;
    float val;
    char temp_nom[30], temp_description[55], temp_categorie[30];
    int temp_prix;
    float temp_note;
    if(l == NULL){
        printf("List est vide.\n");
        return l;
    }
    for (tmp = l; tmp->next != l; tmp = tmp->next) {
        for (p = tmp->next; p != l; p = p->next) {
            if (p->note < tmp->note) {
                val = tmp->note;
                tmp->note = p->note;
                p->note = val;
                strcpy(temp_nom, tmp->nom);
                strcpy(tmp->nom, p->nom);
                strcpy(p->nom, temp_nom);
                strcpy(temp_description, tmp->description);
                strcpy(tmp->description, p->description);
                strcpy(p->description, temp_description);
                strcpy(temp_categorie, tmp->categorie);
                strcpy(tmp->categorie, p->categorie);
                strcpy(p->categorie, temp_categorie);
                temp_prix = tmp->prix;
                tmp->prix = p->prix;
                p->prix = temp_prix;
            }
        }
    }
    return l;
}

// Fonction pour trier les plats par prix
plat* trier_par_prix(plat* l) {
    plat *tmp, *p;
    float val;
    char temp_nom[30], temp_description[55], temp_categorie[30];
    int temp_prix;
    float temp_note;
    if(l == NULL){
        printf("List est vide.\n");
        return NULL;
    }
    for (tmp = l; tmp->next != l; tmp = tmp->next) {
        for (p = tmp->next; p != l; p = p->next) {
            if (p->prix < tmp->prix) {
                val = tmp->note;
                tmp->note = p->note;
                p->note = val;
                strcpy(temp_nom, tmp->nom);
                strcpy(tmp->nom, p->nom);
                strcpy(p->nom, temp_nom);
                strcpy(temp_description, tmp->description);
                strcpy(tmp->description, p->description);
                strcpy(p->description, temp_description);
                strcpy(temp_categorie, tmp->categorie);
                strcpy(tmp->categorie, p->categorie);
                strcpy(p->categorie, temp_categorie);
                temp_prix = tmp->prix;
                tmp->prix = p->prix;
                p->prix = temp_prix;
            }
        }
    }
    return l;
}


void free_memory(char* nom, char* description, char* categorie, char* nom_Plat, char* nom_Rech, char* nv_Nom, char* nv_Description, char* nv_Categorie, char* nom_Plat_Supp, char* nomR, char* categorieR, plat* l) {
    free(nom);
    free(description);
    free(categorie);
    free(nom_Plat);
    free(nom_Rech);
    free(nv_Nom);
    free(nv_Description);
    free(nv_Categorie);
    free(nom_Plat_Supp);
    free(nomR);
    free(categorieR);
    Free_list(l);
}


int main(){
    plat* l = NULL;
    charger_menu(&l);

    int i,j;

    int choix,c,c1,c2,c3,c4,c5,ajo,supp,ErrorNum,nv_Prix,prix,valide,nv_valide;
    float note,nv_Note;
    char*nom=NULL,*description=NULL,*categorie=NULL,*nom_Plat=NULL,*nom_Rech=NULL,*nv_Nom=NULL,*nv_Description=NULL,*nv_Categorie=NULL,*nom_Plat_Supp=NULL;
    char*nomR=NULL,*categorieR=NULL;

    printf("Menu principal\n");

    do{
        printf("+----------------------------------+\n");
        printf("| 1-> Gestion des restaurants      |\n");
        printf("| 2-> Sauvegarder le menu          |\n");
        printf("| 3-> Quitter                      |\n");
        printf("+----------------------------------+\n");
        printf("Choix : ");

        if (scanf("%d", &choix) != 1 || (choix < 1 || choix > 3)) {
            printf("* Veuillez entrer un entier entre 1 et 3 *\n");
            while (getchar() != '\n');
            continue;
        }
        system("cls");

        switch (choix) {
            case 1:
            do{
                printf("+----------------------------------+\n");
                printf("|     Gestion des restaurants      |\n");
                printf("| 1- Ajout des plats               |\n");
                printf("| 2- Modification des plats        |\n");
                printf("| 3- Suppression des plats         |\n");
                printf("| 4- Recherche des plats           |\n");
                printf("| 5- Afficher des plats            |\n");
                printf("| 6- Gérer les catégories des plats|\n");
                printf("| 7- Options de tri personnalisées |\n");
                printf("| 8- MENU principal                |\n");
                printf("+----------------------------------+\n");
                printf("Choix : ");

                if (scanf("%d", &c1) != 1) {
                    system("cls");
                    printf("* Veuillez entrer un entier valide *\n");
                    while (getchar() != '\n');
                    continue;
                }

                system("cls");

            switch (c1) {
                case 1:

                    printf("Entrez le nom :");
                    vider_Chaine();
                    while ((nom = Saisir_Chaine_Du_Caractere()) == NULL || strlen(nom) == 0) {
                        printf("* Le nom ne peut pas etre vide *\n");
                        printf("Entrez le nom :");
                    }
                    printf("Entrez la description :");
                    while ((description = Saisir_Chaine_Du_Caractere()) == NULL || strlen(description) == 0) {
                        printf("* La description ne peut pas etre vide *\n");
                        printf("Entrez la description :");
                    }
                    printf("+----------------------+\n");
                    printf("| 1- Entrees           |\n");
                    printf("| 2- Plats principaux  |\n");
                    printf("| 3- Desserts          |\n");
                    printf("| 4- Salades           |\n");
                    printf("| 5- Soupes            |\n");
                    printf("+----------------------+\n");
                    while (1) {
                    printf("choisisser une categorie : ");
                    if (scanf("%d", &choix) != 1) {
                        while (getchar() != '\n'); // Clear the input buffer
                        printf("* Entree invalide. Veuillez entrer un numero. *\n");
                        continue;
                    }

                    switch (choix) {
                        case 1:
                            categorie = "Entrees";
                            break;
                        case 2:
                            categorie = "Plats principaux";
                            break;
                        case 3:
                            categorie = "Desserts";
                            break;
                        case 4:
                            categorie = "Salades";
                            break;
                        case 5:
                            categorie = "Soupes";
                            break;
                        default:
                            printf("* Choix invalide. Veuillez entrer un numero entre 1 et 5. *\n");
                            continue;
                    }

                        printf("Vous avez choisi la categorie : %s\n", categorie);
                        break;
                    }
                    printf("Entrez la note :");
                        while (scanf("%f", &note) != 1 || note < 1 || note > 5) {
                        printf("* Entrez une note valide entre 1 et 5 *\n");
                        while (getchar() != '\n');
                        printf("Entrez a nouveau la note en nombre reel :");
                        }
                    printf("Entrer le prix :");
                    while (scanf("%d", &prix) != 1 || prix<0 ) {
                        printf("* Entree invalide. Veuillez entrer un entier . *\n");
                        while (getchar() != '\n'); // Clear the input buffer
                        printf("Entrez a nouveau le prix en nombre entier :");
                        continue;
                    }
                    printf("1.Ajout au debut\n2.Ajout a la fin\n3.Ajout apres un plat specifique\n ");
                   do {
                    printf("Choix : ");
                    if(scanf("%d",&c2) != 1){
                    printf("* Entrer un entier s'il vous plait entre 1 et 3 *\n");
                    while (getchar() != '\n');
                    continue;
                }
                    } while(c2 != 1 && c2 != 2 && c2 != 3);
                    if(c2 == 1){
                        l=ajout_Debut( l, nom, description, categorie, note,prix);
                        printf("Le plat a ete ajoute avec succes\n");
                    }else if(c2 == 2){
                        l=ajout_Fin( l, nom, description, categorie, note,prix);
                        printf("Le plat a ete ajoute avec succes\n");
                    }else{
                        printf("Entrez le nom du plat a rechercher :");
                        vider_Chaine();
                        nom_Plat = Saisir_Chaine_Du_Caractere();
                        ajo=rechercher_plat(l,nom_Plat);
                        if(ajo == 1){
                           l=ajout_Mileu( l, nom, description, categorie, note, nom_Plat,prix);
                           printf("Le plat a ete ajoute avec succes\n");
                        }else{
                            printf("Le plat que vous avez entrer n'exite pas\n");
                        }
                    }
                    system("cls");
                    break;
                case 2:

                    printf("Liste des plats :\n");
                    afficher_nom_plat(l);

                    printf("Entrez le nom a rechercher :");
                    vider_Chaine();
                    nom_Rech = Saisir_Chaine_Du_Caractere();

                    c=rechercher_plat(l,nom_Rech);

                    if(c == 1){
                     printf("Entrez le nouveau nom :");
                     nv_Nom = Saisir_Chaine_Du_Caractere();
                     printf("Entrez la nouvelle description :");
                     nv_Description = Saisir_Chaine_Du_Caractere();
                     printf("+----------------------+\n");
                    printf("| 1- Entrees           |\n");
                    printf("| 2- Plats principaux  |\n");
                    printf("| 3- Desserts          |\n");
                    printf("| 4- Salades           |\n");
                    printf("| 5- Soupes            |\n");
                    printf("+----------------------+\n");
                     while (1) {
                    printf("choisisser une nouvelle categorie : ");
                    if (scanf("%d", &choix) != 1) {
                        while (getchar() != '\n'); // Clear the input buffer
                        printf("* Entree invalide. Veuillez entrer un numero. *\n");
                        continue;
                    }

                    switch (choix) {
                        case 1:
                            nv_Categorie = "Entrees";
                            break;
                        case 2:
                            nv_Categorie = "Plats principaux";
                            break;
                        case 3:
                            nv_Categorie = "Desserts";
                            break;
                        case 4:
                            nv_Categorie = "Salades";
                            break;
                        case 5:
                            nv_Categorie = "Soupes";
                            break;
                        default:
                            printf("* Choix invalide. Veuillez entrer un numero entre 1 et 5. *\n");
                            continue;
                    }

                        printf("Vous avez choisi la categorie : %s\n", nv_Categorie);
                        break;
                    }
                     printf("Entrez la nouvelle note : ");
                     while (scanf("%f", &nv_Note) != 1 || nv_Note < 1 || nv_Note > 5) {
                        printf("* Entrez une note valide entre 1 et 5 *\n");
                        while (getchar() != '\n'); // Pour vider le tampon d'entrée
                        printf("Entrez à nouveau la note : ");
                        }
                        printf("Entrez le nouveau prix : ");
                    while (scanf("%d", &nv_Prix) != 1 || nv_Prix < 1 ) {
                        printf("* Entrez une note valide superieur à 0 *\n");
                        while (getchar() != '\n'); // Pour vider le tampon d'entrée
                        printf("Entrez à nouveau la note : ");
                        }
                     l=modifier_Plat( l, nom_Rech, nv_Nom, nv_Description, nv_Categorie,nv_Note, nv_Prix);
                    }else{
                        printf("Le plat '%s' n'a ete pas trouve.\n", nom_Rech);

                    }
                    system("cls");
                    break;
                case 3:

                    printf("+-----------------------------------------+\n");
                    printf("|         Options de suppression          |\n");
                    printf("| 1- Suppression au début                 |\n");
                    printf("| 2- Suppression à la fin                 |\n");
                    printf("| 3- Suppression après un plat spécifique |\n");
                    printf("| 4- Retour                               |\n");
                    printf("+-----------------------------------------+\n");
                   // printf("Choix : ");
                    do{
                    printf("Choix :");
                    if(scanf("%d",&c3) != 1){
                    printf("* Veuillez entrer un entier entre 1 et 4 *\n");
                    while (getchar() != '\n');
                    continue;
                }
                system("cls");
                    }while(c3!=1 && c3!=2 && c3!=3 && c3!=4);
                    if(c3 == 1){
                        l=suppression_Debut(l);
                        printf("Le plat a ete supprime avec succes\n");
                        printf("Apuiyer entrer pour retourner");
                        while (_getch() != '\r');
                         system("cls");
                    }else if(c3 == 2){
                        l=suppression_Fin(l);
                        printf("Le plat a ete supprime avec succes\n");
                        printf("Presse entrer pour retourner");
                        while (_getch() != '\r');
                         system("cls");
                    }else if(c3 == 3){
                        printf("Liste des plats :\n");
                    afficher_nom_plat(l);
                        printf("Entrez le nom du plat a rechercher :");
                        vider_Chaine();
                        nom_Plat_Supp = Saisir_Chaine_Du_Caractere();
                        supp=rechercher_plat(l, nom_Plat_Supp);
                        if(supp == 1){
                          l=suppression_Mileu( l, nom_Plat_Supp);
                          printf("Le plat a ete supprime avec succes\n");
                          printf("Apuiyer entrer pour retourner");
                        while (_getch() != '\r');
                         system("cls");
                        }else{
                          printf("Le plat que vous avez entrer n'exite pas\n");
                          printf("Apuiyer entrer pour retourner");
                        while (_getch() != '\r');
                         system("cls");
                        }
                    }else{
                        break;
                    }
                    system("cls");
                    break;
                case 4:
                        printf("+-------------------------------+\n");
                        printf("|       Recherche des plats     |\n");
                        printf("| 1- Recherche par nom du plat  |\n");
                        printf("| 2- Recherche par catégorie    |\n");
                        printf("| 3- Recherche avancée          |\n");
                        printf("| 4- Retour                     |\n");
                        printf("+-------------------------------+\n");

                    do {
                        printf("Choix :");
                        if(scanf("%d",&c4) != 1){
                   printf("* Entrer un entier s'il vous plait entre 1 et 4 *\n");
                    while (getchar() != '\n');
                    continue;
                }
                    } while (c4 != 1 && c4 != 2 && c4 != 3 && c4 != 4);
                    system("cls");
                switch (c4) {
                    case 1:
                        printf("Entrez le nom du plat : ");
                        vider_Chaine();
                        nomR = Saisir_Chaine_Du_Caractere();
                        l = recherche_Plat_Par_Nom(l, nomR);
                    break;
                    case 2:
                        printf("Entrez la categorie : ");
                        vider_Chaine();
                        categorieR = Saisir_Chaine_Du_Caractere();
                        l = recherche_Plat_Par_Categorie(l, categorieR);
                    break;
                    case 3:
                    // recherche avancée
                    break;
                    case 4:
                    break;
                    default:
                    printf("Choix invalide.\n");
                    break;
                }
                break;
                case 5:
                    system("cls");
                    afficher_plat(l);

                    printf("Press Enter to return...\n");

                    while (_getch() != '\r');
                    system("cls");
                    break;
                case 6:
                    if(l == NULL){
                       printf("Liste est vide\n");
                    }else{
                    l=gerer_categories_plat(l);
                    if(l != NULL){
                    printf("les plats sont bien organisee\n");
                    }
                    }
                    break;
                case 7:
                        if(l == NULL){
                        printf("Liste est vide\n");
                    }else{
                     printf("Tri des plats  personnalisees\n");
                     printf(" 1.Tri par note du plat\n 2.Tri par prix du plat\n 3.Retour\n ");
                    do {
                        printf("Choix :");
                        if(scanf("%d",&c5) != 1){
                        printf("* Entrer un entier s'il vous plait entre 1 et 3 *\n");
                    while (getchar() != '\n');
                    continue;
                        }
                    } while (c5 != 1 && c5 != 2 && c5 != 3);
                    switch (c5)
                    {
                    case 1:
                     l=trier_par_note(l);
                     if(l != NULL){
                     printf("Les plats sont bien triees\n");
                     }
                        break;
                    case 2:
                    l=trier_par_prix(l);
                    if(l != NULL){
                    printf("Les plats sont bien triees\n");
                    }
                    break;
                    case 3:
                         printf("D'accord\n");
                        break;
                    default:
                        printf("Choix invalid\n");
                        break;
                    }
                }
                break;
                case 8:
                    printf("D'accord\n");
                    system("cls");
                    break;
                default:
                    printf("* Entrer un entier s'il vous plait entre 1 et 8 *\n");
                    break;
                    }
                    }while(c1!=8);
                    break;


                case 2:
                    sauvegarder_menu(l);
                break;
                case 3:
                    printf("Au revoir");
                    break;
                default:
                    printf("Choix invalid\n");
                    break;
        }
    }while(choix!=2);

     free_memory(nom, description, categorie, nom_Plat, nom_Rech, nv_Nom, nv_Description, nv_Categorie, nom_Plat_Supp, nomR, categorieR, l);

    return 0;
}
