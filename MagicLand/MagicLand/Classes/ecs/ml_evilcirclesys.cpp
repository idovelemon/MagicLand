#include "ml_evilcirclesys.h"

#include "ml_allcoms.h"
#include "ml_entity.h"

namespace magicland {

MLEvilCircleSys::MLEvilCircleSys(MLEntity* entity)
:MLSystem(entity) {
}

MLEvilCircleSys::~MLEvilCircleSys() {
}

void MLEvilCircleSys::Run(float delta) {

  ML_SAFE_ASSERT(m_Entity != NULL, "No Entity Error");
  if(m_Entity != NULL) {
    MLComTransform* transform = reinterpret_cast<MLComTransform*>(m_Entity->GetComponent(ML_COMTYPE_TRANSFORM));
    ML_SAFE_ASSERT(transform != NULL, "No Component Error");

    MLComDisplay* display = reinterpret_cast<MLComDisplay*>(m_Entity->GetComponent(ML_COMTYPE_DISPLAY));
    ML_SAFE_ASSERT(display != NULL, "No Component Error");

    MLComSpeed* speed = reinterpret_cast<MLComSpeed*>(m_Entity->GetComponent(ML_COMTYPE_SPEED));
    ML_SAFE_ASSERT(speed != NULL, "No Component Error");

    if(transform != NULL
      && display != NULL
      && speed != NULL) {
        // Rotate
        VECTOR2 rot = transform->GetRot();
        float degree = transform->VecToDegree(transform->GetRot());
        degree += speed->GetRotSpeed();
        rot.x = cos(degree / 180.0f * 3.14159);
        rot.y = sin(degree / 180.0f * 3.14159);
        transform->SetRot(rot.x, rot.y);

        // Draw
        display->GetSprite()->setRotation(degree);
    }
  }
}

} // namespace magicland