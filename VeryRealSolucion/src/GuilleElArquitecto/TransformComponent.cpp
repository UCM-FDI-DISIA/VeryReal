#include "TransformComponent.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace VeryReal;
TransformComponent::TransformComponent() {

}

TransformComponent::~TransformComponent() {

}
std::pair<bool, std::string> TransformComponent::InitComponent(Vector3 position, Vector3 rotation, Vector3 scale) {
    this->position = position;
    this->rotation = Vector4(rotation);
    this->rotationInit = rotation;
    this->scale = scale;
    return {true, "TransformComponent initialized"};
}

void TransformComponent::Translate(VeryReal::Vector3 translateposition) {
	position += translateposition;
}
void TransformComponent::Rotate(VeryReal::Vector3 rotaterotation) {
    rotation += Vector4(rotaterotation);
}
void TransformComponent::Scaler(VeryReal::Vector3 scalerscale) {
	scale += scalerscale; }

Vector3 VeryReal::TransformComponent::up() { 
	Vector3 rot = rotation.toEuler();

    Vector3 upVector;

    Vector3 vector_radians = rot;
    vector_radians.SetX(rot.GetX() * M_PI / 180.0);
    vector_radians.SetY(rot.GetY() * M_PI / 180.0);
    vector_radians.SetZ(rot.GetZ() * M_PI / 180.0);

    upVector.SetX(sin(vector_radians.GetX()));
    upVector.SetY(cos(vector_radians.GetX()) * cos(vector_radians.GetZ()));
    upVector.SetZ(cos(vector_radians.GetX()) * sin(vector_radians.GetZ()));

    return upVector;

}

VeryReal::Vector3 VeryReal::TransformComponent::getFacingDirection() {
        // Convertir de grados a radianes
        Vector3 rot = rotation.toEuler();
        float radY = rot.GetY() * 3.14159f / 180.0f;

        // Direccion por defecto (mirando hacia el fondo)
        VeryReal::Vector3 direction(0, 0, -1);

        // Aplicar rotacion alrededor del eje Y
        VeryReal::Vector3 rotatedDirection(direction.GetX() * cos(radY) - direction.GetZ() * sin(radY), 
                                           direction.GetY(),
                                           direction.GetX() * sin(radY) + direction.GetZ() * cos(radY));

        return rotatedDirection.Normalize();
}

