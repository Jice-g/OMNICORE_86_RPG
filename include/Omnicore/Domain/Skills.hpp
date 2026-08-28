#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <span>
#include <cstdint>

#include <Omnicore/Domain/Attributes.hpp>

namespace Omnicore::Domain
{

constexpr auto MAX_SPEC_SKILL = 3; // Modifie la taille du tableau de spécialisation




    // ============================================================
	// SPECIALIZATION
	// ============================================================

	/// @brief Variable structuré qui définie une Spécialisation de compétence
	/// @details
	/// + name : nom de la spécialisation qui sera remonté jusqu'à l'UI
	/// + specId : identification unique de la spécialisation
	/// + specialDescript : desciptif de la spécialisation
	/// <la variable structurée est écrite depuis un fichier json dans un catalogue>
	class Specialization {
	public:
		std::string name;
		std::string specId;
		std::string specialDescript;
	};


	/// @brief Spécialisation active dans Actor
	/// @details
	/// + specializ référence une pecialization du catalogue
	/// + level donne le niveau de spécialisation [0..2]
	class ActiveSpecialization {
	public:
		ActiveSpecialization(Specialization& special, int8_t level = 0);
		const Specialization& specializ;
		void IncreaseLevel();
		void DecreaseLevel();
		int8_t Level() const noexcept;
	private:
		int8_t m_level; // [0..2]
	};


	/// @brief Variable structuré qui définie une Compétence (Skill)
	/// @details
	/// + basicAttribute : l'attribut de base sur lequel se définit la Compétence
	/// + skillId : identification unique de la compétence
	/// + descript : desciptif de la compétence
	/// + specializations : spécialisations auxquelles accède la compétence du personnage [MAX_SPEC_SKILL]
	/// <la variable structurée est écrite depuis un fichier json dans un catalogue>
	class Skill {
	public:
		eAttribute basicAttribute;
		std::string skillId;
		std::string descript;
		std::array<Specialization, MAX_SPEC_SKILL> specializations;
	};








}; // namespace Omnicore::Domain