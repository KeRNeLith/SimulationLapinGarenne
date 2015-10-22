#ifndef LAPINADULTEMALE_H
#define LAPINADULTEMALE_H

#include "lapinadulte.h"

/**
 * @brief The LapinAdulteMale class Gère la représentation d'un lapin adulte de sexe masculin.
 */
class LapinAdulteMale
        : public LapinAdulte
{
public:
    /**
     * @brief LapinAdulteMale Constructeur par défaut.
     */
    LapinAdulteMale();
    /**
     * @brief ~LapinAdulteMale Destructeur.
     */
    virtual ~LapinAdulteMale();
};

#endif // LAPINADULTEMALE_H
