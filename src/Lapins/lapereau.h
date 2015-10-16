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

public:
    /**
     * @brief Lapereau Constructeur par défaut.
     */
    Lapereau();
    /**
     * @brief ~Lapereau Destructeur.
     */
    virtual ~Lapereau();
};

#endif // LAPEREAU_H
