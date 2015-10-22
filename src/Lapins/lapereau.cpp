#include "lapereau.h"

#include "../general/general.h"

Lapereau::Lapereau()
    : Lapin()
    , m_age(0)
{
    // Distribution uniforme pour déterminer le sexe (1 chance sur 2)
    std::uniform_int_distribution<> sexDist(0, 1);
    m_male = sexDist(randEngine);
}

Lapereau::~Lapereau()
{
}

void Lapereau::updateAge(unsigned int update)
{
    m_age += update;
}
