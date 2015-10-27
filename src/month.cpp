#include "month.h"

#include <fstream>

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

std::vector<rabbits_t> Month::addFemale(const rabbits_t number, const unsigned int beginMonth)
{
    m_adultsFemale[0] += number;

    // Nombre de mois restant avant le premier anniversaire
    unsigned int nbMonths;
    if (beginMonth >= m_monthNumber)
        nbMonths = 12 - (beginMonth - m_monthNumber);
    else
        nbMonths = m_monthNumber - beginMonth;

    // Applique un pro rata de nombre de portée jusqu'au premier anniversaire
    return computeLitters(number, beginMonth, nbMonths);
}

std::vector<rabbits_t> Month::update()
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
    const unsigned int nbGeneration = m_adultsFemale.size()-1;
    std::uniform_int_distribution<> survivalDist(0, 99);
    rabbits_t nbFemale = 0;     // Nombre de hase qui vont donner des lapereaux sur l'année qui suit
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

        // Met à jour le nombre hases qui donneront des lapereaux
        nbFemale += m_adultsFemale[i];
    }

    nbFemale += m_adultsFemale[1];  // Hases n'ayant pas encore été comptés (celle ayant 1 an)

    // Calculs de portées des femelles qui restent en vie pour l'année suivante
    return computeLitters(nbFemale, m_monthNumber);
}

void Month::addNewBorns(const rabbits_t number)
{
    m_newBorns += number;
}

std::vector<rabbits_t> Month::computeLitters(const rabbits_t nbRabbits, const unsigned int beginMonth, const unsigned int nbMonths)
{
    // Tableau des 12 mois de l'année qui va contenir le nombre de lapereaux mis à bas sur une année (mois par mois)
    std::vector<rabbits_t> monthsLitters(12, 0);

    std::uniform_int_distribution<> littersDist(std::trunc(4*nbMonths/(double)12.0), std::trunc(8*nbMonths/(double)12.0));  // TODO choisir la distribution (plus sur le 5 6 et 7)
    // Détermine les mois où le lapin femelle adulte aura ses portées
    for (rabbits_t rabbit = 0 ; rabbit < nbRabbits ; rabbit++)
    {
        int nbLitters = littersDist(randEngine);

        // Initialise avec les index des mois de l'année (en prenant pour mois 0 le mois courant)
        // Exemple si le mois courant est Juin, on répartit les portée de Juin à Juin de l'année suivante.
        std::vector<unsigned int> possibleLitters(nbMonths);
        for (unsigned int i = 0 ; i < nbMonths ; i++)
            possibleLitters[i] = (i + beginMonth + 1 /* Voir x */) % 12; // x : La prochaine naissance ne peut être que le mois suivant au mieux, décale donc le premier mois possible pour les portées

        std::uniform_int_distribution<> youngRabbitPerLitterDist(3, 6); // TODO choisir la distribution
        // On calcule les différentes portées à affecter à la hase
        for (unsigned int i = nbLitters ; i > 0 ; i--)
        {
            std::uniform_int_distribution<> selectMonthDist(0, possibleLitters.size()-1);

            int selectedIndex = selectMonthDist(randEngine);    // Sélectionne un index correspondant à un mois de l'année encore disponible
            monthsLitters[possibleLitters[selectedIndex]] += youngRabbitPerLitterDist(randEngine);  // Ajoute une portée avec un nombre de lapereaux à ce mois
            possibleLitters.erase(possibleLitters.begin() + selectedIndex); // Supprime le mois pour ne pas avoir 2 portées pour ce même mois
        }
    }

    return monthsLitters;
}

const std::string Month::monthName() const
{
    std::string name = "";
    switch (m_monthNumber)
    {
    case 0:
        name = "Janvier";
        break;
    case 1:
        name = "Février";
        break;
    case 2:
        name = "Mars";
        break;
    case 3:
        name = "Avril";
        break;
    case 4:
        name = "Mai";
        break;
    case 5:
        name = "Juin";
        break;
    case 6:
        name = "Juillet";
        break;
    case 7:
        name = "Août";
        break;
    case 8:
        name = "Septembre";
        break;
    case 9:
        name = "Octobre";
        break;
    case 10:
        name = "Novembre";
        break;
    case 11:
        name = "Décembre";
        break;
    }

    return name;
}

rabbits_t Month::getNewBorns() const
{
    return m_newBorns;
}

rabbits_t Month::giveBirth()
{
    const rabbits_t newBorn = m_newBorns;
    m_newBorns = 0;     // Remet à 0 les nouveaux né du mois
    return newBorn;
}

std::vector< rabbits_t > Month::getMaleAdults() const
{
    return m_adultsMale;
}

std::vector< rabbits_t > Month::getFemaleAdults() const
{
    return m_adultsFemale;
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
