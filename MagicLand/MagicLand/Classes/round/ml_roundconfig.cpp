#include "ml_roundconfig.h"

#include "cocos2d.h"

#include "marco.h"
#include "ecs/ml_allcoms.h"
#include "ecs/ml_entity.h"
#include "ecs/ml_playersys.h"
#include "ecs/ml_single_particle.h"
#include "ml_entitymgr.h"

namespace magicland {

//------------------------------------------------------------------
// Class/TypeDef
//------------------------------------------------------------------
class MLRoundConfigImp {
public:
  static MLRoundConfigImp* SharedInstance();
  static void DestroyInstance();

public:
  int32_t Init();
  void Destroy();
  int32_t ConfigRound(int32_t round);

private:
  MLRoundConfigImp();
  virtual ~MLRoundConfigImp();
  MLEntity* CreatePlayer();
  MLEntity* CreateMonster();

  static MLRoundConfigImp* s_Instance;
  ML_DISALLOW_COPY_AND_ASSIGN(MLRoundConfigImp);
};

//------------------------------------------------------------------
// Implement
//------------------------------------------------------------------

//------------------------------------------------------------------
// Implement MLRoundConfigImp
//------------------------------------------------------------------
MLRoundConfigImp* MLRoundConfigImp::s_Instance = NULL;

MLRoundConfigImp::MLRoundConfigImp() {
}

MLRoundConfigImp::~MLRoundConfigImp() {
}

MLRoundConfigImp* MLRoundConfigImp::SharedInstance() {
  if(s_Instance == NULL) {
    s_Instance = new MLRoundConfigImp();
    ML_SAFE_ASSERT(s_Instance != NULL, "Memory Error");
  }

  return s_Instance;
}

void MLRoundConfigImp::DestroyInstance() {
  ML_SAFE_DELETE(s_Instance);
}

int32_t MLRoundConfigImp::Init() {
  return 0;
}

void MLRoundConfigImp::Destroy() {
}

int32_t MLRoundConfigImp::ConfigRound(int32_t round) {

  MLEntity* player = CreatePlayer();
  MLEntityMgr::AddEntity(player);
  ML_SAFE_DROP(player);
  //MLEntity* monster = CreateMonster();
  //MLEntityMgr::AddEntity(monster);

  return 0;
}

MLEntity* MLRoundConfigImp::CreatePlayer() {

  MLEntity* entity = new MLEntity(ML_ETYMAINTYPE_PLAYER, ML_ETYSUBTYPE_PLAYER);
  ML_SAFE_ASSERT(entity != NULL, "Memory Error");
  if(entity != NULL) {
    // Create Display Component
    MLComDisplay* display = new MLComDisplay(entity, "Image/Player/Player.png"
      ,reinterpret_cast<cocos2d::CCLayer*>(cocos2d::CCDirector::sharedDirector()->getRunningScene()->getChildByTag(1)));
    ML_SAFE_ASSERT(display != NULL, "Memeory Error");
    display->GetSprite()->setAnchorPoint(ccp(0.5f, 0.5f));
    display->GetSprite()->setPosition(ccp(400, 64));
    entity->AddComponent(display);
    ML_SAFE_DROP(display);

    // Create Transform Component
    MLComTransform* transform = new MLComTransform(entity, 400, 64, 1.0f, 1.0f, 1.0f, 0.0f);
    ML_SAFE_ASSERT(transform != NULL, "Memory Error");
    entity->AddComponent(transform);
    ML_SAFE_DROP(transform);

    // Create Weapons Component
    MLComWeapons* weapons = new MLComWeapons(entity);
    ML_SAFE_ASSERT(weapons != NULL, "Memory Error");
    entity->AddComponent(weapons);
    weapon::MLWeapon* weapon = new weapon::MLSingleParticle();
    weapon->SetOwnner(entity);
    weapons->AddWeapon(weapon);
    weapons->SetCurWeaponType(weapon::kWeaponSingleParticle);
    ML_SAFE_DROP(weapon);
    ML_SAFE_DROP(weapons);

    // Create System
    MLSystem* system = new MLPlayerSys(entity);
    ML_SAFE_ASSERT(system != NULL, "Memory Error");
    entity->AttachSystem(system);
    ML_SAFE_DROP(system);
  }

  return entity;
}

MLEntity* MLRoundConfigImp::CreateMonster() {
  MLEntity* entity = NULL;
  return entity;
}

//------------------------------------------------------------------
// Implement MLRoundConfig
//------------------------------------------------------------------
int32_t MLRoundConfig::Init() {
  int32_t result = -1;

  MLRoundConfigImp* instance = MLRoundConfigImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Error");
  if(instance != NULL) {
    result = instance->Init();
  }

  return result;
}

void MLRoundConfig::Destroy() {

  MLRoundConfigImp* instance = MLRoundConfigImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Error");
  if(instance != NULL) {
    instance->Destroy();
    MLRoundConfigImp::DestroyInstance();
  }
}

int32_t MLRoundConfig::ConfigRound(int32_t round) {

  MLRoundConfigImp* instance = MLRoundConfigImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Error");
  if(instance != NULL) {
    instance->ConfigRound(round);
  }

  return 0;
}

} // namespace magicland