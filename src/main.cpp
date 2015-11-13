#include <iostream>

/*#include <QApplication>
#include <QMainWindow>*/

#include "simulation.h"

int main(int /*argc*/, char** /*argv*/)
{
    //const unsigned int nbMonth = 180;
    const unsigned int nbMonth = 100;

    // Pour le temps d'exécution
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    Simulation simu;
    simu.writeToFile("simu.log");
	unsigned int i = 0;
    while(simu.getNbRabbit() < 10000000000)
    {
        simu.simulateNextMonth();
        simu.writeToFile("simu.log");
        std::cout <<"Mois " << ++i << " => Nombre de lapin : " << simu.getNbRabbit() << std::endl;
		
    }

    // Calcul du temps d'exécution
    std::chrono::duration<double> duration = std::chrono::steady_clock::now() - begin;
    std::cout << "Temps : " << duration.count() << "s" << std::endl;

    return 0;
}
