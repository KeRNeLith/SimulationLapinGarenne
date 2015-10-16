#ifndef LAPIN_H
#define LAPIN_H

/**
 * @brief The Lapin class Gère la représentation abstraite d'un lapin.
 */
class Lapin // should be abstract class
{
protected:
    unsigned short m_tauxSurvie;    ///< Taux de survie du lapin (0% - 100%).
    unsigned int m_age;             ///< Âge du lapin (en mois).

public:
    /**
     * @brief Lapin Constructeur par défaut.
     */
    Lapin();
    /**
     * @brief ~Lapin Destructeur.
     */
    virtual ~Lapin();
};

#endif // LAPIN_H
