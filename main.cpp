/*_______________________________________ By Amir FARES _______________________________________*/
#include <iostream>
#include "GestPile.h"
#include <cmath> // need it for function fmod

using namespace std;

//Prototype ____________________________
bool Valide(string Expression);
void Transformation(string ExpInf,string *ExpPost);
float Valider_Exp(string ExpPost);

int main()
{
    string ExpInf,ExpPost;
    cout << "Donner l'expression : " ;
    cin >> ExpInf;
    if(!(Valide(ExpInf)))
    {
        cout << "Expression est non valide " << endl ;
    }
    else
    {
        Transformation(ExpInf,&ExpPost);
        //cout << ExpPost << endl ;
        float x=Valider_Exp(ExpPost);
        cout << "L'expressin egal : " << x << endl ;
    }

    return 0;
}

//Function ______________________________

bool Valide(string Expression)
{
    Liste *Pile=NULL;
    for(int i=0;i<(Expression.size());i++)
    {
        if((Expression[i]=='(')||(Expression[i]=='[')||(Expression[i]=='{'))
        {
            Pile=Empiler(Pile,Expression[i]);
        }
        if((Expression[i]==')')||(Expression[i]==']')||(Expression[i]=='}'))
        {
            if(PileVide(Pile))
            {
                return(false);
            }
            else
            {
                char x;
                Pile=Depiler(Pile,&x);
                if(!(((x=='(')&&(Expression[i]==')'))||((x=='[')&&(Expression[i]==']'))||((x=='{')&&(Expression[i]=='}'))))
                {
                    return (false);
                }
            }
        }
    }
    if(!(PileVide(Pile)))
    {
        return(false);
    }
    return (true);
}

void Transformation(string ExpInf,string *ExpPost)
{
    int j=0;
    string Temp;//string because ExpPost * par address
    Liste *PileOper=NULL;//pile of operators
    char tmp=0;// temporary char for depiler
    for(int i=0;i<ExpInf.size();i++)
    {
        if(((ExpInf[i]>=48)&&(ExpInf[i]<=57))||(ExpInf[i]=='.'))//if number add it to string
        {
            Temp.resize(j+1, '$'); // change string size to j+1 and the added size fill it with $$$$$
            Temp[j]=ExpInf[i];
            j++;
        }
        else
        {
            if((ExpInf[i]=='(')||(ExpInf[i]=='[')||(ExpInf[i]=='{'))
            {
                // empiler ( dans la pile
                PileOper=Empiler(PileOper,ExpInf[i]);
            }

            if((ExpInf[i]==')')||(ExpInf[i]==']')||(ExpInf[i]=='}'))
            {
                // depiler and add to string until found (
                PileOper=Depiler(PileOper,&tmp);
                while(!((tmp=='(')||(tmp=='[')||(tmp=='{')))
                {
                    //add to string
                    Temp.resize(j+1, '$');
                    Temp[j]=tmp;
                    j++;
                    //depiler
                    PileOper=Depiler(PileOper,&tmp);
                }
            }

            if((ExpInf[i]=='+')||(ExpInf[i]=='-'))
            {
                //empiler the operator
                if(PileVide(PileOper))
                {
                    PileOper=Empiler(PileOper,ExpInf[i]);
                    // add space between numbers
                    if((Temp[j-1]>=48)&&(Temp[j-1]<=57))
                    {
                        Temp.resize(j+1, '$');
                        Temp[j]=' ';
                        j++;
                    }
                }
                else
                {
                    PileOper=Depiler(PileOper,&tmp);
                    if((tmp=='+')||(tmp=='-')||(tmp=='/')||(tmp=='*')||(tmp=='%'))
                    {
                        //add the past operator to the string
                        Temp.resize(j+1, '$');
                        Temp[j]=tmp;
                        j++;
                    }
                    else
                    {
                        PileOper=Empiler(PileOper,tmp);
                        // add space between numbers
                        if((Temp[j-1]>=48)&&(Temp[j-1]<=57))
                        {
                            Temp.resize(j+1, '$');
                            Temp[j]=' ';
                            j++;
                        }
                    }
                    //empiler the new operator
                    PileOper=Empiler(PileOper,ExpInf[i]);
                }
            }
            if((ExpInf[i]=='*')||(ExpInf[i]=='/')||(ExpInf[i]=='%'))
            {

                //empiler the operator
                if(PileVide(PileOper))
                {
                    PileOper=Empiler(PileOper,ExpInf[i]);
                    // add space between numbers
                    if((Temp[j-1]>=48)&&(Temp[j-1]<=57))
                    {
                        Temp.resize(j+1, '$');
                        Temp[j]=' ';
                        j++;
                    }
                }
                else
                {
                    PileOper=Depiler(PileOper,&tmp);
                    if((tmp=='/')||(tmp=='*')||(tmp=='%'))
                    {
                        //add the past operator to the string
                        Temp.resize(j+1, '$');
                        Temp[j]=tmp;
                        j++;
                    }
                    else
                    {
                        PileOper=Empiler(PileOper,tmp);
                        // add space between numbers
                        if((Temp[j-1]>=48)&&(Temp[j-1]<=57))
                        {
                            Temp.resize(j+1, '$');
                            Temp[j]=' ';
                            j++;
                        }
                    }
                    //empiler the new operator
                    PileOper=Empiler(PileOper,ExpInf[i]);
                }
            }
        }

    }
    while(!(PileVide(PileOper)))
    {
        PileOper=Depiler(PileOper,&tmp);
        //add the rest of operators to the string
        Temp.resize(j+1, '$');
        Temp[j]=tmp;
        j++;
    }
    *ExpPost=Temp;
}

float Valider_Exp(string ExpPost)
{
    string Temp;int j=0; // for the number before transform it to float
    float x; // for return the result
    bool num=false;//number before
    ListeN *PileNum=NULL;
    for(int i=0;i<ExpPost.size();i++)
    {
        if(((ExpPost[i]>=48)&&(ExpPost[i]<=57))||(ExpPost[i]=='.'))//if number add it to string
        {
            //Add the number to string
            Temp.resize(j+1, '$');
            Temp[j]=ExpPost[i];
            j++;
            num=true;//there is number before
        }
        else
        {
            if(num)//if there is number before this char change it to float and stack it in PileNum
            {
                PileNum=EmpilerN(PileNum,stof(Temp)); // stof need c++ version 11  // transform string to float and empiler
                j=0; // restart Temp to vide
            }
            if((ExpPost[i]=='+')||(ExpPost[i]=='-')||(ExpPost[i]=='/')||(ExpPost[i]=='*')||(ExpPost[i]=='%'))
            {
                float a,b;
                PileNum=DepilerN(PileNum,&b);
                PileNum=DepilerN(PileNum,&a);
                switch(ExpPost[i])
                {
                    case '+' : a=a+b;break;
                    case '-' : a=a-b;break;
                    case '*' : a=a*b;break;
                    case '/' : a=a/b;break;
                    case '%' : a=fmod(a,b);break; // fmod need c++ version 11 // for modules operation between two float
                }
                PileNum=EmpilerN(PileNum,a);
            }

            num=false;
        }
    }
    PileNum=DepilerN(PileNum,&x); // depiler the last value (result) to return it
    return x;
}
