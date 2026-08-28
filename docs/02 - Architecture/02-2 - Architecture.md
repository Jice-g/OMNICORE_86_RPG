# ARCHITECTURE — OMNICORE 8/6 RPG
### Document technique — `docs/Architecture/Architecture.md`
<br>

> **Statut :** document vivant — chantier en cours

> **Portée :** choix techniques, découpage en couches, diagramme de domaine, analyse minimale Persistence / Serialization / Repository

> **Public :** contributeurs, relecteurs, recruteurs

> **Dépend de :** `ArchitecturePrinciples.md` (principes, stables) — ce document en est la **traduction concrète en couches et classes**, il ne redéfinit aucun principe.

---
<br>

## 1. Objectif

`ArchitecturePrinciples.md` fixe les règles de conception (ce qui ne doit *pas* changer). Ce document répond à une question différente : **où en est-on concrètement**, quelles couches existent, quelles classes sont déjà modélisées, et où va-t-on pour ce qui n'est pas encore tranché — en particulier la chaîne Persistence / Serialization / Repository, qui n'a pour l'instant qu'une définition minimale dans `Domain.md` (§9).

Ce document n'est **pas** une conception détaillée de la persistance. C'est un état des lieux, volontairement minimal, pour que les décisions à venir (walking skeleton, spikes) aient un cadre à respecter plutôt que d'improviser leur propre architecture au fil du code.

<br>

## 2. Les couches — rappel et état d'implémentation

Rappel de `RPG_Project.md` §4.4 (Principe 8 — Dépendances orientées) :

```
Interface utilisateur
        │
Application
        │
Services            ← Repository (façade), UniverseLoader
        │
Domain               ← Entity, Actor, Character, Skill... (ce diagramme)
        │
Infrastructure       ← Persistence, Serialization
```

| Couche | Contenu prévu | État |
|---|---|---|
| **Domain** | `Entity`, `Actor`, `Character`, `Creature`, `Skill`, `Item`... | Modélisé (diagramme §3), pas encore codé |
| **Services** | `Repository` (façade métier typée), `UniverseLoader` (orchestrateur de chargement) | Nommé dans l'arborescence cible, non conçu |
| **Infrastructure** | `Persistence` (lecture/écriture disque), `Serialization` (conversion objet -> JSON/CSV) | Nommé dans l'arborescence cible, non conçu |

Le sens de lecture du tableau ci-dessus est important : le Domain est stable et documenté en détail ; tout ce qui touche à la persistance est volontairement laissé au milieu, en attente du retour d'expérience des spikes (§5).

<br>

## 3. Modèle de domaine — diagramme de classes

![Schema_UML](../../assert/Art_Design/Architecture/omnicore_domain_uml.svg)

Source PlantUML : [`OMNICORE_Domain_UML.puml`](./OMNICORE_Domain_UML.puml), dans ce même dossier.

Le contenu métier de ce diagramme (attributs, relations, cardinalités) est détaillé et commenté classe par classe dans `docs/Domain.md` — ce document-ci n'en donne que la vue d'ensemble visuelle.

> 🟠 **Correction apportée à l'export.** Le fichier source `OMNICORE_UML_Diagramme_V2_6.md` utilise la syntaxe `class X : Y { }` pour l'héritage (ex. `class MediaAsset : Entity`). Cette syntaxe n'est pas reconnue par le moteur PlantUML utilisé pour le rendu (v1.2024.7) — elle produit une erreur de parsing silencieuse au-delà de la première occurrence (ligne 93). Corrigé en `class X extends Y { }`, syntaxe équivalente et supportée, sur les 9 occurrences du fichier (`MediaAsset`, `Item`, `Equipment`, `Armor`, `Tool`, `Weapon`, `Faction`, `Character`, `Creature`). Le fichier `.puml` versionné ici contient la version corrigée ; le `.md` d'origine reste inchangé sous ce nom, à mettre à jour séparément si cette syntaxe doit rester la référence.

<br>

## 4. Analyse minimale — Persistence / Serialization / Repository

Objectif de cette section : poser les responsabilités et les frontières, pas les signatures. Le détail (interfaces, formats de fichiers, gestion d'erreurs) reste au niveau spike/pseudo-code, pas ici.

### 4.1 Trois responsabilités distinctes, trois couches

| Composant | Couche | Répond à la question | Connaît |
|---|---|---|---|
| **Repository** | Services | *Quoi* charger/sauvegarder (vocabulaire métier) | Le Domain (types retournés), pas le format fichier |
| **Serialization** | Infrastructure | *Comment* convertir un objet JSON/CSV | Le Domain (pour construire les objets), le format |
| **Persistence** | Infrastructure | *Où* lire/écrire (disque, chemin, encodage) | Rien du Domain — uniquement des flux d'octets/texte |

Cette séparation découle directement du Principe 7 (le Domain ignore la persistance) et du Principe 8 (dépendances à sens unique) : `SkillDatabase` (Domain) n'a et n'aura jamais de méthode `load()` — c'est `SkillRepository` qui dépend de `SkillDatabase`, jamais l'inverse. C'est déjà acté dans `Domain.md` (§7, note sur `SkillDatabase`) ; cette section ne fait que le formaliser au niveau des couches.

### 4.2 Repository — façade métier

Point d'entrée unique pour le reste de l'application (`Services`, `Application`). Vocabulaire du domaine, pas du fichier :

```
SkillRepository::loadCatalog(path) -> SkillDatabase
SkillRepository::saveCatalog(db, path) -> void
```

Un `Repository` par agrégat racine (`SkillRepository`, `ItemRepository`, `AssetRepository`...), pas un `Repository` générique — cohérent avec Principe 11 (modularité, une responsabilité par sous-système) et avec la mention déjà existante d'`AssetRepository` dans `Domain.md` (§7, chargement des `MediaAsset`).

### 4.3 Serialization — conversion pure

Fonctions de conversion sans effet de bord disque : `json → Skill`, `Skill → json`. Testable indépendamment de tout fichier réel (un `nlohmann::json` construit en mémoire suffit pour un test unitaire).

C'est cette couche qui absorbe la double compatibilité JSON/CSV prévue par le Principe 1, sans que `Repository` ni `Domain` n'aient à savoir lequel des deux formats est utilisé à un instant donné.

### 4.4 Persistence — accès disque

Ouverture de fichier, lecture de flux, gestion des erreurs d'E/S (fichier absent, droits, encodage). Ne construit aucun objet du Domain — fournit du texte brut ou un flux à la couche `Serialization`.

### 4.5 Orchestration — UniverseLoader

Coordonne plusieurs `Repository` pour charger un univers complet (catalogues de compétences, objets, créatures...) dans le bon ordre, avec gestion des dépendances entre catalogues (ex. un `ItemCatalog` qui référence des `Skill` requis doit charger `SkillCatalog` avant). Nommé dans l'arborescence cible (`Services/UniverseLoader`), conception différée — pertinent seulement une fois plusieurs `Repository` réellement codés.

<br>

## 5. Où en est-on — spikes et prochaine étape

Cette analyse reste volontairement à ce niveau de granularité : elle donne un cadre (3 responsabilités, sens des dépendances, un `Repository` par agrégat) sans figer d'interface C++ concrète. Les interfaces réelles (signatures, gestion d'erreurs, choix entre exceptions et codes de retour) seront éprouvées par les spikes de persistance (`PersistSkill_Prototype`, puis `PersistTool_Prototype`, `PersistActor_Prototype`), documentés dans `docs/Decisions/WalkingSkeletonSpike.md`.

Le spike `Skill` a vocation à devenir, une fois stabilisé, la première implémentation réelle de `SkillRepository` — pas un prototype qu'on jette pour recommencer de zéro, mais un brouillon dont la version définitive hérite directement.

**Prochaine étape :** schématisation concrète du spike (UML + pseudo-code), à partir de ce cadre.

<br>

## 6. Documents liés

| Document | Contenu |
|---|---|
| `ArchitecturePrinciples.md` | Principes fondateurs — ce document en est l'application concrète |
| `Domain.md` | Modèle de domaine détaillé, classe par classe |
| `Decisions/WalkingSkeletonSpike.md` | ADR — démarche walking skeleton, spikes de persistance |
| `SkillCatalog.schema.md` | Format JSON de référence pour le premier spike |

---
<br>

*Document technique du projet OMNICORE 8/6 RPG — traduction en couches et classes des principes fixés dans `ArchitecturePrinciples.md`.*
