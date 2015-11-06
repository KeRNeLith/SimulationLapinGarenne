#include <iostream>

/*#include <QApplication>
#include <QMainWindow>*/

#include "simulation.h"

int main(int /*argc*/, char** /*argv*/)
{
    //const unsigned int nbMonth = 180;
    const unsigned int nbMonth = 100;

    Simulation simu;
    simu.writeToFile("simu.log");
	unsigned int i = 0;
    while(simu.getNbRabbit() < 10000000000)
    {
        simu.simulateNextMonth();
        simu.writeToFile("simu.log");
        std::cout <<"Mois " << ++i << " => Nombre de lapin : " << simu.getNbRabbit() << std::endl;
		
    }

    return 0;
}
