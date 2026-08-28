# Architecture Principles

> **OmniCore 86 RPG System**
> Principes fondateurs de l'architecture logicielle  

*« Le code implémente des mécanismes. Les données définissent les univers. Le MJ et les joueurs créent les histoires. »*

---

# 1. Objectif

Ce document définit les principes fondamentaux de conception d'OmniCore.

Contrairement aux diagrammes UML ou à la documentation technique, il ne décrit pas l'implémentation. Il expose les règles de conception qui orientent toutes les décisions architecturales du projet.

Ces principes servent de référence pour :

* garantir la cohérence du moteur dans le temps ;
* faciliter les contributions Open Source ;
* limiter la dette technique ;
* assurer la pérennité du projet.

Ces principes sont considérés comme stables et ne doivent évoluer qu'exceptionnellement.

---

# 2. Philosophie générale

OmniCore est conçu comme un moteur de jeu de rôle générique, indépendant de tout univers particulier.

Le moteur contient les mécanismes du jeu de rôle 8/6 Dystopie seulement. les règles du jeu (cf. BookOfRules)
Le moteur ne contient aucune règle spécifique à un univers de jeu en particulier (medfan, horreur, cyberpunk...). Les règles spéciales, compétences, créatures, équipements et contenus sont décrits sous forme de données externes.

L'objectif est de permettre la création de nouveaux univers sans modification du code source.

Le moteur privilégie :

* la simplicité ;
* la lisibilité ;
* la robustesse ;
* la maintenabilité ;
* l'extensibilité.

---

# 3. Les principes fondamentaux

## Principe 1 — Data Driven

Le comportement du moteur est piloté par des données et non par du code.

Les univers de jeu sont décrits dans des fichiers externes (JSON, CSV ou autres formats d'import).

Le code ne doit jamais contenir de contenu spécifique à un univers.

---

## Principe 2 — Séparation du moteur et des données

Le moteur ne connaît pas les univers.

Les univers ne connaissent pas le moteur.

Le moteur fournit les mécanismes.

Les données définissent le contenu.

Cette séparation permet :

* d'ajouter de nouveaux univers ;
* de modifier les règles ;
* de créer des extensions ;
* de développer des outils indépendants.

---

## Principe 3 — Séparation entre définition et état

Chaque concept métier existe sous deux formes :

* sa définition dans le catalogue ;
* son état dans une partie.

Exemples :

* Skill / ActiveSkill
* Specialization / ActiveSpecialization
* Item / InventoryItem
* CreatureTemplate / Creature

Les définitions sont partagées.

Les états appartiennent exclusivement aux personnages, créatures ou parties.

---

## Principe 4 — Les catalogues sont la référence

Toutes les définitions sont regroupées dans des catalogues.

Exemples :

* SkillCatalog
* ItemCatalog
* CreatureCatalog
* TemplateCatalog

Les catalogues constituent la source officielle des données.

Les objets du domaine ne doivent jamais dupliquer ces informations.

---

## Principe 5 — Les catalogues sont immuables

Les catalogues sont chargés au démarrage.

Une fois validés, ils sont figés (`freeze()`).

Aucune modification ne peut intervenir pendant la partie.

Cette règle garantit :

* la stabilité mémoire ;
* la validité des références ;
* la reproductibilité des sauvegardes.

---

## Principe 6 — Référencement par identifiant stable

Toutes les références utilisent un identifiant fonctionnel stable.

Exemple :

```
combat.melee
weapon.handgun
science.physics
```

Les identifiants ne sont jamais générés automatiquement à l'exécution.

Les noms affichés peuvent changer.

Les identifiants ne changent jamais.

---

## Principe 7 — Les objets métier sont indépendants de la persistance

Les classes métier ne connaissent ni JSON, ni CSV, ni les fichiers.

La sérialisation est assurée par un système dédié.

Le domaine métier reste indépendant des technologies utilisées pour stocker les données.

---

## Principe 8 — Dépendances orientées

Les dépendances doivent toujours aller dans une seule direction.

```
Interface utilisateur
        │
Application
        │
Services
        │
Domain
        │
Infrastructure
```

Les couches basses ne dépendent jamais des couches supérieures.

Cette règle s'applique même en l'absence d'entrée/sortie directe : une classe du domaine ne doit détenir aucun membre dont le type appartient à une couche supérieure, même par simple composition. Exemple concret : `SkillDatabase` (domaine) n'a pas connaissance de `SkillRepository` (persistance) — c'est `SkillRepository` qui dépend de `SkillDatabase`, jamais l'inverse.

---

## Principe 9 — Composition plutôt qu'héritage

Lorsque cela est possible, la composition est privilégiée.

L'héritage est réservé aux véritables relations de spécialisation.

Cette approche améliore la flexibilité du moteur.

---

## Principe 10 — Validation centralisée

Les règles de validation ne sont pas dispersées dans les objets.

Elles sont regroupées dans un moteur de validation unique.

Les objets métier restent simples.

---

## Principe 11 — Modularité

Chaque sous-système possède une responsabilité clairement définie.

Exemples :

* Character System
* Equipment System
* Rule Engine
* Validation Engine
* Serialization
* Persistence
* Catalog System

Chaque module doit pouvoir évoluer indépendamment.

---

## Principe 12 — Architecture extensible

L'ajout d'un nouvel univers, d'une compétence, d'un objet ou d'une créature doit nécessiter uniquement l'ajout de nouvelles données.

Le moteur ne doit pas être modifié pour intégrer du contenu.

---

## Principe 13 — Open Source Friendly

L'architecture est conçue pour faciliter les contributions externes.

Les objectifs sont :

* limiter les conflits Git ;
* favoriser des fichiers lisibles ;
* éviter les dépendances implicites ;
* documenter les décisions importantes.

---

## Principe 14 — Lisibilité avant sophistication

Une architecture simple et compréhensible est préférée à une architecture complexe optimisée prématurément.

Le projet privilégie :

* un code explicite ;
* des responsabilités claires ;
* une documentation abondante.

---

# 4. Les objectifs à long terme

L'architecture doit permettre, sans remise en cause de ses principes :

* l'ajout de nouveaux univers ;
* la gestion de campagnes persistantes ;
* le multijoueur ;
* la synchronisation Cloud ;
* une interface Web ;
* des applications mobiles ;
* des assistants basés sur l'IA ;
* des outils d'édition avancés.

---

# 5. Conclusion

L'objectif d'OmniCore n'est pas uniquement de produire un moteur de jeu de rôle.

Le projet vise à construire une architecture logicielle robuste, modulaire et pérenne, capable d'évoluer pendant de nombreuses années tout en restant simple à comprendre, à maintenir et à enrichir par une communauté Open Source.
