cmake_minimum_required(VERSION 3.20)

project(OMNICORE_86_RPG
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Squelette volontairement minimal — aucune cible pour l'instant.
# Les sous-répertoires (spikes/, src/, tests/...) seront ajoutés
# au fil des prochaines étapes, et nottamment le stub du walking skeleton (Étape 0).
