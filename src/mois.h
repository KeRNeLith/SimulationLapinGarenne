#ifndef MOIS_H
#define MOIS_H

#include <vector>

#include "Lapins/lapereau.h"
#include "Lapins/lapinadultemale.h"
#include "Lapins/lapinadultefemelle.h"

/**
 * @brief The Mois class Gère le stockage des données de simulation d'un mois de l'année.
 */
class Mois
{
private:
    std::vector<Lapereau> m_lapereau;               ///< Données de simulation liés aux lapereaux.
    std::vector<LapinAdulteMale> m_adulteMale;      ///< Données de simulation liés aux lapins adultes mâles.
    std::vector<LapinAdulteFemelle> m_adulteFemelle;///< Données de simulation liés aux lapins adultes femelles.

public:
    /**
     * @brief Mois Constructeur par défaut.
     */
    Mois();
    /**
     * @brief ~Mois Destructeur.
     */
    ~Mois();
};

#endif // MOIS_H
