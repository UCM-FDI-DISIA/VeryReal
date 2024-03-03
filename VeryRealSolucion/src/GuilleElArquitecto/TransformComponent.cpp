#include "TransformComponent.h"
VeryReal::TransformComponent::TransformComponent() {

}
VeryReal::TransformComponent::TransformComponent(Vector3 position, Vector3 rotation, Vector3 scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}
VeryReal::TransformComponent::~TransformComponent() {

}
void VeryReal::TransformComponent::Translate(Vector3 translateposition) {
	position += translateposition;
}
void VeryReal::TransformComponent::Rotate(Vector3 rotaterotation) {
	rotation += rotaterotation;
}
void VeryReal::TransformComponent::Scaler(Vector3 scalerscale) {
	scale += scalerscale;
}