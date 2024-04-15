#include "TransformComponent.h"
using namespace VeryReal;
TransformComponent::TransformComponent() {

}

TransformComponent::~TransformComponent() {

}
bool TransformComponent::InitComponent(int a,Vector3 position, Vector3 rotation, Vector3 scale) {
	this->a = a;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	return true;
}
void TransformComponent::Translate(VeryReal::Vector3 translateposition) {
	position += translateposition;
}
void TransformComponent::Rotate(VeryReal::Vector3 rotaterotation) {
	rotation += rotaterotation;
}
void TransformComponent::Scaler(VeryReal::Vector3 scalerscale) {
	scale += scalerscale;
}

VeryReal::Vector3 VeryReal::TransformComponent::getFacingDirection() {
        // Convertir de grados a radianes
        float radY = rotation.GetY() * 3.14159f / 180.0f;

        // Direccion por defecto (mirando hacia el fondo)
        VeryReal::Vector3 direction(0, 0, -1);

        // Aplicar rotacion alrededor del eje Y
        VeryReal::Vector3 rotatedDirection(direction.GetX() * cos(radY) - direction.GetZ() * sin(radY), direction.GetY(),
                                           direction.GetX() * sin(radY) + direction.GetZ() * cos(radY));

        return rotatedDirection.Normalize();
}

