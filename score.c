#include<stdio.h>
#include<stdlib.h>


//déclaration de la liste

typedef struct element
  {
        int nj,sj;     //nj : numéro de joueur , sj : score du joueur
        struct element *suiv;
  }element;
typedef element* liste;

//déclaration de la file

typedef struct elemfile *efile;
typedef struct elemfile
  {
    int njf;      //numéro de joueur dans la file
    efile suivf;

  }cellulef;

typedef struct
  {
     efile tete,queue;
  }file;

//une procédure qui retourne l'adresse du joueur ayant le score minimal et l’adresse de l’élément qui le précède
//on suppose que le scorre minimal est au premier element apres on le compare avec les autres element et a chaque fois on trouve un score plus petit que min on met un pointeur sur lui . aprs on rentre dans une nouvelle boucle qui arrete lorsque elle pointe au l'element avant l'elemnet qui a le score min

void ScoreMin(liste l, liste p , liste q  )
{
    int min;
    p = l;
    min = p->sj;

    while(p->suiv!=l)
    {
        if( p->sj < min)
        {
            min = p->sj;
            q=p;
        }

        p = p->suiv;
    }

    p=l;

    while(p->suiv!=q)
    {
        p=p->suiv;

    }

}

//la primitive enfiler

void enfiler(file *f,int x)
{
    efile newe;

    newe = malloc(sizeof(cellulef));
    newe -> njf = x;
    newe -> suivf = NULL;

    if ((*f).tete == NULL)

        (*f).tete = newe;

    else

        (*f).queue -> suivf = newe;

    (*f).queue = newe;

}

//la primitive défiler

void defiler(file *f,int *x)
{
    efile temp;
    temp = (*f).tete;
    *x = temp -> njf;

    if ((*f).tete == (*f).queue)
    {
        (*f).tete = NULL;
        (*f).queue = NULL;
    }
    else

        (*f).tete = (*f).tete -> suivf;

    free(temp);
}

//une action paramétrée qui remplace un joueur de la liste par un joueur de la file d’attente

void remplace(liste l,file *f)
{
    int x;
    liste r,p,q;

    defiler(f,&x);
    ScoreMin(l,p,q);

    if(q == l)
    {
        r=(liste*)malloc(sizeof(element));

        r -> suiv = q -> suiv;

        r -> sj = 0;
        r -> nj = x;

        p -> suiv = r;
        l =r;

        x = q -> nj;

        enfiler(&f,x);
        free(q);
    }
    else
    {
        r=(liste*)malloc(sizeof(element));

        r -> nj = x;
        r -> sj = 0;

        r -> suiv = q -> suiv;
        p -> suiv = r;

        x = q -> nj;

        enfiler(&f,x);
        free(q);
    }

}

//les nouvelles déclarations de structures

//enregistrement des elements

typedef struct enreg
{
    int nnj,i;      //nnj :  nouvel numéro de joueur  , i : compteur
}Enreg;


//la nouvelle déclaration de la liste

typedef struct nelement
  {
        Enreg infol;
        int nsj;     //nsj : nouvel score du joueur
        struct nelement *nsuiv;
  }nelement;
typedef nelement* nliste;


//la nouvelle déclaration de la file

typedef struct nelemfile *nefile;
typedef struct nelemfile
  {
    Enreg infof;
    nefile nsuivf;

  }ncellulef;
typedef struct
  {
     nefile ntete,nqueue;
  }nfile;

//declaration des nouvelles primitive

//la  nouvelle primitive enfiler

void nenfiler(nfile *nf,Enreg nx)
{
    nefile newe;

    newe = malloc(sizeof(ncellulef));
    newe ->infof = nx;
    newe -> nsuivf = NULL;

    if ((*nf).ntete == NULL)

        (*nf).ntete = newe;

    else

        (*nf).nqueue -> nsuivf = newe;

    (*nf).nqueue = newe;

}


//la nouvelle primitive défiler

void ndefiler(nfile *nf,Enreg *nx)
{
    nefile temp;
    temp = (*nf).ntete;
    *nx = temp ->infof;

    if ((*nf).ntete == (*nf).nqueue)
    {
        (*nf).ntete = NULL;
        (*nf).nqueue = NULL;
    }
    else

        (*nf).ntete = (*nf).ntete -> nsuivf;

    free(temp);
}


//la procédure Remplace avec la nouvelle structure
//------------------------------------------------
//une fonction qui retourne l'adresse de joueur qui a joué le maximum de fois

nliste jmax(nliste p)
{
    nliste l,q;
    int max;

    max = p->infol.i;
    l = p->nsuiv;

    while(l != p)
    {
        if(max < l->infol.i)
        {
            max = l->infol.i;
            q = l;
        }
        l = l->nsuiv;
    }

   return q;
}
//une procedure qui remplace le joueur ayant joué le maximum de fois et ayant un score minimal

void remplace2(nliste l,nfile *f)
{
    Enreg x;
    nliste r,p,q,u;

    defiler(&f,&x);
    ScoreMin(l,p,q);
    u = jmax(u);

    if(q == u)
    {
        if(q == l)
        {
             r=(liste*)malloc(sizeof(nelement));

             r -> nsuiv = q -> nsuiv;

             r -> nsj = 0;
             r ->infol.nnj = x.nnj;
             r ->infol.i = x.i++;

             p -> nsuiv = r;
             l =r;

             x = q->infol;

             nenfiler(&f,x);
             free(q);
        }
        else
        {
            r=(liste*)malloc(sizeof(nelement));

            r ->infol.nnj = x.nnj;
            r ->nsj = 0;
            r ->infol.i = x.i++;


            r -> nsuiv = q -> nsuiv;
            p -> nsuiv = r;

            x = q ->infol;

            nenfiler(&f,x);
            free(q);
        }

    }

}
