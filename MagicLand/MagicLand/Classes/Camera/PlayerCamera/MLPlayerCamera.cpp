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
	calculateCamrea();
}

void MLPlayerCamera::Kill()
{
	m_IsDead = true;
}

bool MLPlayerCamera::IsDead() const
{
	return m_IsDead;
}

void MLPlayerCamera::calculateCamrea()
{
	MLComTransform* playerTransform = (MLComTransform*)MLEntityMgr::SharedInstance()->GetPlayer()->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(playerTransform != NULL, "please make sure the playerTransform is not null");
	if(playerTransform != NULL)
	{
		int cameraPosX = m_Layer->getPositionX();
		int cameraPosY = m_Layer->getPositionY();
		int playerPosX = playerTransform->GetPos().x;
		int playerPosY = playerTransform->GetPos().y;

		if (playerPosX > 800 - 800 * 0.3 - cameraPosX)
		{
			cameraPosX = -(playerPosX - (800 - 800 * 0.3));
		}
		else if (playerPosX < 800 * 0.3 - cameraPosX)
		{
			cameraPosX -= playerPosX - (800 * 0.3 - cameraPosX);
		}

		if (playerPosX < 800 * 0.3)
		{
			cameraPosX = 0;
		}
		else if (playerPosX > 1600 - 800 * 0.3)
		{
			cameraPosX = -800;
		}

		CCPoint position;
		position.x = cameraPosX;
		position.y = cameraPosY;

		ML_SAFE_ASSERT(m_Layer != NULL, "Layer can not be null");
		if(m_Layer != NULL)
		{
			m_Layer->setPosition(position);
		}
	}
}