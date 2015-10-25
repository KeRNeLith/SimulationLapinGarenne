#ifndef SIMULATION_H
#define SIMULATION_H

#include <random>
#include <vector>

#include "Lapins/lapereau.h"
#include "month.h"

/**
 * @brief The Simulation class Gère le stockage des données de simulation.
 * Elle est chargée de faire progresser la simulation en fournissant une interface adaptée.
 */
class Simulation
{
private:
    unsigned int m_monthSimulated;  ///< Nombre de mois simulés.
    std::vector<Month> m_months;    ///< Données de simulation sur l'année.
    std::vector<Lapereau> m_lapereau;   ///< Données de simulation liés aux lapereaux.

    void evolveToAdult(std::uniform_int_distribution<>& survivalDist,
                       const unsigned int currentMonthIndex,
                       std::vector<Lapereau>::iterator itLapereau);

public:
    /**
     * @brief Simulation Constructeur par défaut.
     */
    Simulation();
    /**
     * @brief ~Simulation Destructeur.
     */
    ~Simulation();

    void simulateNextMonth();

    rabbits_t getNbRabbit();
};

#endif // SIMULATION_H
