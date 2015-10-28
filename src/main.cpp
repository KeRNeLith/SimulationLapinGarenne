#include <iostream>

#include "simulation.h"

int main()
{
    //const unsigned int nbMonth = 180;
    const unsigned int nbMonth = 80;

    Simulation simu;
    simu.writeToFile("simu.log");
    for (unsigned int i = 0 ; i < nbMonth ; i++)
    {
        simu.simulateNextMonth();
        simu.writeToFile("simu.log");
        std::cout <<"Mois " << i << " => Nombre de lapin : " << simu.getNbRabbit() << std::endl;
    }

    return 0;
}

