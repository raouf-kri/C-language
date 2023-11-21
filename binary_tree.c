#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// des couleurs pour l'affichage

#define Rouge "\033[31m"
#define Vert "\033[32m"
#define Jaune "\033[33m"
#define Cyan "\033[36m"
#define fin "\033[0m"

/*------------------------------------------------------------PARTIE DECLARATION------------------------------------------------------------*/

//déclaration de la liste

typedef struct elemlis
  {
        int infol;
        struct elemlis *suivl;

  }elemlis;
typedef elemlis* liste;

//déclaration des elements de l'arbre

typedef struct elemarbre
{
    liste point;
    char mot[30];

}ElemArbre;

//déclaration de l'arbre

typedef struct larbre *arbre;
typedef struct larbre
{
    ElemArbre infoA;
    arbre filsG,filsD;

}noeud;

//déclaration de la file

typedef struct elemfile *efile;
typedef struct elemfile
  {
    arbre infof;
    efile suivf;

  }cellulef;

typedef struct
  {
     efile tete,queue;
  }file;

//declaration de la liste des mots (partie 3)

typedef struct elemlis3
  {
        arbre infol3;
        struct elemlis3 *suivl3;

  }elemlis3;
typedef elemlis3* liste3;


//la nouvelle déclaration de la file pour la partie 3

typedef struct elemfile3 *efile3;
typedef struct elemfile3
  {
    liste3 infof3;
    efile3 suivf3;

  }cellulef3;

typedef struct
  {
     efile3 tete3,queue3;
  }file3;

// les primitives de la file
/*--------------------------*/
//la primitive enfiler

void enfiler(file *f,arbre x)
{
    efile newe;

    newe = malloc(sizeof(cellulef));
    newe->infof = x;
    newe -> suivf = NULL;

    if ((*f).tete == NULL)

        (*f).tete = newe;

    else

        (*f).queue -> suivf = newe;

    (*f).queue = newe;

}

//la primitive défiler

void defiler(file *f,arbre *x)
{
    efile temp;
    temp = (*f).tete;
    *x = temp ->infof;

    if ((*f).tete == (*f).queue)
    {
        (*f).tete = NULL;
        (*f).queue = NULL;
    }
    else

        (*f).tete = (*f).tete -> suivf;

    free(temp);
}

// les nouvelles primitives de la file pour la partie 3
/*----------------------------------------------------*/
//la primitive enfiler

void enfiler3(file3 *f,liste3 x)
{
    efile3 newe;

    newe = malloc(sizeof(cellulef3));
    newe->infof3 = x;
    newe->suivf3 = NULL;

    if ((*f).tete3 == NULL)

        (*f).tete3 = newe;

    else

        (*f).queue3 -> suivf3 = newe;

    (*f).queue3 = newe;

}

//la primitive défiler

void defiler3(file3 *f,liste3 *x)
{
    efile3 temp;
    temp = (*f).tete3;
    *x = temp ->infof3;

    if ((*f).tete3 == (*f).queue3)
    {
        (*f).tete3 = NULL;
        (*f).queue3 = NULL;
    }
    else

        (*f).tete3 = (*f).tete3 -> suivf3;

    free(temp);
}
/*------------------------------------------------------------PARTIE FONCTION------------------------------------------------------------*/

//Partie 1
//--------

// une fonction qui crée la liste

// on la donne un tableau d'entier puis elle le trie et insere ses valeur dans une liste

liste const_liste(int n,int t[])
{
    liste q,p,tete;
    int i,j,x;

    for(i=0; i< n; i++)
    {
        for(j = i+1 ; j<n ;j++)
        {
            if(t[i]> t[j])
            {
                x = t[i];
                t[i] = t[j];
                t[j] = x;
            }
        }
    }

    p = malloc(sizeof(elemlis));
    p->infol = t[0];
    p->suivl = NULL;

    tete = q = p;

    for(i=1 ; i<n ; i++)
    {
         p = malloc(sizeof(elemlis));
         p->infol = t[i];
         p->suivl = NULL;
         q->suivl = p;
         q=p;
    }

    return tete;
}

// une fonction qui crée un noeud de l'arbre

//on la donne un mot et un tableau de numero de page et elle cree un noeud

arbre const_case(char mot[30],int n,int t[])
{
    arbre A;

    A = malloc(sizeof(noeud));

    strcpy(A->infoA.mot ,mot);
    A->infoA.point = const_liste(n,t);

    A->filsD = NULL;
    A->filsG = NULL;

    return A;
}

// une fonction qui construit la structure de l'arbre

// cette fonction fait un appel au fonction const_case et cree 10 noeuds

arbre const_tree()
{
    arbre a;
    char mot[30];
    int n;

    strcpy(mot,"Process");n=3;int t1[]={1,10,13};
    a = const_case(mot,n,t1);

    strcpy(mot,"RAM");n=2;int t2[]={2,14};
    a->filsG = const_case(mot,n,t2);

    strcpy(mot,"Memoire");n=3;int t3[]={1,6,21};
    a->filsD = const_case(mot,n,t3);

    strcpy(mot,"UAL");n=4;int t4[]={16,5,7,19};
    a->filsG->filsG = const_case(mot,n,t4);

    strcpy(mot,"ACC");n=3;int t5[]={11,3,9};
    a->filsG->filsD = const_case(mot,n,t5);

    strcpy(mot,"MAR");n=2;int t6[]={6,18};
    a->filsD->filsG = const_case(mot,n,t6);

    strcpy(mot,"MBR");n=4;int t7[]={4,10,17,12};
    a->filsD->filsD = const_case(mot,n,t7);

    strcpy(mot,"Instruction");n=5;int t8[]={4,16,7,22,5};
    a->filsG->filsG->filsG = const_case(mot,n,t8);

    strcpy(mot,"Donnees");n=3;int t9[]={1,24,8};
    a->filsD->filsD->filsD = const_case(mot,n,t9);

    strcpy(mot,"Adresses");n=2;int t10[]={13,12};
    a->filsD->filsG->filsG = const_case(mot,n,t10);

    return a;
}

// une fonction qui saisir et creer  les noeuds d’un arbre

file fonc_saisie()
{
    int i,j,m,n,t[100];
    char mot[30];
    arbre a=NULL;
    file f;

    f.tete = NULL;

    do
    {
        printf("Combien de mot voulez-vous introduire ? ");
        scanf("%d",&m);
        printf("\n");

    }while(m<=0);

    for(i=0 ; i<m ;i++)
    {
        printf("- Donner le mot numero %d : ",i+1);
        scanf("%s",mot);
        printf("\n");

        printf("le mot (%s) apparait dans combien de page ? ",mot);
        scanf("%d",&n);
        printf("\n");

        for(j=0 ; j<n ;j++)
        {
            if(j != 0)
            {
                printf("|Donner la %deme page ou %s apparait : ",j+1,mot);
                scanf("%d",&t[j]);
            }
            else
            {
                printf("|Donner la %dere page ou %s apparait : ",j+1,mot);
                scanf("%d",&t[j]);
            }

        }

        printf("\n\n");

        a = const_case(mot,n,t);
        enfiler(&f,a);
    }
    return f;
}

// une fonction qui Construit la structure d’un arbre par saisie de données au clavier.

arbre const_saisie()
{
    arbre a=NULL,b=NULL;
    file f;
    f = fonc_saisie();

    defiler(&f,&a);
    b=a;

    while(f.tete != NULL)
    {
        if(b->filsG == NULL)

            defiler(&f,&b->filsG);

        else
            if(b->filsD == NULL)

                defiler(&f,&b->filsD);

            else

                b=b->filsG;
    }
    return a;
}

// L'affichage
//------------

// une fonction qui Affiche le contenu de l’arbre

void affiche1(arbre a)
{

    file f;
    arbre x=NULL;
    liste l=NULL;

    f.tete=NULL;
    enfiler(&f,a);

    while(f.tete != NULL)
    {
        defiler(&f,&x);

        printf("%s : ",x->infoA.mot);
        l = x->infoA.point;

        while(l != NULL)
        {
            printf("%d   ",l->infol);
            l = l->suivl;
        }

        if(x->filsG != NULL)

            enfiler(&f,x->filsG);

        if(x->filsD != NULL)

            enfiler(&f,x->filsD);

        printf("\n\n");
    }
}

void affiche2(arbre a)
{
    file f1,f2;
    arbre y=NULL,x=NULL;
    liste l=NULL;

    f1.tete=NULL;
    f2.tete=NULL;

    enfiler(&f1,a);

    //enfiler les noeuds de l'arbre en largeur

    while(f1.tete != NULL)
    {
        defiler(&f1, &x);
        enfiler(&f2,x);

        if(x->filsG != NULL)

            enfiler(&f1,x->filsG);

        if(x->filsD != NULL)

            enfiler(&f1,x->filsD);
    }

    enfiler(&f1,a);
    defiler(&f2,&y);

    // parcours de l'arbre

    while(f1.tete != NULL)
    {
        defiler(&f1, &x);

        //afficher le fils gauche si il existe

        if(x->filsG != NULL)
        {
            defiler(&f2,&y);

            printf("%s -> [",y->infoA.mot);
            l = y->infoA.point;

            while(l != NULL)
            {
                if(l->suivl != NULL)
                {
                    printf("%d,",l->infol);
                    l = l->suivl;
                }
                else
                {
                    printf("%d]",l->infol);
                    l = l->suivl;
                }
            }

            enfiler(&f1,x->filsG);
        }
        else
            printf("NULL");

        //afficher la racine

        printf(Rouge" <------FG------ "fin"(%s -> [",x->infoA.mot);  //FG : fils gauche
        l = x->infoA.point;

        while(l != NULL)
        {
            if(l->suivl != NULL)
            {
                printf("%d,",l->infol);
                l = l->suivl;
            }
            else
            {
                printf("%d])"Rouge" ------FD------> "fin,l->infol);   //FD : fils droit
                l = l->suivl;
            }
        }

        //afficher le fils droit si il existe

        if(x->filsD != NULL)
        {
            defiler(&f2,&y);

            printf("%s -> [",y->infoA.mot);
            l = y->infoA.point;

            while(l != NULL)
            {
                if(l->suivl != NULL)

                    printf("%d,",l->infol);

                else

                    printf("%d]",l->infol);

                l = l->suivl;
            }

            enfiler(&f1,x->filsD);
            printf("\n\n");
        }
        else
        {
            printf("NULL");
            printf("\n\n");
        }

    }
}

// une fonction qui Recherche un mot dans l’arbre

int recherche(arbre a, char M[30])
{
    if(a == NULL)

        return 0;         // Valeur non trouvée

    if(strcmp(a->infoA.mot,M) == 0)

        return 1;        // Valeur trouvée

    // Recherche récursive dans les sous-arbres gauche et droit

    return recherche(a->filsG,M) || recherche(a->filsD,M);

}

//une procedure qui Recherche un mot dans l’arbre et l'afficher ainsi que la liste des numéros de page et le niveau

void rech_affiche(arbre a,char M[30],int niv)
{
    liste p;
    if(a!=NULL)
    {

        if(strcmp(a->infoA.mot,M) == 0)
        {
            p = a->infoA.point;
            printf("%s fait apparaitre dans  ",a->infoA.mot);

            while(p != NULL)
            {
                printf("P[%d]  ",p->infol);
                p = p->suivl;
            }

            printf("et il est au niveau %d.\n",niv);
        }
            niv++;
            rech_affiche(a->filsG,M,niv);
            rech_affiche(a->filsD,M,niv);
    }
}

// une procedure qui Ajoute un numéro de page pour un mot qui existe déjà dans l’arbre

void ajout(arbre a,char M[30], int N)
{
    liste p,q,s;
    if(a != NULL)
    {
        if(strcmp(a->infoA.mot,M) == 0)
        {
            s = malloc(sizeof(liste));
            s->infol = N;
            s->suivl = NULL;

            p = a->infoA.point;
            if(a->infoA.point == NULL )

                a->infoA.point=s;

            else
            {
                if(p->infol > s->infol)
                {
                    a->infoA.point=s;
                    s->suivl=p;
                }

                else
                {
                    q = p->suivl;

                    while(q != NULL  &&  q->infol < s->infol)
                    {
                        p = q;
                        q = p->suivl;
                    }
                    if(q == NULL)

                        p ->suivl = s;

                    else
                    {
                        p->suivl = s;
                        s->suivl = q;
                    }
                }
            }
        }
        else
        {
            ajout(a->filsG,M,N);
            ajout(a->filsD,M,N);
        }
    }
}

// une procedure qui Supprime un numéro de page

void supprime(arbre a,char M[30], int N)
{
    liste p,q,tete;


    if(a != NULL)
    {

        if(strcmp(a->infoA.mot,M) == 0)
        {
            p = a->infoA.point;
            tete = q = p;

            if(a->infoA.point != NULL && a->infoA.point->infol == N)
            {
                a->infoA.point = a->infoA.point->suivl;
            }
            while(p != NULL && p->infol != N)
            {
                q = p;
                p = p->suivl;

            }

            if(p == NULL)
            {
                return;
            }

            q->suivl = p->suivl;
            free(p);

        }
        supprime(a->filsG,M, N);
        supprime(a->filsD,M, N);
    }
}

//Partie 2
//--------


// triage de l'arbre
//------------------

//une procedure qui met les noeuds de l'arbre dans un tableau et trie le tableau

void creertab(arbre a, ElemArbre t[], int i)
{
    file f;
    arbre x;

    f.tete=f.queue=NULL;

    enfiler(&f, a);

    while(f.tete != NULL)
    {
        defiler(&f, &x);

        strcpy(t[i].mot,x->infoA.mot);
        t[i].point = x->infoA.point;

        i++;

        if(x->filsG != NULL)

            enfiler(&f, x->filsG);

        if(x->filsD != NULL)

            enfiler(&f, x->filsD);


    }

    int k, j, min;
    ElemArbre temp;

    for (k = 0; k < i-1; k++)
    {
        min = k;
        for (j = k+1; j < i; j++)
        {
            min = k;
            if (strcmp(t[j].mot,t[min].mot) < 0)
            {
                min = j;
                if(min != k)
                {

                    temp = t[k];
                    t[k] = t[min];
                    t[min] = temp;
                }
            }
        }
    }
}

//fonction qui retourne le nombre de noeuds dans un arbre

int combien(arbre a)
{
    if(a == NULL)
    {
        return 0;
    } else
    {
        return 1 + combien(a->filsG) + combien(a->filsD);
    }
}

//une fonction qui cree un arbre equilibré a partir d'un tableau

arbre trier(ElemArbre t[], int star, int ennd)
{
    arbre b;

    if (star > ennd)
    {
        return NULL;
    }

    int mid = (star + ennd) / 2;

    //allocation de la racine
    b = malloc(sizeof(noeud));
    b->infoA = t[mid];
    b->filsG = NULL;
    b->filsD = NULL;

    b->filsG = trier(t, star, mid-1);

    b->filsD = trier(t, mid+1, ennd);

    return b;
}

//une procedure qui affiche un arbre ordonné

void affichageord(arbre a)
{
    ElemArbre x;

    if(a != NULL)
    {

            affichageord(a->filsG);

            strcpy(x.mot,a->infoA.mot);
            x.point = a->infoA.point;

            printf("%s -> ", x.mot);
            while(x.point != NULL)
            {
                printf("P[%d]  ",x.point->infol);
                x.point = x.point->suivl;
            }
            printf("\n\n");

            affichageord(a->filsD);
    }
}

//une procedure qui recherche un mot donné dans l’arbre et retourner son niveau

void recherchetwo(arbre a, char M[30],int niv)
{
    arbre temp = a;

    while(strcmp(temp->infoA.mot,M) != 0)
	{

      if(temp != NULL)
      {
         niv++;

         //go to left tree
         if(strcmp(temp->infoA.mot,M) > 0)
         {

            temp = temp->filsG;
         }
         //else go to right tree
         else
         {
            temp = temp->filsD;
         }

         //not found
         if(temp == NULL)
         {
            printf("Le mot introduit n'existe pas.\n");
            return NULL;
         }
      }
	}
	printf("Le mot (%s) est situe au niveau %d.\n",M,niv);
}

//une fonction qui ajoute un mot donné dans l’arbre avec un numéro de page

arbre ajoutdeux(arbre a,char M[], int val)
{
    liste s,p,q;
    arbre pere,curr,nouv;

    s = p = q =malloc(sizeof(elemlis));
    s->infol = val;
    s->suivl = NULL;

    nouv = malloc(sizeof(noeud));

    strcpy(nouv->infoA.mot ,M);
    nouv->infoA.point = s;

    nouv->filsD = NULL;
    nouv->filsG = NULL;

    pere = a;

    curr = NULL;

    while (pere!= NULL)
    {
        curr = pere;

        if(strcmp(pere->infoA.mot,M) == 0)
        {
            p = pere->infoA.point;

            if(val < pere->infoA.point->infol)
            {

                s->suivl = pere->infoA.point;
                pere->infoA.point = s;

            }else
            {
                while(p != NULL && p->infol < val)
                {
                    q = p;
                    p = p->suivl;
                }

                s->suivl = p;
                q->suivl = s;

            }
            return a;
        }
        else if (strcmp(pere->infoA.mot,M) > 0)

            pere = pere->filsG;

            else

            pere = pere->filsD;


    }
    if (strcmp(curr->infoA.mot,M) > 0)

        curr->filsG = nouv;

    else

        curr->filsD = nouv;

    return a;

}

//une fonction qui supprime un mot de l’index avec tous les numéros de pages associées au mot

arbre supprimedeux(arbre a,char M[])
{
    arbre curr,pere,nouv,temp,prev;
    curr=pere=nouv=temp=prev=NULL;

    curr = a;

    while (curr != NULL && strcmp(curr->infoA.mot,M) != 0)
    {
        pere = curr;
        if (strcmp(curr->infoA.mot,M) > 0)

            curr = curr->filsG;

        else

            curr = curr->filsD;

    }

    if (curr == NULL)
    {
        printf("\nLe mot (%s) n'existe pas.\n",M);
        return a;
    }
    if (curr->filsG == NULL || curr->filsD == NULL)
    {

        if (curr->filsG == NULL)

            nouv = curr->filsD;

        else

            nouv = curr->filsG;


        if (pere == NULL)

            return nouv;


        if (curr == pere->filsG)

            pere->filsG = nouv;


        else

            pere->filsD = nouv;

        free(curr);

    }

    else
    {
        temp = curr->filsD;

        while (temp->filsG != NULL)
        {
            prev = temp;
            temp = temp->filsG;
        }

        if(prev != NULL)

            prev->filsG = temp->filsD;
        else

            curr->filsD = temp->filsD;

        curr->infoA = temp->infoA;

        free(temp);
    }
    return a;
}

//Partie 3
//--------

//construction des chemins

void const_chamins(arbre a, liste3 path,file3 *paths)
{
    liste3 nouvn;

    if (a == NULL)
        return;

    // ajouter un noeuds au chemins
    nouvn = (liste3) malloc(sizeof(elemlis3));

    nouvn->infol3 = a;
    nouvn->suivl3 = path;
    path = nouvn;

    // on enfile si on arrive a une feuille
    if (a->filsG == NULL && a->filsD==NULL)

        enfiler3(paths,path);

    else
    {
        const_chamins(a->filsG, path, paths);
        const_chamins(a->filsD, path, paths);
    }
}

//affichage des chemins

void affiche_chemins(file3 paths)
{
    liste3 path;

    while(paths.tete3 != NULL)
    {
        defiler3(&paths,&path);

        while(path != NULL)
        {
            if(path->suivl3!=NULL)

                printf("%s "Rouge"<- "fin, path->infol3->infoA.mot);

            else

                printf("%s", path->infol3->infoA.mot);

            path = path->suivl3;
        }
        printf("\n");
    }
}

int main()
{
    arbre a;
    file3 f;
    liste3 p3=NULL;
    int mp,ms,niv=0,b,n;
    char men1[30],men2[30],men3[30],men4[30],mot[30],c[30];

    printf("+--------------------BIENVENUE--------------------+\n");
    printf("|Nous sommes ravis de partager ce projet avec vous|\n");
    printf("|Noms des etudians : "Rouge"-KHIARI Mohamed Abderraouf"fin"   |\n");
    printf("|                    "Rouge"-BARAGH Yasser Abdeldjalil"fin"   |\n");
    printf("+-------------------------------------------------+\n\n");
    printf(Rouge"******************************************************************************************************************\n"fin);
    printf(Rouge"******************************************************************************************************************\n\n"fin);

    // le menu principal

    do
    {
        printf(Cyan"+==================================== MENU PRINCIPAL ====================================+\n"fin);
        printf(Cyan"|"fin"1) Si vous voulez faire des opperations sur un arbre binaire "Cyan"NON ORDONNE "fin Rouge"tappez (1)"fin".    "Cyan"|\n"fin);
        printf(Cyan"|"fin"2) Si vous voulez faire des opperations sur un arbre binaire "Cyan"ORDONNE "fin Rouge"tappez (2)"fin".        "Cyan"|\n"fin);
        printf(Cyan"+========================================================================================+\n\n"fin);

        //1-->partie 1
        //2-->partie 2
        do
        {
            printf("- Choisir un des arbre ci-dessus : ");
            scanf("%s",&c); if (strcmp(c,"1")==0) mp =1; else if(strcmp(c,"2")==0)  mp=2;

        }while(mp != 1 && mp != 2);

        printf("\n");
        // un choix entre l'arbre exemplair et l'arbre par saisi
        printf("- Si vous voulez introduire un  nouvel arbre "Rouge"tappez (new)"fin".\n");
        printf("- Si vous voulez travailler sur un arbre deja construit "Rouge"tappez (old)"fin".\n\n");

        do
        {
            printf("(new\\old) : ");
            scanf("%s",&men2);

        }while((strcmp(men2,"new") != 0) && (strcmp(men2,"old") != 0));

        printf("\n\n");

        if(strcmp(men2,"new") == 0)

           a = const_saisie();   // creation d'un arbre par saisi

        else

            a = const_tree();   // l'exemple

        if(mp == 1)    //partie 1
        {
            //menu partie 1
            do
            {
                printf(Jaune"+================================================== MENU ARBRE 1 ==================================================+\n"fin);
                printf(Jaune"|"fin"1) Si vous voulez "Jaune"AFFICHER LE CONTENU "fin"de l'arbre "Rouge"tappez (1)"fin".                                                      "Jaune"|\n"fin);
                printf(Jaune"|"fin"2) Si vous voulez "Jaune"AFFICHER LA STRUCTURE "fin"de l'arbre (chaque noeud avec son fils gauche et droit) "Rouge"tappez (2)"fin".       "Jaune"|\n"fin);
                printf(Jaune"|"fin"3) Si vous voulez "Jaune"RECHERCHER "fin "un mot dans l'arbre "Rouge"tappez (3)"fin".                                                      "Jaune"|\n"fin);
                printf(Jaune"|"fin"4) Si vous voulez "Jaune"AJOUTER "fin"un numero de page pour un mot qui existe deja "Rouge"tappez (4)"fin".                               "Jaune"|\n"fin);
                printf(Jaune"|"fin"5) Si vous voulez "Jaune"SUPPRIMER "fin"un numero de page pour un mot "Rouge"tappez (5)"fin".                                             "Jaune"|\n"fin);
                printf(Jaune"|"fin"6) Si vous voulez "Jaune"AFFICHER TOUS LES CHEMINS "fin"de l'arbre "Rouge"tappez (6)"fin".                                                "Jaune"|\n"fin);
                printf(Jaune"+==================================================================================================================+\n\n"fin);

                printf("- que voulez-vous faire ?\n\n");
                do
                {
                    printf("choisir(1,2,3,4,5,6) : ");
                    scanf("%d",&ms);

                }while(ms != 1 && ms != 2  &&  ms != 3  &&  ms != 4  &&  ms != 5  &&  ms != 6);

                printf("\n");

                switch (ms)
                {
                case 1://le premier affichage

                    printf(Jaune"AFFICHAGE 1\n"fin);
                    printf(Jaune"-----------\n\n"fin);

                    affiche1(a);
                    break;

                case 2://le deuxiem affichage

                    printf(Jaune"AFFICHAGE 2\n"fin);
                    printf(Jaune"-----------\n\n"fin);

                    affiche2(a);
                    break;

                case 3://la recherche

                    printf(Jaune"TOPIC 3\n"fin);
                    printf(Jaune"-------\n\n"fin);

                    printf("Donner un mot pour rechercher : ");
                    scanf("%s",&mot);
                    printf("\n");

                    rech_affiche(a,mot,niv);

                    break;

                case 4://l'ajout

                    printf(Jaune"TOPIC 4\n"fin);
                    printf(Jaune"-------\n\n"fin);

                    printf("Donner le mot ou vous voulez ajouter un numero : ");
                    scanf("%s",&mot);
                    printf("\n");

                    b = recherche(a,mot);

                    if(b == 1)
                    {
                        printf("Donner le numero qui vous souhaite a ajouter : ");
                        scanf("%d",&n);
                        printf("\n");

                        ajout(a,mot,n);

                        printf("voulez-vous afficher l'arbre apres l'ajout ?\n\n");

                        do
                        {
                            printf("(oui\\non) : ");
                            scanf("%s",&men4);

                        }while((strcmp(men4,"oui") != 0) && (strcmp(men4,"non") != 0));

                        if(strcmp(men4,"oui") == 0)
                        {
                            printf("\n");
                            affiche1(a);
                        }

                    }
                    else

                        printf("le mot %s n'existe pas.\n",mot);

                    break;

                case 5://la suppression

                    printf(Jaune"TOPIC 5\n"fin);
                    printf(Jaune"-------\n\n"fin);

                    printf("Donner le mot ou vous voulez supprimer un numero : ");
                    scanf("%s",&mot);
                    printf("\n");

                    b = recherche(a,mot);

                    if(b == 1)
                    {
                        printf("Donner le numero qui vous souhaite a supprimer : ");
                        scanf("%d",&n);
                        printf("\n");

                        supprime(a,mot,n);

                        printf("voulez-vous afficher l'arbre apres la suppresion ?\n\n");

                        do
                        {
                            printf("(oui\\non) : ");
                            scanf("%s",&men4);

                        }while((strcmp(men4,"oui") != 0) && (strcmp(men4,"non") != 0));

                        if(strcmp(men4,"oui") == 0)
                        {
                            printf("\n");
                            affiche1(a);
                        }

                    }
                    else

                        printf("le mot %s n'existe pas.\n",mot);

                    break;

                case 6://les chemins

                    f.tete3=NULL;
                    f.queue3=NULL;

                    printf(Jaune"TOPIC 6\n"fin);
                    printf(Jaune"-------\n\n"fin);

                    const_chamins(a,p3,&f);
                    affiche_chemins(f);

                    break;

                }

                printf("\n");
                printf("- "Rouge"Tappez (retour)"fin" pour revenir vers le menu de l'arbre.\n");
                printf("- "Rouge"Tappez (fin)"fin" pour quitter le menu de l'arbre.\n\n");

                do
                {
                    printf("(retour\\fin) : ");
                    scanf("%s",&men3);

                }while((strcmp(men3,"retour") != 0) && (strcmp(men3,"fin") != 0));
                printf("\n");

            }while(strcmp(men3,"retour")==0);
        }
        else   //partie 2
        {
            //triage de l'arbre

            ElemArbre y[100];
            int i=0,z=0;
            arbre tr=NULL;

            creertab(a,y,i);
            z=combien(a);
            tr=trier(y,0,z-1);

            //menu partie 2
            do
            {
                printf(Vert"+================================================== MENU ARBRE 2 ==================================================+\n"fin);
                printf(Vert"|"fin"1) Si vous voulez "Vert"AFFICHER "fin"le contenu de l'arbre par ordre croissant "Rouge"tappez (1)"fin".                                  "Vert"|\n"fin);
                printf(Vert"|"fin"2) Si vous voulez "Vert"RECHERCHER "fin"sur un mot dans l'arbre "Rouge"tappez (2)"fin".                                                  "Vert"|\n"fin);
                printf(Vert"|"fin"3) Si vous voulez "Vert"AJOUTER "fin"un mot et un numero de page "Rouge"tappez (3)"fin".                                                 "Vert"|\n"fin);
                printf(Vert"|"fin"4) Si vous voulez "Vert"SUPPRIMER "fin"un mot et tous les pages associees "Rouge"tappez (4)"fin".                                        "Vert"|\n"fin);
                printf(Vert"|"fin"5) Si vous voulez "Vert"AFFICHER TOUS LES CHEMINS "fin"de l'arbre "Rouge"tappez (5)"fin".                                                "Vert"|\n"fin);
                printf(Vert"+==================================================================================================================+\n\n"fin);

                printf("- que voulez-vous faire ?\n\n");
                do
                {
                    printf("choisir(1,2,3,4,5) : ");
                    scanf("%d",&ms);

                }while(ms != 1 && ms != 2  &&  ms != 3  &&  ms != 4  &&  ms != 5);

                printf("\n");

                switch (ms)
                {
                case 1://l'affichage

                    printf(Vert"AFFICHAGE\n"fin);
                    printf(Vert"---------\n\n"fin);

                    affichageord(tr);
                    break;

                case 2://la recherche

                    printf(Vert"TOPIC 2\n"fin);
                    printf(Vert"-------\n\n"fin);

                    printf("Donner un mot pour rechercher : ");
                    scanf("%s",&mot);
                    printf("\n");

                    recherchetwo(tr,mot,niv);
                    break;

                case 3://l'ajout

                    printf(Vert"TOPIC 3\n"fin);
                    printf(Vert"-------\n\n"fin);

                    printf("Donner le mot qui vous voulez ajouter dans l'arbre : ");
                    scanf("%s",&mot);
                    printf("\n");

                    printf("Donner le numero de page qui vous voulez ajouter dans l'arbre : ");
                    scanf("%d",&n);
                    printf("\n");

                    tr=ajoutdeux(tr,mot,n);

                    printf("voulez-vous afficher l'arbre apres l'ajout ?\n\n");

                    do
                    {
                        printf("(oui\\non) : ");
                        scanf("%s",&men4);

                    }while((strcmp(men4,"oui") != 0) && (strcmp(men4,"non") != 0));

                    if(strcmp(men4,"oui") == 0)
                    {
                        printf("\n");
                        affiche2(tr);
                    }
                    break;

                case 4://la suppression

                    printf(Vert"TOPIC 4\n"fin);
                    printf(Vert"-------\n\n"fin);

                    printf("Donner le mot qui vous voulez supprimer : ");
                    scanf("%s",&mot);

                    tr=supprimedeux(tr,mot);

                    printf("\nvoulez-vous afficher l'arbre apres la suppresion ?\n\n");

                    do
                    {
                        printf("(oui\\non) : ");
                        scanf("%s",&men4);

                    }while((strcmp(men4,"oui") != 0) && (strcmp(men4,"non") != 0));

                    if(strcmp(men4,"oui") == 0)
                    {
                        printf("\n\n");
                        affiche2(tr);
                    }
                    break;

                case 5://les chemins

                    f.tete3=NULL;
                    f.queue3=NULL;

                    printf(Vert"TOPIC 5\n"fin);
                    printf(Vert"-------\n\n"fin);

                    const_chamins(tr,p3,&f);
                    affiche_chemins(f);
                    break;

                }

                printf("\n");
                printf("- "Rouge"Tappez (retour)"fin" pour revenir vers le menu de l'arbre.\n");
                printf("- "Rouge"Tappez (fin)"fin" pour quitter le menu de l'arbre.\n\n");

                do
                {
                    printf("(retour\\fin) : ");
                    scanf("%s",&men3);

                }while((strcmp(men3,"retour") != 0) && (strcmp(men3,"fin") != 0));
                printf("\n");

            }while(strcmp(men3,"retour")==0);
        }

        printf("\n");
        printf("- "Rouge"Tappez (retour)"fin" pour revenir vers le menu principal.\n");
        printf("- "Rouge"Tappez (exit)"fin" pour terminer.\n\n");

        do
        {
            printf("(retour\\exit) : ");
            scanf("%s",&men1);

        }while((strcmp(men1,"retour") != 0) && (strcmp(men1,"exit") != 0));
        printf("\n");

    }while(strcmp(men1,"retour")==0);

    return 0;
}


