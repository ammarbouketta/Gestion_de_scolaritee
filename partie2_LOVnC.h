
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int     EXTRAIR_CHAINE      (Tenreg e, char *chaine_enreg);
void    RECHERCHE_LOVnC     (char *cle, char *nom_fichier, int *Trouv, int *i, int *j);
float   MOYEN_PROMOTION     ();
static int __FOREGROUND = 0;
void textcolor (int color);

void textcolor (int color)
{
    __FOREGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), color);
}
char *strtok_r (char *s, const char *delim, char **save_ptr)//le meme fonctionnement que strtok
{
  char *end;
  if (s == NULL)
    s = *save_ptr;
  if (*s == '\0')
    {
      *save_ptr = s;
      return NULL;
    }
  /* Scan leading delimiters.  */
  s += strspn (s, delim);
  if (*s == '\0')
    {
      *save_ptr = s;
      return NULL;
    }
  /* Find the end of the token.  */
  end = s + strcspn (s, delim);
  if (*end == '\0')
    {
      *save_ptr = end;
      return s;
    }
  /* Terminate the token and make *SAVE_PTR point past it.  */
  *end = '\0';
  *save_ptr = end + 1;
  return s;
}
/***QUESTION 04: CREATION DE "NOTES_FINALES.bin" A PARTIR DE "NOTES.bin"***/
void CHARGEMENT_INITIAL_LOVnC ()//remplire le fichier NOTES_FINALES  à partir du fichier NOTES.BIN
{
    if( OUVRIR_LOVnC(&F2,"NOTES_FINALES.bin",'N')  )
    {
        Tenreg e;
        int i=1,j=0;
        int p=0,q=0;

        Tbloc_LOVnC Buff_LOVnC;

        Buff_LOVnC.tab[0]='\0';
        Buff_LOVnC.NB=0;
        Buff_LOVnC.suivant=0;

        int longeur;

        char chaine_enreg[taille_max_LOVnC+1];

        for( i=1 ; i<=Entete_TOF(F1,1) ; i++ )
        {
            LireDir_TOF(F1,i,&Buff_TOF);
            for( j=0 ; j<Buff_TOF.NB ; j++ )
            {
                e=Buff_TOF.tab[j];
                longeur=EXTRAIR_CHAINE(e,chaine_enreg);
                if(Buff_LOVnC.NB+longeur<taille_max_LOVnC)
                {
                    strcat(Buff_LOVnC.tab,chaine_enreg);
                    Buff_LOVnC.NB+=longeur;
                    Aff_Entete_LOVnC(&F2,3,Entete_LOVnC(F2,3)+1);
                }
                else
                {
                    q=p;
                    p=Alloc_Bloc_LOVnC(&F2);
                    EcrirDir_LOVnC(F2,p,&Buff_LOVnC);

                    if( q )
                    {
                        LireDir_LOVnC(F2,q,&Buff_LOVnC);
                        Buff_LOVnC.suivant=p;
                        EcrirDir_LOVnC(F2,q,&Buff_LOVnC);
                    }

                    Buff_LOVnC.tab[0]='\0';
                    Buff_LOVnC.NB=0;
                    Buff_LOVnC.suivant=0;

                    strcat(Buff_LOVnC.tab,chaine_enreg);
                    Buff_LOVnC.NB+=longeur;
                    Aff_Entete_LOVnC(&F2,3,Entete_LOVnC(F2,3)+1);
                }
            }
        }
        q=p;
        p=Alloc_Bloc_LOVnC(&F2);
        Buff_LOVnC.NB=strlen(Buff_LOVnC.tab);
        EcrirDir_LOVnC(F2,p,&Buff_LOVnC);

        if( q )
        {
            LireDir_LOVnC(F2,q,&Buff_LOVnC);
            Buff_LOVnC.suivant=p;
            EcrirDir_LOVnC(F2,q,&Buff_LOVnC);
        }

    }
    //FERMER_TOF(&F1);
    //FERMER_LOVnC(&F2);
}

/***QUESTION 05: MISE A JOURS DE "NOTES_FINALES.bin" A PARTIR DE "TP.txt"***/
void MISE_A_JOUR_LOVnC()//avoir une note sur 20 aprés additionement de la note du tp avec l'interro (mise à jour d'aprés fichier text
{
    Tbloc_LOVnC Buff_LOVnC;

    FILE *f=fopen("TP.txt","r");
    if(f!=NULL)
    {
        char cle1[8], cle2[8], note_TP[3],note_ch[3], enreg[taille_max_LOVnC+1],rest[taille_max_LOVnC+1],*champ;
        char c='\0';
        int Trouv,i,j,note,lue;

        lue=fscanf(f,"%s",cle1);
        while(lue!=-1)
        {
            //fscanf(f,"%s",cle1);
            fscanf(f,"%s",cle2);
            fscanf(f,"%s",note_TP);

            RECHERCHE_LOVnC(cle1,"NOTES_FINALES.bin",&Trouv,&i,&j);
            if(Trouv)
            {
                LireDir_LOVnC(F2,i,&Buff_LOVnC);
                strncpy(enreg,Buff_LOVnC.tab+j,Buff_LOVnC.NB-j);
                champ=strtok(enreg,"$");
                champ=strtok(NULL,"$");
                champ=strtok(NULL,"$");
                champ=strtok(NULL,"$");
                champ=strtok(NULL,"$");

                note=atoi(champ)+atoi(note_TP);
                itoa(note,note_ch,10);
                //if(strlen(note_ch)==1) {note_ch[1]=note_ch[0]; note_ch[0]='0'; note_ch[2]='\0';}
                Buff_LOVnC.tab[j+16]=note_ch[0];
                if (strlen(note_ch)==2 && strlen(champ)==2) Buff_LOVnC.tab[j+17]=note_ch[1];
                else if (strlen(note_ch)==2 && strlen(champ)==1)
                {
                    strncpy(rest,Buff_LOVnC.tab+j+17,Buff_LOVnC.NB-j-17);
                    rest[Buff_LOVnC.NB-j-17]='\0';
                    Buff_LOVnC.tab[j+17]=note_ch[1]; Buff_LOVnC.tab[j+18]='\0';
                    Buff_LOVnC.tab[j+1]=Buff_LOVnC.tab[j+1]+1;
                    strcat(Buff_LOVnC.tab,rest);
                    Buff_LOVnC.NB++;
                }
                EcrirDir_LOVnC(F2,i,&Buff_LOVnC);

            }

            RECHERCHE_LOVnC(cle2,"NOTES_FINALES.bin",&Trouv,&i,&j);
            if(Trouv)
            {
                LireDir_LOVnC(F2,i,&Buff_LOVnC);
                strncpy(enreg,Buff_LOVnC.tab+j,Buff_LOVnC.NB-j);
                champ=strtok(enreg,"$");
                champ=strtok(NULL,"$");
                champ=strtok(NULL,"$");
                champ=strtok(NULL,"$");
                champ=strtok(NULL,"$");

                note=atoi(champ)+atoi(note_TP);
                itoa(note,note_ch,10);
                //if(strlen(note_ch)==1) {note_ch[1]=note_ch[0]; note_ch[0]='0'; note_ch[2]='\0';}
                Buff_LOVnC.tab[j+16]=note_ch[0];
                if (strlen(note_ch)==2 && strlen(champ)==2) Buff_LOVnC.tab[j+17]=note_ch[1];
                else if (strlen(note_ch)==2 && strlen(champ)==1)
                {
                    strncpy(rest,Buff_LOVnC.tab+j+17,Buff_LOVnC.NB-j-17);
                    rest[Buff_LOVnC.NB-j-17]='\0';
                    Buff_LOVnC.tab[j+17]=note_ch[1]; Buff_LOVnC.tab[j+18]='\0';
                    Buff_LOVnC.tab[j+1]=Buff_LOVnC.tab[j+1]+1;
                    strcat(Buff_LOVnC.tab,rest);
                    Buff_LOVnC.NB++;
                }
                EcrirDir_LOVnC(F2,i,&Buff_LOVnC);

            }

            c=fgetc(f);
            lue=fscanf(f,"%s",cle1);
        }
    }
}


/***QUESTION 06: INSERTION D'UN NOUVEL ENREGISTREMENT DANS "NOTES_FINALES.bin"***/
void INSERTION_LOVnC()
{
    Tbloc_LOVnC Buff_LOVnC;
    char chaine_enreg[taille_max_LOVnC+1],cle[8];
    int Trouv,i,j,p;
    Tenreg e;

    printf("\nDonner le matricule, le numero du groupe et la note de l'etudiant: ");
    scanf("%s%d%d",e.NUM,&e.GROUPE,&e.NOTE);
    int taille_enreg=EXTRAIR_CHAINE(e,chaine_enreg);
    int annee=EXTRAIR_ANNEE(e.NUM);

    for( i=5 ; i<=11 ; i++){cle[i-5]=chaine_enreg[i];}
    cle[7]='\0';
    p=0;
    RECHERCHE_LOVnC(cle,"NOTES_FINALES.bin",&Trouv,&i,&j);
    if(!Trouv && nb_etudiants[annee-1][e.GROUPE-1]<25)
    {
        int Arret=0,k,taille;
        char rest[taille_max_LOVnC+1],*champ;
        while(!Arret)
        {
            if(i==0)
            {
                p=Entete_LOVnC(F2,2);
                i=Alloc_Bloc_LOVnC(&F2);
                strcpy(Buff_LOVnC.tab,chaine_enreg);
                Buff_LOVnC.NB+=taille_enreg;
                Buff_LOVnC.suivant=0;
                EcrirDir_LOVnC(F2,i,&Buff_LOVnC);
                if(p!=0)
                {
                    LireDir_LOVnC(F2,p,&Buff_LOVnC);
                    Buff_LOVnC.suivant=i;
                    EcrirDir_LOVnC(F2,p,&Buff_LOVnC);
                }
                Arret=1;
            }
            else
            {
                LireDir_LOVnC(F2,i,&Buff_LOVnC);
                rest[0]='\0';
                for( k=j ; k<Buff_LOVnC.NB ; k++)
                {
                    rest[k-j]=Buff_LOVnC.tab[k];
                }

                taille=strlen(chaine_enreg);
                if (j+taille<=taille_max_LOVnC)
                {
                    for( k=j ; k<j+taille ; k++ )
                    {
                        Buff_LOVnC.tab[k]=chaine_enreg[k-j];
                    }


                    if(strlen(rest)>0)
                    {
                        champ=strtok(rest,"$");
                        strcpy(chaine_enreg,champ);
                        strcat(chaine_enreg,"$");
                        champ=strtok(NULL,"$");
                        strcat(chaine_enreg,champ);
                        strcat(chaine_enreg,"$");
                        champ=strtok(NULL,"$");
                        strcat(chaine_enreg,champ);
                        strcat(chaine_enreg,"$");
                        champ=strtok(NULL,"$");
                        strcat(chaine_enreg,champ);
                        strcat(chaine_enreg,"$");
                        champ=strtok(NULL,"$");
                        strcat(chaine_enreg,champ);
                        strcat(chaine_enreg,"$");

                        j=k;
                        EcrirDir_LOVnC(F2,i,&Buff_LOVnC);
                    }
                    else
                    {
                        Buff_LOVnC.tab[k]='\0';
                        Buff_LOVnC.NB+=taille_enreg;
                        EcrirDir_LOVnC(F2,i,&Buff_LOVnC);
                        Arret=1;
                    }
                }
                else
                {
                    Buff_LOVnC.NB=j;
                    EcrirDir_LOVnC(F2,i,&Buff_LOVnC);
                    i=Buff_LOVnC.suivant;
                    j=0;
                }
            }
        }
        Aff_Entete_LOVnC(&F2,3,Entete_LOVnC(F2,3)+1);
    }
    //FERMER_LOVnC(&F2);
}

/***QUESTION 07: SUPPRESSION D'UN ENREGISTREMENT DONNE PAR LE NUMERO D'INSCRIPTION DE "NOTES_FINALES.bin"***/
void SUPPRESSION_LOVnC()//suppresion logique on met le champ effacée à 1
{
    char cle[8];
    textcolor(12);
    printf("\nDonner le matricule de l'etudiant a supprimer: ");
    textcolor(15);
    scanf("%s",cle);
    int Trouv,i,j;
    RECHERCHE_LOVnC(cle,"NOTES_FINALES.bin",&Trouv,&i,&j);
    if(Trouv)
    {
        LireDir_LOVnC(F2,i,&Buff_LOVnC);
        Buff_LOVnC.tab[j+3]='1';
        EcrirDir_LOVnC(F2,i,&Buff_LOVnC);
        Aff_Entete_LOVnC(&F2,4,Entete_LOVnC(F2,4)+1);
        Aff_Entete_LOVnC(&F2,3,Entete_LOVnC(F2,3)-1);
    }
    //FERMER_LOVnC(&F2);
}
/***QUESTION 08: CONSULTAION DES NOTES DES ETUDIANTS***/
//consultation des étudiant qui ont une note inférieur  à 10
void CONSULTATION_INFA_DIX()
{
    //OUVRIR_LOVnC(&F2,"NOTES_FINALES.bin",'A');
    int i,eff,note;
    char chaine_buffer[taille_max_LOVnC+1],*rest,*champ,*NUM;

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
            NUM=champ;
            champ=strtok_r(rest,"$",&rest);
            champ=strtok_r(rest,"$",&rest);
            note=atoi(champ);
            if(!eff && note<10)
            {
                printf("\n%s",NUM);
            }
        }
        i=Buff_LOVnC.suivant;
    }

}
//consultation des étudiant qui ont une note éliminatoire utilisant la moyenne de la promo

void CONSULTATION_INFA_NE()
{
    //OUVRIR_LOVnC(&F2,"NOTES_FINALES.bin",'A');
    int i,eff,note;
    char chaine_buffer[taille_max_LOVnC+1],*rest,*champ,*NUM;

    float NE=MOYEN_PROMOTION()*0.6;

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
            NUM=champ;
            champ=strtok_r(rest,"$",&rest);
            champ=strtok_r(rest,"$",&rest);
            note=atoi(champ);
            if(!eff && note<NE)
            {
                printf("\n%s",NUM);
            }
        }
        i=Buff_LOVnC.suivant;
    }

}
/***QUESTION 09: REPRESENTAION GRAPHIQUE DES TROIS PREMIERS BLOCS DU FICHIER "NOTES_FINALES.bin"***/
void AFFICHER_LOVnC_question9()
{
    //int n=OUVRIR_LOVnC(&F2,"NOTES_FINALES.bin",'A');
    textcolor(14);
    printf("\n LE  CONTENU DE L'ENTETE EST : ");
    textcolor(15);
    printf("\n**1- Tete  : %d",Entete_LOVnC(F2,1));
    printf("\n**2- Queue : %d   ",Entete_LOVnC(F2,2));
    printf("\n**3- Nombre d'enregistrements : %d   ",Entete_LOVnC(F2,3));
    printf("\n**4- Nombre d'enregistrements supprimes loqiquement : %d   ",Entete_LOVnC(F2,4));
    textcolor(14);
    printf("\n\n** LE NOMBRE DE LECTURE ET ECRITURE EST :");
    textcolor(15);
    printf("\n**1- Le nombre de lecture est : %d",NbLect_LOVnC);
    printf("\n**1- Le nombre d'ecriture est : %d",NbEcrit_LOVnC);
    int i,nb_bloc;
    char chaine_bloc[taille_max_LOVnC+1],*rest,*champ,*eff;

    nb_bloc=3;


    for(i=Entete_LOVnC(F2,1) ; i!=0 && nb_bloc!=0 ; i=Buff_LOVnC.suivant , nb_bloc--)
    {
        printf("\nBLOC %d",i);
        LireDir_LOVnC(F2,i,&Buff_LOVnC);
        strcpy(chaine_bloc,Buff_LOVnC.tab);
        rest=chaine_bloc;
        int j=0;
        while((champ=strtok_r(rest,"$",&rest)) && j<Buff_LOVnC.NB)
        {
            j+=atoi(champ);
            eff=strtok_r(rest,"$",&rest);

            champ=strtok_r(rest,"$",&rest);
             if(!strcmp(eff,"0")) printf("\n%s ",champ);
            champ=strtok_r(rest,"$",&rest);
             if(!strcmp(eff,"0")) printf("%d ",atoi(champ));
            champ=strtok_r(rest,"$",&rest);
             if(!strcmp(eff,"0")) printf("%d ",atoi(champ));
        }
    }
}



/***QUESTION 10: COMPARAISON ENTRE LES PERFERMANACES DES FICHIERS TOF ET LOVnC***/
void COMPARAISON_TOF_LOVnC()//comparaison de taux de la recherche dans la strecture TOF et LOVnC
{
    char NUM[8];
    int Trouv_TOF,i_TOF,j_TOF;
    int Trouv_LOVnC,i_LOVnC,j_LOVnC;

    printf("Donner le matricule de l''etudiant a rechercher: ");
    scanf("%s",NUM);
    NbEcrit_TOF=0;  NbLect_TOF=0;
    NbEcrit_LOVnC=0;    NbLect_LOVnC=0;

    RECHERCHE_TOF(NUM,"NOTES.bin",&Trouv_TOF,&i_TOF,&j_TOF);
    RECHERCHE_LOVnC(NUM,"NOTES_FINALES.bin",&Trouv_LOVnC,&i_LOVnC,&j_LOVnC);

    printf("\nTOF:\tTrouv %d\tNumero du bloc %d\tNumero d'enregistrement %d\tNombre de lectures %d\tNombre d''ecritures %d",Trouv_TOF,i_TOF,j_TOF,NbLect_TOF,NbEcrit_TOF);
    printf("\nLOVnC:\tTrouv %d\tNumero du bloc %d\tDeplacement dans le bloc (nombre de caracteres) %d\tNombre de lectures %d\tNombre d''ecritures %d",Trouv_LOVnC,i_LOVnC,j_LOVnC,NbLect_LOVnC,NbEcrit_LOVnC);

}

