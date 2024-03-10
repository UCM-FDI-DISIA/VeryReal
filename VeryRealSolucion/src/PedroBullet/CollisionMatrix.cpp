#include "CollisionMatrix.h"

CollisionMatrix::CollisionMatrix() {
    for (auto& row : matrix) {
        row.fill(false);
    }
}

void CollisionMatrix::SetCollision(PhysicsLayer layer1, PhysicsLayer layer2, bool collides) {
    matrix[static_cast<int>(layer1)][static_cast<int>(layer2)] = collides;
    matrix[static_cast<int>(layer2)][static_cast<int>(layer1)] = collides; // La matriz es simétrica
}

bool CollisionMatrix::GetCollision(PhysicsLayer layer1, PhysicsLayer layer2) const {
    return matrix[static_cast<int>(layer1)][static_cast<int>(layer2)];
}
