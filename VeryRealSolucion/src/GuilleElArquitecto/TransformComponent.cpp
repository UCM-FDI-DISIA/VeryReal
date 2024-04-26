#include "TransformComponent.h"
#define _USE_MATH_DEFINES
#include <math.h>

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
	scale += scalerscale; }

Vector3 VeryReal::TransformComponent::up() { 
	Vector3 upVector;

	Vector3 rot_radians = rotation;

	rot_radians.SetX(rotation.GetX() * (float)M_PI / 180.0f);
    rot_radians.SetY(rotation.GetY() * (float)M_PI / 180.0f);
    rot_radians.SetZ(rotation.GetZ() * (float)M_PI / 180.0f);

	upVector.SetX(sin(rot_radians.GetX()));
    upVector.SetY(cos(rot_radians.GetX()) * cos(rot_radians.GetZ()));
    upVector.SetZ(cos(rot_radians.GetX()) * sin(rot_radians.GetZ()));

	return upVector; 

}

Vector3 VeryReal::TransformComponent::forward() { 
	Vector3 forwardVector;

	Vector3 rot_radians = rotation;

    rot_radians.SetX(rotation.GetX() * (float)M_PI / 180.0f);
    rot_radians.SetY(rotation.GetY() * (float)M_PI / 180.0f);
    rot_radians.SetZ(rotation.GetZ() * (float)M_PI / 180.0f);

    forwardVector.SetX(cos(rot_radians.GetY()));
    forwardVector.SetY(-tan(rot_radians.GetX()));
    forwardVector.SetZ(-sin(rot_radians.GetY()));

	return forwardVector; 

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

