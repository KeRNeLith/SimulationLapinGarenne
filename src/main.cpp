#include <iostream>
#include <sstream>

#include "simulation.h"

int main(int /*argc*/, char** /*argv*/)
{
	// Variables pour calculer Fibonacci en parallèle
	bool		stop = false;									// Booléen qui active ou non le calcul de Fibonacci
	rabbits_t	tmpCoupleJeune;
	rabbits_t	coupleJeune = 1;								// Nombre de lapins "jeunes"
	rabbits_t	coupleAdulte = 0;								// Nombre de lapins adultes
	rabbits_t	nbRabbitFibo = coupleAdulte + coupleJeune;		// Nombre de lapins total calculés par Fibonacci
    
    //const unsigned int nbMonth = 100;
    const unsigned int nbReplic = 100;
    for (unsigned int rep = 0 ; rep < nbReplic ; rep++)
    {
        std::cout << "Réplication " << rep << std::endl;
        std::cout << "---------------------------------------------------------------------------------" << std::endl;

        // Pour le temps d'exécution
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::duration<double> time;

        Simulation simu;
        std::stringstream ssLog;
        ssLog << "simu" << rep << ".log";
        std::stringstream ssCSV;
        ssCSV << "data" << rep << ".csv";
        simu.writeToFile(ssLog.str(), 0.0);
        simu.writeToCSV(ssCSV.str(), nbRabbitFibo, 0.0, true);

        unsigned int i = 0;
        // Jusqu'à atteindre 1 Milliard de lapins
        while(simu.getNbRabbit() < 1000000000)
        {
            // Calcul de la suite de Fibonacci jusqu'à que le nombre dépasse la taille des int64_t
            if (!stop)  // Si on peut encore stocker des lapins
            {
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

            simu.writeToFile(ssLog.str(), time.count());            // Ecriture des résultats dans le log
            simu.writeToCSV(ssCSV.str(), nbRabbitFibo, time.count(), false);  // Fichier CSV de statistiques

            std::cout <<"Mois " << ++i << " => Nombre de lapin : " << simu.getNbRabbit() << std::endl;
        }

        // Calcul du temps d'exécution
        std::chrono::duration<double> duration = std::chrono::steady_clock::now() - begin;
        std::cout << "Temps : " << duration.count() << "s" << std::endl;
    }

    return 0;
}
