#include "simulation.h"

#include <future>
#include <thread>

#include "general/general.h"

Simulation::Simulation()
    : m_monthSimulated(0)
{
    // Initialise les 12 mois de l'année
    for (unsigned int i = 0 ; i < 12 ; i++)
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

    for (unsigned int i = 0, nbMonths = 5 ; i < newAdults.size() ; i++, nbMonths++)
    {
        // Tiens compte des mois restant avant la première année du lapin pour l'affecter au bon mois de l'année
        const unsigned int beforeFirstYear = (12 /* Un an */ - nbMonths /* X mois avant anniversaire */);
        const unsigned int birthdayMonthIndex = (currentMonthIndex + beforeFirstYear) % 12;

        // Affecte les adultes mâles et femelles au mois de leur anniversaire
        affectLitters(m_months[birthdayMonthIndex].addFemale(newAdults[i].first, currentMonthIndex));
        m_months[birthdayMonthIndex].addMale(newAdults[i].second);
    }

    // Met à jour les données de simulation pour les lapins adultes concernés
    affectLitters(m_months[currentMonthIndex].update());

    // Fait naitre tous les lapereaux prévu pour ce mois ci
    m_youngRabbits.addYoungRabbit(m_months[currentMonthIndex].getNewBorns());

    // Fin de la simulation du mois
    m_monthSimulated++;
}

void Simulation::affectLitters(const std::vector<rabbits_t> litters)
{
    const unsigned int nbLittersMonths = litters.size();
    for (unsigned int i = 0 ; i < nbLittersMonths ; i++)
        m_months[i].addNewBorns(litters[i]);
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
