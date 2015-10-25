#include <iostream>

#include "simulation.h"

int main()
{
    //const unsigned int nbMonth = 180;
    const unsigned int nbMonth = 10;
    Simulation simu;
    for (unsigned int i = 0 ; i < nbMonth ; i++)
    {
        simu.simulateNextMonth();
        std::cout <<"Mois " << i << " => Nombre de lapin : " << simu.getNbRabbit() << std::endl;
    }

    return 0;
}

