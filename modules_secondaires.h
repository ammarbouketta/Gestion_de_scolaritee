

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Tenreg  GENERER_ENREG       ();
void    RECHERCHE_TOF       (char *cle, char *nom_fichier, int *Trouv, int *i, int *j);
void    INSERTION_TOF       (Tenreg e, char* nom_fichier, int taille_bloc, int repetition);
void    SUPPRESSION_TOF     (char *nom_fichier, int i, int j);
void    REORGANISATION_TOF  ();
int     EXTRAIR_ANNEE       (char *NUM);
int     HASHAGE             (int N, int n);
int     EXISTE_TXT          (char *nom_fichier, char *NUM);
void    AFFICHER_TOF        ();
int     EXTRAIR_CHAINE      (Tenreg e, char *chaine_enreg);
void    RECHERCHE_LOVnC     (char *cle, char *nom_fichier, int *Trouv, int *i, int *j);
float   MOYEN_PROMOTION     ();
void    REORGANISATION_LOVnC();
void    AFFICHER_LOVnC      ();

/***génération des champs d'un enregistrement d'une maniére aléatoire aléatoires ***/
Tenreg GENERER_ENREG()
{
    Tenreg e;
    int n;
    char s[5],s2[5];

    n=rand()%5+15;
    itoa(n,s,10);
    strcpy(e.NUM,s);
    e.NUM[2]='/';
    e.NUM[3]='\0';
    n=rand()%9999+1;
    itoa(n,s,10);
    for( int i=strlen(s) ; i<4 ; i++ )
    {
        strcpy(s2,"0");
        strcat(s2,s);
        strcpy(s,s2);
    }
    strcat(e.NUM,s);

    e.GROUPE=rand()%12+1;
    e.NOTE=rand()%11;

    return e;
}
/***recherche dans tof un élément et retourner vrai et les indices ou il existe ou bien retourner faux et les indice de leur emplacement ***/
void RECHERCHE_TOF(char *cle, char *nom_fichier, int *Trouv, int *i, int *j)
{
    //OUVRIR_TOF(&F1,nom_fichier,'A');
    *i=1;   *j=0;   *Trouv=0;

    int Arret=0;
    int BlocInf=1, BlocSup=Entete_TOF(F1,1);
//recherche entre les bloc
    while(!*Trouv && !Arret && BlocInf<=BlocSup)
    {
        *i=(BlocInf+BlocSup)/2;
        LireDir_TOF(F1,*i,&Buff_TOF);
        if(strcmp(Buff_TOF.tab[0].NUM,cle)>0) BlocSup=*i-1;
        else if(strcmp(Buff_TOF.tab[Buff_TOF.NB-1].NUM,cle)<0) BlocInf=*i+1;
        else
        {
            int EnregInf=0, EnregSup=Buff_TOF.NB-1;
            //recherche  intra bloc
            while(!*Trouv && !Arret && EnregInf<=EnregSup)
            {
                *j=(EnregInf+EnregSup)/2;
                if(strcmp(Buff_TOF.tab[*j].NUM,cle)>0) EnregSup=*j-1;
                else if(strcmp(Buff_TOF.tab[*j].NUM,cle)<0) EnregInf=*j+1;
                else *Trouv=1;
            }
            if(EnregInf>EnregSup) *j=EnregInf;
            Arret=1;
        }
    }
    if(BlocInf>BlocSup) *i=BlocInf;
    //FERMER_TOF(&F1);
}
/***Insertion d'un élément dans tof utilisant le module de la recherche faisant des décalages ***/
void INSERTION_TOF(Tenreg e, char* nom_fichier, int taille_bloc, int repetition)
{
    //OUVRIR_TOF(&F1,"NOTES.bin",'A');
    int Trouv, i, j;

        RECHERCHE_TOF(e.NUM,"NOTES.bin",&Trouv,&i,&j);
        if(!Trouv || repetition)
        {
            int Arret=0;
            while(!Arret)
            {
                if(i>Entete_TOF(F1,1))
                {
                    i=Alloc_Bloc_TOF(&F1);
                    Buff_TOF.tab[0]=e;
                    Buff_TOF.NB=1;
                    EcrirDir_TOF(F1,i,&Buff_TOF);
                    Arret=1;
                }
                else
                {
                    LireDir_TOF(F1,i,&Buff_TOF);
                    Tenreg X=Buff_TOF.tab[Buff_TOF.NB-1];
                    int k;
                    for( k=Buff_TOF.NB-1 ; k>j ; k--)
                    {
                        Buff_TOF.tab[k]=Buff_TOF.tab[k-1];
                    }
                    if(Buff_TOF.NB<taille_bloc)
                    {
                        Buff_TOF.tab[Buff_TOF.NB]=X;
                        Buff_TOF.tab[j]=e;
                        Buff_TOF.NB++;
                        EcrirDir_TOF(F1,i,&Buff_TOF);
                        Arret=1;
                    }
                    else
                    {
                        Buff_TOF.tab[j]=e;
                        EcrirDir_TOF(F1,i,&Buff_TOF);
                        e=X;
                        i++;
                        j=0;
                    }
                }
            }
            Aff_Entete_TOF(&F1,2,Entete_TOF(F1,2)+1);
        }
    //FERMER_TOF(&F1);
}
//suppression physique d'un élément par des décalages
void SUPPRESSION_TOF (char *nom_fichier, int i, int j)
{
    //OUVRIR_TOF(&F1,"NOTES.bin",'A');
    LireDir_TOF(F1,i,&Buff_TOF);
    for( int k=j ; k<Buff_TOF.NB-1 ; k++)
    {
        Buff_TOF.tab[k]=Buff_TOF.tab[k+1];
    }
    Buff_TOF.NB--;
    EcrirDir_TOF(F1,i,&Buff_TOF);
    Aff_Entete_TOF(&F1,2,Entete_TOF(F1,2)-1);
    //FERMER_TOF(&F1);
}

void REORGANISATION_TOF()
{
    //OUVRIR_TOF(&F1,"NOTES.bin",'A');
    int i,j,k=1,l=0;

    for( i=1 ; i<=Entete_TOF(F1,1) ; i++ )
    {
        LireDir_TOF(F1,i,&Buff_TOF);
        for( j=0 ; j<Buff_TOF.NB ; j++ )
        {
            Buff1_TOF.tab[l]=Buff_TOF.tab[j];
            l++;
            if(l==taille_max_TOF)
            {
                Buff1_TOF.NB=l;
                EcrirDir_TOF(F1,k,&Buff1_TOF);
                k++;
                l=0;
            }
        }
    }
    Buff1_TOF.NB=l;
    EcrirDir_TOF(F1,k,&Buff1_TOF);
    Aff_Entete_TOF(&F1,1,k);
    //FERMER_TOF(&F1);
}
//extraire l'année à partir d'une chaine
int EXTRAIR_ANNEE(char *NUM)
{
    char s[3]={NUM[0],NUM[1],'\0'};

    return atoi(s);
}
//c'est une fonction qui est utiliser pour le remplissage de fichier texte
int HASHAGE(int N, int n )
{
    return (2*N-n)%(N+1);
}
/***ROLE:pour avoir si un enreg est déja exister dans le fichier texte ***/
int EXISTE_TXT(char *nom_fichier, char *NUM)
{
    FILE *f=fopen(nom_fichier,"r");
    char ligne[50],*matricule;
    while(fgets(ligne,50,f))
    {
        matricule=strtok(ligne," ");
        if(!strcmp(NUM,matricule)) return 1;
        matricule=strtok(NULL," ");
        if(!strcmp(NUM,matricule)) return 1;
    }
    return 0;
}

void AFFICHER_TOF()//affichage de la strecture TOF
{
    //OUVRIR_TOF(&F1,"NOTES.bin",'A');
    int i,j,rep1=1;
    Tenreg e;
    printf("\n**DES INFOS : \n");
    textcolor(12);
    printf("Le nombre des blocs est : %d \nLe nombre d'enregistrement est : %d\n",F1.entet.nb_bloc,F1.entet.nb_enreg);

    for( i=1 ; (i<=Entete_TOF(F1,1))&&(rep1!=0) ; i++ )
    {
        LireDir_TOF(F1,i,&Buff_TOF);
        textcolor(15);
        if (i>=2)
        {
        printf("Voullez vous continue ?? il vous reste %d blocs (press 1 si oui ;0 sinon) : ",Entete_TOF(F1,1)-i+1);
        scanf("%d",&rep1);
         }
         if (rep1==1)
         {
        textcolor(10);
        printf("\n\t\t  ==BLOC== : %d\n",i);
        textcolor(12);
        printf("\t =========   ======    ==== \n");
        printf("\t|MATRICULE   GROUPE    NOTE | \n");
        printf("\t =========   ======    ==== \n");
        for( j=0 ; j<Buff_TOF.NB ; j++)
        {
             textcolor(9);
            e=Buff_TOF.tab[j];
            printf("\t%s || ",e.NUM);
            textcolor(3);
            if (e.GROUPE>9)
            printf("   %d || ",e.GROUPE);
            else
            printf("   %d  || ",e.GROUPE);
            textcolor(1);
            if (e.NOTE>9)
            printf("   %d ||  \n",e.NOTE);
            else
            printf("   %d  ||  \n",e.NOTE);


        }
         }
        printf("\n\n");
    }
    //FERMER(&F1);
}

int EXTRAIR_CHAINE(Tenreg e, char *chaine_enreg)
{
    char s[20];

    strcpy(chaine_enreg,"$0$");
    strcat(chaine_enreg,e.NUM);
    strcat(chaine_enreg,"$");
    itoa(e.GROUPE,s,10);
    if( strlen(s)==1) { s[1]=s[0]; s[0]='0' ; s[2]='\0'; }
    strcat(chaine_enreg,s);
    strcat(chaine_enreg,"$");
    itoa(e.NOTE,s,10);
    //if( strlen(s)==1) { s[1]=s[0]; s[0]='0' ; s[2]='\0'; }
    strcat(chaine_enreg,s);
    strcat(chaine_enreg,"$");
    itoa(strlen(chaine_enreg)+2,s,10);
    strcat(s,chaine_enreg);
    strcpy(chaine_enreg,s);
    chaine_enreg[strlen(chaine_enreg)]='\0';

    return strlen(chaine_enreg);
}


void RECHERCHE_LOVnC(char *cle, char *nom_fichier, int *Trouv, int *i, int *j)//recherche séquentiel dans la liste pour avoir si l'enregistrement existe ou pas
{
    //int n=OUVRIR_LOVnC(&F2,nom_fichier,'A');
    *i=Entete_LOVnC(F2,1);
    *j=0;
    *Trouv=0;
    int Arret=0;

    char chaine_buff[taille_max_LOVnC+1];
    char *champ,*rest;
    int taille,eff;
    while(!*Trouv && !Arret  && *i!=0)
    {
        LireDir_LOVnC(F2,*i,&Buff_LOVnC);
        strcpy(chaine_buff,Buff_LOVnC.tab);
        rest=chaine_buff;
        while(!*Trouv && !Arret && *j<Buff_LOVnC.NB)
        {
            champ=strtok_r(rest,"$",&rest);
            taille=atoi(champ);
            champ=strtok_r(rest,"$",&rest);
            eff=atoi(champ);
            champ=strtok_r(rest,"$",&rest);
            if(!strcmp(champ,cle))
            {
                if(eff) Arret=1;
                else *Trouv=1;
            }
            else if(strcmp(champ,cle)>0)
            {
                Arret=1;
            }
            else
            {
                *j=*j+taille;
                //printf("\n%d %d",*j,Buff_LOVnC.NB);
                champ=strtok_r(rest,"$",&rest);
                champ=strtok_r(rest,"$",&rest);
            }
        }
        if(*j>=Buff_LOVnC.NB)
        {
            *j=0;
            *i=Buff_LOVnC.suivant;
        }
    }
}

float MOYEN_PROMOTION()//rendre la moyenne de la promo
{
    //OUVRIR_LOVnC(&F2,"NOTES_FINALES.bin",'A');
    float somme=0,nb_etudiant=0;
    int i,eff;
    char chaine_buffer[taille_max_LOVnC+1],*rest,*champ;

    i=Entete_LOVnC(F2,1);
    while(i!=0)
    {
        LireDir_LOVnC(F2,i,&Buff_LOVnC);
        strcpy(chaine_buffer,Buff_LOVnC.tab);
        rest=chaine_buffer;
        while((champ=strtok_r(rest,"$",&rest)))
        {
            champ=strtok_r(rest,"$",&rest);
            eff=atoi(champ);
            champ=strtok_r(rest,"$",&rest);
            champ=strtok_r(rest,"$",&rest);
            champ=strtok_r(rest,"$",&rest);
            if(!eff)
            {
                somme+=atoi(champ);
                nb_etudiant++;
            }
        }
        i=Buff_LOVnC.suivant;
    }
    return somme/nb_etudiant;
}

void REORGANISATION_LOVnC()//pour réorganiser le fichier à partir de certain taux
                           //comparant le nombre d'enregistrement  supprimer qui ont un champ eff=1 par le nombre d'enregistrement existe eff=0
{
    int i,l=Entete_LOVnC(F2,1);

    LireDir_LOVnC(F2,l,&Buff1_LOVnC);
    Buff1_LOVnC.NB=0;
    Buff1_LOVnC.tab[0]='\0';

    char chaine_buff[taille_max_LOVnC+1], *rest, chaine_enreg[taille_max_LOVnC+1], *champ ,eff;

    for( i=Entete_LOVnC(F2,1) ; i!=0 ; i=Buff_LOVnC.suivant)
    {
        LireDir_LOVnC(F2,i,&Buff_LOVnC);
        strcpy(chaine_buff,Buff_LOVnC.tab);
        rest=chaine_buff;

        while((champ=strtok_r(rest,"$",&rest)))
              {
                  strcpy(chaine_enreg,champ);
                  strcat(chaine_enreg,"$");
                  champ=strtok_r(rest,"$",&rest);
                  eff=champ[0];

                    strcat(chaine_enreg,champ);
                    strcat(chaine_enreg,"$");
                    champ=strtok_r(rest,"$",&rest);
                    strcat(chaine_enreg,champ);
                    strcat(chaine_enreg,"$");
                    champ=strtok_r(rest,"$",&rest);
                    strcat(chaine_enreg,champ);
                    strcat(chaine_enreg,"$");
                    champ=strtok_r(rest,"$",&rest);
                    strcat(chaine_enreg,champ);
                    strcat(chaine_enreg,"$");

                    if(eff!='1')
                    {
                        if(Buff1_LOVnC.NB+strlen(chaine_enreg)<=taille_max_LOVnC)
                        {
                            strcat(Buff1_LOVnC.tab,chaine_enreg);
                            Buff1_LOVnC.NB+=strlen(chaine_enreg);
                        }
                        else
                        {
                            EcrirDir_LOVnC(F2,l,&Buff1_LOVnC);
                            l=Buff1_LOVnC.suivant;
                            LireDir_LOVnC(F2,l,&Buff1_LOVnC);
                            Buff1_LOVnC.NB=0;
                            Buff1_LOVnC.tab[0]='\0';
                            strcat(Buff1_LOVnC.tab,chaine_enreg);
                            Buff1_LOVnC.NB+=strlen(chaine_enreg);
                        }
                    }
              }
    }
    Buff1_LOVnC.suivant=0;
    EcrirDir_LOVnC(F2,l,&Buff1_LOVnC);
    Aff_Entete_LOVnC(&F2,2,l);
    Aff_Entete_LOVnC(&F2,4,0);

}
void AFFICHER_LOVnC()
{
    //int n=OUVRIR_LOVnC(&F2,"NOTES_FINALES.bin",'A');
    int i,nb_bloc;
    char chaine_bloc[taille_max_LOVnC+1],*rest,*champ,*eff;
     printf("\n**DES INFOS : \n");
    textcolor(12);
    printf("Le nombre des blocs est : %d \nLe nombre d'enregistrement est : %d\n",Entete_LOVnC(F2,2),Entete_LOVnC(F2,3));
    textcolor(15);
    printf("\nDonner le nombre de blocs a afficher (ou -1 pour afficher tout les blocs): ");
    scanf("%d",&nb_bloc);

    for(i=Entete_LOVnC(F2,1) ; i!=0 && nb_bloc!=0 ; i=Buff_LOVnC.suivant , nb_bloc--)
    {
        printf("\n**************BLOC %d *****************",i);
        LireDir_LOVnC(F2,i,&Buff_LOVnC);
        strcpy(chaine_bloc,Buff_LOVnC.tab);
        rest=chaine_bloc;
        int j=0;
        while((champ=strtok_r(rest,"$",&rest)) && j<Buff_LOVnC.NB)
        {
            textcolor(9);
            printf("\n%d",atoi(champ));
            j+=atoi(champ);
            eff=strtok_r(rest,"$",&rest);
            textcolor(10);
            printf("$%s",eff);
            champ=strtok_r(rest,"$",&rest);
            textcolor(3);
            printf("$%s",champ);
            champ=strtok_r(rest,"$",&rest);
            textcolor(12
                      );
            printf("$%d",atoi(champ));
            champ=strtok_r(rest,"$",&rest);
            textcolor(15);
            printf("$%d",atoi(champ));
        }

    }
}


