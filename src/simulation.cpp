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
    for (int i = 0 ; i < 3 ; i++)
        m_lapereau.push_back(Lapereau());
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

    m_months[currentMonthIndex].update();

    m_monthSimulated++;
}

void Simulation::evolveToAdult(std::uniform_int_distribution<>& survivalDist,
                               const unsigned int currentMonthIndex,
                               std::vector<Lapereau>::iterator itLapereau)
{
    // On verifie que le lapin survit à sa periode lapereau (20%)
    if (survivalDist(randEngine) < 20)
    {
// TODO tenir compte des mois restants jusqu'a la fin de la premiere année du lapin
        unsigned int beforeFirstYear = 12 - itLapereau->getAge();
        const unsigned int birthdayMonthIndex = (currentMonthIndex + beforeFirstYear + 1) % 12;
//std::cout << birthdayMonthIndex << " " << currentMonthIndex << " " << itLapereau->getAge() << " " << beforeFirstYear << std::endl;
        if (itLapereau->isMale())
            m_months[birthdayMonthIndex].addMale();
        else
            m_months[birthdayMonthIndex].addFemale();
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
