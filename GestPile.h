#include <iostream>

using namespace std;

typedef struct Liste // pile for char
{
    char val;
    struct Liste *suiv;
}Liste;

typedef struct ListeN // pile for float
{
    float val;
    struct ListeN *suiv;
}ListeN;

//Prototype ____________________________
Liste *Empiler(Liste *pile,char v); // function for char
Liste *Depiler(Liste *pile,char *v); // function for char
bool PileVide(Liste *pile); // function for char
void AffichePile(Liste *pile); // function for char
ListeN *EmpilerN(ListeN *pile,float v); // function for float
ListeN *DepilerN(ListeN *pile,float *v); // function for float
bool PileVideN(ListeN *pile); // function for float

//function _____________________________

Liste *Empiler(Liste *pile,char v)
{
    Liste *ptr=new Liste;
    ptr->val=v;
    ptr->suiv=NULL;
    if(!(PileVide(pile)))
    {
        ptr->suiv=pile;
    }
    pile=ptr;
    return (pile);
}

Liste *Depiler(Liste *pile,char *v)
{
    if(!(PileVide(pile)))
    {
        Liste *ptr = pile;
        *v = pile->val;
        if(pile->suiv!=NULL)
        {
            pile=pile->suiv;
            delete(ptr);
        }
        else
        {
            delete(ptr);
            pile=NULL;
        }
    }
    else
    {
        cout << "La Pile est vide !" << endl;
    }
    return pile;
}

bool PileVide(Liste *pile)
{
    return(pile==NULL);
}

void AffichePile(Liste *pile)
{
    while (!PileVide(pile))
    {
        char v;
        pile=Depiler(pile,&v);
        cout << v << endl ;
    }
}

ListeN *EmpilerN(ListeN *pile,float v)
{
    ListeN *ptr=new ListeN;
    ptr->val=v;
    ptr->suiv=NULL;
    if(!(PileVideN(pile)))
    {
        ptr->suiv=pile;
    }
    pile=ptr;
    return (pile);
}

ListeN *DepilerN(ListeN *pile,float *v)
{
    if(!(PileVideN(pile)))
    {
        ListeN *ptr = pile;
        *v = pile->val;
        if(pile->suiv!=NULL)
        {
            pile=pile->suiv;
            delete(ptr);
        }
        else
        {
            delete(ptr);
            pile=NULL;
        }
    }
    else
    {
        cout << "La Pile est vide !" << endl;
    }
    return pile;
}

bool PileVideN(ListeN *pile)
{
    return(pile==NULL);
}
