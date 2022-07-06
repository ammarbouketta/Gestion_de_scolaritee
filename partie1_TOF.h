#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

Tenreg  GENERER_ENREG       ();
void    RECHERCHE_TOF       (char *cle, char *nom_fichier, int *Trouv, int *i, int *j);
void    INSERTION_TOF       (Tenreg e, char* nom_fichier, int taille_bloc, int repetition);
void    SUPPRESSION_TOF     (char *nom_fichier, int i, int j);
void    REORGANISATION_TOF  ();
int     EXTRAIR_ANNEE       (char *NUM);
int     HASHAGE             (int N, int n);
int     EXISTE_TXT          (char *nom_fichier, char *NUM);
void    AFFICHER_TOF        ();

int nb_etudiants[6][12];

/***QUESTION 01: CREATION DU FICHIER "NOTES.bin" A PARTIR DES DONNEES ALEATOIRES***/
void CHARGEMENT_INITIAL_TOF ()
{
    OUVRIR_TOF(&F1,"NOTES.bin",'N');
    int N;
    printf("\nDonner le nombre des etudiants: ");
    scanf("%d",&N);

    int k;
    Tenreg e;

    for( k=1 ; k<=N ; k++ )
    {
        e=GENERER_ENREG();
        //strcpy(e.NUM,"16/1111");    e.GROUPE=3; e.NOTE=10;
        INSERTION_TOF(e,"NOTES.bin",taille_max_TOF,1);
    }
    //FERMER_TOF(&F1);
}

void NETTOYAGE_TOF()//on supprime les doublons qui ont le meme matricule et on supprime aussi les étudiants des groupes qui ont plus de 25
{
    //OUVRIR_TOF(&F1,"NOTES.bin",'A');
    int i,j,supp,group,annee;

    for( i=0 ; i<6 ; i++){ for(j=0 ; j<12 ; j++) {nb_etudiants[i][j]=0;}}

    for( i=1 ; i<=Entete_TOF(F1,1) ; i++)
    {
        LireDir_TOF(F1,i,&Buff_TOF);
        for( j=0 ; j<Buff_TOF.NB ; j++ )
        {
            do
            {
                supp=0;
                group=Buff_TOF.tab[j].GROUPE-1;
                annee=EXTRAIR_ANNEE(Buff_TOF.tab[j].NUM)-15;

                if(nb_etudiants[annee][group]==25)
                    {
                        SUPPRESSION_TOF("NOTES.bin",i,j);
                        supp=1;
                    }
                else
                {
                    if((j==0 && i>1 && !strcmp(Buff1_TOF.tab[Buff1_TOF.NB-1].NUM,Buff_TOF.tab[j].NUM)) || (j>0 && !strcmp(Buff_TOF.tab[j].NUM,Buff_TOF.tab[j-1].NUM)))
                    {
                        SUPPRESSION_TOF("NOTES.bin",i,j);
                        supp=1;
                    }
                    else nb_etudiants[annee][group]++;
                }
            }while(supp && j<Buff_TOF.NB);
        }
        EcrirDir_TOF(F1,i,&Buff_TOF);
        Buff1_TOF=Buff_TOF;
    }
   // FERMER_TOF(&F1);
}
/***QUESTION 02: CREATION DU FICHIER "TP.txt"***/
void CREATION_TXT()//formant des binome à partir du  fichier NOTE.bin
{
    Tbloc_TOF Buff_TOF;
    Tbloc_TOF Buff1_TOF;

    //OUVRIR_TOF(&F1,"NOTES.bin",'A');
    FILE *f=fopen("TP.txt","w");
    int i,j,i_h,j_h,note;

    for( i=1 ; i<=Entete_TOF(F1,1) ; i++ )
    {
        LireDir_TOF(F1,i,&Buff_TOF);
        if(i==Entete_TOF(F1,1)) i_h=i;
        else i_h=HASHAGE(Entete_TOF(F1,1)-2,i-1)+1;
        LireDir_TOF(F1,i_h,&Buff1_TOF);
        for( j=0 ; j<Buff_TOF.NB ; j++)
        {
            fclose(f);
            if(!EXISTE_TXT("TP.txt",Buff_TOF.tab[j].NUM))
            {
                f=fopen("TP.txt","a");
                fprintf(f,"%s ",Buff_TOF.tab[j].NUM);
                j_h=HASHAGE(Buff1_TOF.NB,j);
                if( i_h==i && j_h==j ) fprintf(f,"%s ","#");// si on a le nombre d'étudiant impair donc on aura un monome
                else fprintf(f,"%s ",Buff1_TOF.tab[j_h].NUM);
                note=rand()%6;
                fprintf(f,"%d\n",note);
            }
            else f=fopen("TP.txt","a");
        }
    }
    fclose(f);
    //FERMER(&F1);
}
/***QUETSION 03: MISE-A-JOURS DU FICHIER "NOTES.bin" A PARTIR DU FICHIER "TP.txt"***/
void MISE_A_JOURS_TOF()
{
    //Tbloc_TOF Buff_TOF;
    //OUVRIR_TOF(&F1,"NOTES.bin",'A');
    FILE *f=fopen("TP.txt","r");

    char NUM1[8],NUM2[8],c='\0';
    int note,Trouv,i,j;

    while(c!=EOF)
    {
        fscanf(f,"%s",NUM1);
        fscanf(f,"%s",NUM2);
        fscanf(f,"%d",&note);
        RECHERCHE_TOF(NUM1,"NOTES.bin",&Trouv,&i,&j);
        if(Trouv)
        {
            LireDir_TOF(F1,i,&Buff_TOF);
            Buff_TOF.tab[j].NOTE+=note;
            EcrirDir_TOF(F1,i,&Buff_TOF);
        }
        if(strcmp(NUM2,"#"))
        {
            RECHERCHE_TOF(NUM2,"NOTES.bin",&Trouv,&i,&j);
            if(Trouv)
            {
                LireDir_TOF(F1,i,&Buff_TOF);
                Buff_TOF.tab[j].NOTE+=note;
                EcrirDir_TOF(F1,i,&Buff_TOF);
            }
        }
        c=fgetc(f);
    }
    fclose(f);
    //FERMER(&F1);

}



