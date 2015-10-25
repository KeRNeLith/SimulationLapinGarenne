#ifndef SIMULATION_H
#define SIMULATION_H

#include <random>
#include <vector>

#include "month.h"
#include "youngrabbit.h"

/**
 * @brief The Simulation class Gère le stockage des données de simulation.
 * Elle est chargée de faire progresser la simulation en fournissant une interface adaptée.
 */
class Simulation
{
private:
    unsigned int m_monthSimulated;  ///< Nombre de mois simulés.
    std::vector<Month> m_months;    ///< Données de simulation sur l'année.
    YoungRabbit m_youngRabbits;     ///< Données de simulation pour tous les lapereaux.
    //std::vector<Lapereau> m_lapereau;   ///< Données de simulation liés aux lapereaux.

    /*void evolveToAdult(std::uniform_int_distribution<>& survivalDist,
                       const unsigned int currentMonthIndex,
                       std::vector<Lapereau>::iterator itLapereau);*/

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

    /**
     * @brief getNbRabbit Calcul et retourne le nombre total de lapins vivants dans la simulation.
     * @return Nombre de lapins vivants dans la simulation.
     */
    rabbits_t getNbRabbit() const;
};

#endif // SIMULATION_H
