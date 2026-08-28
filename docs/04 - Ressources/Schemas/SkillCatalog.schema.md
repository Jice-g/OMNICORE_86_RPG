# SkillCatalog Schema

> **OmniCore 86 RPG System**
> Spécification du catalogue des compétences

---

# 1. Objectif

Ce document définit le schéma officiel du **SkillCatalog**.

Il constitue le contrat entre :

* les fichiers de données (`commonskills.json`, `fantasyskills.json`, etc.) ;
* le moteur OmniCore ;
* les outils d'édition (86 RPG Builder) ;
* les futurs convertisseurs CSV / JSON.

L'objectif est de garantir que tous les catalogues de compétences utilisent une structure unique, stable et indépendante de leur univers de jeu.

---

# 2. Principes

Le SkillCatalog est :

* **Data Driven** ;
* indépendant du moteur ;
* indépendant de l'interface graphique ;
* indépendant du système d'exploitation.

Le moteur ne contient aucune compétence codée en dur.

Toutes les compétences sont décrites dans un ou plusieurs catalogues externes.

---

# 3. Structure générale

Chaque fichier de compétences représente un catalogue.

Exemple :

```text
commonskills.json

fantasyskills.json

steamskills.json

cyberskills.json

horrorskills.json
```

Chaque catalogue possède la structure suivante :

```text
SkillCatalog

├── catalog
├── universe
├── version
└── skills[]
```

---

# 4. Métadonnées du catalogue

## catalog

Nom du type de catalogue.

Valeur attendue :

```text
SkillCatalog
```

Cette information permet au moteur de vérifier qu'un fichier correspond bien au type attendu.

---

## universe

Nom de l'univers ou du module auquel appartient le catalogue.

Exemples :

```text
Common

Fantasy

Cyberpunk

ScienceFiction

Horror
```

Cette information est utilisée par le UniverseLoader.

---

## version

Version du schéma.

Exemple :

```text
1
```

Elle permettra de gérer la compatibilité des futures évolutions du format.

---

# 5. Liste des compétences

Le catalogue contient une collection de compétences.

```text
skills[]
```

Chaque élément décrit une compétence complète.

---

# 6. Structure d'une compétence

Chaque compétence possède les propriétés suivantes.

```text
Skill

├── id
├── attribute
├── name
├── description
├── defaultLevel
└── specializations[]
```

---

## id

Identifiant unique et permanent.

Exemple :

```text
sk_phy-athletism-std
```

Contraintes :

* unique dans l'ensemble des catalogues chargés ;
* écrit en anglais ;
* jamais modifié après publication ;
* utilisé lors de la sérialisation.

Cet identifiant constitue la référence officielle de la compétence.

---

## attribute

Caractéristique associée par défaut.

Valeurs possibles :

```text
PHY

DEX

ESP

PER

SOC

CHA

POU

NEU
```

Le Rule Engine pourra exceptionnellement utiliser un autre attribut lorsqu'une règle le prévoit.

---

## name

Nom affiché au joueur.

Exemple :

```text
Athlétisme
```

Cette valeur est localisable.

Elle n'est jamais utilisée comme identifiant interne.

---

## description

Description fonctionnelle de la compétence.

Elle permet :

* l'affichage dans les outils ;
* la génération de documentation ;
* l'aide au MJ.

---

## defaultLevel

Valeur de base attribuée lors du chargement.

Au chargement dans la SkillDatabase : 0

---

## specializations

Collection des spécialisations disponibles pour cette compétence.

Une compétence peut contenir zéro, une ou plusieurs spécialisations.

---

# 7. Structure d'une spécialisation

```text
Specialization

├── id
├── name
├── description
└── defaultLevel
```

---

## id

**Identifiant permanent.**

Exemple :

```text
sp_running

sp_archery

sp_joinery
```

Une spécialisation appartient toujours à une seule compétence.

Son identifiant n'a donc pas besoin d'intégrer le nom de la compétence.
  
**Portée de l'unicité.**
L'unicité du SpecId est garantie uniquement à l'intérieur d'un même Skill.
Un même SpecId peut légitimement apparaître dans plusieurs Skill différents du catalogue — c'est le cas par exemple de compétences génériques (sp_diagnostic, sp_maintenance) réutilisées dans plusieurs domaines techniques.
La résolution d'une spécialisation passe toujours par son Skill parent (ActiveSkill.findSpecialization(specId)), jamais par une recherche globale d'un SpecId isolé.

---

## name

Nom affiché.

Exemple :

```text
Course

Escalade

Natation
```

---

## description

Description destinée au joueur et aux outils.

---

## defaultLevel

Valeur initiale.

Au chargement dans la SkillDatabase : 0

---

# 8. Référencement

Le SkillCatalog constitue la référence officielle des compétences.

Les personnages ne possèdent jamais directement une compétence.

Ils stockent uniquement son identifiant.

Exemple :

```text
Character

↓

ActiveSkill

↓

SkillId

↓

SkillCatalog

↓

Skill
```

Lors du chargement d'une sauvegarde :

* le SkillId est lu ;
* le SkillCatalog retrouve la définition ;
* la référence mémoire est reconstruite.

---

# 9. Validation

Lors du chargement, le Validation Engine vérifie notamment :

* unicité des identifiants ;
* présence des champs obligatoires ;
* validité de l'attribut ;
* cohérence des spécialisations ;
* absence de doublons.

Un catalogue invalide ne peut pas être chargé.

---

# 10. Évolutions

Le schéma est conçu pour rester compatible avec les futures versions du moteur.

De nouveaux champs pourront être ajoutés sans remettre en cause les catalogues existants.

Par exemple :

* tags ;
* coût d'apprentissage ;
* prérequis ;
* niveau maximal ;
* règles particulières ;
* compatibilité avec certains univers.

---

# 11. Exemple simplifié

```text
SkillCatalog

catalog : SkillCatalog

universe : Common

version : 1

skills

    Athlétisme

        Course

        Escalade

        Natation

    Combat

        Mains nues

        Armes courtes

        Armes longues
```

---

# 12. Relations avec l'architecture

Le SkillCatalog est l'une des spécialisations du système générique `Catalog<T>`.

Il est chargé par le `UniverseLoader`, validé par le `ValidationEngine`, puis figé (`freeze()`) avant le début de la partie.

À partir de ce moment, il devient la source de référence unique pour toutes les compétences utilisées par le moteur.
