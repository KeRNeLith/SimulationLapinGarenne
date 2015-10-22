#include "lapereau.h"

#include "../general/general.h"

Lapereau::Lapereau()
    : Lapin(20)
{
    // Distribution uniforme pour déterminer le sexe (1 chance sur 2)
    std::uniform_int_distribution<> sexDist(0, 1);
    m_male = sexDist(randEngine);
}

Lapereau::~Lapereau()
{
}
