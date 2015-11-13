#include "youngrabbit.h"

#if defined(MULTI_THREADING)
#include <future>
#endif  // endif MULTI_THREADING
#include <fstream>
#include <iomanip>
#include <random>
#include <utility>

YoungRabbit::YoungRabbit()
    : m_youngRabbits(9, std::make_pair(0, 0))
{
}

YoungRabbit::~YoungRabbit()
{
}

void YoungRabbit::addYoungRabbit(const rabbits_t nbRabbit)
{
    if (nbRabbit <= 0)
        return;

    std::uniform_int_distribution<> sexDist(0, 1);
    rabbits_t nbFemales = 0;

#if defined(MULTI_THREADING)
    if (nbRabbit >= 30000)
    {
        rabbits_t nbComputePerThread = nbRabbit/MAXTHREADS;
        std::vector< std::future<rabbits_t> > drawPartFunc;

        rabbits_t count = 0;
        // Répartit le nombre de tirages aléatoire à faire sur MAXTHREADS threads
        for (unsigned int i = 0 ; i < MAXTHREADS ; i++)
        {
            // Complète le dernier thread avec les opérations qui serait restante dans le cas où la division en MAXTHREADS n'est pas entière
            if (i == MAXTHREADS-1)
                nbComputePerThread = nbRabbit - count;

            drawPartFunc.push_back(std::async(  std::launch::async,
                                                [&sexDist](const rabbits_t nbCompute)
                                                {
                                                    rabbits_t nbFemales = 0;

                                                    for (rabbits_t i = 0 ; i < nbCompute ; i++)
                                                        if (sexDist(randEngine) == 1)
                                                            nbFemales++;

                                                    return nbFemales;
                                                },
                                                nbComputePerThread));
            count += nbComputePerThread;
        }

        // Attend la fin de chacun des threads
        for (unsigned int i = 0 ; i < MAXTHREADS ; i++)
            nbFemales += drawPartFunc[i].get();
    }
    else
    {
#endif  // endif MULTI_THREADING
        for (rabbits_t i = 0 ; i < nbRabbit ; i++)
        {
            // Tire au sort le sexe du lapereau
            if (sexDist(randEngine) == 1)   // 0 = mâle | 1 = femelle
                nbFemales++;
        }
#if defined(MULTI_THREADING)
    }
#endif  // endif MULTI_THREADING

    m_youngRabbits[0].first += nbFemales;  // Augmente le nombre de femelles
    m_youngRabbits[0].second += (nbRabbit - nbFemales); // Augmente le nombre de mâles
}


/* TODO : pour la mise en place de la gaussienne changer la structure de données, passer en vecteur de vecteur de paires
	pour répartir qui sera adulte au bout de combien de temps */

std::vector< std::pair<rabbits_t, rabbits_t> > YoungRabbit::update()
{
    // Lois de distribution pour le taux de survie
    std::uniform_int_distribution<> survivalDist(0, 99);

    std::vector< std::pair< rabbits_t, rabbits_t > > newAdultsByMonth(5, std::make_pair(0, 0)); // Stocke les évolutions à l'âge adulte des lapereaux (du mois 5 à 9)
	const int survivalRate = (4 / (double) 12) * 20 + 20;							// Taux de survie pour les lapins passant automatiquement adultes
	// Les lapereaux de plus de 8 mois passent automatiquement adultes
    
	// Femelles
    rabbits_t nbFemalesAdult = 0;                           // Nombre de femelles passant véritablement adulte
    const rabbits_t nbFemales = m_youngRabbits[8].first;	// Nombre de femelles devant passer adulte
	
    for (rabbits_t i = 0 ; i < nbFemales ; i++)
         if (survivalDist(randEngine) < survivalRate )
             nbFemalesAdult++;
    // Mâles
    rabbits_t nbMalesAdult = 0;								// Nombre de mâles passant véritablement adulte
    const rabbits_t nbMales = m_youngRabbits[8].second;		// Nombre de mâles devant passé adulte
    for (rabbits_t i = 0 ; i < nbMales ; i++)
         if (survivalDist(randEngine) < survivalRate)
             nbMalesAdult++;

    // Affecte les lapereaux (9 mois) ayant survécus aux adultes automatiquement
    newAdultsByMonth[4].first = nbFemalesAdult;
    newAdultsByMonth[4].second = nbMalesAdult;

    // Fait progresser les lapereaux d'un mois
    for (unsigned int i = m_youngRabbits.size()-1 ; i > 0 ; i--)
        m_youngRabbits[i] = m_youngRabbits[i-1];
    m_youngRabbits[0] = std::make_pair(0, 0);

    // Lois de distribution pour passer à la maturité adulte
    std::uniform_int_distribution<> distribution(0, 3); // TODO distri pour le mois de maturité ==> gaussien

    // Parcours des lapereaux qui sont candidats à l'évolution en maturité adulte
    for (unsigned int i = 5, monthsIndex = 0 ; i < m_youngRabbits.size() ; i++, monthsIndex++)
    {
		// Calcul du taux de survie
		int survivalRate2 = ((12 - i) / 12) * 20 + 20;		// Taux de survie du lapereau selon le mois

        // Nombre de passage à la maturité adulte pour les mâles et les femelles pour la génération courante
        rabbits_t nbAdultsF = 0;
        rabbits_t nbAdultsM = 0;

        // Simule les passages à la maturité adulte pour les femelles
        const rabbits_t nbFemales = m_youngRabbits[i].first;
        for (rabbits_t j = 0 ; j < nbFemales ; j++)
        {
            int rand = distribution(randEngine);
            // Devient adulte
            if (rand == 0)
            {
                nbAdultsF++;
                // On verifie que le lapin survit à sa periode lapereau (20%)
                if (survivalDist(randEngine) < survivalRate2)
                    newAdultsByMonth[monthsIndex].first++;
            }
        }

        // Simule les passages à la maturité adulte pour les mâles
        const rabbits_t nbMales = m_youngRabbits[i].second;
        for (rabbits_t j = 0 ; j < nbMales ; j++)
        {
            int rand = distribution(randEngine);
            // Devient adulte
            if (rand == 0)
            {
                nbAdultsM++;
                // On verifie que le lapin survit à sa periode lapereau (20%)
                if (survivalDist(randEngine) < survivalRate2)
                    newAdultsByMonth[monthsIndex].second++;
            }
        }

        // Enlève les lapins passé à la maturité adulte (et/ou mort)
        m_youngRabbits[i].first -= nbAdultsF;
        m_youngRabbits[i].second -= nbAdultsM;
    }

    return newAdultsByMonth;
}

void YoungRabbit::writeToFile(const std::string& filename)
{
    std::ofstream file;
    file.open(filename.c_str(), std::fstream::out | std::fstream::app);

    if (!file.fail())
    {
        file << "Lapereaux :" << std::endl;
        for (unsigned int i = 0 ; i < m_youngRabbits.size() ; i++)
            file << i << " mois : F = " << std::setw(10) << m_youngRabbits[i].first << "\tM = " << std::setw(10) << m_youngRabbits[i].second << std::endl;
        file.close();
    }
}

rabbits_t YoungRabbit::getNbRabbit() const
{
    rabbits_t count = 0;

    // Compte le nombre de lapereaux mâles et femelles
    for (unsigned int i = 0 ; i < m_youngRabbits.size() ; i++)
        count += (m_youngRabbits[i].first + m_youngRabbits[i].second);

    return count;
}
