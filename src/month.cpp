#include "month.h"

Month::Month()
{
}

Month::~Month()
{
}
#include <iostream>
void Month::addMale(const unsigned int age)
{
    m_adulteMale.push_back(LapinAdulteMale(age));
}

void Month::addFemale(const unsigned int age)
{
    m_adulteFemelle.push_back(LapinAdulteFemelle(age));
}

unsigned int Month::getNbRabbit()
{
    unsigned int count = m_adulteMale.size();
    count += m_adulteMale11.size();
    count += m_adulteMale12.size();
    count += m_adulteMale13.size();
    count += m_adulteMale14.size();
    count += m_adulteMale15.size();

    count += m_adulteFemelle.size();
    count += m_adulteFemelle11.size();
    count += m_adulteFemelle12.size();
    count += m_adulteFemelle13.size();
    count += m_adulteFemelle14.size();
    count += m_adulteFemelle15.size();

    return count;
}
