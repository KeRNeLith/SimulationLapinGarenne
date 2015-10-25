#ifndef YOUNGRABBIT_H
#define YOUNGRABBIT_H

#include <vector>

#include "general/general.h"

/**
 * @brief The YoungRabbit class Gère l'évolution des lapereaux jusqu'à leur maturité.
 */
class YoungRabbit
{
private:
    /**
     * @brief m_youngRabbits Stocke le nombre de lapereaux par tranche de mois, chaque mois est représenté par un indice dans le vecteur.
     * Chaque tranche possède un nombre de lapereaux mâles et un nombre de lapereaux femelles.
     * Il y a 9 tranches, soit de la naissance au huitième mois.
     */
    std::vector< std::pair<rabbits_t, rabbits_t> > m_youngRabbits;

public:
    /**
     * @brief YoungRabbit Constructeur par défaut.
     */
    YoungRabbit();
    /**
     * @brief ~YoungRabbit Destructeur.
     */
    ~YoungRabbit();

    /**
     * @brief addYoungRabbit Ajoute un certain nombre de lapereaux à la simulation (naissance de nbRabbit lapereaux).
     * @param nbRabbit Nombre de lapereaux à ajouter.
     */
    void addYoungRabbit(const rabbits_t nbRabbit = 1);

    /**
     * @brief update Met à jour les données de simulations pour faire progresser les lapereaux de 1 mois dans la simulation.
     * @return Vecteur représentant les tranches de mois 5 à 9 pour les lapereaux qui deviennent adultes.
     * L'indice 0 correspond donc aux lapereaux qui deviennent adultes a 5 mois.
     * Les paires stockent en first le nombre de femelle pour le mois, alors que second donne le nombre de mâles.
     */
    std::vector< std::pair<rabbits_t, rabbits_t> > update();

    /**
     * @brief getNbRabbit Calcul et retourne le nombre total de lapereau vivants dans la simulation.
     * @return Nombre de lapereaux vivants dans la simulation.
     */
    rabbits_t getNbRabbit() const;
};

#endif // YOUNGRABBIT_H
