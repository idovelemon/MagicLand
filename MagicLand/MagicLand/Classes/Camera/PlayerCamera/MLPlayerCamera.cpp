#include "MLPlayerCamera.h"
#include "../../EntityComponent/MLEntityMgr.h"
#include "../../EntityComponent/MLComTransform.h"
#include "../../marco.h"
using namespace MagicLand;

MLPlayerCamera::MLPlayerCamera()
{
}

MLPlayerCamera::MLPlayerCamera(CCLayer* layer)
{
	m_Layer = layer;
}

MLPlayerCamera::~MLPlayerCamera()
{
	if (m_Layer)
	{
		m_Layer->removeFromParent();
		m_Layer->removeAllChildren();
		m_Layer->release();
		m_Layer = NULL;
	}
}

bool MLPlayerCamera::Init()
{
	return true;
}

void MLPlayerCamera::Update(float delta)
{
	MLComTransform* pTransform = (MLComTransform*)MLEntityMgr::SharedInstance()->GetPlayer()->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "please make sure the pTransform is not null");

	CCPoint position;
	position.x = -pTransform->GetPos().x + 200;
	position.y = 0;
	m_Layer->setPosition(position);
}

void MLPlayerCamera::Kill()
{
	m_IsDead = true;
}

bool MLPlayerCamera::IsDead() const
{
	return m_IsDead;
}