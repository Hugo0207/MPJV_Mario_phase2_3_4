#pragma once
#include "CorpsRigide.h"

class RigidBodyForceGenerator
{
public:
    virtual void updateForce(CorpsRigide* corpsRigide, float deltaTemps) = 0;
};
