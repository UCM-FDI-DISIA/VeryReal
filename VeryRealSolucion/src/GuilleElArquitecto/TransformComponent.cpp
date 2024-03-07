#include "TransformComponent.h"
VeryReal::TransformComponent::TransformComponent() {

}
VeryReal::TransformComponent::TransformComponent(VeryReal::Vector3 position, VeryReal::Vector3 rotation, VeryReal::Vector3 scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}
VeryReal::TransformComponent::~TransformComponent() {

}
void VeryReal::TransformComponent::Translate(VeryReal::Vector3 translateposition) {
	position += translateposition;
}
void VeryReal::TransformComponent::Rotate(VeryReal::Vector3 rotaterotation) {
	rotation += rotaterotation;
}
void VeryReal::TransformComponent::Scaler(VeryReal::Vector3 scalerscale) {
	scale += scalerscale;
}