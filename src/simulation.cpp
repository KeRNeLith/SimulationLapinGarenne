#include "simulation.h"

#include <iomanip>
#include <fstream>

#include "general/general.h"

Simulation::Simulation()
    : m_monthSimulated(0)
{
    // Initialise les 12 mois de l'année
    for (unsigned int i = 0 ; i < 12 ; i++)
        m_months.push_back(Month(i));

    // Population de depart (cf. Australie)
    m_youngRabbits.addYoungRabbit(24);
}

Simulation::~Simulation()
{
}

void Simulation::simulateNextMonth()
{
    /// Boucle principale de la simulation d'un mois
    const unsigned int currentMonthIndex = m_monthSimulated % 12;

    // Met à jour les données de simulation pour les lapereaux (et récupère les nouveaux adultes)
    std::vector< std::pair< rabbits_t, rabbits_t > > newAdults = m_youngRabbits.update();

    for (unsigned int i = 0, nbMonths = 5 ; i < newAdults.size() ; i++, nbMonths++)
    {
        // Tient compte des mois restants avant la première année du lapin pour l'affecter au bon mois de l'année
        const unsigned int beforeFirstYear = (12 /* Un an */ - nbMonths /* X mois avant anniversaire */);
        const unsigned int birthdayMonthIndex = (currentMonthIndex + beforeFirstYear) % 12;

        // Affecte les adultes mâles et femelles au mois de leur anniversaire
        affectLitters(m_months[birthdayMonthIndex].addFemale(newAdults[i].first, currentMonthIndex));
        m_months[birthdayMonthIndex].addMale(newAdults[i].second);
    }

    // Met à jour les données de simulation pour les lapins adultes concernés
    affectLitters(m_months[currentMonthIndex].update());

    // Fait naitre tous les lapereaux prévu pour ce mois ci
    m_youngRabbits.addYoungRabbit(m_months[currentMonthIndex].giveBirth());

    // Fin de la simulation du mois
    m_monthSimulated++;
}

void Simulation::writeToFile(const std::string& filename, const double time)
{
    // Ecrit les données de simulation dans un fichier
    std::ofstream file;

    file.open(filename.c_str(), std::fstream::out | std::fstream::app);
    if (!file.fail())
    {
        file << "---------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        file << "Time : " << time << "s" << std::endl;
        file << "Mois simulé : " << m_monthSimulated << std::endl << std::endl;
        file.close();
    }

    m_youngRabbits.writeToFile(filename);

    file.open(filename.c_str(), std::fstream::out | std::fstream::app);
    if (!file.fail())
    {
        file << std::endl << "Lapins Adultes :" << std::endl;
        file << "\t\t\t\t\t";
        for (unsigned int i = 0 ; i < m_months.size() ; i++)
            file << std::setw(32) << m_months[i].monthName().c_str();
        file << std::endl;

        const unsigned int nbGenerations = m_months[0].getMaleAdults().size();
        for (unsigned int i = 0 ; i < nbGenerations ; i++)
        {
            file << std::setw(2) << i << " ans : \t\t\t";
            for (unsigned int j = 0 ; j < m_months.size() ; j++)
            {
                file << "| F : " << std::setw(10) << m_months[j].getFemaleAdults()[i] << " M : " << std::setw(10) << m_months[j].getMaleAdults()[i] << " |";
            }

            file << std::endl;
        }

        file << "futurs lapereaux :\t";
        for (unsigned int i = 0 ; i < m_months.size() ; i++)
            file << std::setw(32) << m_months[i].getNewBorns();
        file << std::endl;

        file << std::endl << "Nombre total de lapin : " << getNbRabbit() << std::endl << std::endl;
        file.close();
    }
}

void Simulation::writeToCSV(const std::string& filename, const rabbits_t totalFibo, const double time, const bool entete)
{
	std::ofstream file;

	file.open(filename.c_str(), std::fstream::out | std::fstream::app);
	if (!file.fail())
	{
		rabbits_t nbFemale = 0, nbMale = 0;
		
		if (entete)
			file << "Month,Nb Rabbit Total,Nb Adults Male,Nb Adults Female"
				<< ",Nb Young Rabbit Male,Nb Young Rabbit Female,Nb Litters"
				<< ",Nb Fibonacci Total, Time" << std::endl;

		file << m_monthSimulated << "," << getNbRabbit() << ",";
		for (unsigned int i = 0; i < m_months.size(); i++) {
			for (unsigned int j = 0; j < m_months[i].getMaleAdults().size(); j++)
				nbMale += m_months[i].getMaleAdults()[j];
			for (unsigned int j = 0; j < m_months[i].getFemaleAdults().size(); j++)
				nbFemale += m_months[i].getFemaleAdults()[j];
		}		// Calcul du nombre total de femelles et de males
		
		// Ecriture des résultats pour les adultes dans le fichier
		file << nbMale << "," << nbFemale << ",";			
		file.close();
	}

	m_youngRabbits.writeToCSV(filename);

	// Ecriture des portées prévues
	file.open(filename.c_str(), std::fstream::out | std::fstream::app);
	if( !file.fail())
	{
		rabbits_t nbLitters = 0;
		for (unsigned int i = 0; i < m_months.size(); i++)
			nbLitters += m_months[i].getNewBorns();
		
		file << nbLitters << "," << totalFibo << "," << time << std::endl;
		file.close();
	}
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
