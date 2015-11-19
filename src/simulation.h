#ifndef SIMULATION_H
#define SIMULATION_H

#include <random>
#include <vector>

#include "month.h"
#include "youngrabbit.h"

/**
 * @brief The Simulation class Gère le stockage des données de simulation.
 * Elle est chargée de faire progresser la simulation en fournissant une interface adaptée.
 */
class Simulation
{
private:
    unsigned int m_monthSimulated;  ///< Nombre de mois simulés.
    std::vector<Month> m_months;    ///< Données de simulation sur l'année.
    YoungRabbit m_youngRabbits;     ///< Données de simulation pour tous les lapereaux.

    /**
     * @brief affectLitters Affecte tous les lapereaux issues des portées générées aux bons mois en les ajoutants à ceux qui existent déjà.
     * NOTE : Ces lapereaux ne sont pas encore nés, il ne verront le jours que lorsque les mois en question seront mis à jour)
     * @param litters Tableau des portées par mois (Chaque indice i contient le nombre de lapereaux qui verront le jour au i-ème mois).
     */
    void affectLitters(const std::vector<rabbits_t> litters);

public:
    /**
     * @brief Simulation Constructeur par défaut.
     */
    Simulation();
    /**
     * @brief ~Simulation Destructeur.
     */
    ~Simulation();

    /**
     * @brief simulateNextMonth Avance la simulation de un mois.
     */
    void simulateNextMonth();

    /**
     * @brief writeToFile Enregistre les données de simulation actuelles dans un fichier.
     * @param filename Nom du fichier dans lequel enregistrer.
     */
    void writeToFile(const std::string& filename);

	/**
	* @brief writeToCSV Enregistre les données de simulation actuelles dans un fichier .csv pour tracé depuis un tableur.
	* @param filename Nom du fichier dans lequel enregistrer.
	* @param totalFibo Nombre de lapins au total calculé par Fibonacci.
	* @param entete Ordonne à la méthode d'écrire l'entête CSV ou non.
	*/
	void writeToCSV(const std::string& filename, const rabbits_t totalFibo, const bool entete);

    /**
     * @brief getNbRabbit Calcul et retourne le nombre total de lapins vivants dans la simulation.
     * @return Nombre de lapins vivants dans la simulation.
     */
    rabbits_t getNbRabbit() const;
};

#endif // SIMULATION_H
