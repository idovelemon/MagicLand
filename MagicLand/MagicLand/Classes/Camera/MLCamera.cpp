#include "MLCamera.h"
#include "../marco.h"
using namespace MagicLand;

MLCamera::MLCamera()
{
}

MLCamera::MLCamera(CCLayer* layer)
    :m_Layer(layer)
    ,m_IsDead(false)
{
    ML_SAFE_ASSERT(layer != NULL, "Please pass a valid layer pointer");
}

MLCamera::~MLCamera()
{
    if(m_Layer != NULL)
    {
        m_Layer->removeFromParent();
        m_Layer->removeAllChildren();
        m_Layer->release();
        m_Layer = NULL;
    }
}

void MLCamera::Kill()
{
    m_IsDead = true;
}

bool MLCamera::IsDead() const
{
    return m_IsDead;
}