#pragma once
#include <array>
#include "PhysicsValues.h"

class CollisionMatrix {
public:
    static const int LAYER_COUNT = 4; // Cambia esto según la cantidad de capas que tengas

    CollisionMatrix() { }
    virtual ~CollisionMatrix(){}
     void Init();

    void SetCollision(PhysicsLayer layer1, PhysicsLayer layer2, bool collides);
    bool GetCollision(PhysicsLayer layer1, PhysicsLayer layer2) const;

private:
    std::array<std::array<bool, LAYER_COUNT>, LAYER_COUNT> matrix;
};
