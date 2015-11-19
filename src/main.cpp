#include <iostream>

/*#include <QApplication>
#include <QMainWindow>*/

#include "simulation.h"

int main(int /*argc*/, char** /*argv*/)
{
	// Variables pour calculer Fibonacci en parallèle
	rabbits_t tmpCoupleJeune;
	rabbits_t coupleJeune = 1;												// Nombre de lapins "jeunes"
	rabbits_t coupleAdulte = 0;												// Nombre de lapins adultes

    //const unsigned int nbMonth = 180;
    const unsigned int nbMonth = 100;

    // Pour le temps d'exécution
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    Simulation simu;

    simu.writeToFile("simu.log");
	simu.writeToCSV("data.csv", (coupleAdulte + coupleJeune), true);
	unsigned int i = 0;
    while(simu.getNbRabbit() < 10000000000)
    {
        simu.simulateNextMonth();
        simu.writeToFile("simu.log");

		tmpCoupleJeune = coupleAdulte;								// Les adultes créent des couples jeunes
		coupleAdulte += coupleJeune;											// Les jeunes deviennent adultes
		coupleJeune = tmpCoupleJeune;											// Mise à jour du nombre de couples jeunes
		simu.writeToCSV("data.csv", (coupleJeune + coupleAdulte), false);
        std::cout <<"Mois " << ++i << " => Nombre de lapin : " << simu.getNbRabbit() << std::endl;	
    }

    // Calcul du temps d'exécution
    std::chrono::duration<double> duration = std::chrono::steady_clock::now() - begin;
    std::cout << "Temps : " << duration.count() << "s" << std::endl;

    return 0;
}
