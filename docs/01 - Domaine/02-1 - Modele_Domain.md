# Modèle du Domaine — OMNICORE 8/6 RPG
### `docs/Domain.md`


**Objet du document :** ce document définit le modèle conceptuel du domaine métier de l'écosystème OMNICORE 8/6 RPG. Il constitue la référence pour l'architecture logicielle, les diagrammes UML, les schémas JSON, le développement C++, les interfaces utilisateur et les futures extensions IA et simulation.

Le domaine métier est défini ici **en français**. La modélisation technique (classes, objets, framework, code) est implémentée **en anglais**, les commentaires du code seront rédigés **en français**, conformément aux pratiques de l'art. La table de correspondance du §2 fait le lien entre les deux.

---

## Sommaire

1. Principe directeur
2. Présentation du domaine
3. Domaines fondamentaux — Univers et Campagne
4. Entités fondamentales — hiérarchie
5. Les entités en jeu — Character, Creature et leurs propriétés
6. Équipements
7. Faction
8. Génération de contenu
9. Gestion des données
10. Simulation (futur)
11. Relations principales

---

## 1. Principe directeur

Toute donnée du système doit pouvoir être :

- créée manuellement ;
- chargée depuis un fichier ;
- générée procéduralement ;
- générée par IA ;
- validée par OMNICORE ;
- sauvegardée dans un format standard.

Ce principe est la règle fondamentale du modèle de domaine : il s'applique à toute entité décrite dans ce document, et toute nouvelle entité ajoutée au domaine doit pouvoir s'y conformer avant d'être acceptée dans le modèle.

Les entités agissantes sont associées à différentes structures de données selon leur type d'acteur, via un **Gabarit** (`Template`). Les types d'acteurs identifiés à ce stade sont :

- `Character` (PJ, PNJ)
- `Creature`
- `Companion` — une créature dotée d'un propriétaire attaché (règles spécifiques à définir)
- `NPC_IA` — PNJ piloté par IA (règles à développer ultérieurement)

---

## 2. Présentation du domaine

Le système modélise un univers composé :

- d'**entités** (`Entity`) ;
- de **règles** (`Rules`) ;
- de **relations** (`Relations`, `Links`) ;
- de **catalogues** (`Catalog`, `Inventory`) ;
- de **gabarits** (`Template`).

### Glossaire et correspondance logicielle

| Concept métier | Définition | Représentation logicielle cible |
|---|---|---|
| Entité | Objet identifiable de l'univers de jeu possédant une existence propre et pouvant être manipulé par le système. | `Entity` |
| Règle | Principe définissant les contraintes, calculs ou comportements applicables aux éléments du jeu. | `RuleEngine`, `ValidationRule`, `Rule` |
| Relation | Lien existant entre deux ou plusieurs éléments du domaine, décrivant leur interaction ou leur dépendance. | Association UML, référence d'objet, composition, agrégation |
| Catalogue | Collection organisée d'éléments de même nature mise à disposition du système pour la création, la validation ou la génération de contenu. | `Catalog`, `SkillCatalog`, `Inventory`, `CreatureCatalog` |
| Personnage (PJ, PNJ) | Individu doté de caractéristiques, de compétences et d'équipements, capable d'interagir avec l'univers de jeu. Contrôlé par un joueur (PJ) ou par le meneur de jeu (PNJ). | `Character` |
| Créature | Être vivant non humanoïde possédant ses propres caractéristiques, comportements et capacités particulières. | `Creature` |
| Attribut | Caractéristique fondamentale représentant les aptitudes naturelles d'un personnage ou d'une créature. | `Attribute`, `DerivedAttribute` |
| Compétence | Savoir-faire acquis permettant de réaliser des actions ou de résoudre des situations dans un domaine particulier. | `Skill` |
| Équipement | Objet pouvant être porté, utilisé, transporté ou possédé par un personnage ou une créature. | `Item` (classe abstraite) → `Equipment` (classe abstraite, porté/possédé) → `Armor`, `Tool` → `Weapon` |
| Spécialisation | Chaque compétence peut se spécialiser dans un domaine particulier. Par exemple : Informatique > Dev. Logiciel | `Specialization` |
| Blessure | En action et en combat, les personnages encaissent des blessures qui persistent et nécessitent des soins. | `Injury` |
| Faction | Organisation, groupe ou communauté partageant des intérêts, objectifs ou ressources communs. | `Faction` |
| Lieu | Emplacement ou zone de l'univers dans lequel évoluent les personnages, créatures et objets. | `Location` |
| Campagne | Ensemble cohérent de scénarios, de personnages, de lieux et d'événements se déroulant dans un même cadre de jeu. | `Campaign` |
| Univers | Cadre général décrivant le monde de jeu, son contexte, ses règles particulières, son histoire et ses acteurs. | `Universe` |
| Gabarit | Modèle de référence servant à créer ou générer automatiquement des personnages, créatures, équipements, lieux ou autres éléments du jeu. | `Template` |

> **Note de nommage —** le concept « Équipement » se décline en deux niveaux : `Item` (classe abstraite racine — tout objet possédable, dérivée d'`Entity`) et `Equipment` (classe abstraite intermédiaire — tout ce qui se porte/s'équipe, dérivée d'`Item`). `Armor` et `Tool` dérivent d'`Equipment` ; `Weapon` dérive de `Tool` (une arme se manipule comme n'importe quel outil). Cf. §4 et §6.

Toutes les données manipulées par le moteur appartiennent à ce domaine.

---

## 3. Domaines fondamentaux — Univers et Campagne

L'utilisateur commence par sélectionner un **Univers**. Au sein de cet Univers, il peut créer une nouvelle **Campagne** ou charger une Campagne existante. La Campagne constitue alors l'espace de travail principal de l'application et contient l'ensemble des personnages, créatures, lieux, factions, équipements et paramètres de jeu associés.

### Univers — `Universe`

Cadre général du monde simulé.

**Exemples :** Cyberpunk, Science-fiction, Fantasy, Steampunk, Horror, Modern, Generics.

**Responsabilités :**
- Définir les règles actives ;
- Sélectionner les catalogues ;
- Sélectionner les gabarits ;
- Définir les paramètres de génération.

### Campagne — `Campaign`

Représente une campagne ou configuration de jeu.

**Exemple :**
```
Universe: Cyberpunk
Campaigns: [
  "Marseille 2086",
  "Zone Rouge",
  "Dieu des Machines"
]
```

L'Univers fournit les ressources et les règles ; la Campagne contient les instances concrètes créées par l'utilisateur. Quand l'utilisateur charge une campagne, il charge aussi l'Univers correspondant.

```
Campaign
    │
    └── Universe
```

D'un point de vue architecture, cela permet d'écrire :

```
Universe [1] ──── [0..*] Campaign
```

Un même Univers pourra servir de base à plusieurs Campagnes.

**Architecture générale :**

```
Universe
│
├── Catalogs
├── Rules
├── Templates
├── GlobalParameters
│
└── Campaigns
      │
      ├── Actors
      ├── Items
      ├── Locations
      └── Factions
```

**Précision utile :** `Campaign` regroupe l'ensemble des données créées ou utilisées par l'utilisateur : personnages, créatures, factions, lieux, équipements, paramètres, ressources spécifiques. Une campagne constitue l'unité principale de sauvegarde et de chargement du système.

**Représentation physique :** une campagne est stockée sous la forme d'un ensemble structuré de dossiers et de fichiers dédiés.

```
Campaigns/
└── Marseille_2086/
    │
    ├── campaign.json
    │
    ├── actors/
    │   ├── john_doe.json
    │   └── ...
    │
    ├── creatures/
    │
    ├── factions/
    │
    ├── locations/
    │
    ├── items/
    │   ├── inventory1.csv
    │   └── ...
    │
    ├── templates/
    │
    └── generated/
```

---

## 4. Entités fondamentales — hiérarchie

Arbre des dérivations par héritage :

```
Entity (abstraite)
│
├── Actor (abstraite)
│   ├── Character
│   └── Creature
│
├── Item (abstraite)
│   └── Equipment (abstraite)
│       ├── Armor
│       └── Tool
│           └── Weapon
│
├── Faction
│
└── Location
```

> `MediaAsset` n'hérite plus d'`Entity` (décision du 2026-08, cf. §4-bis) — c'est une classe catalogue autonome, au même titre que `Skill`, référencée par les `Entity` mais absente de leur hiérarchie d'héritage.

**Notation utilisée dans ce document :**
- `{ }` — variable structurée (objet unique, composé de plusieurs champs) ;
- `[ ]` — collection (liste d'éléments de même type).

Une propriété combinant les deux, par exemple une liste de `Skill` dont chaque élément porte sa propre liste de `Specialization`, est notée `Skill[ ] ` avec la précision « chaque `Skill` porte `specializations: Specialization[ ] ` » dans sa fiche dédiée (cf. §5), plutôt que par un double crochet.
  
  
### Entité — `Entity`

Classe conceptuelle racine de toutes les entités du jeu. Toute chose identifiable dans le système est une `Entity`. Classe abstraite, non instanciable directement.

**Propriétés communes :**

| Propriété | Champ | Description |
|---|---|---|
| Identifiant | `instanceID` | Identifiant unique |
| Nom | `name` | Nom de l'entité (chaîne de caractères) |
| Description | `description` | Texte de description détaillée |
| Étiquettes | `tags` | Mots-clés de classification libre (type d'item, de personnage ou de créature) |
| Illustration | `portrait` | Référence (par indirection) vers un `MediaAsset` — nullable, jamais un chemin de fichier en dur. Partageable entre plusieurs `Entity`. |
<br>  
  

### Illustration — `MediaAsset` <a id="4-bis"></a>

> **Décision du 2026-08 :** `MediaAsset` **n'hérite plus d'`Entity`** (Principe 9 — composition plutôt qu'héritage). L'héritage précédent donnait à `MediaAsset` des champs sans usage métier clair (`tags`, `description`, et surtout `picture` — une illustration pouvant elle-même pointer vers une illustration, sans limite structurelle). `MediaAsset` est désormais une **classe catalogue autonome**, gérée comme `Skill` : chargée depuis un fichier externe (CSV), identifiée par une clé unique.

Jamais un simple chemin de fichier en dur — c'est le principe d'indirection : plusieurs `Entity` peuvent référencer le même `MediaAsset` sans dupliquer le fichier.

**Propriétés propres :**

| Propriété | Champ | Description |
|---|---|---|
| Identifiant | `name` | **Clé unique** du `MediaAsset` — fait à la fois office de nom et d'identifiant (pas de champ `id` séparé, à la différence de `Skill`/`Specialization`) |
| Type | `kind` | `Portrait`, `Icon`, `Emblem`, `Illustration`, `Map` |
| Chemin | `filePath` | Chemin logique relatif — jamais manipulé comme un handle de fichier ouvert |

Aucune méthode de chargement : le domaine référence, la couche `Persistence` (`AssetRepository`) charge.

🟢 **`MediaAssetDatabase` — décidé (2026-08), différé.** Gestion "à la façon des Skills" confirmée : liste CSV, clé unique = `name`. Structure prévue au simple — un `MediaAssetDatabase` (`Map<String, MediaAsset>`, sur le modèle de `SkillDatabase`) sera conçu au moment de son spike dédié, pas avant.

🟡 *Point encore ouvert :* `name` étant privé, un accesseur (`Name() : String`) est nécessaire pour l'exposer — absent du schéma fourni, ajouté par cohérence avec `Kind()`/`FilePath()`, à confirmer.

  
  
### Acteur — `Actor`

Entité agissante (PJ, PNJ, Créature...). Dérivée de `Entity`. Classe abstraite, non instanciable directement — les valeurs initiales de ses propriétés peuvent être déterminées par un `Template` lors de la création.

**Hérité de `Entity` :** `instanceID``, `name`, `description`, `tags`.

**Propriétés propres :**

| Propriété | Champ | Description |
|---|---|---|
| Contrôleur | `controller` | `playerName`, `gameMaster`, et ultérieurement `aiController` |
| Puissance | `power` | Valeur du pool des attributs de base |
| Niveau | `level` | Valeur totale des points de compétence |
| Morphologie | `morphology { }` | Espèce, modificateurs de taille et de corpulence (cf. §5) |
| Attributs | `attributes { }` | Attributs de base : PHY, DEX, ESP, PER, SOC, CHA — POU, NEU en optionnels |
| Attributs dérivés | `derivedAttributes { }` | Attributs calculés à partir des attributs de base |
| Blessures | `injuries [ ]` | Liste des blessures actives et de leur malus associé |
| Compétences | `activeSkills [ ]` | Liste des compétences actives, chacune portant ses spécialisations |

**Responsabilités :** agir dans le monde ; interagir avec d'autres entités ; utiliser des compétences ; utiliser des équipements.

`Actor` se décline en :
- **Personnage** — `Character` (PJ, PNJ majeur ou mineur)
- **Créature** — `Creature`

Les attributs et les règles applicables ne sont pas strictement identiques entre les deux déclinaisons (cf. §5).

---
  
  
## 5. Les entités en jeu
  
  
### Personnage — `Character`

Représente un individu, PJ ou PNJ (majeur ou mineur). Dérivé de `Actor`.

**Hérité de `Entity` :** `instanceID``, `name`, `description`, `tags`.
**Hérité de `Actor` :** `controller`, `power`, `level`, `morphology`, `attributes`, `derivedAttributes`, `injuries`, `activeSkills`.

**Propriétés propres :**

| Propriété | Champ | Description |
|---|---|---|
| Rôle du personnage | `characterRole` | Archétype narratif : guerrier, magicien, universitaire, villageois... |
| Attributs littéraux | `literalAttributes { }` | Culture, Chemin de vie, Quête, Ombre, Traits [ ] (cf. `BookOfRules` §2.A) |
| Inventaire | `inventory [ ]` | Liste des équipements du personnage (`Item`, toutes sous-classes confondues) |
| Ressource Financière | `finance { }` | Ressource financière abstraite (cf. note ci-dessous) |
| Familiers | `familiars [ ]` | Créatures adoptées — référence non-propriétaire vers des `Actor` |
| Factions | `factions [ ]` | Appartenance(s) — référence non-propriétaire vers des `Faction` |

> **Note — `characterRole` vs `Entity.tags` :** `characterRole` est un champ descriptif narratif (l'archétype du personnage), distinct des `tags` d'`Entity` qui servent au filtrage et à la classification technique par le système (recherche, catalogues, règles conditionnelles). Les deux coexistent délibérément : l'un raconte, l'autre indexe.

> **Note — `finance` :** en V1, ce champ reste volontairement minimal (`totalRessource`, `pay()`, `collect()`) — c'est la vérité de l'UML actuel. Une mécanique plus riche (barème RF ↔ Niveau de dépense, érosion journalière) a été esquissée mais relève de règles de jeu encore à stabiliser ; elle sera reprise dans une prochaine révision du `BookOfRules`, puis redescendra dans ce document et l'UML le moment venu — pas avant.

Les valeurs possibles pour l'ensemble de ces propriétés seront définies dans les règles de personnage (`characterRules`), applicables aux PJ, aux PNJ et, avec des variantes, aux Créatures.


### Attributs littéraux — Litterals

Trame narrative du personnage. Composée par le `Character`.

| Propriété | Champ | Description |
|---|---|---|
| Histoire | `story[9]` | 9 réponses fixes de trame de vie (cf. `BookOfRules` §2.A). Pour l'instant en texte court ; une historisation plus riche (lien vers fichier texte externe) est envisagée mais différée à la phase Persistence. |
| Culture | `culture` | Culture d'origine |
| Chemin de vie | `lifePath` | Parcours narratif |
| Quête | `quest` | Objectif ou motivation narrative |
| Ombre | `darkness` | Part sombre du personnage |
| Traits | `quirks[5]` | Traits de caractère, jusqu'à 5 — même concept que `Creature.quirks` (cf. note ci-dessous) |

> Conformément au `BookOfRules` §2.A.

**Relation :** `Character ┗━ [1] Litterals`

> **Note — `Litterals.quirks` vs `Creature.quirks` :** même concept
> ("Peur du feu", etc.), à deux échelles. Pour un `Character`, un trait
> s'inscrit dans la trame narrative complète (`Litterals`, avec `story`,
> `culture`...) — il peut par exemple découler d'un traumatisme raconté
> dans `story`, , ou comme un aspect psychologique ou social supplémentaire.
> Pour une `Creature`, `quirks` est porté directement (pas de `Litterals` complet) :
> une forme allégée, sans récit associé. Même terme, même mécanique de jeu, appareil narratif différent.
  
  
### Créature — `Creature`

Être vivant non standard. Dérivée de `Actor`.

**Hérité de `Entity` :** `instanceID`, `name`, `description`, `tags`.
**Hérité de `Actor` :** `controller`, `power`, `level`, `morphology`, `attributes`, `derivedAttributes`, `injuries`, `activeSkills`.

**Propriétés propres :**

| Propriété | Champ | Description |
|---|---|---|
| Catégorie | `category` | Volatile, Aquatique, Reptilien, Magique, Spectrale... |
| Armes naturelles | `naturalWeapons [ ]` | Griffes, morsure, queue, souffle... — une créature peut en cumuler plusieurs |

**`naturalWeapons` — chaque élément :**

Chaque élément de `naturalWeapons` est un `Weapon` à part entière (cf. §6) — pas une structure distincte : une griffe, une morsure ou un souffle de feu portent les mêmes propriétés (`att`, `dmg`, `def`, `range`, `specialEffect`, `hands`) qu'une arme d'inventaire. Le souffle de feu d'un dragon, par exemple, se modélise avec `range > 0` et `specialEffect: "brûlure"`.

> **Note — `equiped`/`handled` sur les armes naturelles :** dans la
> majorité des cas, ces toggles hérités de `Equipment`/`Tool` ne sont pas
> utilisés pour les `naturalWeapons` d'une Creature. Ils restent
> toutefois disponibles : Wolverine équipe ses griffes ou pas, un vampire
> a ses crocs rentrés ou sortis, ce peut-être le cas d'une créature quelconque.
> En V1, non exploité. En V2/V3 (jeu en temps réel), pourrait modéliser
> un état "rentré/sorti" pour les armes naturelles à activation
> (griffes, dard, crocs, carapace...).

Certaines Compétences ou `naturalWeapons` sont spécifiques à certaines créatures. Rien n'interdit toutefois de les affecter à un personnage comme un pouvoir spécial (par exemple : Vol, griffes...).

```
Creature
 ├── Morphology (→ species, sizeModifier, massModifier)
 ├── Attributes
 ├── DerivedAttributes
 └── NaturalWeapons (→ Weapon [0..*])
```
  
  
### Morphologie — `Morphology`

Décrit une espèce et ses caractéristiques de taille et de corpulence.

| Propriété | Champ | Description |
|---|---|---|
| Espèce | `species` | Humain, Elfe, Nain, Canin, Félin, Dragon, Cyborg... |
| Modificateur de taille | `sizeModifier` | Entier signé `[-6 ; +6]` |
| Modificateur de corpulence | `massModifier` | Entier signé `[-6 ; +6]` |

**Responsabilités :** bonus naturels ; contraintes biologiques ; règles spécifiques.

**Relation :** `Character/Creature ┗━ [1] Morphology`
  
  
### Attributs — `Attributes`

Caractéristique fondamentale.

**Attributs fixes de base :**

| Attribut | Champ | Description |
|---|---|---|
| PHY | `phy` | Force physique, constitution, vigueur |
| DEX | `dex` | Dextérité |
| ESP | `esp` | Esprit, mental, intelligence |
| PER | `per` | Perception des sens et intuitive |
| SOC | `soc` | Sociabilité, charme, charisme |
| CHA | `cha` | Chance |

**Optionnels :**

| Attribut | Champ | Description |
|---|---|---|
| POU | `pou` | [Univers Fantastique] Sensibilité magique, arcane, foi active |
| NEU | `neu` | [Univers Cyberpunk] Tolérance aux implants, interface réseau |

**Relation :** `Character/Creature ┗━ [1] Attributes`

**Plages de valeurs autorisées** *(extension logicielle de calibration, à valider dans une future révision du `BookOfRules`, qui ne fixe aujourd'hui que la plage `[1;4]` pour les PJ)* :

| Type d'acteur | Plage |
|---|---|
| PJ | `[1 ; 4]` |
| PNJ majeur | `[1 ; 4]` |
| PNJ mineur | `[0 ; 4]` |
| PNJ légendaire / très puissant | `[1 ; 5]` |
| Créature | `[0 ; 6]` |

La distinction entre ces catégories s'appuie sur `Entity.tags` et `Character.characterRole`.
  
  
### Attributs dérivés — `DerivedAttributes`

Valeurs calculées, propres à chaque `Actor`.

| Attribut | Champ | Description |
|---|---|---|
| MNV | `mnv` | Points de Manœuvre : potentiel d'action global par tour de jeu |
| DPL | `dpl` | Capacité de déplacement par tour de jeu |
| RFX | `rfx` | Réflexes et initiative |
| DFP | `dfp` | Défense passive (calculée à partir de RFX) |
| RP | `rp` | Résistance Physique : capacité à encaisser des dommages physiques |
| RM | `rm` | Résistance Mentale : capacité à encaisser des chocs psychologiques |

Calculés par le `RuleEngine` : `Actor::calculateDerivedAttributes()` ne fait pas le calcul elle-même, elle délègue à une fonction statique du moteur de règles (ex. `RuleEngine::DerivedAttributes(attributes, universeTag)`). Appelée par le constructeur et à chaque modification des attributs de base.

**Relation :** `Character/Creature ┗━ [1] DerivedAttributes`
  
  
### Blessures — `Injury`

| Propriété | Champ | Description |
|---|---|---|
| Libellé | `tag` | Libellé de la blessure |
| Gravité | `severity` | Légère, Modérée, Grave, Critique |
| Malus | `penalty` | −1 ; −2 ; −3 ; −5 |

Correspondre exactement à l'échelle unifiée du `BookOfRules` §8 (valable indifféremment pour RP et RM).

**Relation :** `Character/Creature ┗━ [0..*] Injury`
  
  
### Compétence — Skill (catalogue)

Modèle de référence d'une compétence, tel qu'il existe dans le `SkillDatabase`.
Immuable une fois inséré, partagé par tous les Actors qui la pratiquent.

| Propriété | Champ | Description |
|---|---|---|
| Identifiant | `skillId` | Identifiant unique de la compétence dans le catalogue |
| Libellé | `name` | Nom de la Compétence |
| Attribut de base | `basicAttribute` | Attribut de base lié à la compétence |
| Description | `descript[3]` | Description en 3 niveaux (cf. `BookOfRules` §2.C) |
| Spécialisations | `specializations[]` | Spécialisations disponibles pour cette compétence (catalogue) |

> Conformément au `BookOfRules` §2.C.

**Relation :** `SkillDatabase ┗━ [0..*] Skill` (catalogue, composition)


### Compétence active — ActiveSkill (instance)

Instance d'une compétence possédée par un `Actor` (Character ou Creature).
Référence son `Skill` de catalogue, porte son propre niveau.

| Propriété | Champ | Description |
|---|---|---|
| Compétence référencée | `skill` | Référence (non-propriétaire) vers le `Skill` de catalogue |
| Niveau | `skillLevel` | Niveau de la compétence chez cet Actor, `[0 ; 4]` |
| Spécialisations actives | `activeSpecializ[]` | Liste des `ActiveSpecialization` acquises par cet Actor pour cette compétence |

**Relation :** `Actor ┗━ [0..*] ActiveSkill : skills` (composition) → `ActiveSkill ─→ Skill` (référence catalogue, non-propriétaire)


### SkillDatabase

Catalogue passif des `Skill` disponibles pour un Univers. Ne charge rien
lui-même (pas de `load()`) — peuplé de l'extérieur par un futur
`SkillRepository` (couche Persistence). Garantit l'unicité des `skillId`
insérés.


### Spécialisation — Specialization (catalogue)

Sous-compétence avancée, référencée depuis un `Skill`.

| Propriété | Champ | Description |
|---|---|---|
| Identifiant | `specId` | Identifiant unique **au sein du `Skill` parent** — pas global (cf. `SkillCatalog.schema.md` §7) |
| Nom affiché | `name` | Appellation courante de la Spécialisation, destinée à l'affichage UI (ex. liste déroulante), quelle que soit la couche de présentation |
| Description | `specialDescript` | Description de la Spécialisation |

**Relation :** `Skill ┗━ [0..*] Specialization` (composition, catalogue)


### Spécialisation active — ActiveSpecialization (instance)

Instance d'une spécialisation acquise par un Actor pour une `ActiveSkill` donnée.

| Propriété | Champ | Description |
|---|---|---|
| Spécialisation référencée | `specializ` | Référence (non-propriétaire) vers la `Specialization` de catalogue |
| Niveau | `level` | Niveau de spécialisation acquis (entier, fixé à la construction) |

**Relation :** `ActiveSkill ┗━ [0..*] ActiveSpecialization : activeSpecializ` (composition) → `ActiveSpecialization ─→ Specialization` (référence catalogue, non-propriétaire)
  
  
## 6. Équipements
  
  
### Item

Racine de tout objet possédable. Dérivée de `Entity`.

**Hérité de `Entity` :** `instanceID`, `name`, `description`, `tags`, `portrait`.

**Propriétés propres :**

| Propriété | Champ | Description |
|---|---|---|
| Encombrement | `encumbrance` | Intervalle `[0 ; 5]` |
| Résistance | `damageResistance` | Résistance aux dommages (points de vie de l'objet) |
| Valeur | `value` | Valeur sur le marché |
| Rareté | `rarity` | Difficulté à trouver ce type d'équipement, `[0 ; 10]` |
| Force minimale | `minStrength` | Force minimale (PHY) requise pour porter l'équipement |

**Relation :** `Character ┗━ [0..*] Item` — **seul point de stockage physique de l'équipement**. Tout ce qui suit (`Equipment`, `Armor`, `Tool`, `Weapon`) cohabite dans cette même collection par polymorphisme ; `getWeapons()`, `getArmor()`, `getHandled()` sont des vues calculées par filtrage, jamais des stockages séparés.
  
  
### Equipment (classe abstraite) — `Equipment : Item`

Tout objet qui se porte ou s'équipe (par opposition à un `Item` simplement transporté).

**Hérité de `Item` :** `encumbrance`, `damageResistance`, `value`, `rarity`, `minStrength`.

**Propriétés propres :**

| Propriété | Champ | Description |
|---|---|---|
| Équipé | `equiped` | Le personnage le porte actuellement (sur lui, à la ceinture...) |

**Responsabilités :** `equip()`, `unequip()`, `isEquiped()`.
  
  
### Armure — `Armor : Equipment`

Protection contre les dommages.

**Hérité d'`Equipment` :** `encumbrance`, `damageResistance`, `value`, `rarity`, `minStrength`, `equiped`.

**Propriétés propres :**

| Propriété | Champ | Description |
|---|---|---|
| Protection | `damageProtection` | Capacité à absorber les dégâts (distincte de `damageResistance`) |

Si les dégâts encaissés par l'armure en un seul coup dépassent `damageResistance`, `damageProtection` diminue d'un point.
  
  
### Outil — `Tool : Equipment`

Tout équipement qui se prend en main pour être utilisé (par opposition à ce qui se porte passivement, comme une armure).

**Hérité d'`Equipment` :** `encumbrance`, `damageResistance`, `value`, `rarity`, `minStrength`, `equiped`.

**Propriétés propres :**

| Propriété | Champ | Description |
|---|---|---|
| En main | `handled` | Le personnage le tient actuellement en main |

**Responsabilités :** `takeIt()`, `dropIt()`, `isHandled()`.
  
  
### Armes — `Weapon : Tool`

Armes de contact ou à distance, et boucliers. Une arme est un outil qu'on manie.

**Hérité de `Tool` :** `encumbrance`, `damageResistance`, `value`, `rarity`, `minStrength`, `equiped`, `handled`.

**Propriétés propres :**

| Propriété | Champ | Description |
|---|---|---|
| Attaque | `att` | Bonus d'attaque |
| Dommage | `dmg` | Dégâts infligés à l'adversaire |
| Défense | `def` | Défense contre l'attaque adverse (pertinent pour les armes de parade et boucliers) |
| Portée | `range` | Portée, `[0 ; 4]` — 0 = arme de contact |
| Prise en main | `hands` | `1` ou `2` — arme à une main ou deux mains |
| Effet spécial | `specialEffect` | Poison, brûlure... (couvre aussi les armes naturelles à distance type souffle) |

---
  
  
## 7. Faction

Organisation, groupe ou communauté partageant des intérêts, objectifs ou ressources communs. Dérivée de `Entity`.

**Exemples :** Corporation, Clan, Gouvernement, Organisation criminelle.

**Relations :**
```
Faction
 ├── Members
 ├── Assets
 └── Territories
```

---
  
  
## 8. Génération de contenu
  
  
### Gabarit — `Template`

Modèle de génération.

**Exemples :** `CharacterTemplate`, `CreatureTemplate`, `EquipmentTemplate`, `LocationTemplate`, `FactionTemplate`.

**Responsabilités :** fournir des modèles ; guider la génération ; servir de base à l'IA.
  
  
### Contenu généré — `GeneratedContent`

Objet produit automatiquement, par génération procédurale, par IA, ou par combinaison de gabarits.

---
  
  
## 9. Gestion des données
  
  
### Catalogue — `Catalog`

Collection de définitions.

**Exemples :** `SkillCatalog`, `ItemCatalog`, `CreatureCatalog`, `LocationCatalog`.

### Dépôt — `Repository`

Composant chargé du chargement et de la sauvegarde.

**Formats supportés :** JSON, CSV.

---
  
  
## 10. Simulation (futur)

Section prospective — non prioritaire pour la V1, conservée pour cadrer les évolutions futures.
  
  
### Position

Position spatiale : `x`, `y`, `z`.

### Entité spatiale — `SpatialEntity`

Entité possédant une position. Exemples : `Character`, `Creature`, `Vehicle`, `Location`.
  
  
### Combat

Simulation de confrontation.

**Responsabilités :** initiative ; déplacement ; attaque ; défense ; dégâts.
  
  
### Événement mondial — `WorldEvent`

Événement affectant le monde. Exemples : catastrophe, conflit, migration, crise.

---
  
  
## 11. Relations principales

```
Universe
 └── Campaign

Campaign
 ├── Characters
 ├── Creatures
 ├── Items
 ├── Locations
 ├── Factions
 └── Templates

Character
 ├── Morphology
 ├── Attributes
 ├── DerivedAttributes
 ├── Injuries
 ├── Skills (→ Specializations)
 ├── Inventory (→ Item → Equipment → Armor/Tool → Weapon)
 ├── Familiars (→ Actor, référence non-propriétaire)
 ├── Factions (→ Faction, référence non-propriétaire)
 └── Portrait (→ MediaAsset, référence partagée)

Creature
 ├── Morphology (→ species, sizeModifier, massModifier)
 ├── Attributes
 ├── DerivedAttributes
 ├── NaturalWeapons (→ Weapon [0..*])
 └── Inventory (→ Item)

Faction
 ├── Members
 └── Locations

Location
 ├── Characters
 ├── Creatures
 └── Items

Template
 ├── CharacterTemplate
 ├── CreatureTemplate
 ├── EquipmentTemplate
 ├── FactionTemplate
 └── LocationTemplate
```