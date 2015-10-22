#ifndef MONTH_H
#define MONTH_H

#include <vector>

#include "Lapins/lapinadultemale.h"
#include "Lapins/lapinadultefemelle.h"

/**
 * @brief The Month class Gère le stockage des données de simulation d'un mois de l'année.
 */
class Month
{
private:
    unsigned int m_monthNumber;
    std::vector< std::vector< LapinAdulteMale > > m_adultsMale;
    std::vector< std::vector< LapinAdulteFemelle > > m_adultsFemale;

    std::vector< LapinAdulteFemelle* > m_tempAdultsFemale;
    /*std::vector<LapinAdulteMale> m_adulteMale;      ///< Données de simulation liés aux lapins adultes mâles de moins de 11 ans.
    std::vector<LapinAdulteMale> m_adulteMale11;    ///< Données de simulation liés aux lapins adultes mâles de 11 ans.
    std::vector<LapinAdulteMale> m_adulteMale12;    ///< Données de simulation liés aux lapins adultes mâles de 12 ans.
    std::vector<LapinAdulteMale> m_adulteMale13;    ///< Données de simulation liés aux lapins adultes mâles de 13 ans.
    std::vector<LapinAdulteMale> m_adulteMale14;    ///< Données de simulation liés aux lapins adultes mâles de 14 ans.
    std::vector<LapinAdulteFemelle> m_adulteFemelle;    ///< Données de simulation liés aux lapins adultes femelles de moins de 11 ans.
    std::vector<LapinAdulteFemelle> m_adulteFemelle11;  ///< Données de simulation liés aux lapins adultes femelles de 11 ans.
    std::vector<LapinAdulteFemelle> m_adulteFemelle12;  ///< Données de simulation liés aux lapins adultes femelles de 12 ans.
    std::vector<LapinAdulteFemelle> m_adulteFemelle13;  ///< Données de simulation liés aux lapins adultes femelles de 13 ans.
    std::vector<LapinAdulteFemelle> m_adulteFemelle14;  ///< Données de simulation liés aux lapins adultes femelles de 14 ans.*/

public:
    /**
     * @brief Month Constructeur par défaut.
     */
    Month(unsigned int month);
    /**
     * @brief ~Month Destructeur.
     */
    ~Month();

    void addMale();
    void addFemale();

    void update();

    unsigned int getNbRabbit();
};

#endif // MONTH_H