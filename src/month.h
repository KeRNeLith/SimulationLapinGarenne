#ifndef MONTH_H
#define MONTH_H

#include <vector>

#include "general/general.h"

/**
 * @brief The Month class Gère le stockage des données de simulation d'un mois de l'année.
 */
class Month
{
private:
    unsigned int m_monthNumber;             ///< Numéro du mois (1 à 12).
    rabbits_t m_newBorns;                   ///< Nombre de lapereaux qui naitront ce mois ci.
    std::vector< rabbits_t > m_adultsMale;  ///< Données de simulation pour les mâles du mois courant (Par tranche d'années 0 à 14 ans).
    std::vector< rabbits_t > m_adultsFemale;///< Données de simulation pour les femelles du mois courant (Par tranche d'années 0 à 14 ans).

    /**
     * @brief computeLitters Calcule une répartition des portées pour nbRabbits hase sur une année à partir du mois courant.
     * @param nbRabbits Nombre de hase à considérer.
     * @param beginMonth Mois à partir duquel on commence à générer des portées de lapereaux.
     * @param nbMonths Nombre de mois sur lequel on génère des portées.
     * @return Tableau représentant le nombre de lapereaux par mois qui naitront au cours de l'année qui suit.
     */
    std::vector<rabbits_t> computeLitters(const rabbits_t nbRabbits, const unsigned int beginMonth, const unsigned int nbMonths = 12);

public:
    /**
     * @brief Month Constructeur par défaut.
     */
    Month(unsigned int month);
    /**
     * @brief ~Month Destructeur.
     */
    ~Month();

    /**
     * @brief addMale Ajoute un nombre de lapins adultes mâles au mois.
     * @param number Nombre de lapins à ajouter.
     */
    void addMale(const rabbits_t number = 1);

    /**
     * @brief addFemale Ajoute un nombre de lapins adultes femelles au mois.
     * @param number Nombre de lapins à ajouter.
     * @param beginMonth Mois à partir duquel on autorise les portées.
     * @return Tableau représentant le nombre de lapereaux par mois qui naitront au cours de l'année qui suit grâce aux hase ajoutées.
     */
    std::vector<rabbits_t> addFemale(const rabbits_t number, const unsigned int beginMonth);

    /**
     * @brief update Met à jour les données de simulation du mois pour un pas de temps.
     * @return Tableau représentant le nombre de lapereaux par mois qui naitront au cours de l'année qui suit grâce aux hases de ce mois.
     */
    std::vector<rabbits_t> update();

    /**
     * @brief addNewBorns Ajoute des lapereaux qui naitront ce mois ci.
     * @param number Nombre de lapereaux à ajouter.
     */
    void addNewBorns(const rabbits_t number = 1);

    // Accesseurs
    /**
     * @brief getNewBorns Récupère le nombre de lapereaux qui doivent naitre ce mois ci.
     * @return Nombre de lapereaux qui doivent naitre.
     */
    rabbits_t getNewBorns() const;

    /**
     * @brief giveBirth Récupère le nombre de lapereaux qui doivent naitre ce mois ci.
     * NOTE : Réinitilise le compteur de lapereaux à faire naitre.
     * @return Nombre de lapereaux qui doivent naitre.
     */
    rabbits_t giveBirth();

    /**
     * @brief getMaleAdults Récupère le nombre de lapins mâles répartient par année.
     * @return Tableau du nombre de lapins adultes mâles par tranches d'âge.
     */
    std::vector< rabbits_t > getMaleAdults() const;

    /**
     * @brief getFemaleAdults Récupère le nombre de lapins femelles réparties par année.
     * @return Tableau du nombre de lapins adultes femelles par tranches d'âge.
     */
    std::vector< rabbits_t > getFemaleAdults() const;

    /**
     * @brief getNbRabbit Calcul et retourne le nombre total de lapins vivants sur le mois courant.
     * @return Nombre de lapins vivants sur le mois courant.
     */
    rabbits_t getNbRabbit() const;

    /**
     * @brief monthName Retourne le nom mois correspondant.
     * @return Nom du mois courant.
     */
    const std::string monthName() const;
};

#endif // MONTH_H
