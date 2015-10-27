#include <iostream>

#include "simulation.h"

int main()
{
    //const unsigned int nbMonth = 180;
    const unsigned int nbMonth = 80;

    Simulation simu;
    for (unsigned int i = 0 ; i < nbMonth ; i++)
    {
        simu.writeToFile("simu.log");
        simu.simulateNextMonth();
        std::cout <<"Mois " << i << " => Nombre de lapin : " << simu.getNbRabbit() << std::endl;
    }

    simu.writeToFile("simu.log");

    return 0;
}

