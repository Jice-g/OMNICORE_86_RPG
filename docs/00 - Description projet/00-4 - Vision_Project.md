
# Projet OmniCore_86RPG_System et 86_RPG_Builder


## 1. Vision

OmniCore_86RPG_System est un moteur logiciel modulaire destiné à modéliser des univers ludiques, leurs entités, leurs règles et leurs interactions.
### Le projet est né du besoin :
 * de structurer et d'automatiser la création de personnages pour le jeu de rôle 8/6 Dystopie, mais son architecture vise une portée plus large : fournir un socle générique capable de gérer personnages, créatures, équipements, lieux, factions et systèmes de règles.
 * de créer un dépôt porte-folio pour des recruteurs potentiels, démontrant des compétences d'ingénierie logicielle, d'architecture et d'innovation.
 
Le moteur constitue la source unique de vérité métier et reste indépendant de toute interface utilisateur.
86_RPG_Builder représente la première application utilisant ce moteur.

## 2. Contexte

Le système de jeu 8/6 Dystopie possède :
•	des attributs ;
•	des compétences ;
•	des spécialisations ;
•	des équipements ;
•	des calculs dérivés ;
•	des règles de validation.

La gestion manuelle de ces éléments devient rapidement compliqué quand il s’agit de jouer en distanciel. Une interface tel que ce qui existe sur le marché (comme Roll20 notamment) dédié à 8/6 Dystopie ajouterait à la publication du jeu, une valeur supplémentaire.

Le projet vise à fournir un environnement logiciel permettant :
•	la création assistée ;
•	la validation automatique ;
•	la génération procédurale ;
•	l'exploitation future par des outils numériques,
•	la possibilité future de jouer en réseau à distance.

## 3. Objectifs de la Version 1

La première version du projet a pour objectif de produire un moteur métier fiable et réutilisable.
Fonctionnalités principales :
•	création de personnages ;
•	calcul automatique des caractéristiques dérivées ;
•	validation des règles ;
•	gestion des compétences ;
•	gestion des spécialisations ;
•	gestion des équipements ;
•	gestion des blessures ;
•	sauvegarde et chargement JSON, CSV.

Cette version constitue le socle technique du projet.

## 4. Principes d'Architecture

Le projet repose sur plusieurs principes fondamentaux :
 - Séparation des responsabilités
 - Le moteur métier est totalement indépendant de l'interface utilisateur.
 - Source unique de vérité
 - Toutes les règles sont implémentées dans OmniCore_86RPG_System.
 - Aucune règle métier n'est dupliquée dans les interfaces.
 - Approche Data-Driven
 - Les données métier doivent être définies dans des fichiers externes :
   •	JSON ;
   •	CSV ;
L'objectif est de modifier le contenu sans modifier le code.
Évolutivité
Toute évolution future doit pouvoir être ajoutée sans remise en cause de l'architecture fondamentale.


## 5. Architecture Générale
```
 86_RPG_Builder	== Formulaires < Environnement Windows, Linux, Apple, Mobile, Web (cloud) >
    |
 OmniCore_86RPG_System
    |  
    |── Rules Engine
    |── Validation Engine
    |── Character System
    |── Creature System
    |── Equipment System
    |── Template System
    |── Serialization
```

Le Builder constitue une interface utilisateur.
Le Core constitue le moteur métier.


## 6. Technologies Cibles

Core
 •	C++

Interface Desktop Windows
 •	C#
 •	.NET
 •	Qt
 
ou autre dans divers environnements

Persistance
 •	JSON
 •	CSV

Gestion de version
 •	Git
 •	GitHub

Tests
 •	Framework de tests unitaires C++


## 7. Vision Long Terme

Le projet est conçu pour évoluer progressivement.
Étape 1
Moteur de création de personnages.
Étape 2
Gestion complète des créatures, équipements et templates.
Étape 3
Déploiement en réseau avec profils utilisateurs.
Étape 4
Gestion des jets de dé, actions, combats.
Gestion des blessures des états et des Avantages/Désavantages
Gestion interactive entre les utilisateurs
Étape 7
Support WebAssembly.
Étape 6
Application mobile.
Étape 8
Simulation spatiale.
Ajout :
 - cartes ;
 - coordonnées ;
 - déplacements ;
 - portée ;
 - zones d'effet.
Étape 9
Moteur de simulation d'univers.
Gestion :
 - factions ;
 - territoires ;
 - événements ;
 - campagnes.
Étape 4
Intégration d'assistants IA capables de produire :
- personnages ;
- créatures ;
 - équipements ;
 - lieux ;
 - factions ;
 - éléments narratifs.
Les contenus générés devront toujours être validés par le moteur métier.


## 8. Objectifs Pédagogiques

Le projet constitue un support d'apprentissage continu.
Compétences visées :
 - analyse fonctionnelle ;
 - conception logicielle ;
 - architecture logicielle ;
 - programmation orientée objet ;
 - développement C++ ;
 - développement C# ;
 - tests ;
 - Git ;
 - DevOps ;
 - Réseau et infrastruture
 - IA appliquée ;
 - systèmes interactifs.


## 9. Objectifs Professionnels

Le projet sert également de démonstrateur technique pour :
 - l'entrée en Bachelor IT ;
 - la recherche d'alternance ;
 - les projets académiques ;
 - les futurs travaux de niveau Master.

L'objectif n'est pas seulement de produire une application, mais de construire progressivement une plateforme logicielle démontrant des compétences d'ingénierie logicielle, d'architecture et d'innovation.

## 10. Devise du Projet

Construire un moteur robuste, extensible et réutilisable, capable d'évoluer d'un simple générateur de personnages vers une plateforme complète de modélisation, de simulation et de génération de contenu pour univers ludiques et narratifs.


