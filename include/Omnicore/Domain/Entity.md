Objectif de la classe Entity
----------------------------

Entity est la classe racine de toutes les entités du moteur OmniCore (JDR).

Elle fournit :
 - une identité unique
 - un nom - une description structurée (16 lignes max)

 - des tags (3 étiquettes max)

Elle sert de base à :
Actor, Character, Creature, Item, Skill, etc.


Justification technique des choix
-----------------------------------

✔ std::array pour description et tags

 - taille fixe → structure stable
 - allocation interne → pas de heap
 - rapide, compact, sérialisable
 - parfait pour des données structurelles
	

✔ std::span pour les setters

 - accepte vector, array, C-array, initializer_list

 - flexible : l’utilisateur peut fournir 1, 2, 5, 16 lignes

 - sécurisé : taille connue

 - moderne C++20

 - zéro allocation
	

✔ explicit
	Empêche les conversions implicites :
	Entity e = "Gobelin"; // interdit

✔ virtual ~Entity()
	Indispensable pour détruire correctement :
	Entity* e = new Character(...);
	delete e; // appelle ~Character()

✔ = default
	Indique que le compilateur génère un destructeur trivial.
	
✔ [[nodiscard]]
Empêche d’ignorer un getter important tel que le nom de notre entité.


Exemple d’utilisation
----------------------

✔ Description courte
entity.SetDescription({"Ligne 1", "Ligne 2"});

✔ Description longue (tronquée automatiquement)
std::vector<std::string> desc = {...};
entity.SetDescription(desc);

✔ Tags
entity.SetTags({"Humanoïde", "PNJ"});


Diagramme UML simplifié
-----------------------

+----------------------+
|      Entity          |
+----------------------+
| - m_id : uint64_t    |
| - m_name : string    |
| - m_description[16]  |
| - m_tags[3]          |
+----------------------+
| + GetName()          |
| + SetName()          |
| + SetDescription()   |
| + SetTags()          |
+----------------------+


Résumé
-------

Identité		uint64_t			rapide, portable
Nom				std::string			flexible
Description		std::array<16>		structure fixe
Tags			std::array<3>		structure fixe
Setters			std::span			flexible + sûr
Constructeur	explicit			pas de conversion implicite
Destructeur		virtual				polymorphisme
Getters			ref const			zéro copie

