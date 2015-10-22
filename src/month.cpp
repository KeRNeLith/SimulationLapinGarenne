#include "month.h"

#include "general/general.h"

Month::Month(unsigned int month)
    : m_monthNumber(month)
    , m_adultsMale(15)
    , m_adultsFemale(15)
{
}

Month::~Month()
{
}

void Month::addMale()
{
    m_adultsMale[0].push_back(LapinAdulteMale());
}

void Month::addFemale()
{
    m_adultsFemale[0].push_back(LapinAdulteFemelle());
    // Détermine les mois où le lapin femelle adulte aura ses portées
    // TODO
}

void Month::update()
{
    // Fait progresser les lapins d'un an (les lapins de 15 ans sont automatiquement tués)
    for (unsigned int i = m_adultsFemale.size()-1 ; i > 0 ; i--)
    {
        m_adultsFemale[i] = std::move(m_adultsFemale[i-1]);
        m_adultsMale[i] = std::move(m_adultsMale[i-1]);
    }
    // Il n'y a plus de lapin avec 0 années il passent tous à 1 ans (car ils complètent leur période entre la fin de maturité et leur première année)
    m_adultsFemale[0].clear();

    // On traite les lapins ayant entre 2 et 14 ans car les lapins ayant 1 an ont déjà été traité lors de leur affectation au groupe 0 année
    // Application des taux de mortalité
    // Applique le taux de survie de 50% sur les lapins entre 2 et 10 ans
    std::uniform_int_distribution<> survivalDist(0, 99);
    for (unsigned int i = 2 ; i <= 10 ; i++)
    {
        unsigned int nbDeathM = 0;
        unsigned int nbDeathF = 0;
        for (unsigned int j = 0 ; j < m_adultsMale[i].size() ; i++)
        {
            if (survivalDist(randEngine) < 50)
                nbDeathM++;
        }

        for (unsigned int j = 0 ; j < m_adultsFemale[i].size() ; i++)
        {
            if (survivalDist(randEngine) < 50)
                nbDeathF++;
        }

        m_adultsMale[i].resize(m_adultsMale[i].size() - nbDeathM);
        m_adultsFemale[i].resize(m_adultsFemale[i].size() - nbDeathF);
    }

    // Applique le taux de survie de 40% diminué de 10% par année sur les lapins entre 11 et 14 ans
    int survivalRate = 40;
    for (unsigned int i = 11 ; i < m_adultsMale.size() ; i++)
    {
        unsigned int nbDeathM = 0;
        unsigned int nbDeathF = 0;
        for (unsigned int j = 0 ; j < m_adultsMale[i].size() ; i++)
        {
            if (survivalDist(randEngine) < survivalRate)
                nbDeathM++;
        }

        for (unsigned int j = 0 ; j < m_adultsFemale[i].size() ; i++)
        {
            if (survivalDist(randEngine) < survivalRate)
                nbDeathF++;
        }

        m_adultsMale[i].resize(m_adultsMale[i].size() - nbDeathM);
        m_adultsFemale[i].resize(m_adultsFemale[i].size() - nbDeathF);
        survivalRate -= 10;
    }

    // TODO faire les calculs de portées des femelles
}

unsigned int Month::getNbRabbit()
{
    unsigned int count = 0;

    for (unsigned int i = 0 ; i < m_adultsMale.size() ; i++)
        count += m_adultsMale[i].size();

    for (unsigned int i = 0 ; i < m_adultsFemale.size() ; i++)
        count += m_adultsFemale[i].size();

    return count;
}
