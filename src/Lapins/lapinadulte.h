#ifndef LAPINADULTE_H
#define LAPINADULTE_H

#include "lapin.h"

class LapinAdulte   // should be abstract class
        : public Lapin
{
public:
    /**
     * @brief LapinAdulte Constructeur par défaut.
     */
    LapinAdulte();
    /**
     * @brief ~LapinAdulte Destructeur.
     */
    virtual ~LapinAdulte();
};

#endif // LAPINADULTE_H
