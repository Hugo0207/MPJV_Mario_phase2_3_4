#pragma once
#include "CorpsRigide.h"
#include <array>

class Boite : public CorpsRigide
{
private:
    float width, height, depth;

public:
    Boite(float width, float height, float depth);

    void setDimensions(float width, float height, float depth);
    std::array<Vector, 8> getTransformedVertices() const;

    void calculateDerivedData() override;
};
