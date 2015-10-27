#include "youngrabbit.h"

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
    std::uniform_int_distribution<> sexDist(0, 1);
    for (rabbits_t i = 0 ; i < nbRabbit ; i++)
    {
        // Tire au sort le sexe du lapereau
        if (sexDist(randEngine) == 1)
            m_youngRabbits[0].first++;  // Augmente le nombre de femelles
        else
            m_youngRabbits[0].second++; // Augmente le nombre de mâles
    }
}

std::vector< std::pair<rabbits_t, rabbits_t> > YoungRabbit::update()
{
    std::vector< std::pair< rabbits_t, rabbits_t > > newAdultsByMonth(5, std::make_pair(0, 0)); // Stocke les évolutions à l'âge adulte des lapereaux (du mois 5 à 9)
    // Les lapereaux de plus de 8 mois passe automatiquement adultes
    newAdultsByMonth[4] = m_youngRabbits[m_youngRabbits.size()-1];

    // Fait progresser les lapereaux d'un mois
    for (unsigned int i = m_youngRabbits.size()-1 ; i > 0 ; i--)
        m_youngRabbits[i] = m_youngRabbits[i-1];
    m_youngRabbits[0] = std::make_pair(0, 0);

    // Lois de distribution pour le taux de survie et la chance de passer à la maturité adulte
    std::uniform_int_distribution<> survivalDist(0, 99);
    std::uniform_int_distribution<> distribution(0, 3); // TODO distri pour le mois de maturité

    // Parcours les lapereaux qui sont candidats à l'évolution en maturité adulte
    for (unsigned int i = 5, monthsIndex = 0 ; i < m_youngRabbits.size() ; i++, monthsIndex++)
    {
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
                if (survivalDist(randEngine) < 20)
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
                if (survivalDist(randEngine) < 20)
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
