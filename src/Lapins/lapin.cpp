#include "lapin.h"

Lapin::Lapin(const unsigned short survivalRate, const unsigned int age)
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
