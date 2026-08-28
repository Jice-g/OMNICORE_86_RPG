# PROJET OMNICORE 8/6 RPG
### Document de présentation du projet — `docs/RPG_Project.md`
<br>

> **Statut :** document vivant — chantier en cours  

> **Portée :** vue d'ensemble du projet, à l'intersection du jeu de rôle *8/6 Dystopie* et de la plateforme logicielle *OMNICORE 8/6 RPG*  

> **Public :** contributeurs, relecteurs, recruteurs, joueurs et MJ testeurs  

> **Auteur :** Jean-Christophe Gerace *@jicé*  


---
<br>  

## 1. Résumé en une phrase

**OMNICORE 8/6 RPG** est une plateforme applicative multiplateforme (PC et cloud), écrite en C++, permettant de jouer à distance au système de jeu de rôle sur table *8/6 Dystopie* — dans l'esprit de Roll20, mais pensée et optimisée dès sa conception pour ce seul système de règles plutôt que comme un outil générique.
*8/6 Dystopie* est un système de jeu de rôle générique et modulaire original, détaillé dans `docs/BookOfRules`.
Création indépendante, design conçu et développé par *Jicé*
<br> <br> 
## 2. Double ambition du projet

Ce dépôt sert deux objectifs assumés simultanément, et c'est un choix de conception à part entière plutôt qu'un compromis :

1. **Un objectif de formation et de démonstration technique.** Le projet sert de terrain d'apprentissage et de vitrine pour une alternance en développement logiciel / DevOps : architecture C++ propre, pratiques de génie logiciel (tests, CI, documentation, gestion de versions), et un dépôt public lisible par un recruteur en quelques minutes.
2. **Un objectif de création et de commercialisation.** *8/6 Dystopie* est un jeu de rôle sur table à part entière, conçu pour être publié et joué en dehors de tout support numérique. OMNICORE en est l'interface d'accompagnement, pas une dépendance : le jeu doit rester jouable avec une feuille de personnage papier et des dés physiques.

Ces deux ambitions ne sont pas concurrentes : chaque brique du logiciel (moteur de règles, gestion des fiches, cartes) est aussi une pièce de portfolio et une pièce de produit.
<br><br>
## 3. Le jeu : 8/6 Dystopie
  
  
*8/6 Dystopie*  

- Né d'un constat simple : les tables de jeu de rôle ont des habitudes, des réflexes, des systèmes qu'elles connaissent et aiment déjà — et il n'était pas question de leur en imposer un de plus qui les oblige à tout réapprendre.  
- Mon ambition de départ n'était donc pas d'inventer une nouvelle règle pour elle-même, mais de concevoir une règle générique et modulaire, pensée dès l'origine pour jouer des aventures dans n'importe quel univers, en reprenant ce que les systèmes existants — D&D et ses héritiers, Open D6, les règles en D100, FATE — font le mieux, et en les faisant cohabiter dans un seul moteur simple, cohérent et adaptable.
- Le système n'est spécifique à aucun genre en particulier.
- Le Maître de Jeu y reste ce qu'il a toujours été dans un bon jeu de rôle sur table : un conteur, un metteur en scène et un arbitre, qui détient les clés du monde et fait vivre les intrigues auxquelles ses joueurs et joueuses seront confrontés.  
  
La règle est là pour le servir, pas pour se substituer à lui : elle propose une mécanique de résolution simple et un cadre de création de personnage riche, mais laisse la table libre de la façon dont elle raconte ce qui s'y joue.
C'est cette exigence de simplicité au service du récit, conjuguée à une architecture pensée en blocs (attributs, compétences, univers) qui peuvent être ajoutés, retirés ou adaptés sans jamais déséquilibrer l'ensemble, qui a guidé chaque choix de conception du système - du moteur de dés jusqu'à la gamme de livrets d'univers qui l'accompagne. Ce dont j'avais besoin c'était une règle rassemblant de manière structurée et cohérente un ensemble de concepts de jeu qui correspondent à ce qu'on peut attendre à la fois, de mieux, de fluide, de source narrative et de modularité. 

*Principes de la règle D8/6 Dystopie*
- **Moteur de résolution :** 1D6 + 1D8 + Attribut + Compétence + Spécialisation, contre un Niveau de Difficulté. Le D6 porte les mécaniques d'Avantage/Désavantage (via un dé de D8 additionnel, cf. règles), le D8 porte la dimension narrative et les jets de Chance pure.
- **Personnage :** attributs littéraux (identité, Aspects) + attributs numériques (Physique, Dextérité, Esprit, Perception, Sociabilité, Chance, et des attributs optionnels selon l'univers — Pouvoir, Neuro-connexion).
- **Combat :** géré par gestion de ressources (points de Manœuvre) et un système de Blessures plutôt qu'une simple jauge de points de vie, avec une échelle de gravité unique (Légère / Modérée / Grave / Critique) commune à la Résistance Physique et au Stress Mental.
- **Narration :** Points de Destin, Compels et invocation d'Aspects, dans la filiation de FATE, articulés avec le moteur de dés.
- **Modularité :** le socle de règles est indépendant de l'univers joué ; une gamme de livrets de Compétences par Univers (Médiéval, Horreur lovecraftienne, Contemporain, Cyberpunk au lancement) permet de décliner le système sans le réécrire, chacun avec ses propres règles de *Do It Yourself*.
- **Ressource Financière (RF) :** gestion abstraite de la richesse (jauge 0–25, achats exprimés en Niveaux de dépense, avec érosion journalière, encaissement...), pour éviter la comptabilité de pièces au profit du rythme de jeu.

Le détail complet des règles, exemples de jeu et tables de référence vit dans `docs/BookOfRules` (à rédiger dans la suite de ce travail) et dans le Mémo du joueur / écran du MJ qui en seront dérivés.
  
  
  ## 4. Le logiciel : OMNICORE
<br>
### 4.1 Positionnement

OMNICORE n'ambitionne pas de remplacer les outils de table virtuelle génériques (Roll20, Foundry VTT...). Il en reprend l'usage central — jouer à distance autour d'une table virtuelle — mais renonce délibérément à la généricité au profit d'une intégration native avec les règles de *8/6 Dystopie* : calculs dérivés automatiques, gestion du pool de dés D6/D8, suivi des jauges (RP, RM, MNV, PDD, RF) directement liés au moteur de règles plutôt que simulés par des scripts génériques.  

Toutefois la V1, se limitera à développer, tester et stabiliser la gestion des univers, des campagnes, des équipement et de la création de feuilles de personnage.
<br><br>
### 4.2 Périmètre fonctionnel (V1)

| Domaine | Fonctionnalités visées |
|---|---|
| **Univers** | Création, chargement, modification, duplication, archivage ; bibliothèques (compétences, spécialisations, équipements, créatures, archétypes) |
| **Campagnes** | Création, chargement et gestion, rattachées à un Univers ; journal, documents |
| **Feuilles de personnage** | Création guidée (attributs, compétences, spécialisations), calcul automatique des dérivés, suivi de jauges en jeu |
| **PNJ et créatures** | Gabarits à trois niveaux de détail (figurant, secondaire, principal), bibliothèque réutilisable entre campagnes |
| **Bloc-notes** | Notes de MJ (privées) et de joueurs (partagées ou non), liées aux personnages, lieux ou sessions |  
  
  
### 4.3 Périmètre à prévoir (roadmap V2 et V3)

| Domaine | Fonctionnalités visées |
|---|---|
| **Comptes utilisateurs** | Création, authentification, gestion de profil |
| **Profil utilisateur** | Association entre un profil utilisateur user_n et un personnage Character (PJ) ou la fonction de Maître de jeu |
| **Jets de dé ** | Test sur Compétence 1D6+1D8 (Attribut + Compétence + Spécialisation vs Niveau de Difficulté) et chance pure (D8)
| **Cartes** | Import et affichage de cartes, marqueurs de position, outils de mesure adaptés au mode « simplifié » et au mode « battle-map » des règles |
| **Moteur de résolution** | Lancers de dés intégrés (1D6+1D8, gestion des pools d'Avantage/Désavantage en D8 et jet de chance pure (D8), application automatique des modificateurs de personnage |
<br><br>


### 4.4 Architecture — principes directeurs

- **Séparation stricte Domaine / Infrastructure / Interface**, pour que le moteur de règles (`RuleEngine`) reste testable et portable indépendamment du rendu graphique ou du réseau.
- **Le moteur de règles comme brique isolée et réutilisable**, découplée de la persistance (Repository, Serialization, Persistence) et de la présentation, afin de pouvoir l'exposer plus tard via une API si le besoin d'intégrations tierces apparaît.
- **Modèle de domaine aligné sur le vocabulaire du jeu** : `Entity`, `Actor`, `Character`, `Skill`... reflètent directement les concepts du `BookOfRules`, pour que le code reste lisible à la lumière des règles et vice-versa.
- **Cible cloud et PC dès la conception**, sans réécriture ultérieure prévue : la couche domaine ne doit dépendre d'aucune hypothèse de déploiement.

Le détail des choix techniques (langage, framework UI, stratégie de persistance, stratégie réseau/temps réel) est développé dans `docs/Architecture` et les arbitrages successifs sont tracés dans `docs/Decisions`.
<br><br>
  
## 5. Arborescence du dépôt

```
OMNICORE_86_RPG
│
├── licence
├── docs
│     ├── RPG_Project        		← ce document
│     ├── BookOfRules        		← règles complètes du jeu
│     ├── Specifications     		← cahier des charges fonctionnel détaillé
│     ├── Vision             		← intentions produit et design, long terme
│     ├── Domain              		← modèle de domaine (glossaire, entités, relations)
│     ├── ArchitecturePrinciples	← principes fondateurs de l'architecture logicielle
│     ├── Architecture        		← choix techniques et structure logicielle
│     ├── Decisions           		← journal des décisions (ADR)
│     └── Roadmap             		← jalons et priorisation
│
├── assert                    ← ressources (images, cartes, icônes...)
├── tests                     ← tests unitaires et d'intégration
├── debug                     ← outils et configurations de debug
│
├── include
│    └─ Omnicore
│        ├─── Domain
│        │      ├── RuleEngine
│        │      ├── Entity
│        │      ├── Actor
│        │      ├── Character
│        │      ├── Skill
│        │      └── ...
│        │
│        ├── Services
│        │      ├── Repository        ← façade typée métier (LoadSkillCatalog, SaveCampaign...)
│        │      └── UniverseLoader    ← orchestrateur du cycle de chargement (§5 Architecture.md)
│        │
│        └── Infrastructure
│               ├── Persistence       ← lecture/écriture fichiers, seule couche à toucher le disque
│               └── Serialization     ← conversion Objet domaine ⇄ JSON/CSV
│
├── src
│    └─ Omnicore
│       ├─── Domain
│       │      ├── RuleEngine
│       │      ├── Entity
│       │      ├── Actor
│       │      ├── Character
│       │      ├── Skill
│       │      └── ...
│       │
│       ├── Services
│       │      ├── Repository        ← façade typée métier (LoadSkillCatalog, SaveCampaign...)
│       │      └── UniverseLoader    ← orchestrateur du cycle de chargement (§5 Architecture.md)
│       │
│       └── Infrastructure
│              ├── Persistence       ← lecture/écriture fichiers, seule couche à toucher le disque
│              └── Serialization     ← conversion Objet domaine ⇄ JSON/CSV
│
├── .gitignore
├── CMake
├── CHANGELOG.md
├── Engineering_Manifesto.md
└── README.md
```
Cette organisation sépare volontairement le domaine métier du reste dès la V1, même si les couches Infrastructure et Interface ne sont pas encore matérialisées dans l'arborescence — elles viendront s'ajouter à côté de `Domain` (par exemple `include/UI`, `include/Network`) sans avoir à réorganiser le cœur de règles.
  
 <br><br> 
## 6. Documentation associée

Ce document est le point d'entrée ; il renvoie vers les documents suivants, à consulter selon le besoin :

| Document | Contenu |
|---|---|
| `BookOfRules` | Règles complètes du jeu, synthétisée |
| `Specifications` | Cahier des charges fonctionnel — cas d'usage, écrans, règles de gestion logicielles à partir du `BookOfRules` |
| `Vision` | Intentions à long terme, positionnement, valeurs du projet |
| `Domain` | Modèle de domaine — glossaire partagé entre règles du jeu et code |
| `ArchitecturePrinciples` | Principes fondateurs de l'architecture logicielle |
| `Architecture` | Choix techniques, découpage en couches, diagrammes |
| `Decisions` | Journal des décisions d'architecture et de design (ADR) |
| `Roadmap` | Jalons, priorisation, état d'avancement |
  
<br><br> 
## 7. Feuille de route immédiate
<br><br>
<br><br>
    
## 8. Licence et philosophie

Le dépôt est destiné à une publication en logiciel libre dès les premières versions fonctionnelles, à la fois pour servir de démonstration ouverte et pour amorcer un développement communautaire autour du moteur de règles. Les conditions précises seront fixées dans `licence` à la racine du dépôt.

---
<br><br>
*Document rédigé dans le cadre du projet OMNICORE 8/6 RPG — double ambition d'apprentissage technique (C++/DevOps) et de création ludique (jeu de rôle 8/6 Dystopie).*
