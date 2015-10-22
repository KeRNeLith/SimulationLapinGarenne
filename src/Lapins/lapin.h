#ifndef LAPIN_H
#define LAPIN_H

/**
 * @brief The Lapin class Gère la représentation abstraite d'un lapin.
 */
class Lapin // should be abstract class
{
protected:
    unsigned short m_survivalRate;  ///< Taux de survie du lapin (0% - 100%).
    unsigned int m_age;             ///< Âge du lapin (en mois).

public:
    /**
     * @brief Lapin Constructeur par défaut.
     */
    Lapin(const unsigned int age = 0, const unsigned short survivalRate = 50);
    /**
     * @brief ~Lapin Destructeur.
     */
    virtual ~Lapin();

    void updateAge(unsigned int update = 1);

    // Accesseurs
    unsigned short getSurvivalrate() const { return m_survivalRate; }
    unsigned int getAge() const { return m_age; }
};

#endif // LAPIN_H
