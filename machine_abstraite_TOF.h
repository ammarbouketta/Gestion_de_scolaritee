#include <stdlib.h>
#include <stdio.h>
#define taille_max_TOF 20

/***LES STRUCTURES DE DONNEES DU FICHIER TOF***/
typedef struct
{
    char NUM[8];
    int GROUPE;
    int NOTE;
}Tenreg;

typedef struct
{
    Tenreg tab[taille_max_TOF];
    int NB;
}Tbloc_TOF;

typedef struct
{
    int nb_bloc;
    int nb_enreg;
}Tentet_TOF;

typedef struct
{
    FILE *f;
    Tentet_TOF entet;
}TOF;
/***LES VARIABLES GLOBALES***/
int NbLect_TOF=0;
int NbEcrit_TOF=0;
TOF F1;
Tbloc_TOF Buff_TOF,Buff1_TOF,Buff2_TOF;
/***LES INTERFACES DES MODULES DE LA MACHINE ABSTRAITE DU FICHIER TOF***/
int     OUVRIR_TOF       (TOF *F, char *nom_fichier, char mod );
int     FERMER_TOF       (TOF *F);
void    LireDir_TOF      (TOF F, int i, Tbloc_TOF *buff);
void    EcrirDir_TOF     (TOF F, int i, Tbloc_TOF *buff);
int     Entete_TOF       (TOF F, int i);
void    Aff_Entete_TOF   (TOF *F, int i, int v);
int     Alloc_Bloc_TOF   (TOF *F);
/***LES IMPLEMENTATIONS DES MODULES DE LA MACHINES ABSTRAITE DU FICHIER TOF***/
int OUVRIR_TOF (TOF *F, char *nom_fichier, char mod )
{
    if (mod=='a' || mod=='A')
    {
        (*F).f=fopen(nom_fichier,"rb+");
        if ((*F).f==NULL) return 0;
        fseek((*F).f,0,SEEK_SET);
        fread(&((*F).entet),sizeof(Tentet_TOF),1,F->f);
        return 1;
    }
    if (mod=='n' || mod=='N')
    {
        (*F).f=fopen(nom_fichier,"wb+");
        if ((*F).f==NULL) return 0;
        (*F).entet.nb_bloc=0;
        (*F).entet.nb_enreg=0;
        fseek((*F).f,0,SEEK_SET);
        fwrite(&((*F).entet),sizeof(Tentet_TOF),1,(*F).f);
        return 1;
    }
    return 0;
}

int FERMER_TOF (TOF *F)
{
    fseek((*F).f,0,SEEK_SET);
    fwrite(&((*F).entet),sizeof(Tentet_TOF),1,(*F).f);
    fclose((*F).f);
    (*F).f=NULL;
    return 1;
}

void LireDir_TOF (TOF F, int i, Tbloc_TOF *buff)
{

    fseek(F.f,sizeof(Tentet_TOF)+(i-1)*sizeof(Tbloc_TOF),SEEK_SET);
    fread(buff,sizeof(Tbloc_TOF),1,F.f);
    NbLect_TOF++;
}

void EcrirDir_TOF (TOF F, int i, Tbloc_TOF *buff)
{
    fseek(F.f,sizeof(Tentet_TOF)+(i-1)*sizeof(Tbloc_TOF),SEEK_SET);
    fwrite(buff,sizeof(Tbloc_TOF),1,F.f);
    NbEcrit_TOF++;
}

int Entete_TOF (TOF F, int i)
{
    switch (i)
    {
    case 1:
        return F.entet.nb_bloc;
    case 2:
        return F.entet.nb_enreg;
    default :
        return -1;
    }
}

void Aff_Entete_TOF (TOF *F, int i, int v)
{
    switch (i)
    {
    case 1:
        (*F).entet.nb_bloc=v;
        break;
    case 2:
        (*F).entet.nb_enreg=v;
        break;
    default : ;
    }
}

int Alloc_Bloc_TOF (TOF *F)
{
    Aff_Entete_TOF(F,1,Entete_TOF(*F,1)+1);
    return Entete_TOF(*F,1);
}

