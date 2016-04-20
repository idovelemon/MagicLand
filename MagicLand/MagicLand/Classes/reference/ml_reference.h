//------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2015/11/29
// Version: 1.0
// Brief: This file will define the reference counted technology. Every class
// in magicland must inherit this interface to make sure the safe pointer operate.
//------------------------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLREFERENCE_H_
#define ML_ENTITYCOMPONENT_MLREFERENCE_H_

#include "marco.h"

namespace magicland {

class MLReference {
public:
  MLReference();
  virtual ~MLReference();

  virtual void Grab();
  virtual void Drop();

protected:
  int m_RefCounted;  // The referenced count

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLReference);
};

}; // namespace magicland

#endif // ML_ENTITYCOMPONENT_MLREFERENCE_H_