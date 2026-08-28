# OMNICORE

## Cahier des charges fonctionnel -- Version 1.0

### Gestion des univers, campagnes et feuilles de personnage
<br><br>
  
# 1. Objet du document

Le présent cahier des charges définit les fonctionnalités de la première
version (V1) d'**OMNICORE**, plateforme officielle du système de jeu de
rôle **8/6 Dystopie**.

Cette version constitue le socle fonctionnel de la plateforme.

Elle ne permet pas encore de jouer en ligne, de réaliser des jets de dés
ou d'utiliser une carte interactive. Son objectif est de fournir un
environnement complet de préparation et de gestion des campagnes.  
  
# 2. Objectifs

La version 1 doit permettre :

-   la création et l'administration des univers ;
-   la création et la gestion des campagnes ;
-   la création et la gestion des feuilles de personnage ;
-   le chargement et la conservation de l'ensemble des données liées à une campagne.  
  
# 3. Périmètre

La V1 couvre exclusivement les fonctionnalités de préparation.

Elle ne comprend pas :

-   la gestion des comptes utilisateurs ;
-   moteur de jets de dés ;
-   automatisation des règles ;
-   gestion des combats ;
-   carte interactive ;
-   chat texte ;
-   chat vocal ;
-   visioconférence.

Ces fonctionnalités feront l'objet des versions ultérieures.


# 4. Évolutions prévues — Comptes utilisateur

La V1 ne gère pas de comptes utilisateurs (cf. §3). Le système devra
cependant permettre, dans une version future :

-   la création d'un compte utilisateur ;
-   l'authentification ;
-   l'association entre un compte et son contenu (personnage ou fonction de MJ) ;
-   la modification des informations du profil ;
-   la suppression du compte.

Chaque utilisateur pourra être propriétaire (MJ) ou membre (joueur) de
plusieurs univers et de plusieurs campagnes.

Ce point suppose de prévoir, pour les objets concernés, une propriété
`userId` (ou équivalent) qui restera `NULL` en V1 :

-   `Campaign.ownerId` — le MJ, propriétaire de la campagne ;
-   `Character.userId` — le joueur associé, pour les PJ uniquement.

Cette propriété ne concerne que les entités porteuses d'une notion de
propriétaire ou de membre (campagne, personnage joueur). Elle n'a pas de sens sur les
objets de catalogue (compétences, équipements, créatures...), qui restent
partagés et indépendants de tout utilisateur.
 
  
# 5. Gestion des univers

## Objectif

L'univers constitue le cadre de référence des campagnes.

Il détermine les règles optionnelles disponibles ainsi que les
bibliothèques de contenus utilisables lors de la création des
personnages.

Chaque campagne est obligatoirement rattachée à un univers.

## Fonctionnalités

-   Création d'un univers.
-   Modification d'un univers.
-   Duplication d'un univers.
-   Archivage.
-   Suppression.

## Paramètres

Chaque univers possède notamment :

-   nom ;
-   description ;
-   illustration ;
-   catégorie ;
-   modules de règles activés.

Il référence également les bibliothèques :

-   compétences ;
-   spécialisations ;
-   équipements ;
-   armes ;
-   armures ;
-   objets divers ;
-   créatures ;
-   archétypes.

# 6. Gestion des campagnes

Une campagne représente une partie persistante.

Fonctionnalités :

-   créer ;
-   modifier ;
-   archiver ;
-   supprimer.

Une campagne comporte :

-   nom ;
-   description ;
-   illustrations ;
-   univers associé ;
-   maître de jeu ;
-   liste des joueurs ;
-   PJ ;
-   PNJ ;
-   créatures ;
-   journal ;
-   documents.

# 7. Gestion des personnages

Types de fiches :

-   Personnage Joueur (PJ)
-   Personnage Non Joueur (PNJ)
-   Créature

Actions :

-   créer ;
-   modifier ;
-   dupliquer ;
-   archiver (PJ, PNJ, Créatures) ;
-   supprimer.

# 8. Feuille de personnage

La feuille gère notamment :

-   identité ;
-   illustration ;
-   historique ;
-   attributs ;
-   compétences ;
-   spécialisations ;
-   ressources ;
-   blessures ;
-   états ;
-   équipement ;
-   inventaire ;
-   expérience ;
-   progression.

Les informations affichées s'adaptent automatiquement aux modules actifs
de l'univers.

# 9. Gestion de l'évolution

La plateforme permet :

-   évolution des compétences ;
-   évolution des spécialisations ;
-   gestion des blessures ;
-   évolution de l'expérience ;
-   évolution de l'équipement ;
-   évolution de l'inventaire.

Toutes les modifications sont sauvegardées automatiquement.

# 10. Bibliothèques

Chaque univers dispose de bibliothèques de référence :

-   compétences ;
-   spécialisations ;
-   archétypes ;
-   équipements ;
-   armes ;
-   armures ;
-   objets ;
-   créatures.

# 11. Journal de campagne

Chaque campagne possède un journal comprenant :

-   notes du MJ ;
-   notes partagées ;
-   chronologie ;
-   documents ;
-   illustrations.

# 12. Persistance

La plateforme assure :

-   sauvegarde automatique ;
-   restauration ;
-   archivage ;
-   export des données de campagne.

# 13. Architecture fonctionnelle

``` text
Utilisateur
    └── Univers
        └── Campagnes
            ├── Personnages (PJ)
            ├── PNJ
            ├── Créatures
            ├── Items
            ├── Journal
            ├── Images			
            └── Documents
```

Les personnages appartiennent à une campagne.

Chaque campagne dépend obligatoirement d'un univers.

# 14. Contraintes

La V1 ne comporte aucune fonctionnalité de jeu en temps réel.

Elle constitue exclusivement un outil de préparation, de gestion et de
suivi des campagnes.

Elle doit être conçue pour accueillir ultérieurement :

-   les comptes utilisateurs ;
-   le moteur de règles ;
-   les jets de dés ;
-   les combats ;
-   la carte interactive ;
-   la table virtuelle.

# 15. Livrable attendu

À l'issue de la V1, OMNICORE doit permettre à un maître de jeu de
préparer intégralement une campagne de **8/6 Dystopie**, de créer ses
univers, d'administrer ses campagnes et de gérer toutes les feuilles de
personnage sans recourir à des documents externes.
