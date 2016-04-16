#include "reference/ml_reference.h"

using namespace MagicLand;

MLReference::MLReference()
    :m_RefCounted(1)
{
}

MLReference::~MLReference()
{
}

void MLReference::Grab()
{
    m_RefCounted++;
}

void MLReference::Drop()
{
    m_RefCounted--;
    if(m_RefCounted <= 0)
    {
        delete this;
    }
}