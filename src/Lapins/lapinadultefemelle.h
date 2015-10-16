#ifndef LAPINADULTEFEMELLE_H
#define LAPINADULTEFEMELLE_H

#include "lapinadulte.h"

/**
 * @brief The LapinAdulteFemelle class Gère la représentation d'un lapin adulte de sexe féminin.
 */
class LapinAdulteFemelle
        : public LapinAdulte
{
public:
    /**
     * @brief LapinAdulteFemelle Constructeur par défaut.
     */
    LapinAdulteFemelle();
    /**
     * @brief ~LapinAdulteFemelle Destructeur.
     */
    virtual ~LapinAdulteFemelle();
};

#endif // LAPINADULTEFEMELLE_H
