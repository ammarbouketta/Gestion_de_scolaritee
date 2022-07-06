# Gestion_de_scolaritee(inscription + les notes )
#PARTIE1
    On souhaite effectuer des mises à jour des notes des étudiants dans un fichier nommé « NOTES.bin » contenant pour chaque étudiant : un numéros d’inscription, un numéros de groupe et une note d’interrogation sur 10. En d’autres termes, chaque enregistrement de « NOTES.bin » est constitué des champs : < NUM, GROUPE, NOTE >. Ces mises à jour sont réalisées à partir d’un fichier texte nommé « TP.txt » contenant, sur chaque ligne, le numéro du premier étudiant, le numéro du deuxième étudiant et une note TP à ajouter à la note correspondante dans « NOTES.bin ». Le fichier « NOTES.bin » est organisé selon la méthode TOF : fichier vu comme Tableau, Ordonné selon les valeurs des numéros d’inscription NUM, avec des enregistrements de taille Fixe. Un bloc peut contenir au maximum 20 enregistrements.
    Le programme doit être réalisé en langage C. Il faut utiliser le modèle vu en cours (LirDir, EcrirDir, Entete, Aff_Entete,Ouvrir, Fermer, et Alloc_Bloc). Pour ce faire, il faut traduire ces opérations en langage C. Programmez les modules suivants :
1. Création du fichier « NOTES.bin » : ici, on veut créer des données aléatoires pour remplir la note de l’interrogation sur 10. Chaque enregistrement est composé de trois champs : < NUM, GROUPE, NOTE >. La création du fichier s’appuiera sur un module de chargement initial qui consiste à remplir le fichier avec N enregistrements (N étant un entier à lire, par exemple : 1000, 1500, 2000, etc.). Pour que le chargement initial soit rapide, vous devrez le réaliser avec des valeurs aléatoires comme suit :
    • NUM : Un code aléatoire formé de l’année de la première inscription sur deux caractères entre ’15’ et ’20’ suivi par ’/’ suivi par un nombre sur 4 caractères entre ’0001’ et ’9999’. Exemple, 19/0145. Dans notre cas, on suppose que le nombre des inscrits pour chaque année ne dépasse pas 300.
    • GROUPE : Un numéro aléatoire entre ’1’ et ’12’
    • NOTE : Un nombre réel entre 0 et 10 (ce nombre étant la note du TP).
  Il faut prévoir un traitement de nettoyage de « NOTES.bin » qui consiste à supprimer les enregistrements dans les cas
suivants :
    • NUM : on ne doit pas avoir des numéros d’inscription similaires; les fonctions aléatoires peuvent générer des doublons. Donc, on doit garder un seul étudiant avec le même numéro d’inscription.
    • GROUPE : on ne doit pas avoir des groupes avec plus de 25 étudiants.
2. Création du fichier texte « TP.txt » où chaque ligne contient le numéro du premier binôme, le numéro du deuxième binôme (censés exister dans « NOTES.bin ») et la note TP comprise entre 0 et 5 qui sera ajoutée à la note de l’inter-rogation des deux étudiants par la suite.
3. Réalisation des mises à jours des notes de l’interrogation dans « NOTES.bin » à partir des notes TP de « TP.txt ».
#PARTIE2
Afin de donner au TP un poids similaire à l’interrogation, nous avons décidé de multiplier sa note (entre 0 et 5) par
2. Pour ce faire, on va utiliser le fichier « NOTES.bin » déjà mis à jours et le fichier « TP.txt » et sauvegarder le résultat dans un autre fichier binaire appelé « NOTES_FINALES.bin ». Ce dernier sera organisé selon la méthode LOVC : fichier vu comme Liste, Ordonnée, avec des enregistrements de taille Variables et Sans Chevauchements entre les blocs. La taille d’un bloc est de 128 octets. En plus des champs précédents, chaque enregistrement de «NOTES_FINALES.bin » est constitué de deux caractères pour la taille de l’enregistrement et d’un caractère pour in-diquer si l’enregistrement est effacé logiquement. Les contraintes de la première partie (pas de numéros d’inscription similaires et pas plus de 25 étudiants par groupe) sont maintenues dans cette partie.
Programmez les modules suivants :
4. Création de « NOTES_FINALES.bin » à partir de « NOTES.bin » ayant subi des mises à jour (note entre 0 et 15).
5. Réalisation d’une mise à jour sur les notes de « NOTES_FINALES.bin » à partir de « TP.txt » (pour avoir une note sur 20).
6. Insertion d’un nouvel enregistrement au « NOTES_FINALES.bin », à la suite de la création d’un compte étudiant.
7. Suppression d’un enregistrement donné par le numéro d’inscription.
8. Consultation de tous les étudiants ayant une note inférieure à 10 et tous ceux ayant une note éliminatoire (note élimi-natoire = moyenne des notes * 60%)
9. Affichage de l’en-tête de « NOTES_FINALES.bin », le nombre de LireDir et EcrireDir, ainsi qu’une représentation graphique de l’organisation globale et interne des trois premiers blocs du fichier.
10. Comparaison entre les performances de la structure de « NOTES_FINALES.bin » et de celle de « NOTES.bin » en termes de coût en opération de lecture et écriture de bloc pour la réalisation de l’opération de recherche (facultatif).














