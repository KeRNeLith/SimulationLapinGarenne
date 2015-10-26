#include "month.h"

Month::Month(unsigned int month)
    : m_monthNumber(month)
    , m_newBorns(0)
    , m_adultsMale(15, 0)
    , m_adultsFemale(15, 0)
{
}

Month::~Month()
{
}

void Month::addMale(const rabbits_t number)
{
    m_adultsMale[0] += number;
}

void Month::addFemale(const rabbits_t number)
{
    m_adultsFemale[0] += number;

    // Détermine les mois où le lapin femelle adulte aura ses portées
    for (rabbits_t i = 0 ; i < number ; i++)
    {
        // TODO
    }
}

void Month::update()
{
    // Fait progresser les lapins d'un an (les lapins de 15 ans sont automatiquement tués)
    for (unsigned int i = m_adultsFemale.size()-1 ; i > 0 ; i--)
    {
        m_adultsFemale[i] = m_adultsFemale[i-1];
        m_adultsMale[i] = m_adultsMale[i-1];
    }
    m_adultsFemale[0] = 0;
    m_adultsMale[0] = 0;

    // On traite les lapins ayant entre 2 et 14 ans car les lapins ayant 1 an ont déjà été traité lors de leur affectation au groupe 0 année
    // Application des taux de mortalité
    // Applique le taux de survie de 50% sur les lapins entre 2 et 10 ans et 40% diminué de 10% par année sur les lapins entre 11 et 14 ans
    int survivalRate = 50;
    const unsigned int nbGeneration = m_adultsMale.size()-1;
    std::uniform_int_distribution<> survivalDist(0, 99);
    for (unsigned int i = 2 ; i <= nbGeneration ; i++)
    {
        // Pour le taux dégressif entre 11 et 14 ans
        if (i >= 11)
            survivalRate -= 10;

        rabbits_t nbDeathM = 0;
        rabbits_t nbDeathF = 0;
        // Tire les taux de survie pour les lapins mâles
        const rabbits_t nbRabbitsM = m_adultsMale[i];
        for (rabbits_t j = 0 ; j < nbRabbitsM ; j++)
        {
            if (survivalDist(randEngine) < survivalRate)
                nbDeathM++;
        }

        // Tire les taux de survie pour les lapins femelles
        const rabbits_t nbRabbitsF = m_adultsFemale[i];
        for (rabbits_t j = 0 ; j < nbRabbitsF ; j++)
        {
            if (survivalDist(randEngine) < survivalRate)
                nbDeathF++;
        }

        // Tue les lapins nécessaires
        m_adultsMale[i] -= nbDeathM;
        m_adultsFemale[i] -= nbDeathF;
    }

    // TODO faire les calculs de portées des femelles
}

rabbits_t Month::getNewBorns()
{
    const rabbits_t newBorn = m_newBorns;
    m_newBorns = 0;     // Remet à 0 les nouveaux né du mois
    return newBorn;
}

rabbits_t Month::getNbRabbit() const
{
    rabbits_t count = 0;

    // Nombre de lapins adultes mâles
    for (unsigned int i = 0 ; i < m_adultsMale.size() ; i++)
        count += m_adultsMale[i];

    // Nombre de lapins adultes femelles
    for (unsigned int i = 0 ; i < m_adultsFemale.size() ; i++)
        count += m_adultsFemale[i];

    return count;
}
