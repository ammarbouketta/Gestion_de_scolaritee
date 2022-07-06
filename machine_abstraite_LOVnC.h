#include <stdlib.h>
#include <stdio.h>
#define taille_max_LOVnC 128

/***LES STRUCTURES DE DONNEES DU FICHIER LOVnC***/
typedef struct
{
    char tab[taille_max_LOVnC];
    int NB;
    int suivant;
}Tbloc_LOVnC;

typedef struct
{
    int tete;
    int queu;
    int nb_enreg;
    int nb_supp_logique;
}Tentet_LOVnC;

typedef struct
{
    FILE *f;
    Tentet_LOVnC entet;
}LOVnC;

/***LES VARIABLES GLOBALES***/
int NbEcrit_LOVnC=0;
int NbLect_LOVnC=0;

LOVnC F2;
Tbloc_LOVnC Buff_LOVnC,Buff1_LOVnC;
/***LES INTERFACES DES MODULES DE LA MACHINES ABSTRAITE DU FICHIER LOVnC***/
int     OUVRIR_LOVnC       (LOVnC *F, char *nom_fichier, char mod );
int     FERMER_LOVnC       (LOVnC *F);
void    LireDir_LOVnC      (LOVnC F, int i, Tbloc_LOVnC *buff);
void    EcrirDir_LOVnC     (LOVnC F, int i, Tbloc_LOVnC *buff);
int     Entete_LOVnC       (LOVnC F, int i);
void    Aff_Entete_LOVnC   (LOVnC *F, int i, int v);
int     Alloc_Bloc_LOVnC   (LOVnC *F);
/***LES IMPLEMENTATION DES MODULES DE LA MACHINE ABSTRAITE DU FICHIER LOVnC***/
int OUVRIR_LOVnC (LOVnC *F, char *nom_fichier, char mod )
{
    if (mod=='a' || mod=='A')
    {
        (*F).f=fopen(nom_fichier,"rb+");
        if ((*F).f==NULL) return 0;
        fseek((*F).f,0,SEEK_SET);
        fread(&((*F).entet),sizeof(Tentet_LOVnC),1,(*F).f);
        return 1;
    }
    if (mod=='n' || mod=='N')
    {
        (*F).f=fopen(nom_fichier,"wb+");
        if ((*F).f==NULL) return 0;
        (*F).entet.tete=0;
        (*F).entet.queu=0;
        (*F).entet.nb_enreg=0;
        (*F).entet.nb_supp_logique=0;
        fseek((*F).f,0,SEEK_SET);
        fwrite(&((*F).entet),sizeof(Tentet_LOVnC),1,(*F).f);
        return 1;
    }
    return 0;
}

int FERMER_LOVnC (LOVnC *F)
{
    fseek(F->f,0,SEEK_SET);
    fwrite(&F->entet,sizeof(Tentet_LOVnC),1,F->f);
    fclose(F->f);
    F->f=NULL;
    return 1;
}

void LireDir_LOVnC (LOVnC F, int i, Tbloc_LOVnC *buff)
{
    fseek(F.f,sizeof(Tentet_LOVnC)+(i-1)*sizeof(Tbloc_LOVnC),SEEK_SET);
    fread(buff,sizeof(Tbloc_LOVnC),1,F.f);
    NbLect_LOVnC++;
}

void EcrirDir_LOVnC (LOVnC F, int i, Tbloc_LOVnC *buff)
{
    fseek(F.f,sizeof(Tentet_LOVnC)+(i-1)*sizeof(Tbloc_LOVnC),SEEK_SET);
    fwrite(buff,sizeof(Tbloc_LOVnC),1,F.f);
    NbEcrit_LOVnC++;
}

int Entete_LOVnC (LOVnC F, int i)
{
    switch (i)
    {
    case 1:
        return F.entet.tete;
    case 2:
        return F.entet.queu;
    case 3:
        return F.entet.nb_enreg;
    case 4:
        return F.entet.nb_supp_logique;
    default :
        return -1;
    }
}

void Aff_Entete_LOVnC (LOVnC *F, int i, int v)
{
    switch (i)
    {
    case 1:
        (*F).entet.tete=v;
        break;
    case 2:
        (*F).entet.queu=v;
        break;
    case 3:
        (*F).entet.nb_enreg=v;
        break;
    case 4:
        (*F).entet.nb_supp_logique=v;
        break;
    default : ;
    }
}

int Alloc_Bloc_LOVnC (LOVnC *F2)
{
    Aff_Entete_LOVnC(F2,2,Entete_LOVnC(*F2,2)+1);
    if(Entete_LOVnC(*F2,1)==0) Aff_Entete_LOVnC(F2,1,Entete_LOVnC(*F2,2));
    return Entete_LOVnC(*F2,2);
}

