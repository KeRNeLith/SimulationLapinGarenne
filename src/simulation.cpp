#include "simulation.h"

#include <future>
#include <thread>

#include "general/general.h"

#include <iostream>
Simulation::Simulation()
    : m_monthSimulated(0)
{
    // Initialise les 12 mois de l'année
    for (int i = 1 ; i <= 12 ; i++)
        m_months.push_back(Month(i));

    // TODO REMOVE Test avec une population de depart
    m_youngRabbits.addYoungRabbit(24);
}

Simulation::~Simulation()
{
}

void Simulation::simulateNextMonth()
{
    /*const unsigned int nbRabbits = m_lapereau.size();

    const unsigned int nbComputePerAsync = nbRabbits/maxNbThread;
    unsigned int begin = 0;
    unsigned int end;
    std::vector< std::future<void> > updateAgePartFunc;
    for (unsigned int i = 0 ; i < maxNbThread ; ++i)
    {
        end = begin + nbComputePerAsync - 1;
        if (i == maxNbThread-1)
            end = nbRabbits-1;

        updateAgePartFunc.push_back(std::async( std::launch::async,
                                                [this](const unsigned int begin, const unsigned int end)
                                                {
                                                    for (unsigned int i = begin ; i <= end ; ++i)
                                                        m_lapereau[i].updateAge();
                                                },
                                                begin,
                                                end));
        begin += nbComputePerAsync;
    }

    for (unsigned int i = 0 ; i < maxNbThread ; ++i)
        updateAgePartFunc[i].get();*/


    /// Boucle principale de la simultation d'un mois
    const unsigned int currentMonthIndex = m_monthSimulated % 12;

    // Met à jour les données de simulation pour les lapereaux (et récupère les nouveaux adultes)
    std::vector< std::pair<rabbits_t, rabbits_t > > newAdults = m_youngRabbits.update();

    // Tiens compte des mois restant avant la première année du lapin pour l'affecter au bon mois de l'année
    unsigned int beforeFirstYear = 12 /* Un an */ - 5 /* 5 mois */;
    for (unsigned int i = 0 ; i < newAdults.size() ; i++)
    {
        const unsigned int birthdayMonthIndex = (currentMonthIndex + beforeFirstYear + 1) % 12;

        m_months[birthdayMonthIndex].addFemale(newAdults[i].first);
        m_months[birthdayMonthIndex].addMale(newAdults[i].second);

        beforeFirstYear--;
    }

    // Met à jour les données de simulation pour les lapins adultes concernés
    m_months[currentMonthIndex].update();

    // Fait naitre tous les lapereaux prévu pour ce mois ci
    m_youngRabbits.addYoungRabbit(m_months[currentMonthIndex].getNewBorns());

    // Fin de la simulation du mois
    m_monthSimulated++;
}

rabbits_t Simulation::getNbRabbit() const
{
    rabbits_t count = 0;
    // Nombre de lapins adultes
    for (unsigned int i = 0 ; i < m_months.size() ; i++)
        count += m_months[i].getNbRabbit();
    // Nombre de lapereaux
    count += m_youngRabbits.getNbRabbit();

    return count;
}
