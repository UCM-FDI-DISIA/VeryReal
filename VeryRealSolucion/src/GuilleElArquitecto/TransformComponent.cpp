#include "TransformComponent.h"
TransformComponent::TransformComponent() {

}
TransformComponent::TransformComponent(Vector3 position, Vector3 rotation, Vector3 scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}
TransformComponent::~TransformComponent() {

}
void TransformComponent::Translate(Vector3 translateposition) {
	position += translateposition;
}
void TransformComponent::Rotate(Vector3 rotaterotation) {
	rotation += rotaterotation;
}
void TransformComponent::Scaler(Vector3 scalerscale) {
	scale += scalerscale;
}