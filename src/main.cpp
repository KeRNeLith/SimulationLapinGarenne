#include <iostream>

/*#include <QApplication>
#include <QMainWindow>*/

#include "simulation.h"

int main(int /*argc*/, char** /*argv*/)
{
	// Variables pour calculer Fibonacci en parallèle
	bool		stop = false;									// Booléen qui active ou non le calcul de Fibonacci
	rabbits_t	tmpCoupleJeune;
	rabbits_t	coupleJeune = 1;								// Nombre de lapins "jeunes"
	rabbits_t	coupleAdulte = 0;								// Nombre de lapins adultes
	rabbits_t	nbRabbitFibo = coupleAdulte + coupleJeune;		// Nombre de lapins total calculés par Fibonacci
	const rabbits_t limit = (rabbits_t) pow(2, 64) - 1;			// Nombre de lapins maximal stockable
    
	//const unsigned int nbMonth = 180;
    const unsigned int nbMonth = 100;

    // Pour le temps d'exécution
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::chrono::duration<double> time;

    Simulation simu;

    simu.writeToFile("simu.log");
	simu.writeToCSV("data.csv", nbRabbitFibo, 0.0, true);
	unsigned int i = 0;
    while(simu.getNbRabbit() < 10000000000)
    {
		// Calcul de la suite de Fibonacci jusqu'à que le nombre dépasse la taille des int64_t
		if (!stop) {											// Si on peut encore stocker des lapins
			tmpCoupleJeune = coupleAdulte;						// Les adultes créent des couples jeunes
			coupleAdulte += coupleJeune;						// Les jeunes deviennent adultes
			coupleJeune = tmpCoupleJeune;						// Mise à jour du nombre de couples jeunes
			if ((coupleJeune + coupleAdulte) > 0)				// On vérifie de ne pas dépasser la capacité
				nbRabbitFibo = coupleJeune + coupleAdulte;		// Mise à jour du nombre total de lapins
			else												// Si on dépasse la capacité
				stop = true;									// On arrête le calcul de Fibonacci
		}

		// Simulation
        simu.simulateNextMonth();								// Simulation du mois à venir
		time = std::chrono::steady_clock::now() - begin;		// Récupérationd du temps t
        simu.writeToFile("simu.log");							// Ecriture des résultats dans le log
		simu.writeToCSV("data.csv", nbRabbitFibo, time.count(), false);
        std::cout <<"Mois " << ++i << " => Nombre de lapin : " << simu.getNbRabbit() << std::endl;	
    }

    // Calcul du temps d'exécution
    std::chrono::duration<double> duration = std::chrono::steady_clock::now() - begin;
    std::cout << "Temps : " << duration.count() << "s" << std::endl;

    return 0;
}
