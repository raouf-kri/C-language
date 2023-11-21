#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* ======================================= Partie déclaration ======================================= */

//1) la déclaration de la liste

typedef struct element
{
    char info[30];
    struct element *suiv;
}element;
typedef element* liste;

//2) la déclaration des elements de la pile

typedef struct pliste
{
    liste point;
    char pay;
}Pliste;

//3) la déclaration de la pile

typedef struct elempile* pile;
typedef struct elempile
{
    Pliste infop;
    pile suivp;
} cellulep;

/* ======================================= Partie fonction ======================================= */

//1) fonction PREMIER qui crée le premier élément de la liste

liste premier(char mot[30])
{
    liste p;
    int i;

    p = (liste*)malloc(sizeof(element));

    strcpy( p -> info,mot);
    p -> suiv=NULL;

    return p;
}

//2) fonction AJOUT qui ajoute un élément à la fin d’une liste

void  ajout(char mot[30],liste *tete)
{
    liste q,p;
    int i;

    q = premier(mot);
    p = *tete;

    while(p->suiv !=  NULL)

        p = p -> suiv;

    p -> suiv = q;

}

//3) fonction SUPPRIME qui supprime tous les éléments d’une liste de point d’entrée tete

liste supprime(liste tete)
{
  liste p = tete;

  while(tete != NULL)
  {
     tete = p->suiv;
     p->suiv = NULL;

     free(p);
     p = tete;
  }
  return tete ;
}

/*4) les primitives de la pile
------------------------------*/
//Empliler

void empiler(pile *s,Pliste k)
{
    pile ne;  // le nouvel element de la pile

    ne = malloc(sizeof(cellulep));
    ne -> infop = k;
    ne -> suivp = *s;
    *s = ne;
}

//Dépiler

void depiler(pile *s,Pliste *k)
{
    pile temp; // variable temporaire

    *k = (*s) -> infop;
    temp = *s;
    *s = (*s) -> suivp;

    free(temp);
}

//SommetPile

Pliste  SommetPile(pile s)
{
    return s -> infop;
}

//Pilevide

int Pilevide(pile s)
{
    if(s == NULL)
        return 1;
    else
        return 0;

}

//5) fonction qui construit la structure donnée

pile CONSTSTR(int n)
{
    liste p;
    Pliste dep,dep2;
    pile y,s,pil;
    char mot[30];
    int i;

    y = s = pil =NULL;

    // creation de premier element

    printf("Donner le 1er pays : ");
    scanf("%s",mot);

    p = premier(mot);
    dep.pay = mot[0];
    dep.point = p;

    empiler(&s,dep);

    // creation des elements restants

    for(i=1;i<n;i++)
    {
        printf("Donner le %deme pays : ",i+1);
        scanf("%s",mot);

        p = premier(mot);
        dep.pay = mot[0];
        dep.point = p;

        // tester si il exisite déja un pays qui commence par la meme lettre

        while(Pilevide(s) == 0 && (SommetPile(s).pay) != (dep.pay))
        {
            depiler(&s,&dep2);
            empiler(&y,dep2);
        }

        if(Pilevide(s) == 1)

            empiler(&s,dep);

        else

            ajout(mot,&(s->infop.point));

        while(Pilevide(y) == 0)
        {
            depiler(&y,&dep2);
            empiler(&s,dep2);
        }
    }


    // triage de la pile


    while(Pilevide(s) == 0)
    {
       dep = SommetPile(s);

       while(Pilevide(s) == 0)
       {
          depiler(&s,&dep2);
          empiler(&y,dep2);

          if(dep2.pay < dep.pay)

              dep = dep2;
       }
       while(Pilevide(y) == 0)
       {
          depiler(&y,&dep2);

          if(dep.pay != dep2.pay)

              empiler(&s,dep2);

          else

              empiler(&pil,dep2);

       }
    }

return pil;
}

int main()
{
     Pliste x;
     int n,j=0;
     char c,sup[3];
     pile w=NULL,tete=NULL;

     //lecture de nombres de pays

     do
     {
         printf("Combien de pays veillez-vous inserer ?\n");
         scanf("%d",&n);

     }while(n < 1);

     tete= CONSTSTR(n);
     printf("\n");


     while(Pilevide(tete) == 0)
     {
        depiler(&tete,&x);
        empiler(&w,x);

        // affichage des lettres de la pile
        printf(" %c : ",x.pay);

        //affichage de le contenu de chaque liste et faire --> entre les elements de la liste et (.) a la fin
        while(x.point != NULL)
        {
            if(x.point->suiv != NULL)

                printf("%s -->  ",x.point->info);

            else

                printf("%s.  ",x.point->info);

            x.point=x.point->suiv;
        }

        printf("\n\n");

     }

     printf("Voulez-vous supprimer des pays de cette liste ?\n");
     // si on insere oui il supprime des pays si ils existent si non il arrete

     do
     {
          printf("(oui/non):");
          scanf("%s",sup);

          printf("\n");

     }while((strcmp(sup,"oui") != 0) && (strcmp(sup,"non") != 0));

     if(strcmp(sup,"oui") == 0)
     {
          printf("Introduire la lettre qui vous souhaite a supprimer :");
          scanf("%s",&c);

          while(Pilevide(w) == 0)
          {
             depiler(&w,&x);

             //un compteur pour savoir si les pays qui commencent par la lettre inserée existent ou pas

             if(x.pay != c)

                j = j+0;

             else

                j++;

             empiler(&tete,x);
          }

          printf("\n\n");

          //un deuxieme affichage avec la suppression
          while(Pilevide(tete) == 0 && j != 0)
          {

              depiler(&tete,&x);
              printf(" %c : ",x.pay);

              if(x.pay == c)
              {
                 x.point = supprime(x.point);
                 printf("les pays  qui commence par cette lettre ont ete supprimer.");
              }

              while(x.point != NULL)
              {
                 if(x.point->suiv != NULL)

                    printf("%s -->  ",x.point->info);

                 else

                    printf("%s.  ",x.point->info);

                 x.point=x.point->suiv;
              }

              printf("\n\n");

           }
           if(j == 0)

              printf("il existe pas des pays qui commence par la lettre %c. \n\n",c);

     }
     else
     {
           printf("\n");
           printf("Aurevoir! \n\n");
     }


return 0;}
