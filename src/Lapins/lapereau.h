#ifndef LAPEREAU_H
#define LAPEREAU_H

#include "lapin.h"

/**
 * @brief The Lapereau class Gère la représentation d'un lapereau (Lapin non mature).
 */
class Lapereau
        : public Lapin
{
private:
    bool m_male;    ///< Booléen pour savoir si la lapin est un mâle ou une femelle.
    unsigned int m_age; ///< Âge du lapin (en mois).

public:
    /**
     * @brief Lapereau Constructeur par défaut.
     */
    Lapereau();
    /**
     * @brief ~Lapereau Destructeur.
     */
    virtual ~Lapereau();

    void updateAge(unsigned int update = 1);

    // Accesseurs
    bool isMale() const { return m_male; }
    unsigned int getAge() const { return m_age; }
};

#endif // LAPEREAU_H
