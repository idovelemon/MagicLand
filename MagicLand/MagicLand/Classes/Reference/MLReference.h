//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/11/29
// Version: 1.0
// Brief: This file will define the reference counted technology. Every class
// in MagicLand must inherit this interface to make sure the safe pointer operate.
//------------------------------------------------------------------------
#ifndef __MLREFERENCE__H_
#define __MLREFERENCE__H_

namespace MagicLand {class MLReference;};

class MagicLand::MLReference
{
public:
    MLReference();
    virtual ~MLReference();

public:
    virtual void Grab();
    virtual void Drop();

protected:
    unsigned int m_RefCounted;  // The referenced count
};

#endif