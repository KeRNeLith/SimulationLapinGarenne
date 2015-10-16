#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

#include "mois.h"

/**
 * @brief The Simulation class Gère le stockage des données de simulation.
 * Elle est chargée de faire progresser la simulation en fournissant une interface adaptée.
 */
class Simulation
{
private:
    unsigned int m_moisSimule;  ///< Nombre de mois simulés.
    std::vector<Mois> m_mois;   ///< Données de simulation sur l'année.

public:
    /**
     * @brief Simulation Constructeur par défaut.
     */
    Simulation();
    /**
     * @brief ~Simulation Destructeur.
     */
    ~Simulation();
};

#endif // SIMULATION_H
