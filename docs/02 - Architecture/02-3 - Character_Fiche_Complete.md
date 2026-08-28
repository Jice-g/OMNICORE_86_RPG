# Fiche `Character` complète — OMNICORE 8/6 RPG

> **Base pour :** annotations de codage (à compléter), Pattern JSON de la fiche de personnage.
> **Source :** `OMNICORE_UML_Diagramme_V2.5.md`
> **Portée :** V1 — gestion de fiche de personnage uniquement.

---

## 1. Vue d'ensemble — chaîne d'héritage

```
Entity (abstraite)
  └── Actor (abstraite)
        └── Character
```

`Character` hérite de deux niveaux : `Entity` (identité générique) et `Actor` (comportement d'agent jouable/contrôlable). Ce document liste **toutes** les propriétés et méthodes visibles sur une instance de `Character`, qu'elles soient définies directement ou héritées.

---

## 2. Propriétés — vue consolidée

### 2.1 Héritées de `Entity`

| Propriété | Type | Description | Note de codage |
|---|---|---|---|
| `instanceId` | `Integer` | Identifiant unique de l'instance (`InstanceID` — compteur statique + timestamp) | *(à compléter)* |
| `name` | `String` | Nom de l'entité | *(à compléter)* |
| `description` | `List<String>` | Description détaillée, multi-lignes | *(à compléter)* |
| `tags` | `List<String>` | Étiquettes de classification libre | *(à compléter)* |
| `portrait` | `MediaAsset*` | Illustration associée — nullable, défaut géré côté UI | *(à compléter)* |

### 2.2 Héritées de `Actor`

| Propriété | Type | Description | Note de codage |
|---|---|---|---|
| `controller` | `eControllerType` | `PLAYER` / `GAME_MASTER` / `AI` | *(à compléter)* |
| `userId` | `String` | Identifiant du compte (MJ ou joueur) | *(à compléter)* |
| `attributes` | `Attributes` | Les 8 attributs fixes (PHY/DEX/ESP/PER/SOC/CHA/POU/NEU) | *(à compléter)* |
| `derivedAttributes` | `DerivedAttributes` | MNV, DPL, RFX, DFP, RP, RM — calculés par le RuleEngine | *(à compléter)* |
| `morphology` | `Morphology` | Espèce, modificateurs de taille/corpulence | *(à compléter)* |
| `injuries` | `List<Injury>` | Blessures actives | *(à compléter)* |
| `skills` | `List<ActiveSkill>` | Compétences possédées (instances référençant le catalogue) | *(à compléter)* |
| `power` | `Integer` | Pool des attributs de base | *(à compléter)* |
| `level` | `Integer` | Valeur totale des points de compétence | *(à compléter)* |

### 2.3 Propres à `Character`

| Propriété | Type | Description | Note de codage |
|---|---|---|---|
| `characterRole` | `String` | Archétype narratif (guerrier, magicien...) | *(à compléter)* |
| `gender` | `eGenderType` | MASC / FEMM / FTM / MTF / UNDEF | *(à compléter)* |
| `litteralAttributes` | `Litterals` | Story[9], Culture, LifePath, Quest, Darkness, Quirks[5] | *(à compléter)* |
| `inventory` | `List<Item>` | **Seul stockage physique d'équipement** — armes, armures, outils y cohabitent par polymorphisme | *(à compléter)* |
| `familiars` | `List<&Actor>` | Créatures adoptées — référence non-propriétaire | *(à compléter)* |
| `factions` | `List<&Faction>` | Appartenance(s) — référence non-propriétaire | *(à compléter)* |
| `FinanceRessource` | `Finance` | Ressources financières (encapsulation interne) | *(à compléter)* |

---

## 3. Méthodes — vue consolidée

### 3.1 Héritées de `Entity`

| Méthode | Retour | Rôle | Note de codage |
|---|---|---|---|
| `InstanceID()` | `Integer` | Accesseur identifiant | *(à compléter)* |
| `Name()` | `String` | Accesseur nom | *(à compléter)* |
| `Description()` | `List<String>` | Accesseur description | *(à compléter)* |
| `Tags()` | `List<String>` | Accesseur tags | *(à compléter)* |
| `Portrait()` | `MediaAsset*` | Accesseur illustration | *(à compléter)* |
| `SetDescription(line)` | `Void` | Ajoute une ligne de description | *(à compléter)* |
| `SetTag(tag)` | `Void` | Ajoute un tag | *(à compléter)* |
| `SetPortrait(asset)` | `Void` | Associe une illustration (référence, pas de copie) | *(à compléter)* |

### 3.2 Héritées de `Actor`

| Méthode | Retour | Rôle | Note de codage |
|---|---|---|---|
| `getController()` | `eControllerType` | {query} | *(à compléter)* |
| `getUserId()` | `String` | {query} | *(à compléter)* |
| `getAttributes()` | `Attributes` | Copie — type-valeur simple | *(à compléter)* |
| `getDerivedAttributes()` | `DerivedAttributes` | Copie — type-valeur simple | *(à compléter)* |
| `getMorphology()` | `Morphology` | Copie | *(à compléter)* |
| `getInjuries()` | `List<Injury>` | Vue sur collection possédée — candidat `std::span<const Injury>` | *(à compléter)* |
| `getPower()` | `Integer` | | *(à compléter)* |
| `getLevel()` | `Integer` | | *(à compléter)* |
| `setController(controller)` | `Void` | | *(à compléter)* |
| `setAttributes(attributes)` | `Void` | | *(à compléter)* |
| `calculateDerivedAttributes()` | `Void` | Ne calcule pas elle-même — délègue à `RuleEngine::DerivedAttributes(attributes, universeTag)` (statique, hors Character System). Appelée par le constructeur et à chaque modification des attributs de base. | *(à compléter)* |
| `setMorphology(morpho)` | `Void` | | *(à compléter)* |
| `setPower(pwr)` | `Void` | | *(à compléter)* |
| `setLevel(lvl)` | `Void` | | *(à compléter)* |
| `addInjury(tag, severity)` | `Boolean` | | *(à compléter)* |
| `removeInjury(index)` | `Boolean` | | *(à compléter)* |
| `addSkill(newskill, level)` | `&ActiveSkill` | Crée un `ActiveSkill` référençant un `Skill` du catalogue | *(à compléter)* |
| `skillIndex(skillId)` | `Integer` | | *(à compléter)* |
| `removeSkill(skillIndex)` | `Boolean` | | *(à compléter)* |
| `addSpecialization(skillselect, newspec, level)` | `&ActiveSpecialization` | | *(à compléter)* |
| `removeSpecialization(specIndex)` | `Boolean` | | *(à compléter)* |

### 3.3 Propres à `Character`

| Méthode | Retour | Rôle | Note de codage |
|---|---|---|---|
| `getRole()` | `String` | {query} | *(à compléter)* |
| `getGender()` | `eGenderType` | {query} | *(à compléter)* |
| `getGenderStr()` | `String` | {query} | *(à compléter)* |
| `getLitterals()` | `Litterals` | {query} | *(à compléter)* |
| `getInventory()` | `List<Item>` | **Attention slicing** — stockage réel en `vector<unique_ptr<Item>>`, vue exposée en `vector<Item*>` | *(à compléter)* |
| `getWeapons()` | `List<Weapon>` | **Calculé** — filtre `inventory` sur `is Weapon` | *(à compléter)* |
| `getArmor()` | `Armor` | **Calculé** — filtre `inventory` sur `is Armor AND equiped` | *(à compléter)* |
| `getEquipment(index)` | `Equipment` | {query} | *(à compléter)* |
| `getHandled()` | `Tool[2]` | **Calculé** — filtre `inventory` sur `is Tool AND handled`, 2 emplacements (mains) | *(à compléter)* |
| `setRole(role)` | `Void` | | *(à compléter)* |
| `setGender(gender)` | `Void` | | *(à compléter)* |
| `setArmor(armor)` | `Void` | Délègue à `armor->equip()` ; désenquipe l'armure précédemment portée | *(à compléter)* |
| `addEquipment(equip)` | `Integer` | Accepte tout sous-type d'`Equipment` par polymorphisme | *(à compléter)* |
| `Handle(tool)` | `Tool[2]` | Prend un outil en main ; renvoie l'état des deux emplacements | *(à compléter)* |
| `getFactions()` | `List<&Faction>` | {query} | *(à compléter)* |
| `addFaction(faction)` | `Void` | | *(à compléter)* |
| `removeFaction(faction)` | `Boolean` | | *(à compléter)* |

---

## 4. Classes composées — rappel des structures associées

Ces classes ne sont pas des propriétés de `Character` au sens strict, mais elles composent directement ses propriétés ci-dessus. Listées ici pour que la fiche soit auto-suffisante.

### `Attributes`
`physique, dexterite, esprit, perception, social, chance, pouvoir, neuro, total` — 8 champs fixes + total calculé (`attSum()`).

### `Morphology`
`species, sizeModifier, massModifier`.

### `DerivedAttributes`
`mnv, dpl, rfx, dfp, rp, rm` — calculés via `Actor::calculateDerivedAttributes()`, qui délègue à `RuleEngine::DerivedAttributes(attributes, universeTag)` (statique, hors périmètre Character System).

### `Faction` (référencée via `factions`)
Modélisée a minima pour l'instant — hérite uniquement des propriétés d'`Entity` (`instanceId`, `name`, `description`, `tags`, `portrait`), aucune propriété propre pour le moment.

### `MediaAsset` (référencé via `portrait`)
`kind (MediaAssetKind : Portrait/Icon/Emblem/Illustration/Map), filePath` — partageable entre plusieurs `Entity` par référence d'`InstanceID`, aucune méthode de chargement (délégué à `AssetRepository`, phase Persistence).

### `Injury`
`severity (eInjurySeverity : LEGERE/MODEREE/SEVERE/CRITIQUE), penalty`.

### `Litterals`
`Story[9], Culture, LifePath, Quest, Darkness, Quirks[5]`.

### `Finance`
`totalRessource` (privé) — `pay(value)`, `collect(value)`, `getFinance()`, `setFinance(value)`.

### `ActiveSkill` (élément de `skills`)
`skill (&Skill, référence catalogue), skillLevel, activeSpecializ[]` — méthodes `increaseLevel()`, `decreaseLevel()`, `findSpecialization(specId)`, `getSpecializationIndex(specName)`.

### `Item` et sa hiérarchie (éléments d'`inventory`)
```
Item (encomb, dmResist, value, rareness, phyMin)
 └── Equipment (equiped, equip()/unequip()/isEquiped())
       ├── Armor (dmProtect)
       └── Tool (handled, takeIt()/dropIt()/isHandled())
             └── Weapon (attack, defense, damages, range, specialEffect)
```

---

## 5. Vers le Pattern JSON

Cette fiche constitue la base directe du futur schéma JSON de sauvegarde d'un personnage. Rappels de conception déjà actés qui s'appliqueront à la sérialisation :

- `skills` : DTO persisté (paire id + nom), **hydratation deux phases** contre `SkillDatabase` au chargement — jamais l'objet `Skill` complet dupliqué dans le JSON du personnage.
- `familiars` : référence non-propriétaire — à sérialiser probablement comme une liste d'`InstanceID`, résolue après coup, pas comme des objets imbriqués complets.
- `portrait` : référence vers un `MediaAsset` par `InstanceID` — jamais un chemin de fichier en dur dans le JSON du personnage.
- `inventory` : polymorphe — le JSON devra porter un discriminant de type (`"itemType": "Weapon"` ou équivalent) pour permettre l'hydratation correcte de chaque sous-type au chargement.

---

## 6. Notes de codage — à compléter ensemble

Section réservée pour la prochaine étape : explicitation ligne par ligne de chaque propriété et méthode (choix de type C++ précis, signature exacte, comportement des accesseurs `const`/`span`/copie selon les règles établies dans `ArchitecturePrinciples.md`).
