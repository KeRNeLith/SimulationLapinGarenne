#include "lapin.h"

Lapin::Lapin(const unsigned int age, const unsigned short survivalRate)
    : m_survivalRate(survivalRate)
    , m_age(age)
{
}

Lapin::~Lapin()
{
}

void Lapin::updateAge(unsigned int update)
{
    m_age += update;
}
