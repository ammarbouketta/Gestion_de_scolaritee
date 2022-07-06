#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include "conio.h"
#include "machine_abstraite_TOF.h"
#include "machine_abstraite_LOVnC.h"
#include "partie1_TOF.h"
#include "partie2_LOVnC.h"
#include "modules_secondaires.h"



int main ()
{

    int rep;
    textcolor(10);
    printf("***********************************************************************************************************************\n");
    printf("                                            Concue et Realise par:                                                     \n");
    printf("                                                BOUKETTA Ammar                                                         \n");
    printf("                              -ESI:Ecole Nationale Superieur d'Informatique EX:INI-                                    \n");
    printf("                                                Promotion:2020                                                         \n");
    printf("***********************************************************************************************************************\n");
    textcolor(9);
    printf("\n\nDans ce TP on a fait une application de Scolarite (Gestion des inscriptions et des notes)");
    printf("\nA  pour but d'adaptation des fichiers textes et binaires et leur manipulation en langage C ");
    textcolor(12);
    printf("\n**REMARQUE:");
    textcolor(15);
    printf("\n Dans cette application on a besoin de la fonction standard 'strtok_r'");
    printf("\n Il y a certain versions de code_blocks qui ne contient pas cette fonction");
    printf("\ndonc on était obligee de l'implementer dans partie2_LOVnC");
    textcolor(12);
    printf("\nSi ses instructions n'est pas respecte le comportement de l'application est indefini\n");
    printf("\n\n");

     printf("\n Click on entrer pour voir le menu :\n");
     if (getchar())
        system("cls");
    do
     {
        textcolor(12);

        printf("\n=================== 'PARTIE 01' : ===================================================================================\n");
        printf("                     =========  ");
        textcolor(15);
        printf("\n1-Chargement initial du fichier 'NOTE.bin',et affichage si vous voullez .");
        printf("\n2-Nettoyage du fichier 'NOTE.bin'.");
        printf("\n3-Reorganisation du fichier 'NOTE.bin',et affichage si vous voullez .");
        printf("\n4-Creation du fichier 'TP.txt'.");
        printf("\n5-Mise-a-jours des notes des etudiants (/15) et affichage si vous voullez .");
        textcolor(12);
        printf("\n=================== 'PARTIE 02' : ===================================================================================\n");
        printf("                     =========  ");
        textcolor(15);
        printf("\n6-Chargement initial du fichier 'NOTES_FINALES'.");
        printf("\n7-Mise_a_jours des notes des etudiants(/20).");
        printf("\n8-Insertion d'un nouveau etudiant dans 'NOTE_FINALES.bin'");
        printf("\n9-Suppression d'un etudiant du fichier 'NOTES_FINALES.bin'.");
        printf("\n10-Consultation des etudiant ayant une note inferieur a dix.");
        printf("\n11-Consultation des etudiant ayant une note inferieur a la note eleminatoire.");
        printf("\n12-Affichage de l''entete du fichier 'NOTE_FINALES.bin' et des trois premiers blocs.");
        printf("\n13-Comparaison de la performance des structures TOF et LOVnC.");
        printf("\n14-Sortir de l'application.");
        printf("\n\n");
        textcolor(9);
        printf("\nENTRER LE NUMERO DE VOTRE CHOIX: ");
        scanf("%d",&rep);
         system("cls");
        switch (rep)
        {
        case 1:
            textcolor(13);
            printf(" \n *** Votre choix est : Chargement initial du fichier 'NOTE.bin',et affichage si vous voullez . \n");
            textcolor(15);
            CHARGEMENT_INITIAL_TOF();
            textcolor(10);
            printf("\n** Le chargement initial est terminee **\n");
            textcolor(15);
            break;
        case 2:
    textcolor(13);
            printf(" \n *** Votre choix est : netoyage de fichier . \n");
            textcolor(15);
                NETTOYAGE_TOF();
            textcolor(10);
            printf("\n** Le netoyage est terminee **\n");
            textcolor(15);
         break;
        case 3:
            textcolor(13);
            printf(" \n *** Votre choix est : reorgansation de fichier . \n");
            textcolor(15);
               REORGANISATION_TOF("NOTES.bin");
            textcolor(10);
            printf("\n** La reorganisation est terminee **\n");
            textcolor(15);

            printf("\nEst ce que vous voullez afficher la strecture APRES le netoyage  : (1 pour oui ; 0 pour non ) : ");
            scanf("%d",&rep);
            if (rep==1)
               AFFICHER_TOF();
            break;
        case 4:
            textcolor(13);
            printf(" \n *** Votre choix est : Creation du fichier 'TP.txt'. \n");
            textcolor(15);
                CREATION_TXT();
            textcolor(10);
            printf("\n** La Creation du fichier 'TP.txt' est terminee **\n");
            textcolor(15);

            break;
        case 5:
            textcolor(13);
            printf(" \n *** Votre choix est : Mise-a-jours des notes des etudiants (/15)  . \n");
            textcolor(15);
               MISE_A_JOURS_TOF();
            textcolor(10);
            printf("\n** Mise-a-jours des notes des etudiants (/15) est terminee **\n");
            textcolor(15);

            printf("\nEst ce que vous voullez afficher la strecture APRes le MISE A JOUR : (1 pour oui ; 0 pour non ) : ");
            scanf("%d",&rep);
            if (rep==1)
               AFFICHER_TOF();
            break;
        case 6:
                        textcolor(13);
            printf(" \n *** Votre choix est : Chargement initial du fichier 'NOTES_FINALES'.\n");
            textcolor(15);
               CHARGEMENT_INITIAL_LOVnC();
            textcolor(10);
            printf("\n** Chargement initial du fichier 'NOTES_FINALES' est terminee **\n");
            textcolor(15);

            printf("\nEst ce que vous voullez afficher la strecture  : (1 pour oui ; 0 pour non ) : ");
            scanf("%d",&rep);
            if (rep==1)
               AFFICHER_LOVnC();

            break;
        case 7:
                         textcolor(13);
            printf(" \n *** Votre choix est : Mise_a_jours des notes des etudiants(/20). \n");
            textcolor(15);
              MISE_A_JOUR_LOVnC();
            textcolor(10);
            printf("\n** Mise_a_jours des notes des etudiants(/20)est terminee **\n");
            textcolor(15);
              printf("\nEst ce que vous voullez afficher la strecture apres les mises a jour  : (1 pour oui ; 0 pour non ) : ");
            scanf("%d",&rep);
            if (rep==1)
               AFFICHER_LOVnC();

            break;
        case 8:
            textcolor(13);
            printf(" \n *** Votre choix est : Insertion d'un nouveau etudiant dans 'NOTE_FINALES.bin'. \n");
            textcolor(15);
              INSERTION_LOVnC();
            textcolor(10);
            printf("\n** Insertion d'un nouveau etudiant dans 'NOTE_FINALES.bin' est terminee **\n");
            textcolor(15);
             printf("\nEst ce que vous voullez afficher la strecture apres l'insertion d'un enreg  : (1 pour oui ; 0 pour non ) : ");
            scanf("%d",&rep);
            if (rep==1)
               AFFICHER_LOVnC();
            break;
        case 9:
              textcolor(13);
            printf(" \n *** Votre choix est : Suppression d'un etudiant du fichier 'NOTES_FINALES.bin'. \n");
            textcolor(15);
            SUPPRESSION_LOVnC();
            if(Entete_LOVnC(F2,3)<Entete_LOVnC(F2,4)) REORGANISATION_LOVnC();
            textcolor(10);
            printf("\n** Suppression d'un etudiant du fichier 'NOTES_FINALES.bin' est terminee **\n");
            textcolor(15);
             printf("\n Est ce que vous voullez afficher la strecture apres la suppression d'un enregistrement : (1 pour oui ; 0 pour non ) : ");
            scanf("%d",&rep);
            if (rep==1)
               AFFICHER_LOVnC();
            break;
        case 10:
              textcolor(13);
            printf(" \n *** Votre choix est : Consultation des etudiant ayant une note inferieur a dix. \n");
            textcolor(15);
            CONSULTATION_INFA_DIX();
            textcolor(10);
            printf("\n** Consultation des etudiant ayant une note inferieur a dix est terminee **\n");
            textcolor(15);
            break;
        case 11:
            textcolor(13);
            printf(" \n *** Votre choix est : Consultation des etudiant ayant une note inferieur a la note eleminatoire. \n");
            textcolor(15);
            CONSULTATION_INFA_NE();
            textcolor(10);
            printf("\n** Consultation des etudiant ayant une note inferieur a la note eleminatoire est terminee **\n");
            textcolor(15);
            break;
        case 12:
               textcolor(13);
            printf(" \n *** Votre choix est : Affichage de l''entete du fichier 'NOTE_FINALES.bin' et des trois premiers blocs.  \n");
            textcolor(15);
            AFFICHER_LOVnC_question9();
            textcolor(15);

            break;
        case 13:
            textcolor(13);
            printf(" \n *** Votre choix est : Comparaison de la performance des structures TOF et LOVnC.  \n");
            textcolor(15);
            COMPARAISON_TOF_LOVnC();
            textcolor(10);
            printf("\n** Comparaison de la performance des structures TOF et LOVnC est terminee **\n");
            textcolor(15);

            break;
        case 14:
                printf("                                                                                                                \n");
    printf("                                                                                                                \n");
    printf(" ############     ########## ################## #############              ###############    OOOO              \n");
    printf(" ############     ########## ################## ##############          ##################    OOOO              \n");
    printf(" ############     ########## ####               ####       ####       ####                                      \n");
    printf("  ##### ####       ########  ####               ####        ####     ####                     ####              \n");
    printf("  #####  ####     #### ####  ####               ####        ####    ####                      ####              \n");
    printf("  #####   ####   ####  ####  ####               ####        ####   ####                       ####              \n");
    printf("  #####    #### ####   ####  ####               ####       ####   ####                        ####              \n");
    printf("  #####     #######    ####  ###############    ####      ####    ####                        ####              \n");
    printf("  #####      #####     ####  ###############    ############      ####                        ####              \n");
    printf("  #####       ###      ####  ####               ####    ####      ####                        ####              \n");
    printf("  #####                ####  ####               ####     ####     ####                        ####              \n");
    printf("  #####                ####  ####               ####      ####     ####                       ####              \n");
    printf("  #####                ####  ####               ####       ####     ####                      ####              \n");
    printf("  #####                ####  ####               ####        ####     ####                     ####              \n");
    printf("  #####                ####  ####               ####         ####     ####                    ####              \n");
    printf("  #####                ####  ################## ####          ####      ##################    ####              \n");
    printf("  #####                ####  ################## ####           ####        ###############    ####              \n");
    printf("                                                                                                                \n");

            break;
    default:
            textcolor(4);
            printf("\nChoix invalide!\n");
            textcolor(15);
        }
     }while(rep!=14);
    textcolor(15);
    printf("\nPour signaler les bugs et les erreurs:\n");
    printf("\tja_bouketta@esi.dz\n");
    printf("\n© 2021 Toutes les droits reservees.\n");
    return 0;
}
