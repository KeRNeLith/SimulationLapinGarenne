#include "simulation.h"

#include "general/general.h"
#include <iostream>
Simulation::Simulation()
    : m_monthSimulated(0)
{
    // Initialise les 12 mois de l'année
    for (int i = 0 ; i < 12 ; i++)
        m_months.push_back(Month());

    // TODO REMOVE Test avec une population de depart
    for (int i = 0 ; i < 10 ; i++)
        m_lapereau.push_back(Lapereau());
}

Simulation::~Simulation()
{
}

void Simulation::simulateNextMonth()
{
    std::uniform_int_distribution<> survivalDist(0, 99);
    const unsigned int currentMonthIndex = m_monthSimulated % 12;

    auto it = m_lapereau.begin();
    while (it != m_lapereau.end())
    {
        it->updateAge();
        // Entrée dans la période de maturation (5 à 8 mois)
        if (it->getAge() >= 5)
        {
            // Si on est encore dans la période de maturation
            if (it->getAge() < 9)
            {
// TODO Choisir une loi pour devenir adulte
                std::uniform_int_distribution<> distribution(0, 3);
                int rand = distribution(randEngine);
                // Devient adulte
                if (rand == 0)
                    evolveToAdult(survivalDist, currentMonthIndex, it);
                else
                    it++;
            }
            // Evolution automatique en adulte (> 9 mois)
            else
                evolveToAdult(survivalDist, currentMonthIndex, it);
        }
        else
            it++;
    }

    m_monthSimulated++;
}

void Simulation::evolveToAdult(std::uniform_int_distribution<>& survivalDist,
                               const unsigned int currentMonthIndex,
                               std::vector<Lapereau>::iterator itLapereau)
{
    // On verifie que le lapin survit à sa periode lapereau
    if (survivalDist(randEngine) >= itLapereau->getSurvivalrate())
    {
        if (itLapereau->isMale())
            m_months[currentMonthIndex].addMale(itLapereau->getAge());
        else
            m_months[currentMonthIndex].addFemale(itLapereau->getAge());
    }

    m_lapereau.erase(itLapereau);
}

unsigned int Simulation::getNbRabbit()
{
    unsigned int count = 0;
    for (unsigned int i = 0 ; i < m_months.size() ; i++)
        count += m_months[i].getNbRabbit();
    count += m_lapereau.size();

    return count;
}
